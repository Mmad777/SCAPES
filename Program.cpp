
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QtCore/QDebug>

#include "Label.h"
#include "Operand.h"
#include "Program.h"
#include "statementfactory.h"


Program::Program(QObject *parent) : QObject(parent)
{
    statementFactory = new StatementFactory(this, &labelMap, &variableMap);
}

QStringList Program::readLines(const QString& fileName)
{
    QFile inputFile(fileName);
    QStringList statementList;

    // open file
    if (!inputFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open the program file: " << fileName;
        return statementList;
    }

    // read contents
    QTextStream in(&inputFile);
    while (!in.atEnd())
    {
        // read a line
        QString line = in.readLine();

        // trim the spaces
        line = line.trimmed();

        // ignore the comments
        if (line.startsWith('#'))
            continue;

        // add to statement list
        statementList.append(line);
    }

    return statementList;
}

QString Program::processLabel(int address, QString line)
{
    // tokenize
    QStringList tokens = line.split(QRegExp(":\\s+"));

    // found a label
    if (tokens.size() == 2)
    {
        QString labelName = tokens[0];
        Label *label = new Label(this, labelName, address);
        labelMap.insert(labelName, label);

        return tokens[1];
    }

    return line;
}

bool Program::compile(const QString& fileName)
{
    // clear the identifiers and statements
    labelMap.clear();
    variableMap.clear();
    statements.clear();

    // read the statement lines from the program file, remove comments
    QStringList statementLines = readLines(fileName);

    // build map for labels
    for (int i = 0; i < statementLines.size(); i++)
    {
        QString line_without_label = processLabel(i, statementLines[i]);
        statementLines[i] = line_without_label;
    }

    // compile line by line
    for (QString line : statementLines)
    {
        if (!compileLine(line)) {
            qDebug() << "Can't compile line: " << line;
            return false;
        }
    }

    // success
    return true;
}

bool Program::compileLine(const QString& line)
{
    Label* label = nullptr;

    // tokenize
    QStringList tokens = line.split(QRegExp("\\s+"));

    // check a label exist
    if (tokens.size()< 1)
        return false;
    if (tokens[0].endsWith(":"))
    {
        QString labelName = tokens.takeFirst().chopped(1);

        label = new Label(this, labelName);
    }

    // split out opcode, operands
    if (tokens.size()< 1)
        return false;
    QString opcode = tokens.takeFirst();
    QStringList operands = tokens;

    int address = statements.size();
    Statement *statement = statementFactory->getStatement(address, opcode, operands);
    if (statement == nullptr)
        return false;

    // add to statements list
    statements.append(statement);

    // save label to map
    if (label != nullptr)
    {
        label->setAddress(address);
        labelMap.insert(label->getName(), label);
    }

    // success
    return true;
}

QString Program::print()
{
    QJsonObject output;
    QJsonArray jsonVariables;
    QJsonArray jsonInstructions;

    for (QString variableName : variableMap.keys())
    {
        Variable *variable = variableMap[variableName];
        jsonVariables.append(variable->compile());
    }

    output["Variables"] = jsonVariables;

    for (Statement* statement : statements)
    {
        jsonInstructions.append(statement->compile());
    }
    output["Instructions"] = jsonInstructions;

    QJsonDocument jsonDoc(output);
    QString jsonString = jsonDoc.toJson();

    return jsonString;
}

void Program::execute()
{

}

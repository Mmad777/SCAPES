
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QtCore/QDebug>
#include "flags.h"
#include "executor.h"

Executor::Executor(QObject *parent) : QObject(parent)
{
    statementLoader = new StatementLoader(this, &variableMap);
}

bool Executor::execute(const QString &fileName)
{
    if (!readFile(fileName))
        return false;

    qDebug() << "Parsing success!";

    // reset the flags
    Flags::reset();

    // run the statements
    while (Flags::IP >= 0)
    {
        qDebug() << "Executing instruction : " << Flags::IP;

        Statement *statement = statements.at(Flags::IP);
        statement->run(&variableMap);
    }

    return true;
}

QString Executor::print()
{
    QString output;

    qDebug() << "Results: ";

    for (QString variableName : variableMap.keys())
    {
        Variable *variable = variableMap[variableName];
        QString line= QString("%1 = %2\n").arg(variableName).arg(variable->getValue());

        qDebug() << line;
        output += line;
    }

    return output;
}

bool Executor::readFile(const QString &fileName)
{
    QFile inputFile(fileName);
    QString content;

    // open file
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't open the compiled file: " << fileName;
        return false;
    }

    // read content
    content = inputFile.readAll();

    // close file
    inputFile.close();

    // reset the variables
    variableMap.clear();
    statements.clear();

    // parse content
    QJsonDocument jsonDoc = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject root = jsonDoc.object();

    // -- parse variables
    QJsonArray jsonVariables = root.value("Variables").toArray();
    for (int i = 0; i < jsonVariables.count(); i++) {
        QJsonObject item = jsonVariables.at(i).toObject();
        Variable *variable = new Variable(this);
        variable->load(item);

        variableMap.insert(variable->getName(), variable);
    }

    // -- parse instructions
    QJsonArray jsonInstructions = root.value("Instructions").toArray();
    for (int i = 0; i < jsonInstructions.count(); i++) {
        QJsonObject item = jsonInstructions.at(i).toObject();

        Statement* statement = statementLoader->loadStatement(item);

         if (statement == nullptr) {
            return false;
        }
        // append to the statements list
        statements.append(statement);
    }

    return true;
}

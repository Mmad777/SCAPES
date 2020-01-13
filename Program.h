#ifndef PROGRAM_H
#define PROGRAM_H


#include <QObject>
#include <QVector>
#include <QHash>
#include "Identifier.h"
#include "Label.h"
#include "Variable.h"
#include "Statement.h"
#include "statementfactory.h"

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    bool compile(const QString& fileName);
    QString print();

    void execute();

private:
    QHash<QString, Label*> labelMap;
    QHash<QString, Variable*> variableMap;

    StatementFactory *statementFactory;
    QList<Statement*> statements;

    // Read the program contents, split line by line and remove the comments
    QStringList readLines(const QString& fileName);

    // remove the label from the line, register the label to the map
    QString processLabel(int address, QString line);

    // Compile one line of program
    bool compileLine(const QString& line);
};

#endif // PROGRAM_H

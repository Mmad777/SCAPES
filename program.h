#ifndef PROGRAM_H
#define PROGRAM_H


#include <QObject>
#include <QVector>
#include <QHash>
#include "identifier.h"
#include "label.h"
#include "variable.h"
#include "statement.h"
#include "statementfactory.h"

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    bool compile(const QString& fileName);
    QString print();

private:
    QHash<QString, Variable*> variableMap;
    QList<Statement*> statements;

    QHash<QString, Label*> labelMap;
    StatementFactory *statementFactory;

    // Read the program contents, split line by line and remove the comments
    QStringList readLines(const QString& fileName);

    // remove the label from the line, register the label to the map
    void registerLabel(QString line);

    // Compile one line of program
    bool compileLine(const QString& line);
};

#endif // PROGRAM_H

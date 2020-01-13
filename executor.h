#ifndef EXECUTOR_H
#define EXECUTOR_H


#include <QObject>
#include <QVector>
#include <QHash>
#include "identifier.h"
#include "label.h"
#include "variable.h"
#include "statement.h"
#include "statementloader.h"

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = nullptr);
    bool execute(const QString& fileName);
    QString print();

private:
    QHash<QString, Variable*> variableMap;
    QList<Statement*> statements;

    StatementLoader *statementLoader;

    // read the compiled program, and parse the contents into member variables
    bool readFile(const QString &fileName);
};

#endif // EXECUTOR_H

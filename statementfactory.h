#ifndef STATEMENTFACTORY_H
#define STATEMENTFACTORY_H

#include <QObject>
#include <QHash>
#include "statement.h"
#include "label.h"
#include "variable.h"

class StatementFactory : public QObject
{
    Q_OBJECT
public:
    explicit StatementFactory(QObject *parent, QHash<QString, Label*>* labelMap, QHash<QString, Variable*>* variableMap);

    Statement* getStatement(int address, QString opcode, QStringList operands);

private:
    QHash<QString, Label*> *labelMap;
    QHash<QString, Variable*> *variableMap;
};

#endif // STATEMENTFACTORY_H

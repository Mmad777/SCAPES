#ifndef STATEMENT_H
#define STATEMENT_H

#include <QObject>
#include <QHash>
#include "variable.h"
#include "operand.h"

class Statement : public QObject
{
    Q_OBJECT
public:
    Statement(QObject *parent = nullptr, int address = -1, Operand* operand1 = nullptr, Operand* operand2 = nullptr);

    // deprecated
    explicit Statement(QObject *parent, const QStringList& operands);

    QJsonObject compile();

    virtual void run(QHash<QString, Variable*>* variableMap) = 0;

protected:
    // deprecated
    QStringList operands;

    QString opcode;
    int address;
    Operand* operand1;
    Operand* operand2;
};

#endif // STATEMENT_H

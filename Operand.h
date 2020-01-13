#ifndef OPERAND_H
#define OPERAND_H

#include <QObject>
#include "Identifier.h"
#include "Variable.h"
#include "Label.h"

class Operand : public QObject
{
    Q_OBJECT
public:
    Operand(QObject *parent, Variable* variable);
    Operand(QObject *parent, Label* label);
    Operand(QObject *parent, int constInt);
    Operand(QObject *parent, QString literal);

    enum OperandType { VARIABLE, LABEL, CONST_INT, LITERAL };

    OperandType getType() const;
    void setType(const OperandType &value);

    Variable *getVariable() const;
    void setVariable(Variable *value);

    Label *getLabel() const;
    void setLabel(Label *value);

    int getConstInt() const;
    void setConstInt(int value);

    QString getLiteral() const;
    void setLiteral(const QString &value);

    QJsonObject compile();

private:
    OperandType type;

    Variable* variable;
    Label* label;
    int constInt;
    QString literal;
};

#endif // OPERAND_H

#include "Operand.h"

Operand::Operand(QObject *parent, Variable *variable) : QObject (parent)
{
    this->type = VARIABLE;
    this->variable = variable;
}

Operand::Operand(QObject *parent, Label *label) : QObject (parent)
{
    this->type = LABEL;
    this->label = label;
}

Operand::Operand(QObject *parent, int constInt) : QObject (parent)
{
    this->type = CONST_INT;
    this->constInt = constInt;
}

Operand::Operand(QObject *parent, QString literal) : QObject (parent)
{
    this->type = LITERAL;
    this->literal = literal;
}

Operand::OperandType Operand::getType() const
{
    return type;
}

void Operand::setType(const OperandType &value)
{
    type = value;
}

Variable *Operand::getVariable() const
{
    return variable;
}

void Operand::setVariable(Variable *value)
{
    variable = value;
}

Label *Operand::getLabel() const
{
    return label;
}

void Operand::setLabel(Label *value)
{
    label = value;
}

int Operand::getConstInt() const
{
    return constInt;
}

void Operand::setConstInt(int value)
{
    constInt = value;
}

QString Operand::getLiteral() const
{
    return literal;
}

void Operand::setLiteral(const QString &value)
{
    literal = value;
}

QJsonObject Operand::compile()
{
    QJsonObject output;
    if (type == VARIABLE)
    {
        output["Type"] = "Variable";
        output["Variable"] = variable->compile();
    }
    else if (type == LABEL)
    {
        output["Type"] = "Address";
        output["Address"] = label->compile();
    }
    else if (type == CONST_INT)
    {
        output["Type"] = "ConstantInteger";
        output["Value"] = constInt;
    }
    else if (type == LITERAL)
    {
        output["Type"] = "Literal";
        output["Value"] = literal;
    }

    return output;
}

#include "operand.h"

Operand::Operand(QObject *parent) : QObject (parent)
{
}

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

int Operand::getAddress() const
{
    return address;
}

void Operand::setAddress(int value)
{
    address = value;
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

bool Operand::load(const QJsonObject &json, const QHash<QString, Variable *> *variableMap)
{
    QString type = json.value("Type").toString();
    if (type == "Variable")
    {
        this->type = VARIABLE;

        QString variableName = json.value("Variable").toObject().value("Name").toString();

        this->variable = variableMap->value(variableName);
    }
    else if (type == "Address")
    {
        this->type = ADDRESS;
        this->address = json.value("Address").toObject().value("Location").toInt();
    }
    else if (type == "ConstantInteger")
    {
        this->type = CONST_INT;
        this->constInt = json.value("Value").toInt();
    }
    else if (type == "Literal")
    {
        this->type = LITERAL;
        this->literal = json.value("Value").toString();
    }

    return true;
}

int Operand::getValue()
{
    int value = 0;
    if (this->type == VARIABLE)
        value = this->variable->getValue();
    else if (this->type == CONST_INT)
        value = this->constInt;

    return value;
}

void Operand::setValue(int value)
{
    if (this->type == VARIABLE)
        this->variable->setValue(value);
}

QString Operand::print()
{
    QString value;
    if (type == VARIABLE)
    {
        value = QString::number(this->variable->getValue());
    }
    else if (type == CONST_INT)
    {
        value = QString::number(this->constInt);
    }
    else if (type == LITERAL)
    {
        value = literal;
    }

    return value;
}

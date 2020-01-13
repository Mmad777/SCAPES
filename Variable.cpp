#include "Variable.h"

Variable::Variable(QObject *parent, QString name, int value) : Identifier (parent, name)
{
    this->value = value;
}

int Variable::getValue() const
{
    return value;
}

void Variable::setValue(int value)
{
    this->value = value;
}

QJsonObject Variable::compile()
{
    QJsonObject output;
    output["Type"] = "Integer";
    output["Name"] = name;

    return output;
}

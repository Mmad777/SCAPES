#include "statement.h"

Statement::Statement(QObject *parent, int address, Operand *operand1, Operand *operand2) : QObject (parent)
{
    this->address = address;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

Statement::Statement(QObject *parent, const QStringList& operands) : QObject(parent), operands(operands)
{

}

QJsonObject Statement::compile()
{
    QJsonObject output;

    output["Address"] = address;
    output["Opcode"] = opcode;
    if (operand1 != nullptr)
        output["Operand1"] = operand1->compile();
    if (operand2 != nullptr)
        output["Operand2"] = operand2->compile();

    return output;
}



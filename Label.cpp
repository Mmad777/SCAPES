#include "Label.h"

Label::Label(QObject *parent, QString name, int address) : Identifier (parent, name)
{
    this->address = address;
}


int Label::getAddress() const
{
    return address;
}

void Label::setAddress(int value)
{
    address = value;
}

QJsonObject Label::compile()
{
    QJsonObject output;
    output["Location"] = address;

    return output;
}

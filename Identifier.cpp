#include "Identifier.h"

Identifier::Identifier(QObject *parent, QString name) : QObject(parent)
{
    this->name = name;
}

QString Identifier::getName() const
{
    return name;
}

void Identifier::setName(const QString &value)
{
    name = value;
}

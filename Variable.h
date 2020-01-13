#ifndef VARIABLE_H
#define VARIABLE_H

#include "Identifier.h"

class Variable : public Identifier
{
    Q_OBJECT
public:
    explicit Variable(QObject *parent, QString name, int value = 0);

    int getValue() const;
    void setValue(int value);

    QJsonObject compile() override;

private:
    int value;
};

#endif // VARIABLE_H

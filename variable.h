#ifndef VARIABLE_H
#define VARIABLE_H

#include "identifier.h"

class Variable : public Identifier
{
    Q_OBJECT
public:
    explicit Variable(QObject *parent, QString name = "", int value = 0);

    int getValue() const;
    void setValue(int value);

    QJsonObject compile() override;
    bool load(const QJsonObject& json);

private:
    int value;
};

#endif // VARIABLE_H

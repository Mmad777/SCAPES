#ifndef LABEL_H
#define LABEL_H

#include "Identifier.h"

class Label : public Identifier
{
    Q_OBJECT
public:
    explicit Label(QObject *parent, QString name, int address = 0);

    int getAddress() const;
    void setAddress(int value);

    QJsonObject compile() override;

private:
    int address;
};

#endif // LABEL_H

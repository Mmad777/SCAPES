#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QJsonObject>
#include <QObject>

class Identifier : public QObject
{
    Q_OBJECT
public:
    explicit Identifier(QObject *parent, QString name);

    QString getName() const;
    void setName(const QString &value);

    virtual QJsonObject compile() = 0;

protected:
    QString name;
};

#endif // IDENTIFIER_H

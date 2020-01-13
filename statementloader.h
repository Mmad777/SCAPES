#ifndef STATEMENTLOADER_H
#define STATEMENTLOADER_H

#include <QObject>
#include <QHash>
#include "statement.h"
#include "variable.h"

class StatementLoader : public QObject
{
    Q_OBJECT
public:
    explicit StatementLoader(QObject *parent, QHash<QString, Variable*> *variableMap);

    Statement* loadStatement(const QJsonObject& json);

private:
    QHash<QString, Variable*> *variableMap;
};

#endif // STATEMENTLOADER_H

#ifndef OPERAND_H
#define OPERAND_H

#include <QObject>
#include <QHash>
#include "identifier.h"
#include "variable.h"
#include "label.h"

class Operand : public QObject
{
    Q_OBJECT
public:
    Operand(QObject *parent);
    Operand(QObject *parent, Variable* variable);
    Operand(QObject *parent, Label* label);
    Operand(QObject *parent, int constInt);
    Operand(QObject *parent, QString literal);

    enum OperandType { VARIABLE, LABEL, CONST_INT, LITERAL, ADDRESS };

    OperandType getType() const;
    void setType(const OperandType &value);

    Variable *getVariable() const;
    void setVariable(Variable *value);

    Label *getLabel() const;
    void setLabel(Label *value);

    int getConstInt() const;
    void setConstInt(int value);

    QString getLiteral() const;
    void setLiteral(const QString &value);

    QJsonObject compile();

    bool load(const QJsonObject& json, QHash<QString, Variable*> const *variableMap);

    int getAddress() const;
    void setAddress(int value);

    // universal functions
    int getValue();
    void setValue(int value);
    QString print();

private:
    OperandType type;

    Variable* variable;
    Label* label;
    int constInt;
    QString literal;
    int address;
};

#endif // OPERAND_H

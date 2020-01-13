
#include "statements/addstmt.h"
#include "statements/compstmt.h"
#include "statements/declarrstmt.h"
#include "statements/declintstmt.h"
#include "statements/endstmt.h"
#include "statements/jeqstmt.h"
#include "statements/jlessstmt.h"
#include "statements/jmorestmt.h"
#include "statements/jumpstmt.h"
#include "statements/movstmt.h"
#include "statements/printstmt.h"
#include "statements/readstmt.h"
#include "statementfactory.h"

#include <QRegExp>

bool isNumber(QString str)
{
    QRegExp re("\\d*");
    if (re.exactMatch(str))
       return true;

    return false;
}

StatementFactory::StatementFactory(QObject *parent, QHash<QString, Label*>* labelMap, QHash<QString, Variable*>* variableMap) : QObject(parent)
{
    this->labelMap = labelMap;
    this->variableMap = variableMap;
}

Statement* StatementFactory::getStatement(int address, QString opcode, QStringList operands)
{
    QObject *parent = this->parent();
    int operandCount = operands.size();

    Statement* statement = nullptr;
    if (opcode == "dci" && operandCount == 1)
    {
        Variable *variable1 = new Variable(parent, operands[0]);
        variableMap->insert(operands[0], variable1);

        Operand *operand1 = new Operand(parent, variable1);
        statement = new DeclIntStmt(parent, address, operand1);
    }
    else if (opcode == "dca" && operandCount == 2)
    {
        Variable *variable1 = new Variable(parent, operands[0]);
        variableMap->insert(operands[0], variable1);

        Operand *operand1 = new Operand(parent, variable1);

        int arraySize = operands[1].toInt();
        Operand *operand2 = new Operand(parent, arraySize);

        statement = new DeclArrStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "rdi" && operandCount == 1)
    {
        Variable *variable1 = variableMap->value(operands[0]);
        if (variable1 == nullptr)
            return nullptr;

        Operand *operand1 = new Operand(parent, variable1);
        statement = new ReadStmt(parent, address, operand1);
    }
    else if ((opcode == "prt" || opcode == "print") && operandCount == 1)
    {
        Variable *variable1 = variableMap->value(operands[0]);
        if (variable1 == nullptr)
            return nullptr;

        Operand *operand1 = new Operand(parent, variable1);
        statement = new PrintStmt(parent, address, operand1);
    }
    else if (opcode == "mov" && operandCount == 2)
    {
        Operand *operand1;
        QString operand1_str = operands[0];
        if (isNumber(operand1_str))
        {
            operand1 = new Operand(parent, operand1_str.toInt());
        }
        else
        {
            Variable *variable = variableMap->value(operand1_str);
            if (variable == nullptr)
                return nullptr;
            operand1 = new Operand(parent, variable);
        }

        Operand *operand2;
        QString operand2_str = operands[1];
        if (isNumber(operand2_str))
        {
            operand2 = new Operand(parent, operand2_str.toInt());
        }
        else
        {
            Variable *variable = variableMap->value(operand2_str);
            if (variable == nullptr)
                return nullptr;
            operand2 = new Operand(parent, variable);
        }

        statement = new MovStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "add" && operandCount == 2)
    {
        Operand *operand1;
        QString operand1_str = operands[0];
        if (isNumber(operand1_str))
        {
            operand1 = new Operand(parent, operand1_str.toInt());
        }
        else
        {
            Variable *variable = variableMap->value(operand1_str);
            if (variable == nullptr)
                return nullptr;
            operand1 = new Operand(parent, variable);
        }

        Operand *operand2;
        QString operand2_str = operands[1];
        if (isNumber(operand2_str))
        {
            operand2 = new Operand(parent, operand2_str.toInt());
        }
        else
        {
            Variable *variable = variableMap->value(operand2_str);
            if (variable == nullptr)
                return nullptr;
            operand2 = new Operand(parent, variable);
        }

        statement = new AddStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "cmp" && operandCount == 2)
    {
        Operand *operand1;
        QString operand1_str = operands[0];
        if (isNumber(operand1_str))
        {
            operand1 = new Operand(parent, operand1_str.toInt());
        }
        else
        {
            Variable *variable = variableMap->value(operand1_str);
            if (variable == nullptr)
                return nullptr;
            operand1 = new Operand(parent, variable);
        }

        Operand *operand2;
        QString operand2_str = operands[1];
        if (isNumber(operand2_str))
        {
            operand2 = new Operand(parent, operand2_str.toInt());
        }
        else
        {
            Variable *variable = variableMap->value(operand2_str);
            if (variable == nullptr)
                return nullptr;
            operand2 = new Operand(parent, variable);
        }

        statement = new CompStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "jls" && operandCount == 1)
    {
        Label *label1 = labelMap->value(operands[0]);
        if (label1 == nullptr)
            return nullptr;

        Operand *operand1 = new Operand(parent, label1);
        statement = new JLessStmt(parent, address, operand1);
    }
    else if (opcode == "jmr" && operandCount == 1)
    {
        Label *label1 = labelMap->value(operands[0]);
        if (label1 == nullptr)
            return nullptr;

        Operand *operand1 = new Operand(parent, label1);
        statement = new JMoreStmt(parent, address, operand1);
    }
    else if (opcode == "jeq" && operandCount == 1)
    {
        Label *label1 = labelMap->value(operands[0]);
        if (label1 == nullptr)
            return nullptr;

        Operand *operand1 = new Operand(parent, label1);
        statement = new JEqStmt(parent, address, operand1);
    }
    else if (opcode == "jmp" && operandCount == 1)
    {
        Label *label1 = labelMap->value(operands[0]);
        if (label1 == nullptr)
            return nullptr;

        Operand *operand1 = new Operand(parent, label1);
        statement = new JumpStmt(parent, address, operand1);
    }
    else if (opcode == "end" && operandCount == 0)
    {
        statement = new EndStmt(parent, address);
    }

    return statement;
}


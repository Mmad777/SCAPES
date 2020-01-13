
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

#include "statementloader.h"

StatementLoader::StatementLoader(QObject *parent, QHash<QString, Variable *> *variableMap) : QObject(parent)
{
    this->variableMap = variableMap;
}

Statement *StatementLoader::loadStatement(const QJsonObject &json)
{
    QObject *parent = this->parent();

    // parse the operands
    int address;
    QString opcode;

    address = json.value("Address").toInt();
    opcode = json.value("Opcode").toString();

    QJsonObject operand1_obj = json.value("Operand1").toObject();
    QJsonObject operand2_obj = json.value("Operand2").toObject();

    Operand *operand1 = nullptr;
    Operand *operand2 = nullptr;

    if (!operand1_obj.isEmpty()) {
        operand1 = new Operand(parent);
        operand1->load(operand1_obj, variableMap);
    }

    if (!operand2_obj.isEmpty()) {
        operand2 = new Operand(parent);
        operand2->load(operand2_obj, variableMap);
    }

    // create the statement
    Statement *statement = nullptr;

    if (opcode == "DeclareIntegerVariable")
    {
        statement = new DeclIntStmt(parent, address, operand1);
    }
    else if (opcode == "DeclareArray")
    {
        statement = new DeclArrStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "ReadInteger")
    {
        statement = new ReadStmt(parent, address, operand1);
    }
    else if (opcode == "PrintValue")
    {
        statement = new PrintStmt(parent, address, operand1);
    }
    else if (opcode == "MoveVariable")
    {
        statement = new MovStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "AddValues")
    {
        statement = new AddStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "CompareValues")
    {
        statement = new CompStmt(parent, address, operand1, operand2);
    }
    else if (opcode == "JumpIfLess")
    {
        statement = new JLessStmt(parent, address, operand1);
    }
    else if (opcode == "JumpIfMore")
    {
        statement = new JMoreStmt(parent, address, operand1);
    }
    else if (opcode == "JumpIfEqual")
    {
        statement = new JEqStmt(parent, address, operand1);
    }
    else if (opcode == "JumpUnconditionally")
    {
        statement = new JumpStmt(parent, address, operand1);
    }
    else if (opcode == "EndOfProgram")
    {
        statement = new EndStmt(parent, address);
    }

    return statement;
}

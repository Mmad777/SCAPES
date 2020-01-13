#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterDialog::signup);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::signup()
{
    accept();
}

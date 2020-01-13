#include "logindialog.h"
#include "ui_logindialog.h"
#include "settingsdialog.h"

#include <QSettings>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::signin);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::signin()
{
    QSettings settings(SettingsDialog::m_sSettingsFile, QSettings::IniFormat);

    if (ui->txtUsername->text() == "programmer" && ui->txtPassword->text() == "1234") {
        settings.setValue("User", "programmer");
        settings.sync();

        QString ab = SettingsDialog::m_sSettingsFile;
        QString user = settings.value("User").toString();
        accept();
    }

    if (ui->txtUsername->text() == "administrator" && ui->txtPassword->text() == "5678") {
        settings.setValue("User", "administrator");
        settings.sync();
        accept();
    }
}

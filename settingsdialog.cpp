#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>
#include <QSettings>

QString SettingsDialog::m_sSettingsFile = "settings.ini";

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::onAccepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::onRejected);
    connect(ui->btnDirectory, &QPushButton::clicked, this, &SettingsDialog::onDirectory);

    loadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::onAccepted()
{
    saveSettings();
    accept();
}

void SettingsDialog::onRejected()
{
    reject();
}

void SettingsDialog::onDirectory()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "Output directory");
    ui->txtDirectory->setText(fileName);
}

void SettingsDialog::loadSettings()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    ui->cmbLanguage->setCurrentText(settings.value("Programming language", "").toString());
    ui->txtDirectory->setText(settings.value("Output directory", "").toString());
    QString sText = settings.value("text", "").toString();
}

void SettingsDialog::saveSettings()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    settings.setValue("Programming language", ui->cmbLanguage->currentText());
    settings.setValue("Output directory", ui->txtDirectory->text());
}

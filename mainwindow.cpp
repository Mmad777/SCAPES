#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QtCore/QDebug>
#include <QFile>
#include <QSettings>
#include "program.h"
#include "executor.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateUIForUnauthorized();

    dlgLogin = new LoginDialog;
    dlgRegister = new RegisterDialog;
    dlgSettings = new SettingsDialog;

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);
    connect(ui->actionBuild, &QAction::triggered, this, &MainWindow::build);
    connect(ui->actionRun, &QAction::triggered, this, &MainWindow::run);
    connect(ui->actionPreference, &QAction::triggered, this, &MainWindow::preference);
    connect(ui->actionSign_in, &QAction::triggered, this, &MainWindow::signin);
    connect(ui->actionRegister, &QAction::triggered, this, &MainWindow::signup);
    connect(dlgLogin, &LoginDialog::accepted, this, &MainWindow::signinAccepted);
    connect(dlgRegister, &RegisterDialog::accepted, this, &MainWindow::signupAccepted);
    connect(dlgSettings, &SettingsDialog::accepted, this, &MainWindow::preferenceAccepted);

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif

    dlgLogin->setModal(true);
    dlgLogin->show();

    // for test login
//    signinAccepted();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newDocument()
{
    currentFile.clear();
    ui->txtSourceCode->setText("");
    ui->txtCompiled->setText("");
    ui->txtResult->setText("");

    // disable run
    ui->actionRun->setEnabled(false);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->txtSourceCode->setText(text);
    file.close();

    ui->txtCompiled->setText("");
    ui->txtResult->setText("");

    // disable run
    ui->actionRun->setEnabled(false);
}

void MainWindow::save()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->txtSourceCode->toPlainText();
    out << text;
    file.close();
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->txtSourceCode->toPlainText();
    out << text;
    file.close();
}

void MainWindow::exit()
{
    QCoreApplication::quit();
}

void MainWindow::build()
{
    save();
    if (currentFile.isEmpty())
    {
        return;
    }

    // compile the program
    Program program;
    program.compile(currentFile);

    QString compiledOutput = program.print();

    // get output file path
    QSettings settings(SettingsDialog::m_sSettingsFile, QSettings::NativeFormat);

    // write to file
    QString outputDirectory = settings.value("Output directory", "").toString();
    QString outputFile = outputDirectory.isEmpty()?
                "compiled.json" : QDir::cleanPath(outputDirectory + QDir::separator() + "compiled.json");

    QFile saveFile(outputFile);
    if(!saveFile.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "Warning", "Output directory is not valid");
        return;
    }

    saveFile.write(compiledOutput.toLocal8Bit());
    saveFile.close();

    // show to UI
    ui->txtCompiled->setText(compiledOutput);

    // enable run
    ui->actionRun->setEnabled(true);
}

void MainWindow::run()
{
    QString result;

    // run the compiled file
    Executor executor;
    if (!executor.execute("compiled.json"))
    {
        result = "Failed to run the compiled file.";
    }

    // print the result of the execution
    result = executor.print();

    // display to UI
    ui->txtResult->setText(result);
}

void MainWindow::preference()
{
    dlgSettings->setModal(true);
    dlgSettings->show();
}

void MainWindow::signin()
{
   dlgLogin->setModal(true);
   dlgLogin->show();
}

void MainWindow::signup()
{
    dlgRegister->setModal(true);
    dlgRegister->show();
}

void MainWindow::preferenceAccepted()
{

}

void MainWindow::signinAccepted()
{
    QSettings settings(SettingsDialog::m_sSettingsFile, QSettings::IniFormat);
    QString user = settings.value("User", "").toString();

    if (user == "programmer") {
        updateUIForDeveloper();
    } else if (user == "administrator") {
        updateUIForAdministrator();
    }
}

void MainWindow::signupAccepted()
{

}

void MainWindow::updateUIForUnauthorized()
{
    ui->actionNew->setEnabled(false);
    ui->actionOpen->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionBuild->setEnabled(false);
//    ui->actionRun->setEnabled(false);
    ui->actionPreference->setEnabled(false);
    ui->actionSign_in->setEnabled(true);
    ui->actionRegister->setEnabled(true);
    ui->txtSourceCode->setEnabled(false);
}

void MainWindow::updateUIForDeveloper()
{
    ui->actionNew->setEnabled(true);
    ui->actionOpen->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
    ui->actionExit->setEnabled(true);
    ui->actionBuild->setEnabled(true);
//    ui->actionRun->setEnabled(true);
    ui->actionPreference->setEnabled(false);
    ui->actionSign_in->setEnabled(true);
    ui->actionRegister->setEnabled(true);
    ui->txtSourceCode->setEnabled(true);
}

void MainWindow::updateUIForAdministrator()
{
    ui->actionNew->setEnabled(true);
    ui->actionOpen->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
    ui->actionExit->setEnabled(true);
    ui->actionBuild->setEnabled(true);
//    ui->actionRun->setEnabled(true);
    ui->actionPreference->setEnabled(true);
    ui->actionSign_in->setEnabled(true);
    ui->actionRegister->setEnabled(true);
    ui->txtSourceCode->setEnabled(true);
}

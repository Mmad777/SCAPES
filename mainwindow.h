#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "registerdialog.h"
#include "settingsdialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newDocument();

    void open();

    void save();

    void saveAs();

    void exit();

    void build();

    void run();

    void preference();

    void signin();

    void signup();

    void preferenceAccepted();

    void signinAccepted();

    void signupAccepted();

private:
    void updateUIForUnauthorized();

    void updateUIForDeveloper();

    void updateUIForAdministrator();

private:
    Ui::MainWindow *ui;
    QString currentFile;

private:
    LoginDialog *dlgLogin;
    RegisterDialog *dlgRegister;
    SettingsDialog *dlgSettings;
};
#endif // MAINWINDOW_H

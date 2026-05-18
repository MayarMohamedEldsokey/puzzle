#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "auth/auth_manager.h"
#include "ui/login_screen.h"
#include "ui/registration_screen.h"
#include "ui/homepage.h"

class QQmlApplicationEngine;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(AuthManager* authManager = nullptr, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onSwitchToRegistration();
    void onSwitchToLogin();
    void onLoginSuccess();
    void onRegistrationSuccess();
    void onStartGame();
    void onViewResults();
    void onQmlWindowVisibleChanged(bool visible);

private:
    void setupUI();
    void loadSupabaseConfig();
    void navigateToRegistration();
    void navigateToLogin();

    // Widgets
    QStackedWidget* m_stackedWidget;
    LoginScreen* m_loginScreen;
    RegistrationScreen* m_registrationScreen;
    Homepage* m_homepage;

    // Auth manager
    AuthManager* m_authManager;

    // QML Engine for Dashboard
    QQmlApplicationEngine* m_qmlEngine;
};

#endif // MAINWINDOW_H

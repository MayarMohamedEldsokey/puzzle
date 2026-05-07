#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include "../auth/auth_manager.h"
#include "../auth/validators.h"

class LoginScreen : public QWidget {
    Q_OBJECT

public:
    explicit LoginScreen(AuthManager* authManager, QWidget* parent = nullptr);
    ~LoginScreen();

    void resetForm();

signals:
    void switchToRegistration();

private slots:
    void onLoginButtonClicked();
    void onForgotPasswordClicked();
    void onExitButtonClicked();
    void onLoginSuccess();
    void onLoginFailed(const QString& errorMessage);
    void onEmailTextChanged(const QString& text);
    void onPasswordTextChanged(const QString& text);

private:
    void setupUI();
    void connectSignals();
    void showErrorMessage(const QString& title, const QString& message);
    void clearErrorMessage();
    void setLoginButtonEnabled(bool enabled);

    // UI Components
    QLineEdit* m_emailInput;
    QLineEdit* m_passwordInput;
    QPushButton* m_loginButton;
    QPushButton* m_exitButton;
    QPushButton* m_forgotPasswordButton;
    QLabel* m_errorMessageLabel;
    QLabel* m_titleLabel;
    QLabel* m_subtitleLabel;
    QLabel* m_loadingLabel; // For loading indicator

    // Auth manager
    AuthManager* m_authManager;

    // Validators
    Validators m_validators;

    // UI State
    bool m_isLoading;
};

#endif // LOGIN_SCREEN_H

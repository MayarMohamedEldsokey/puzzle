#ifndef REGISTRATION_SCREEN_H
#define REGISTRATION_SCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include "../auth/auth_manager.h"
#include "../auth/validators.h"

class RegistrationScreen : public QWidget {
    Q_OBJECT

public:
    explicit RegistrationScreen(AuthManager* authManager, QWidget* parent = nullptr);
    ~RegistrationScreen();

    void resetForm();

signals:
    void switchToLogin();

private slots:
    void onSignUpButtonClicked();
    void onBackToLoginClicked();
    void onRegistrationSuccess();
    void onRegistrationFailed(const QString& errorMessage);
    void onEmailTextChanged(const QString& text);
    void onUsernameTextChanged(const QString& text);
    void onPasswordTextChanged(const QString& text);
    void onConfirmPasswordTextChanged(const QString& text);

private:
    void setupUI();
    void connectSignals();
    void showErrorMessage(const QString& title, const QString& message);
    void clearErrorMessage();
    void setSignUpButtonEnabled(bool enabled);
    void updatePasswordStrengthIndicator(const QString& password);
    bool validateAllFields();

    // UI Components
    QLineEdit* m_emailInput;
    QLineEdit* m_usernameInput;
    QLineEdit* m_passwordInput;
    QLineEdit* m_confirmPasswordInput;
    QPushButton* m_signUpButton;
    QPushButton* m_backToLoginButton;
    QLabel* m_errorMessageLabel;
    QLabel* m_titleLabel;
    QLabel* m_subtitleLabel;
    QLabel* m_passwordStrengthLabel;
    QProgressBar* m_passwordStrengthBar;

    // Auth manager
    AuthManager* m_authManager;

    // Validators
    Validators m_validators;

    // UI State
    bool m_isLoading;
};

#endif // REGISTRATION_SCREEN_H

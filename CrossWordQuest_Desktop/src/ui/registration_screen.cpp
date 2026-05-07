#include "registration_screen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

RegistrationScreen::RegistrationScreen(AuthManager* authManager, QWidget* parent)
    : QWidget(parent), m_authManager(authManager), m_isLoading(false)
{
    setupUI();
    connectSignals();
    resetForm();
}

RegistrationScreen::~RegistrationScreen()
{
}

void RegistrationScreen::setupUI()
{
    // Main container layout
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Left pane - Branding
    QWidget* leftPane = new QWidget();
    leftPane->setStyleSheet(
        "QWidget { background-color: #f1f5f9; }"
    );
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPane);
    leftLayout->setContentsMargins(48, 48, 48, 48);
    leftLayout->setSpacing(24);

    // Brand header
    QHBoxLayout* brandLayout = new QHBoxLayout();
    QLabel* brandIcon = new QLabel();
    brandIcon->setStyleSheet(
        "QLabel {"
        "  background-color: #2a4365;"
        "  color: white;"
        "  border-radius: 8px;"
        "  min-width: 40px;"
        "  min-height: 40px;"
        "  padding: 8px;"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "}"
    );
    brandIcon->setText("⊞");
    brandIcon->setAlignment(Qt::AlignCenter);

    QLabel* brandName = new QLabel("CrossWord Quest");
    brandName->setStyleSheet(
        "QLabel {"
        "  font-size: 16px;"
        "  font-weight: 700;"
        "  color: #2a4365;"
        "}"
    );
    brandLayout->addWidget(brandIcon);
    brandLayout->addWidget(brandName);
    brandLayout->addStretch();

    // Main title
    QLabel* titleLabel = new QLabel("Challenge your mind\nwith crossword\npuzzles");
    titleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 32px;"
        "  font-weight: 800;"
        "  color: #334155;"
        "  line-height: 1.5;"
        "}"
    );
    titleLabel->setWordWrap(true);

    // Subtitle
    QLabel* subtitleLabel = new QLabel(
        "Unlock your vocabulary potential. Join thousands of grandmasters "
        "in the ultimate daily intellectual adventure."
    );
    subtitleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 13px;"
        "  color: #64748b;"
        "  line-height: 1.5;"
        "}"
    );
    subtitleLabel->setWordWrap(true);
    subtitleLabel->setMaximumWidth(320);

    // Puzzle graphic placeholder
    QLabel* puzzleGraphic = new QLabel();
    puzzleGraphic->setMinimumHeight(200);
    puzzleGraphic->setAlignment(Qt::AlignCenter);
    puzzleGraphic->setStyleSheet(
        "QLabel {"
        "  border: 1px solid #e2e8f0;"
        "  border-radius: 16px;"
        "  background-color: white;"
        "}"
    );

    // Footer info
    QHBoxLayout* footerLayout = new QHBoxLayout();
    QLabel* versionLabel = new QLabel("Version 2.4.0");
    QLabel* choiceLabel = new QLabel("Editor's Choice 2024");
    versionLabel->setStyleSheet("color: #94a3b8; font-size: 11px;");
    choiceLabel->setStyleSheet("color: #94a3b8; font-size: 11px;");
    footerLayout->addWidget(versionLabel);
    footerLayout->addSpacing(4);
    footerLayout->addWidget(choiceLabel);
    footerLayout->addStretch();

    leftLayout->addLayout(brandLayout);
    leftLayout->addWidget(titleLabel);
    leftLayout->addWidget(subtitleLabel);
    leftLayout->addWidget(puzzleGraphic);
    leftLayout->addStretch();
    leftLayout->addLayout(footerLayout);

    // Right pane - Registration form
    QWidget* rightPane = new QWidget();
    rightPane->setStyleSheet("QWidget { background-color: white; }");
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(48, 48, 48, 48);
    rightLayout->setSpacing(24);

    // Form container
    QWidget* formContainer = new QWidget();
    QVBoxLayout* formLayout = new QVBoxLayout(formContainer);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setSpacing(16);

    // Title
    m_titleLabel = new QLabel("Create Your Account");
    m_titleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 24px;"
        "  font-weight: 700;"
        "  color: #1e293b;"
        "}"
    );

    // Subtitle
    m_subtitleLabel = new QLabel("Join the ultimate intellectual adventure.");
    m_subtitleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  color: #64748b;"
        "}"
    );

    // Email field
    QLabel* emailLabel = new QLabel("Email Address");
    emailLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "  color: #475569;"
        "}"
    );
    m_emailInput = new QLineEdit();
    m_emailInput->setPlaceholderText("Enter your email");
    m_emailInput->setStyleSheet(
        "QLineEdit {"
        "  border: none;"
        "  background-color: #f1f5f9;"
        "  border-radius: 10px;"
        "  padding: 10px 12px;"
        "  font-size: 12px;"
        "  color: #1e293b;"
        "}"
        "QLineEdit:focus {"
        "  background-color: white;"
        "  border: 2px solid #3b5998;"
        "  padding: 9px 11px;"
        "}"
    );
    m_emailInput->setMinimumHeight(40);

    // Username field
    QLabel* usernameLabel = new QLabel("Username");
    usernameLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "  color: #475569;"
        "}"
    );
    m_usernameInput = new QLineEdit();
    m_usernameInput->setPlaceholderText("Choose a username");
    m_usernameInput->setStyleSheet(
        "QLineEdit {"
        "  border: none;"
        "  background-color: #f1f5f9;"
        "  border-radius: 10px;"
        "  padding: 10px 12px;"
        "  font-size: 12px;"
        "  color: #1e293b;"
        "}"
        "QLineEdit:focus {"
        "  background-color: white;"
        "  border: 2px solid #3b5998;"
        "  padding: 9px 11px;"
        "}"
    );
    m_usernameInput->setMinimumHeight(40);

    // Password field
    QLabel* passwordLabel = new QLabel("Password");
    passwordLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "  color: #475569;"
        "}"
    );
    m_passwordInput = new QLineEdit();
    m_passwordInput->setPlaceholderText("••••••••");
    m_passwordInput->setEchoMode(QLineEdit::Password);
    m_passwordInput->setStyleSheet(
        "QLineEdit {"
        "  border: none;"
        "  background-color: #f1f5f9;"
        "  border-radius: 10px;"
        "  padding: 10px 12px;"
        "  font-size: 12px;"
        "  color: #1e293b;"
        "}"
        "QLineEdit:focus {"
        "  background-color: white;"
        "  border: 2px solid #3b5998;"
        "  padding: 9px 11px;"
        "}"
    );
    m_passwordInput->setMinimumHeight(40);

    // Password strength indicator
    m_passwordStrengthLabel = new QLabel("Password strength: None");
    m_passwordStrengthLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 10px;"
        "  color: #64748b;"
        "}"
    );
    m_passwordStrengthBar = new QProgressBar();
    m_passwordStrengthBar->setMaximumHeight(4);
    m_passwordStrengthBar->setStyleSheet(
        "QProgressBar {"
        "  border: none;"
        "  background-color: #e2e8f0;"
        "  border-radius: 2px;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: #dc2626;"
        "  border-radius: 2px;"
        "}"
    );
    m_passwordStrengthBar->setValue(0);

    // Confirm password field
    QLabel* confirmPasswordLabel = new QLabel("Confirm Password");
    confirmPasswordLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "  color: #475569;"
        "}"
    );
    m_confirmPasswordInput = new QLineEdit();
    m_confirmPasswordInput->setPlaceholderText("••••••••");
    m_confirmPasswordInput->setEchoMode(QLineEdit::Password);
    m_confirmPasswordInput->setStyleSheet(
        "QLineEdit {"
        "  border: none;"
        "  background-color: #f1f5f9;"
        "  border-radius: 10px;"
        "  padding: 10px 12px;"
        "  font-size: 12px;"
        "  color: #1e293b;"
        "}"
        "QLineEdit:focus {"
        "  background-color: white;"
        "  border: 2px solid #3b5998;"
        "  padding: 9px 11px;"
        "}"
    );
    m_confirmPasswordInput->setMinimumHeight(40);

    // Error message label
    m_errorMessageLabel = new QLabel();
    m_errorMessageLabel->setStyleSheet(
        "QLabel {"
        "  color: #dc2626;"
        "  font-size: 11px;"
        "  padding: 8px;"
        "  background-color: #fee2e2;"
        "  border-radius: 6px;"
        "}"
    );
    m_errorMessageLabel->setWordWrap(true);
    m_errorMessageLabel->hide();

    // Buttons
    m_signUpButton = new QPushButton("Sign Up");
    m_signUpButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #3b5998;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 12px 16px;"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "}"
        "QPushButton:hover { background-color: #2a4365; }"
        "QPushButton:pressed { background-color: #1a2c45; }"
        "QPushButton:disabled {"
        "  background-color: #cbd5e1;"
        "  color: #94a3b8;"
        "}"
    );
    m_signUpButton->setMinimumHeight(40);

    m_backToLoginButton = new QPushButton("Back to Login");
    m_backToLoginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #f1f5f9;"
        "  color: #475569;"
        "  border: 1px solid #e2e8f0;"
        "  border-radius: 10px;"
        "  padding: 12px 16px;"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "}"
        "QPushButton:hover { background-color: #e2e8f0; }"
        "QPushButton:pressed { background-color: #cbd5e1; }"
    );
    m_backToLoginButton->setMinimumHeight(40);

    // Social buttons
    QHBoxLayout* socialLayout = new QHBoxLayout();
    QLabel* socialLabel = new QLabel("Or sign up with");
    socialLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 10px;"
        "  color: #94a3b8;"
        "  font-weight: 600;"
        "  text-transform: uppercase;"
        "}"
    );
    QPushButton* facebookButton = new QPushButton("f");
    QPushButton* googleButton = new QPushButton("⊕");
    facebookButton->setStyleSheet(
        "QPushButton {"
        "  background-color: white;"
        "  color: #475569;"
        "  border: 1px solid #e2e8f0;"
        "  border-radius: 20px;"
        "  min-width: 40px;"
        "  min-height: 40px;"
        "}"
        "QPushButton:hover { background-color: #f8fafc; }"
    );
    googleButton->setStyleSheet(
        "QPushButton {"
        "  background-color: white;"
        "  color: #475569;"
        "  border: 1px solid #e2e8f0;"
        "  border-radius: 20px;"
        "  min-width: 40px;"
        "  min-height: 40px;"
        "}"
        "QPushButton:hover { background-color: #f8fafc; }"
    );
    socialLayout->addStretch();
    socialLayout->addWidget(socialLabel);
    socialLayout->addStretch();
    socialLayout->addWidget(facebookButton);
    socialLayout->addWidget(googleButton);
    socialLayout->addStretch();

    // Add to form layout
    formLayout->addWidget(m_titleLabel);
    formLayout->addWidget(m_subtitleLabel);
    formLayout->addSpacing(10);
    formLayout->addWidget(emailLabel);
    formLayout->addWidget(m_emailInput);
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(m_usernameInput);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(m_passwordInput);
    formLayout->addWidget(m_passwordStrengthLabel);
    formLayout->addWidget(m_passwordStrengthBar);
    formLayout->addWidget(confirmPasswordLabel);
    formLayout->addWidget(m_confirmPasswordInput);
    formLayout->addWidget(m_errorMessageLabel);
    formLayout->addWidget(m_signUpButton);
    formLayout->addWidget(m_backToLoginButton);
    formLayout->addLayout(socialLayout);

    rightLayout->addWidget(formContainer);
    rightLayout->addStretch();

    mainLayout->addWidget(leftPane, 1);
    mainLayout->addWidget(rightPane, 1);

    setLayout(mainLayout);
    setWindowTitle("CrossWord Quest - Register");
    resize(1000, 700);
}

void RegistrationScreen::connectSignals()
{
    connect(m_signUpButton, &QPushButton::clicked, this, &RegistrationScreen::onSignUpButtonClicked);
    connect(m_backToLoginButton, &QPushButton::clicked, this, &RegistrationScreen::onBackToLoginClicked);

    connect(m_authManager, &AuthManager::registrationSuccess, this, &RegistrationScreen::onRegistrationSuccess);
    connect(m_authManager, &AuthManager::registrationFailed, this, &RegistrationScreen::onRegistrationFailed);

    connect(m_emailInput, &QLineEdit::textChanged, this, &RegistrationScreen::onEmailTextChanged);
    connect(m_usernameInput, &QLineEdit::textChanged, this, &RegistrationScreen::onUsernameTextChanged);
    connect(m_passwordInput, &QLineEdit::textChanged, this, &RegistrationScreen::onPasswordTextChanged);
    connect(m_confirmPasswordInput, &QLineEdit::textChanged, this, &RegistrationScreen::onConfirmPasswordTextChanged);
}

void RegistrationScreen::onSignUpButtonClicked()
{
    clearErrorMessage();

    if (!validateAllFields()) {
        return;
    }

    QString email = m_emailInput->text().trimmed();
    QString username = m_usernameInput->text().trimmed();
    QString password = m_passwordInput->text();

    // Attempt registration
    setSignUpButtonEnabled(false);
    m_isLoading = true;
    m_authManager->registerUser(email, password, username);
}

void RegistrationScreen::onBackToLoginClicked()
{
    emit switchToLogin();
}

void RegistrationScreen::onRegistrationSuccess()
{
    setSignUpButtonEnabled(true);
    m_isLoading = false;
    resetForm();
    // TODO: Navigate to dashboard or show success message
}

void RegistrationScreen::onRegistrationFailed(const QString& errorMessage)
{
    setSignUpButtonEnabled(true);
    m_isLoading = false;
    showErrorMessage("Registration Failed", errorMessage);
}

void RegistrationScreen::onEmailTextChanged(const QString& text)
{
    clearErrorMessage();
}

void RegistrationScreen::onUsernameTextChanged(const QString& text)
{
    clearErrorMessage();
}

void RegistrationScreen::onPasswordTextChanged(const QString& text)
{
    clearErrorMessage();
    updatePasswordStrengthIndicator(text);
}

void RegistrationScreen::onConfirmPasswordTextChanged(const QString& text)
{
    clearErrorMessage();
}

void RegistrationScreen::resetForm()
{
    m_emailInput->clear();
    m_usernameInput->clear();
    m_passwordInput->clear();
    m_confirmPasswordInput->clear();
    clearErrorMessage();
    updatePasswordStrengthIndicator("");
    setSignUpButtonEnabled(true);
}

void RegistrationScreen::showErrorMessage(const QString& title, const QString& message)
{
    m_errorMessageLabel->setText(title + ": " + message);
    m_errorMessageLabel->show();
}

void RegistrationScreen::clearErrorMessage()
{
    m_errorMessageLabel->hide();
}

void RegistrationScreen::setSignUpButtonEnabled(bool enabled)
{
    m_signUpButton->setEnabled(enabled);
    if (!enabled) {
        m_signUpButton->setText("Creating account...");
    } else {
        m_signUpButton->setText("Sign Up");
    }
}

void RegistrationScreen::updatePasswordStrengthIndicator(const QString& password)
{
    if (password.isEmpty()) {
        m_passwordStrengthLabel->setText("Password strength: None");
        m_passwordStrengthBar->setValue(0);
        m_passwordStrengthBar->setStyleSheet(
            "QProgressBar {"
            "  border: none;"
            "  background-color: #e2e8f0;"
            "  border-radius: 2px;"
            "}"
            "QProgressBar::chunk {"
            "  background-color: #dc2626;"
            "  border-radius: 2px;"
            "}"
        );
        return;
    }

    int strength = 0;
    QString strengthText = "";
    QString strengthColor = "";

    // Check length
    if (password.length() >= 12) strength++;
    if (password.length() >= 16) strength++;

    // Check character types
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (const QChar& c : password) {
        if (c.isUpper()) hasUpper = true;
        if (c.isLower()) hasLower = true;
        if (c.isDigit()) hasDigit = true;
        if (QString("!@#$%^&*()-_=+[]{}|;:,.<>?").contains(c)) hasSpecial = true;
    }

    if (hasUpper) strength++;
    if (hasLower) strength++;
    if (hasDigit) strength++;
    if (hasSpecial) strength++;

    // Determine strength level
    if (strength <= 2) {
        strengthText = "Weak";
        strengthColor = "#dc2626"; // Red
    } else if (strength <= 4) {
        strengthText = "Fair";
        strengthColor = "#f59e0b"; // Amber
    } else if (strength <= 6) {
        strengthText = "Good";
        strengthColor = "#eab308"; // Yellow
    } else {
        strengthText = "Strong";
        strengthColor = "#22c55e"; // Green
    }

    m_passwordStrengthLabel->setText("Password strength: " + strengthText);

    int progressValue = (strength * 100) / 8;
    m_passwordStrengthBar->setValue(progressValue);
    m_passwordStrengthBar->setStyleSheet(
        "QProgressBar {"
        "  border: none;"
        "  background-color: #e2e8f0;"
        "  border-radius: 2px;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: " + strengthColor + ";"
        "  border-radius: 2px;"
        "}"
    );
}

bool RegistrationScreen::validateAllFields()
{
    QString email = m_emailInput->text().trimmed();
    QString username = m_usernameInput->text().trimmed();
    QString password = m_passwordInput->text();
    QString confirmPassword = m_confirmPasswordInput->text();

    // Validate email
    ValidationResult emailValidation = m_validators.validateEmail(email);
    if (!emailValidation.isValid) {
        showErrorMessage("Invalid Email", emailValidation.errorMessage);
        return false;
    }

    // Validate username
    ValidationResult usernameValidation = m_validators.validateUsername(username);
    if (!usernameValidation.isValid) {
        showErrorMessage("Invalid Username", usernameValidation.errorMessage);
        return false;
    }

    // Validate password
    ValidationResult passwordValidation = m_validators.validatePassword(password);
    if (!passwordValidation.isValid) {
        showErrorMessage("Weak Password", passwordValidation.errorMessage);
        return false;
    }

    // Validate password match
    ValidationResult matchValidation = m_validators.validatePasswordMatch(password, confirmPassword);
    if (!matchValidation.isValid) {
        showErrorMessage("Password Mismatch", matchValidation.errorMessage);
        return false;
    }

    return true;
}

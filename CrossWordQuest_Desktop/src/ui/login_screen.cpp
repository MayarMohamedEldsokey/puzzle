#include "login_screen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QSize>
#include <QIcon>
#include <QPixmap>
#include <QMovie>
#include <QTimer>

LoginScreen::LoginScreen(AuthManager* authManager, QWidget* parent)
    : QWidget(parent), m_authManager(authManager), m_isLoading(false)
{
    setupUI();
    connectSignals();
    resetForm();
}

LoginScreen::~LoginScreen()
{
}

void LoginScreen::setupUI()
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

    // Puzzle graphic placeholder (simplified for now)
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
    QLabel* versionLabel = new QLabel("Version 3.4.12");
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

    // Right pane - Login form
    QWidget* rightPane = new QWidget();
    rightPane->setStyleSheet("QWidget { background-color: white; }");
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(48, 0, 48, 0);
    rightLayout->setSpacing(24);
    rightLayout->addStretch();

    // Form container
    QWidget* formContainer = new QWidget();
    QVBoxLayout* formLayout = new QVBoxLayout(formContainer);
    formLayout->setSpacing(20);

    // Title
    m_titleLabel = new QLabel("Welcome Back");
    m_titleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 24px;"
        "  font-weight: 700;"
        "  color: #1e293b;"
        "}"
    );

    // Subtitle
    m_subtitleLabel = new QLabel("Enter your credentials to continue your quest.");
    m_subtitleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  color: #64748b;"
        "}"
    );

    // Email/Username field
    QLabel* emailLabel = new QLabel("Username / Email");
    emailLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "  color: #475569;"
        "}"
    );
    m_emailInput = new QLineEdit();
    m_emailInput->setPlaceholderText("Enter your username or email");
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
        "  border: 2px solid #4a6fa5;"
        "  padding: 9px 11px;"
        "}"
    );
    m_emailInput->setMinimumHeight(40);

    // Password field
    QLabel* passwordLabel = new QLabel("Password");
    passwordLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  font-weight: 600;"
        "  color: #475569;"
        "}"
    );

    QHBoxLayout* passwordLabelLayout = new QHBoxLayout();
    passwordLabelLayout->addWidget(passwordLabel);
    passwordLabelLayout->addStretch();
    QLabel* forgotLink = new QLabel("<a href='#' style='color: #64748b; text-decoration: none;'>Forgot?</a>");
    m_forgotPasswordButton = new QPushButton("Forgot?");
    m_forgotPasswordButton->setFlat(true);
    m_forgotPasswordButton->setStyleSheet(
        "QPushButton {"
        "  color: #64748b;"
        "  border: none;"
        "  background-color: transparent;"
        "  font-size: 10px;"
        "  padding: 0px;"
        "}"
        "QPushButton:hover { color: #4a6fa5; }"
    );
    passwordLabelLayout->addWidget(m_forgotPasswordButton);

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
        "  border: 2px solid #4a6fa5;"
        "  padding: 9px 11px;"
        "}"
    );
    m_passwordInput->setMinimumHeight(40);

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
    m_loginButton = new QPushButton("Login →");
    m_loginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4a6fa5;"
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
    m_loginButton->setMinimumHeight(40);

    m_exitButton = new QPushButton("Exit ↩");
    m_exitButton->setStyleSheet(
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
    m_exitButton->setMinimumHeight(40);

    // Social buttons
    QHBoxLayout* socialLayout = new QHBoxLayout();
    QPushButton* steamButton = new QPushButton("🔵");
    QPushButton* googleButton = new QPushButton("⊕");
    steamButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #2a4365;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 20px;"
        "  min-width: 40px;"
        "  min-height: 40px;"
        "}"
        "QPushButton:hover { background-color: #334155; }"
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
    socialLayout->addWidget(steamButton);
    socialLayout->addWidget(googleButton);
    socialLayout->addStretch();

    // Add to form layout
    formLayout->addWidget(m_titleLabel);
    formLayout->addWidget(m_subtitleLabel);
    formLayout->addSpacing(10);
    formLayout->addWidget(emailLabel);
    formLayout->addWidget(m_emailInput);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(m_passwordInput);
    formLayout->addWidget(m_errorMessageLabel);
    formLayout->addWidget(m_loginButton);
    formLayout->addWidget(m_exitButton);
    formLayout->addSpacing(20);
    formLayout->addLayout(socialLayout);

    rightLayout->addWidget(formContainer);
    rightLayout->addStretch();

    mainLayout->addWidget(leftPane, 1);
    mainLayout->addWidget(rightPane, 1);

    setLayout(mainLayout);
    setWindowTitle("CrossWord Quest - Login");
    resize(1000, 600);
}

void LoginScreen::connectSignals()
{
    connect(m_loginButton, &QPushButton::clicked, this, &LoginScreen::onLoginButtonClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &LoginScreen::onExitButtonClicked);
    connect(m_forgotPasswordButton, &QPushButton::clicked, this, &LoginScreen::onForgotPasswordClicked);

    connect(m_authManager, &AuthManager::loginSuccess, this, &LoginScreen::onLoginSuccess);
    connect(m_authManager, &AuthManager::loginFailed, this, &LoginScreen::onLoginFailed);

    connect(m_emailInput, &QLineEdit::textChanged, this, &LoginScreen::onEmailTextChanged);
    connect(m_passwordInput, &QLineEdit::textChanged, this, &LoginScreen::onPasswordTextChanged);
}

void LoginScreen::onLoginButtonClicked()
{
    clearErrorMessage();

    QString email = m_emailInput->text().trimmed();
    QString password = m_passwordInput->text();

    // Validate email
    ValidationResult emailValidation = m_validators.validateEmail(email);
    if (!emailValidation.isValid) {
        showErrorMessage("Invalid Email", emailValidation.errorMessage);
        return;
    }

    // Validate password
    if (password.isEmpty()) {
        showErrorMessage("Missing Password", "Please enter your password");
        return;
    }

    // Attempt login
    setLoginButtonEnabled(false);
    m_isLoading = true;
    m_authManager->login(email, password);
}

void LoginScreen::onForgotPasswordClicked()
{
    // TODO: Implement forgot password flow
}

void LoginScreen::onExitButtonClicked()
{
    QApplication::quit();
}

void LoginScreen::onLoginSuccess()
{
    setLoginButtonEnabled(true);
    m_isLoading = false;
    resetForm();
    // TODO: Navigate to dashboard
}

void LoginScreen::onLoginFailed(const QString& errorMessage)
{
    setLoginButtonEnabled(true);
    m_isLoading = false;
    showErrorMessage("Login Failed", errorMessage);
}

void LoginScreen::onEmailTextChanged(const QString& text)
{
    clearErrorMessage();
}

void LoginScreen::onPasswordTextChanged(const QString& text)
{
    clearErrorMessage();
}

void LoginScreen::resetForm()
{
    m_emailInput->clear();
    m_passwordInput->clear();
    clearErrorMessage();
    setLoginButtonEnabled(true);
}

void LoginScreen::showErrorMessage(const QString& title, const QString& message)
{
    m_errorMessageLabel->setText(title + ": " + message);
    m_errorMessageLabel->show();
}

void LoginScreen::clearErrorMessage()
{
    m_errorMessageLabel->hide();
}

void LoginScreen::setLoginButtonEnabled(bool enabled)
{
    m_loginButton->setEnabled(enabled);
    if (!enabled) {
        m_loginButton->setText("Logging in...");
    } else {
        m_loginButton->setText("Login →");
    }
}

#include "login_screen.h"
#include <QApplication>
#include <QDebug>
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
        "QWidget { background-color: #f8fafc; }"
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
        "  line-height: 1.3;"
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

    // Puzzle graphic crossword visualizer
    QWidget* puzzleGraphic = new QWidget();
    puzzleGraphic->setStyleSheet(
        "QWidget {"
        "  border: 1px solid #e2e8f0;"
        "  border-radius: 16px;"
        "  background-color: #ffffff;"
        "}"
    );
    
    QGridLayout* gridLayout = new QGridLayout(puzzleGraphic);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(16, 16, 16, 16);
    gridLayout->setAlignment(Qt::AlignCenter);
    
    const int GRID_SIZE = 6;
    const char* gridData[GRID_SIZE] = {
        "WORD  ",
        "  E   ",
        "PLAY  ",
        "  D   ",
        "      ",
        "QUEST "
    };
    
    int cellNumbers[GRID_SIZE][GRID_SIZE] = {
        {1, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0, 0}
    };
    
    for (int r = 0; r < GRID_SIZE; ++r) {
        for (int c = 0; c < GRID_SIZE; ++c) {
            char letter = gridData[r][c];
            int num = cellNumbers[r][c];
            QWidget* cell = new QWidget();
            cell->setFixedSize(40, 40);
            
            if (letter != ' ') {
                QVBoxLayout* cellLayout = new QVBoxLayout(cell);
                cellLayout->setContentsMargins(4, 2, 4, 4);
                cellLayout->setSpacing(0);
                
                QLabel* numLabel = new QLabel(num > 0 ? QString::number(num) : "");
                numLabel->setStyleSheet("font-size: 8px; font-weight: bold; color: #94a3b8; font-family: 'Inter'; background: transparent; border: none;");
                numLabel->setFixedHeight(10);
                
                QLabel* letterLabel = new QLabel(QString(letter));
                letterLabel->setStyleSheet("font-size: 16px; font-weight: 800; color: #1e293b; font-family: 'Inter'; background: transparent; border: none;");
                letterLabel->setAlignment(Qt::AlignCenter);
                
                cellLayout->addWidget(numLabel);
                cellLayout->addWidget(letterLabel);
                
                cell->setStyleSheet(
                    "QWidget {"
                    "  background-color: #ffffff;"
                    "  border: 2px solid #cbd5e1;"
                    "  border-radius: 6px;"
                    "}"
                );
            } else {
                cell->setStyleSheet(
                    "QWidget {"
                    "  background-color: #1e293b;"
                    "  border: 2px solid #1e293b;"
                    "  border-radius: 6px;"
                    "}"
                );
            }
            gridLayout->addWidget(cell, r, c);
        }
    }

    leftLayout->addLayout(brandLayout);
    leftLayout->addWidget(titleLabel);
    leftLayout->addWidget(subtitleLabel);
    leftLayout->addWidget(puzzleGraphic);
    leftLayout->addStretch();

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
        "  border: 1px solid #cbd5e1;"
        "  background-color: #f8fafc;"
        "  border-radius: 10px;"
        "  padding: 10px 14px;"
        "  font-size: 13px;"
        "  color: #0f172a;"
        "}"
        "QLineEdit:focus {"
        "  background-color: white;"
        "  border: 2px solid #3b82f6;"
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
    m_forgotPasswordButton = new QPushButton("Forgot?");
    m_forgotPasswordButton->setFlat(true);
    m_forgotPasswordButton->setCursor(Qt::PointingHandCursor);
    m_forgotPasswordButton->setStyleSheet(
        "QPushButton {"
        "  color: #64748b;"
        "  border: none;"
        "  background-color: transparent;"
        "  font-size: 11px;"
        "  font-weight: 600;"
        "  padding: 0px;"
        "}"
        "QPushButton:hover { color: #3b82f6; }"
    );
    passwordLabelLayout->addWidget(m_forgotPasswordButton);

    m_passwordInput = new QLineEdit();
    m_passwordInput->setPlaceholderText("••••••••");
    m_passwordInput->setEchoMode(QLineEdit::Password);
    m_passwordInput->setStyleSheet(
        "QLineEdit {"
        "  border: 1px solid #cbd5e1;"
        "  background-color: #f8fafc;"
        "  border-radius: 10px;"
        "  padding: 10px 14px;"
        "  font-size: 13px;"
        "  color: #0f172a;"
        "}"
        "QLineEdit:focus {"
        "  background-color: white;"
        "  border: 2px solid #3b82f6;"
        "}"
    );
    m_passwordInput->setMinimumHeight(40);

    // Error message label
    m_errorMessageLabel = new QLabel();
    m_errorMessageLabel->setStyleSheet(
        "QLabel {"
        "  color: #dc2626;"
        "  font-size: 12px;"
        "  font-weight: 500;"
        "  padding: 10px 12px;"
        "  background-color: #fef2f2;"
        "  border: 1px solid #fee2e2;"
        "  border-radius: 8px;"
        "}"
    );
    m_errorMessageLabel->setWordWrap(true);
    m_errorMessageLabel->hide();

    // Buttons
    m_loginButton = new QPushButton("Login →");
    m_loginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #3b82f6;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 12px 16px;"
        "  font-size: 13px;"
        "  font-weight: 600;"
        "}"
        "QPushButton:hover { background-color: #2563eb; }"
        "QPushButton:pressed { background-color: #1d4ed8; }"
        "QPushButton:disabled {"
        "  background-color: #94a3b8;"
        "  color: #e2e8f0;"
        "}"
    );
    m_loginButton->setMinimumHeight(40);

    m_exitButton = new QPushButton("Exit ↩");
    m_exitButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #f1f5f9;"
        "  color: #475569;"
        "  border: 1px solid #cbd5e1;"
        "  border-radius: 10px;"
        "  padding: 12px 16px;"
        "  font-size: 13px;"
        "  font-weight: 600;"
        "}"
        "QPushButton:hover { background-color: #e2e8f0; color: #1e293b; }"
        "QPushButton:pressed { background-color: #cbd5e1; }"
    );
    m_exitButton->setMinimumHeight(40);

    // Create Account navigation row
    QHBoxLayout* registerRow = new QHBoxLayout();
    QLabel* registerLabel = new QLabel("Don't have an account?");
    registerLabel->setStyleSheet("color: #64748b; font-size: 12px;");
    m_signUpLinkButton = new QPushButton("Create Account");
    m_signUpLinkButton->setFlat(true);
    m_signUpLinkButton->setCursor(Qt::PointingHandCursor);
    m_signUpLinkButton->setStyleSheet(
        "QPushButton {"
        "  color: #3b82f6;"
        "  border: none;"
        "  background-color: transparent;"
        "  font-size: 12px;"
        "  font-weight: 700;"
        "  padding: 0px;"
        "}"
        "QPushButton:hover { color: #1d4ed8; text-decoration: underline; }"
    );
    registerRow->addStretch();
    registerRow->addWidget(registerLabel);
    registerRow->addWidget(m_signUpLinkButton);
    registerRow->addStretch();



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
    formLayout->addLayout(registerRow);


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
    connect(m_signUpLinkButton, &QPushButton::clicked, this, &LoginScreen::onSignUpLinkClicked);

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
    emit Dashboard();
}

void LoginScreen::onLoginFailed(const QString& errorMessage)
{
    setLoginButtonEnabled(true);
    m_isLoading = false;
    showErrorMessage("Login Failed", errorMessage);
}

void LoginScreen::onEmailTextChanged(const QString& /*text*/)
{
    clearErrorMessage();
}

void LoginScreen::onPasswordTextChanged(const QString& /*text*/)
{
    clearErrorMessage();
}

void LoginScreen::onSignUpLinkClicked()
{
    qDebug() << "DEBUG: LoginScreen::onSignUpLinkClicked - 'Create Account' link was clicked!";
    emit switchToRegistration();
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

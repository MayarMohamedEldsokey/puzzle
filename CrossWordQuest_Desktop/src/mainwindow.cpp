#include "mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("CrossWord Quest - Authentication");
    setWindowIcon(QIcon(""));

    // Initialize auth manager
    m_authManager = new AuthManager(this);
    
    // Enable test mode for development/testing (before Supabase integration)
    m_authManager->setTestMode(true);
    
    loadSupabaseConfig();

    setupUI();

    resize(1000, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Stacked widget for screens
    m_stackedWidget = new QStackedWidget();

    // Create screens
    m_loginScreen = new LoginScreen(m_authManager, this);
    m_registrationScreen = new RegistrationScreen(m_authManager, this);

    // Add screens to stacked widget
    m_stackedWidget->addWidget(m_loginScreen);
    m_stackedWidget->addWidget(m_registrationScreen);

    // Set login as default
    m_stackedWidget->setCurrentWidget(m_loginScreen);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_stackedWidget);

    centralWidget->setLayout(layout);

    // Connect signals
    connect(m_loginScreen, &LoginScreen::switchToRegistration, this, &MainWindow::onSwitchToRegistration);
    connect(m_registrationScreen, &RegistrationScreen::switchToLogin, this, &MainWindow::onSwitchToLogin);

    connect(m_authManager, &AuthManager::loginSuccess, this, &MainWindow::onLoginSuccess);
    connect(m_authManager, &AuthManager::registrationSuccess, this, &MainWindow::onRegistrationSuccess);
}

void MainWindow::loadSupabaseConfig()
{
    // Try to load from .env file in project root
    QString envPath = QCoreApplication::applicationDirPath() + "/../.env";
    QFile envFile(envPath);

    QString supabaseUrl = "https://your-project.supabase.co";
    QString anonKey = "your-anon-public-key";

    if (envFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&envFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("SUPABASE_URL=")) {
                supabaseUrl = line.mid(13).trimmed();
            } else if (line.startsWith("SUPABASE_ANON_KEY=")) {
                anonKey = line.mid(18).trimmed();
            }
        }
        envFile.close();
    } else {
        qWarning() << "Could not load .env file. Using default placeholder values.";
        qWarning() << "Please set SUPABASE_URL and SUPABASE_ANON_KEY in .env file";
    }

    // Initialize auth manager with Supabase credentials
    m_authManager->initialize(supabaseUrl, anonKey);
}

void MainWindow::onSwitchToRegistration()
{
    m_registrationScreen->resetForm();
    m_stackedWidget->setCurrentWidget(m_registrationScreen);
}

void MainWindow::onSwitchToLogin()
{
    m_loginScreen->resetForm();
    m_stackedWidget->setCurrentWidget(m_loginScreen);
}

void MainWindow::onLoginSuccess()
{
    qDebug() << "Login successful!";
    // TODO: Navigate to dashboard
}

void MainWindow::onRegistrationSuccess()
{
    qDebug() << "Registration successful!";
    // Automatically navigate to login screen
    onSwitchToLogin();
    // TODO: Show success message
}

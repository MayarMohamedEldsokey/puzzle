#include "mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QDir>

MainWindow::MainWindow(AuthManager* authManager, QWidget* parent)
    : QMainWindow(parent), m_qmlEngine(nullptr)
{
    setWindowTitle("CrossWord Quest - Authentication");
    setWindowIcon(QIcon(""));

    // Use provided AuthManager or create our own
    if (authManager) {
        m_authManager = authManager;
    } else {
        m_authManager = new AuthManager(this);
        // Enable test mode for development/testing (before Supabase integration)
        m_authManager->setTestMode(true);
    }

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
    qDebug() << "DEBUG: MainWindow::onSwitchToRegistration called - switching widget to RegistrationScreen!";
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
    qDebug() << "Login successful! Dynamic loading crossword dashboard...";

    // Recreate the QML Engine to guarantee a clean state/session
    if (m_qmlEngine) {
        delete m_qmlEngine;
    }
    m_qmlEngine = new QQmlApplicationEngine(this);

    // Search for src/dashboard/Main.qml using an extremely robust multi-level fallback search
    QString qmlPath = QCoreApplication::applicationDirPath() + "/Main.qml"; // Direct copy next to executable
    
    if (!QFile::exists(qmlPath)) {
        qmlPath = QCoreApplication::applicationDirPath() + "/src/dashboard/Main.qml";
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QCoreApplication::applicationDirPath() + "/../src/dashboard/Main.qml";
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QCoreApplication::applicationDirPath() + "/../../src/dashboard/Main.qml";
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QCoreApplication::applicationDirPath() + "/../../../src/dashboard/Main.qml"; // For deep build structures
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QDir::currentPath() + "/src/dashboard/Main.qml"; // Current working directory (project root)
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QDir::currentPath() + "/../src/dashboard/Main.qml"; // Build directory under root
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QDir::currentPath() + "/../../src/dashboard/Main.qml"; // Deep build directory under root
    }
    if (!QFile::exists(qmlPath)) {
        qmlPath = QDir::currentPath() + "/../../../src/dashboard/Main.qml"; // Multi-level build directory under root
    }

    qDebug() << "Resolved QML Path:" << qmlPath;

    if (!QFile::exists(qmlPath)) {
        qWarning() << "CRITICAL: src/dashboard/Main.qml could not be found!";
        return;
    }

    m_qmlEngine->load(QUrl::fromLocalFile(qmlPath));

    if (m_qmlEngine->rootObjects().isEmpty()) {
        qWarning() << "CRITICAL: QQmlApplicationEngine failed to load src/dashboard/Main.qml!";
        return;
    }

    // Connect the root QML Window's visibility changed signal to return to Login Screen on close
    QObject* rootObject = m_qmlEngine->rootObjects().first();
    if (rootObject) {
        connect(rootObject, SIGNAL(visibleChanged(bool)), this, SLOT(onQmlWindowVisibleChanged(bool)));
    }

    // Hide the login MainWindow
    this->hide();
}

void MainWindow::onQmlWindowVisibleChanged(bool visible)
{
    // When the QML window is closed or hidden, visible becomes false
    if (!visible) {
        qDebug() << "QML Dashboard Window closed. Swapping back to C++ Login screen...";
        
        // Log out user
        if (m_authManager) {
            m_authManager->logout();
        }

        // Reset the login form inputs
        if (m_loginScreen) {
            m_loginScreen->resetForm();
        }

        // Show the login MainWindow again
        this->show();
    }
}

void MainWindow::onRegistrationSuccess()
{
    qDebug() << "Registration successful!";
    // Automatically navigate to login screen
    onSwitchToLogin();
    // TODO: Show success message
}

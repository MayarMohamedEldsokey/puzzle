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
    : QMainWindow(parent), m_homepage(nullptr), m_qmlEngine(nullptr)
{
    setWindowTitle("CrossWord Quest - Authentication");
    setWindowIcon(QIcon(""));

    // Use provided AuthManager or create our own
    if (authManager) {
        m_authManager = authManager;
    } else {
        m_authManager = new AuthManager(this);
        // Disable test mode to use real Supabase authentication
        m_authManager->setTestMode(false);
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
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_stackedWidget = new QStackedWidget();

    m_loginScreen = new LoginScreen(m_authManager, this);
    m_registrationScreen = new RegistrationScreen(m_authManager, this);
    m_homepage = new Homepage(this);  // ← create it first

    m_stackedWidget->addWidget(m_loginScreen);
    m_stackedWidget->addWidget(m_registrationScreen);
    m_stackedWidget->addWidget(m_homepage);  // ← add to stack

    m_stackedWidget->setCurrentWidget(m_loginScreen);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_stackedWidget);
    centralWidget->setLayout(layout);

    connect(m_loginScreen, &LoginScreen::switchToRegistration, this, &MainWindow::onSwitchToRegistration);
    connect(m_registrationScreen, &RegistrationScreen::switchToLogin, this, &MainWindow::onSwitchToLogin);
    connect(m_loginScreen, &LoginScreen::Dashboard, this, &MainWindow::onLoginSuccess);
    connect(m_homepage, &Homepage::StartGameClicked, this, &MainWindow::onStartGame);  // ← correct name
    connect(m_homepage, &Homepage::ViewResultsClicked, this, &MainWindow::onViewResults);
    connect(m_homepage, &Homepage::ExitClicked, this, &MainWindow::close);
    connect(m_authManager, &AuthManager::registrationSuccess, this, &MainWindow::onRegistrationSuccess);
}

void MainWindow::loadSupabaseConfig()
{
    // Try to load from .env file.
    // Since build configurations place the executable in different subdirectory levels
    // (e.g., build/Desktop_Qt_.../bin, build/debug, out/, etc.),
    // we search upwards from the executable directory to locate the .env file.
    QString searchDir = QCoreApplication::applicationDirPath();
    QString envPath;
    bool found = false;

    // Search up to 5 parent directories
    for (int i = 0; i < 5; ++i) {
        QString testPath = QDir(searchDir).filePath(".env");
        if (QFile::exists(testPath)) {
            envPath = testPath;
            found = true;
            break;
        }
        QString parentDir = QDir(searchDir).filePath("..");
        // Check if we hit the root and can't go up further
        if (QDir(parentDir).canonicalPath() == QDir(searchDir).canonicalPath()) {
            break;
        }
        searchDir = parentDir;
    }

    // Fallback to the original default if not found
    if (!found) {
        envPath = QCoreApplication::applicationDirPath() + "/../.env";
    }

    QFile envFile(envPath);
    QString supabaseUrl = "db.ewfiosstfkwchdlktdbt.supabase.co";
    QString anonKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImV3Zmlvc3N0Zmt3Y2hkbGt0ZGJ0Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3NzkwNjc4MDUsImV4cCI6MjA5NDY0MzgwNX0.Y4Ye_EAZWTtKCPnPlNpB19iPqL_NyvROveeqMtzjod0";

    if (envFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Successfully loaded .env file from:" << envPath;
        QTextStream in(&envFile);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
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

    // Ensure URL has the https:// scheme (required for QNetworkAccessManager REST requests)
    if (!supabaseUrl.startsWith("http://") && !supabaseUrl.startsWith("https://")) {
        supabaseUrl = "https://" + supabaseUrl;
    }

    // Strip "db." prefix if present, as it is only for PostgreSQL direct connections
    // whereas HTTP REST & Auth APIs use the project domain directly.
    if (supabaseUrl.contains("://db.")) {
        supabaseUrl.replace("://db.", "://");
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
    qDebug() << "Login successful! Switching to Homepage...";

    if (!m_homepage) {
        m_homepage = new Homepage();
        m_stackedWidget->addWidget(m_homepage);
    }

    m_stackedWidget->setCurrentWidget(m_homepage);
}


void MainWindow::onStartGame()
{
    if (m_qmlEngine) {
        delete m_qmlEngine;
        m_qmlEngine = nullptr;
    }

    m_qmlEngine = new QQmlApplicationEngine(this);

    // Load from Qt resources — always works regardless of build location
    m_qmlEngine->load(QUrl("qrc:/src/game/Main.qml"));

    if (m_qmlEngine->rootObjects().isEmpty()) {
        qWarning() << "CRITICAL: Failed to load Main.qml from resources!";
        return;
    }

    auto roots = m_qmlEngine->rootObjects();
    QObject* root = roots.first();
    if (root)
        connect(root, SIGNAL(visibleChanged(bool)),
                this, SLOT(onQmlWindowVisibleChanged(bool)));

    this->hide();
}

void MainWindow::onViewResults()
{
    if (m_qmlEngine) {
        delete m_qmlEngine;
        m_qmlEngine = nullptr;
    }

    m_qmlEngine = new QQmlApplicationEngine(this);

    // Force QML to use basic style to prevent visual controls style crashes/glitches
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");

    // Load from Qt resources — always works regardless of build location
    m_qmlEngine->load(QUrl("qrc:/src/result/GameResultPage.qml"));

    if (m_qmlEngine->rootObjects().isEmpty()) {
        qWarning() << "CRITICAL: Failed to load GameResultPage.qml from resources!";
        return;
    }

    auto roots = m_qmlEngine->rootObjects();
    QObject* root = roots.first();
    if (root)
        connect(root, SIGNAL(visibleChanged(bool)),
                this, SLOT(onQmlWindowVisibleChanged(bool)));

    this->hide();
}

void MainWindow::onQmlWindowVisibleChanged(bool visible)
{
    // When the QML window is closed or hidden, visible becomes false
    if (!visible) {
        qDebug() << "QML Window closed. Swapping back to C++ Homepage...";
        
        // Show the main C++ window again
        this->show();
        
        // Return directly to the Homepage rather than forcing a logout
        if (m_homepage) {
            m_stackedWidget->setCurrentWidget(m_homepage);
        } else {
            m_stackedWidget->setCurrentWidget(m_loginScreen);
        }
    }
}

void MainWindow::onRegistrationSuccess()
{
    qDebug() << "Registration successful!";
    // Automatically navigate to login screen
    onSwitchToLogin();
    // TODO: Show success message
}

#include "auth_manager.h"
#include <QDebug>

AuthManager::AuthManager(QObject* parent)
    : QObject(parent), m_supabaseClient(nullptr), m_isAuthenticated(false), m_testMode(false)
{
}

AuthManager::~AuthManager()
{
    // m_supabaseClient will be deleted when its parent is deleted
}

void AuthManager::initialize(const QString& supabaseUrl, const QString& anonKey)
{
    if (m_supabaseClient) {
        delete m_supabaseClient;
    }

    m_supabaseClient = new SupabaseClient(supabaseUrl, anonKey, this);

    connect(m_supabaseClient, &SupabaseClient::signInFinished, this, &AuthManager::onSignInFinished);
    connect(m_supabaseClient, &SupabaseClient::signUpFinished, this, &AuthManager::onSignUpFinished);
}

void AuthManager::login(const QString& email, const QString& password)
{
    // Check test mode first
    if (m_testMode) {
        if (email == TEST_EMAIL && password == TEST_PASSWORD) {
            // Simulate successful login with test credentials
            m_accessToken = "test-token-12345";
            m_refreshToken = "test-refresh-token";
            m_userId = TEST_USER_ID;
            m_isAuthenticated = true;
            emit authenticationChanged(true);
            emit loginSuccess();
            qDebug() << "Test mode: Login successful with test credentials";
            return;
        } else {
            // Test credentials provided but wrong
            m_isAuthenticated = false;
            emit authenticationChanged(false);
            if (email != TEST_EMAIL) {
                emit loginFailed("Email not found");
            } else {
                emit loginFailed("Incorrect password");
            }
            qDebug() << "Test mode: Login failed";
            return;
        }
    }

    if (!m_supabaseClient) {
        emit loginFailed("Authentication not initialized");
        return;
    }

    m_supabaseClient->signIn(email, password);
}

void AuthManager::registerUser(const QString& email, const QString& password, const QString& username)
{
    // Check test mode first
    if (m_testMode) {
        if (email == TEST_EMAIL) {
            // Email already exists in test mode
            m_isAuthenticated = false;
            emit authenticationChanged(false);
            emit registrationFailed("This email is already registered");
            qDebug() << "Test mode: Registration failed - email already exists";
            return;
        }
        
        // Simulate successful registration
        m_accessToken = "test-token-" + QString::number(qrand());
        m_refreshToken = "test-refresh-token";
        m_userId = "test-user-" + QString::number(qrand());
        m_isAuthenticated = true;
        emit authenticationChanged(true);
        emit registrationSuccess();
        qDebug() << "Test mode: Registration successful for" << email;
        return;
    }

    if (!m_supabaseClient) {
        emit registrationFailed("Authentication not initialized");
        return;
    }

    m_supabaseClient->signUp(email, password, username);
}

QString AuthManager::getAccessToken() const
{
    return m_accessToken;
}

QString AuthManager::getUserId() const
{
    return m_userId;
}

bool AuthManager::isAuthenticated() const
{
    return m_isAuthenticated;
}

void AuthManager::logout()
{
    m_accessToken = "";
    m_refreshToken = "";
    m_userId = "";
    m_isAuthenticated = false;
    emit authenticationChanged(false);
}

void AuthManager::setTestMode(bool enabled)
{
    m_testMode = enabled;
    if (enabled) {
        qDebug() << "Test mode ENABLED - Using hardcoded credentials:";
        qDebug() << "  Email:" << TEST_EMAIL;
        qDebug() << "  Password:" << TEST_PASSWORD;
        qDebug() << "  Username:" << TEST_USERNAME;
    } else {
        qDebug() << "Test mode disabled - Using Supabase";
    }
}

void AuthManager::onSignInFinished(const AuthResponse& response)
{
    if (response.success) {
        m_accessToken = response.accessToken;
        m_refreshToken = response.refreshToken;
        m_userId = response.userId;
        m_isAuthenticated = true;
        emit authenticationChanged(true);
        emit loginSuccess();
    } else {
        m_isAuthenticated = false;
        emit authenticationChanged(false);
        emit loginFailed(response.errorMessage);
    }
}

void AuthManager::onSignUpFinished(const AuthResponse& response)
{
    if (response.success) {
        m_accessToken = response.accessToken;
        m_refreshToken = response.refreshToken;
        m_userId = response.userId;
        m_isAuthenticated = true;
        emit authenticationChanged(true);
        emit registrationSuccess();
    } else {
        m_isAuthenticated = false;
        emit authenticationChanged(false);
        emit registrationFailed(response.errorMessage);
    }
}

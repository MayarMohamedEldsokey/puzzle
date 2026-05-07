#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <QString>
#include <QObject>
#include "supabase_client.h"

class AuthManager : public QObject {
    Q_OBJECT

public:
    explicit AuthManager(QObject* parent = nullptr);
    ~AuthManager();

    // Initialize with Supabase credentials
    void initialize(const QString& supabaseUrl, const QString& anonKey);

    // Authentication methods
    void login(const QString& email, const QString& password);
    void registerUser(const QString& email, const QString& password, const QString& username);

    // Session management
    QString getAccessToken() const;
    QString getUserId() const;
    bool isAuthenticated() const;
    void logout();

    // Enable/disable test mode (hardcoded credentials)
    void setTestMode(bool enabled);

signals:
    void loginSuccess();
    void loginFailed(const QString& errorMessage);
    void registrationSuccess();
    void registrationFailed(const QString& errorMessage);
    void authenticationChanged(bool isAuthenticated);

private slots:
    void onSignInFinished(const AuthResponse& response);
    void onSignUpFinished(const AuthResponse& response);

private:
    SupabaseClient* m_supabaseClient;
    QString m_accessToken;
    QString m_refreshToken;
    QString m_userId;
    bool m_isAuthenticated;
    bool m_testMode;

    // Test credentials
    static constexpr const char* TEST_EMAIL = "test@example.com";
    static constexpr const char* TEST_PASSWORD = "TestPass123!";
    static constexpr const char* TEST_USERNAME = "testuser";
    static constexpr const char* TEST_USER_ID = "test-user-uuid-12345";
};

#endif // AUTH_MANAGER_H

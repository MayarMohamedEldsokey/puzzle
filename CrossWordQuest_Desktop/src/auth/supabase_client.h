#ifndef SUPABASE_CLIENT_H
#define SUPABASE_CLIENT_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QObject>

struct AuthResponse {
    bool success;
    QString accessToken;
    QString refreshToken;
    QString userId;
    QString errorMessage;
    int errorCode; // HTTP status code
};

class SupabaseClient : public QObject {
    Q_OBJECT

public:
    explicit SupabaseClient(const QString& supabaseUrl, const QString& anonKey, QObject* parent = nullptr);
    ~SupabaseClient();

    // Authentication methods
    void signUp(const QString& email, const QString& password, const QString& username);
    void signIn(const QString& email, const QString& password);

signals:
    void signUpFinished(const AuthResponse& response);
    void signInFinished(const AuthResponse& response);
    void errorOccurred(const QString& errorMessage);

private slots:
    void onSignUpReply();
    void onSignInReply();

private:
    QString m_supabaseUrl;
    QString m_anonKey;
    QNetworkAccessManager* m_networkManager;

    // Helper methods
    AuthResponse parseAuthResponse(const QByteArray& responseData, int statusCode);
    void setCommonHeaders(QNetworkRequest& request);
};

#endif // SUPABASE_CLIENT_H

#include "supabase_client.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>

SupabaseClient::SupabaseClient(const QString& supabaseUrl, const QString& anonKey, QObject* parent)
    : QObject(parent), m_supabaseUrl(supabaseUrl), m_anonKey(anonKey)
{
    m_networkManager = new QNetworkAccessManager(this);
}

SupabaseClient::~SupabaseClient()
{
    // QNetworkAccessManager will be deleted with this object due to parent-child relationship
}

void SupabaseClient::signUp(const QString& email, const QString& password, const QString& username)
{
    QUrl url(m_supabaseUrl + "/auth/v1/signup");
    QNetworkRequest request(url);
    setCommonHeaders(request);

    QJsonObject json;
    json["email"] = email;
    json["password"] = password;
    json["user_metadata"] = QJsonObject{{"username", username}};

    QJsonDocument doc(json);

    QNetworkReply* reply = m_networkManager->post(request, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, &SupabaseClient::onSignUpReply);
}

void SupabaseClient::signIn(const QString& email, const QString& password)
{
    QUrl url(m_supabaseUrl + "/auth/v1/token?grant_type=password");
    QNetworkRequest request(url);
    setCommonHeaders(request);

    QJsonObject json;
    json["email"] = email;
    json["password"] = password;

    QJsonDocument doc(json);

    QNetworkReply* reply = m_networkManager->post(request, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, &SupabaseClient::onSignInReply);
}

void SupabaseClient::onSignUpReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        emit errorOccurred("Network error");
        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responseData = reply->readAll();

    AuthResponse response = parseAuthResponse(responseData, statusCode);
    emit signUpFinished(response);

    reply->deleteLater();
}

void SupabaseClient::onSignInReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        emit errorOccurred("Network error");
        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responseData = reply->readAll();

    AuthResponse response = parseAuthResponse(responseData, statusCode);
    emit signInFinished(response);

    reply->deleteLater();
}

AuthResponse SupabaseClient::parseAuthResponse(const QByteArray& responseData, int statusCode)
{
    AuthResponse response;
    response.errorCode = statusCode;

    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = doc.object();

    if (statusCode == 200) {
        response.success = true;
        response.accessToken = jsonObj.value("access_token").toString();
        response.refreshToken = jsonObj.value("refresh_token").toString();
        response.userId = jsonObj.value("user").toObject().value("id").toString();
        response.errorMessage = "";
    } else {
        response.success = false;
        response.accessToken = "";
        response.refreshToken = "";
        response.userId = "";

        // Parse error message from response
        QString errorMessage = jsonObj.value("message").toString();
        if (errorMessage.isEmpty()) {
            errorMessage = jsonObj.value("msg").toString();
        }
        if (errorMessage.isEmpty()) {
            errorMessage = jsonObj.value("error").toString();
        }
        if (errorMessage.isEmpty()) {
            errorMessage = jsonObj.value("error_description").toString();
        }

        // Map Supabase errors to user-friendly messages
        if (statusCode == 429 || errorMessage.contains("rate limit", Qt::CaseInsensitive)) {
            response.errorMessage = "Too many requests. Please wait a minute and try again.";
        } else if (statusCode == 400) {
            if (errorMessage.contains("Invalid login credentials", Qt::CaseInsensitive)) {
                response.errorMessage = "Invalid email or password";
            } else if (errorMessage.contains("User already registered", Qt::CaseInsensitive)) {
                response.errorMessage = "This email is already registered";
            } else if (errorMessage.contains("email", Qt::CaseInsensitive)) {
                response.errorMessage = "Invalid email address";
            } else {
                response.errorMessage = errorMessage.isEmpty() ? "Invalid request" : errorMessage;
            }
        } else if (statusCode == 422) {
            if (errorMessage.contains("email", Qt::CaseInsensitive)) {
                response.errorMessage = "Email not found";
            } else {
                response.errorMessage = "Validation error: " + errorMessage;
            }
        } else if (statusCode == 401) {
            response.errorMessage = "Incorrect password";
        } else if (statusCode == 404) {
            response.errorMessage = "Email not found";
        } else if (statusCode >= 500) {
            response.errorMessage = "Server error. Please try again later.";
        } else {
            response.errorMessage = errorMessage.isEmpty() ? "Authentication failed" : errorMessage;
        }
    }

    return response;
}

void SupabaseClient::setCommonHeaders(QNetworkRequest& request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("apikey", m_anonKey.toLatin1());
}

#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <QString>

class UserModel {
public:
    UserModel();

    // Getters
    QString getEmail() const { return m_email; }
    QString getUsername() const { return m_username; }
    QString getUserId() const { return m_userId; }

    // Setters
    void setEmail(const QString& email) { m_email = email; }
    void setUsername(const QString& username) { m_username = username; }
    void setUserId(const QString& userId) { m_userId = userId; }

    // Clear user data
    void clear();

private:
    QString m_email;
    QString m_username;
    QString m_userId;
};

#endif // USER_MODEL_H

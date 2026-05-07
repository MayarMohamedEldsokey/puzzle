#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <QString>
#include <QRegularExpression>

struct ValidationResult {
    bool isValid;
    QString errorMessage;
};

class Validators {
public:
    // Email validation
    static ValidationResult validateEmail(const QString& email);
    
    // Password validation (12+ chars, uppercase, lowercase, digit, special char)
    static ValidationResult validatePassword(const QString& password);
    static ValidationResult validatePasswordMatch(const QString& password, const QString& confirmPassword);
    
    // Username validation
    static ValidationResult validateUsername(const QString& username);

private:
    // Email regex pattern
    static const QRegularExpression emailRegex;
    
    // Minimum password length
    static constexpr int MIN_PASSWORD_LENGTH = 12;
    
    // Regex patterns for password requirements
    static bool hasUppercase(const QString& str);
    static bool hasLowercase(const QString& str);
    static bool hasDigit(const QString& str);
    static bool hasSpecialChar(const QString& str);
};

#endif // VALIDATORS_H

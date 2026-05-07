#include "validators.h"

const QRegularExpression Validators::emailRegex(
    QStringLiteral("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$")
);

ValidationResult Validators::validateEmail(const QString& email)
{
    ValidationResult result;
    result.isValid = true;
    result.errorMessage = "";

    // Check if empty
    if (email.trimmed().isEmpty()) {
        result.isValid = false;
        result.errorMessage = "Email address is required";
        return result;
    }

    // Check email format
    if (!emailRegex.match(email).hasMatch()) {
        result.isValid = false;
        result.errorMessage = "Invalid email format";
        return result;
    }

    // Check length
    if (email.length() > 254) {
        result.isValid = false;
        result.errorMessage = "Email address is too long";
        return result;
    }

    return result;
}

ValidationResult Validators::validatePassword(const QString& password)
{
    ValidationResult result;
    result.isValid = true;
    result.errorMessage = "";

    if (password.isEmpty()) {
        result.isValid = false;
        result.errorMessage = "Password is required";
        return result;
    }

    // Check minimum length
    if (password.length() < MIN_PASSWORD_LENGTH) {
        result.isValid = false;
        result.errorMessage = QString("Password must be at least %1 characters").arg(MIN_PASSWORD_LENGTH);
        return result;
    }

    // Check for uppercase
    if (!hasUppercase(password)) {
        result.isValid = false;
        result.errorMessage = "Password must contain at least one uppercase letter (A-Z)";
        return result;
    }

    // Check for lowercase
    if (!hasLowercase(password)) {
        result.isValid = false;
        result.errorMessage = "Password must contain at least one lowercase letter (a-z)";
        return result;
    }

    // Check for digit
    if (!hasDigit(password)) {
        result.isValid = false;
        result.errorMessage = "Password must contain at least one digit (0-9)";
        return result;
    }

    // Check for special character
    if (!hasSpecialChar(password)) {
        result.isValid = false;
        result.errorMessage = "Password must contain at least one special character (!@#$%^&*)";
        return result;
    }

    return result;
}

ValidationResult Validators::validatePasswordMatch(const QString& password, const QString& confirmPassword)
{
    ValidationResult result;
    result.isValid = true;
    result.errorMessage = "";

    if (password != confirmPassword) {
        result.isValid = false;
        result.errorMessage = "Passwords do not match";
    }

    return result;
}

ValidationResult Validators::validateUsername(const QString& username)
{
    ValidationResult result;
    result.isValid = true;
    result.errorMessage = "";

    if (username.trimmed().isEmpty()) {
        result.isValid = false;
        result.errorMessage = "Username is required";
        return result;
    }

    if (username.length() < 3) {
        result.isValid = false;
        result.errorMessage = "Username must be at least 3 characters";
        return result;
    }

    if (username.length() > 30) {
        result.isValid = false;
        result.errorMessage = "Username must not exceed 30 characters";
        return result;
    }

    // Only alphanumeric, underscore, and hyphen allowed
    QRegularExpression usernameRegex(QStringLiteral("^[A-Za-z0-9_-]+$"));
    if (!usernameRegex.match(username).hasMatch()) {
        result.isValid = false;
        result.errorMessage = "Username can only contain letters, numbers, underscores, and hyphens";
        return result;
    }

    return result;
}

bool Validators::hasUppercase(const QString& str)
{
    for (const QChar& c : str) {
        if (c.isUpper()) {
            return true;
        }
    }
    return false;
}

bool Validators::hasLowercase(const QString& str)
{
    for (const QChar& c : str) {
        if (c.isLower()) {
            return true;
        }
    }
    return false;
}

bool Validators::hasDigit(const QString& str)
{
    for (const QChar& c : str) {
        if (c.isDigit()) {
            return true;
        }
    }
    return false;
}

bool Validators::hasSpecialChar(const QString& str)
{
    const QString specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    for (const QChar& c : str) {
        if (specialChars.contains(c)) {
            return true;
        }
    }
    return false;
}

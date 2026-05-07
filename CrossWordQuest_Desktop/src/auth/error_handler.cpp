#include "error_handler.h"

QString ErrorHandler::mapSupabaseError(const QString& errorMessage, int statusCode)
{
    if (errorMessage.contains("Invalid login credentials", Qt::CaseInsensitive)) {
        return "Invalid email or password";
    }
    if (errorMessage.contains("User already registered", Qt::CaseInsensitive)) {
        return "This email is already registered";
    }
    if (errorMessage.contains("Email not confirmed", Qt::CaseInsensitive)) {
        return "Please confirm your email before logging in";
    }
    if (statusCode == 401) {
        return "Incorrect password";
    }
    if (statusCode == 404) {
        return "Email not found";
    }
    if (statusCode >= 500) {
        return "Server error. Please try again later.";
    }
    return errorMessage.isEmpty() ? "Authentication failed" : errorMessage;
}

QString ErrorHandler::mapValidationError(const QString& validationMessage)
{
    return validationMessage; // Already user-friendly from validators
}

bool ErrorHandler::isEmailError(const QString& errorMessage)
{
    return errorMessage.contains("Email not found", Qt::CaseInsensitive) ||
           errorMessage.contains("already registered", Qt::CaseInsensitive) ||
           errorMessage.contains("invalid email", Qt::CaseInsensitive);
}

bool ErrorHandler::isPasswordError(const QString& errorMessage)
{
    return errorMessage.contains("Incorrect password", Qt::CaseInsensitive) ||
           errorMessage.contains("Invalid login credentials", Qt::CaseInsensitive);
}

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <QString>

class ErrorHandler {
public:
    static QString mapSupabaseError(const QString& errorMessage, int statusCode);
    static QString mapValidationError(const QString& validationMessage);
    static bool isEmailError(const QString& errorMessage);
    static bool isPasswordError(const QString& errorMessage);

private:
    ErrorHandler(); // Private constructor - static class only
};

#endif // ERROR_HANDLER_H

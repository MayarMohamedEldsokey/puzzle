#include <QApplication>
#include <QFont>
#include "auth/auth_manager.h"
#include "ui/login_screen.h"
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set application style and font
    app.setStyle("Fusion");
    QFont font("Inter", 11);
    app.setFont(font);

    // Create a shared AuthManager (owned by the app)
    AuthManager* authManager = new AuthManager(&app);
    // Enable test mode to make login work without Supabase
    authManager->setTestMode(true);

    // Show the standalone login screen first
    LoginScreen* login = new LoginScreen(authManager);
    login->show();

    // When login succeeds, open the main window and close the login screen
    QObject::connect(authManager, &AuthManager::loginSuccess, [login, authManager]() {
        MainWindow* mw = new MainWindow(authManager);
        mw->show();
        if (login) {
            login->close();
        }
    });

    return app.exec();
}

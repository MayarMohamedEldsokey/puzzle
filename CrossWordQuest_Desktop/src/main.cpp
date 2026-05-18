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
    // Disable test mode to use real Supabase authentication
    authManager->setTestMode(false);

    // Show the MainWindow directly. It starts on the Login screen by default
    // and supports seamless switching between Login and Registration!
    MainWindow* mw = new MainWindow(authManager);
    mw->show();

    return app.exec();
}

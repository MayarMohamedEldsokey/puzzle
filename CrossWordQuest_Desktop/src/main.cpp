#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set application style and font
    app.setStyle("Fusion");
    QFont font("Inter", 11);
    app.setFont(font);

    // Create and show main window
    MainWindow window;
    window.show();

    return app.exec();
}

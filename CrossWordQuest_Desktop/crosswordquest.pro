QT += core gui widgets network sql concurrent

CONFIG += c++17

TARGET = CrossWordQuestAuth
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/auth/supabase_client.cpp \
    src/auth/validators.cpp \
    src/auth/auth_manager.cpp \
    src/auth/error_handler.cpp \
    src/ui/login_screen.cpp \
    src/ui/registration_screen.cpp \
    src/models/user_model.cpp

HEADERS += \
    src/mainwindow.h \
    src/auth/supabase_client.h \
    src/auth/validators.h \
    src/auth/auth_manager.h \
    src/auth/error_handler.h \
    src/ui/login_screen.h \
    src/ui/registration_screen.h \
    src/models/user_model.h

RESOURCES += \
    resources/resources.qrc

# Include paths
INCLUDEPATH += src \
               src/auth \
               src/ui \
               src/models

# Platform-specific settings
win32 {
    # Windows settings
}

unix:!macx {
    # Linux settings
}

macx {
    # macOS settings
}

# Enable warnings
CONFIG += warn_on

# Output paths
DESTDIR = bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

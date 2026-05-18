cmake_minimum_required(VERSION 3.16)

project(CrossWordPP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. استدعاء مكتبات الـ Qt المطلوبة للـ UI والـ C++ والربط بينهما
find_package(Qt6 REQUIRED COMPONENTS Quick Widgets QuickWidgets)

qt_standard_project_setup(REQUIRES 6.10)

# 2. إضافة ملفات الـ C++ الخاصة بالـ Dashboard والـ Main
qt_add_executable(appCrossWordPP
    main.cpp
    Homepage.cpp
    Homepage.h
)

# 3. تسجيل موديول الـ QML وكل الصفحات التابعة له بشكل صحيح بدون تكرار
qt_add_qml_module(appCrossWordPP
    URI CrossWordPP
    VERSION 1.0
    QML_FILES
        Main.qml
        DifficultyCard.qml
        LevelsPage.qml
        GameResultPage.qml
)

set_target_properties(appCrossWordPP PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 4. ربط جميع المكتبات بالملف التنفيذي للمشروع
target_link_libraries(appCrossWordPP
    PRIVATE
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickWidgets
)

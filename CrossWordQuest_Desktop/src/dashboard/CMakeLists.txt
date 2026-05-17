cmake_minimum_required(VERSION 3.16)

project(appbuzzle)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup()

qt_add_executable(appbuzzle
    main.cpp
)

target_link_libraries(appbuzzle PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)

# Copy main.qml to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/main.qml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
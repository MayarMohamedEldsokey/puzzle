cmake_minimum_required(VERSION 3.21)
project(CrossWordQuestAuth LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
    Concurrent
    Qml
    Quick
    REQUIRED
)

# Add executable
add_executable(CrossWordQuestAuth
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    
    # Auth layer
    src/auth/supabase_client.h
    src/auth/supabase_client.cpp
    src/auth/validators.h
    src/auth/validators.cpp
    src/auth/auth_manager.h
    src/auth/auth_manager.cpp
    src/auth/error_handler.h
    src/auth/error_handler.cpp
    
    # UI layer
    src/ui/login_screen.h
    src/ui/login_screen.cpp
    src/ui/registration_screen.h
    src/ui/registration_screen.cpp
    
    # Models
    src/models/user_model.h
    src/models/user_model.cpp
    
    # Resources
    resources/resources.qrc
    
    # Game Dashboard (QML & sources)
    src/game/Main.qml
    src/game/main.cpp
    src/game/CMakeLists.txt
)

# Link Qt libraries
target_link_libraries(CrossWordQuestAuth
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::Concurrent
    Qt6::Qml
    Qt6::Quick
)

# Include directories
target_include_directories(CrossWordQuestAuth PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/auth
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/models
)

# Set output directory
set_target_properties(CrossWordQuestAuth PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Automatically copy Main.qml and GameResultPage.qml to the output directory next to the built executable
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/game/Main.qml DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/result/GameResultPage.qml DESTINATION ${CMAKE_BINARY_DIR}/bin)

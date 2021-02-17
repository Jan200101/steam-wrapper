set(NAME ${CMAKE_PROJECT_NAME})

enable_language(CXX)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui REQUIRED)

SET(QT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.hpp
)

add_executable(${NAME} WIN32 ${QT_SOURCES})
target_link_libraries(${NAME} PRIVATE core Qt${QT_VERSION_MAJOR}::Widgets)
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 11)

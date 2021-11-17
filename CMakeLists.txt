cmake_minimum_required(VERSION 3.5)

project(helpme VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

GET_FILENAME_COMPONENT(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

IF(WIN32)
    SET(pathOPENCV C:/obuild/install)
    SET(OpenCV_DIR ${pathOPENCV})
ELSE()
    SET(OpenCV_DIR C:/obuild)
ENDIF()

FIND_PACKAGE( OpenCV REQUIRED )

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(helpme
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET helpme APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(helpme SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(helpme
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(helpme PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(helpme PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(helpme)
endif()



#add



FIND_LIBRARY( gbHealth NAME libgbhealth.a HINTS ${CMAKE_SOURCE_DIR}/libs REQUIRED)

FIND_LIBRARY( gbFace NAME libgbface.a HINTS ${CMAKE_SOURCE_DIR}/libs REQUIRED)

TARGET_INCLUDE_DIRECTORIES( ${ProjectId}
    PRIVATE ${OpenCV_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include

)

TARGET_LINK_LIBRARIES( ${ProjectId}
    PRIVATE ${gbHealth}
    PRIVATE ${gbFace}
    PRIVATE ${OpenCV_LIBS}
)

IF(WIN32)
TARGET_LINK_LIBRARIES(${ProjectId}
    PRIVATE iphlpapi
)
ENDIF()

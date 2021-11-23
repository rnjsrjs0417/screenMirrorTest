<<<<<<< HEAD
cmake_minimum_required(VERSION 3.5)


project(screenMirrorTest VERSION 0.1 LANGUAGES CXX)

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
        netconnection.cpp
        netconnection.h
        recvthread.cpp
        recvthread.h
        secdialog.hpp
        secdialog.cpp
        secdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(screenMirrorTest
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET screenMirrorTest APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(screenMirrorTest SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(screenMirrorTest
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(screenMirrorTest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(screenMirrorTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(screenMirrorTest)
endif()



#add

target_link_libraries(${ProjectId} PUBLIC pthread)
target_link_libraries(${ProjectId} PUBLIC ws2_32)


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
=======
cmake_minimum_required(VERSION 3.5)

project(qtlib VERSION 0.1 LANGUAGES CXX)

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
    SET(OpenCV_DIR C:/obuild/install)


ELSE()
    SET(OpenCV_DIR C:/obuild)
ENDIF()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        secdialog.cpp
        secdialog.hpp
        secdialog.ui
        netconnection.cpp
        netconnection.h
        recvthread.cpp
        recvthread.h
)

FIND_PACKAGE( OpenCV REQUIRED )

SET(CMAKE_CXX_FLAGS "-fopenmp ${CMAKE_CXX_FLAGS}")

FIND_LIBRARY( gbHealth NAME libgbhealth.a HINTS ${CMAKE_SOURCE_DIR}/libs REQUIRED)

FIND_LIBRARY( gbFace NAME libgbface.a HINTS ${CMAKE_SOURCE_DIR}/libs REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qtlib
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qtlib APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qtlib SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qtlib
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qtlib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qtlib PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qtlib)
endif()

TARGET_INCLUDE_DIRECTORIES( ${ProjectId}
    PRIVATE ${OpenCV_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include

)

TARGET_LINK_LIBRARIES( ${ProjectId}
    PRIVATE ${gbHealth}
    PRIVATE ${gbFace}
    PRIVATE ${OpenCV_LIBS}
>>>>>>> fbca8041db033b145428070811c624f39f4cb251
)

target_link_libraries(${ProjectId} PUBLIC pthread)
target_link_libraries(${ProjectId} PUBLIC ws2_32)

IF(WIN32)
TARGET_LINK_LIBRARIES(${ProjectId}
    PRIVATE iphlpapi
)

ENDIF()

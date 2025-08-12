cmake_minimum_required(VERSION 3.16)

project(MonitoringStation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(Boost_DEBUG 1)
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/local/boost_1_88_0")
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/local/boost_1_88_0/lib64-msvc-14.3")
set(Boost_COMPILER -vc143)
set(Boost_ARCHITECTURE -x64)
#set(BOOST_ROOT C:/local/boost_1_88_0)
#set(BOOST_NO_SYSTEM_PATHS ON)

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost REQUIRED COMPONENTS json)
include_directories(${BOOST_INCLUDE_DIRS})



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#find_package(Boost REQUIRED) #COMPONENTS serialization CONFIG HINTS C:/local/boost_1_88_0/lib64-msvc-14.3/cmake)


#include_directories(${Boost_INCLUDE_DIRS})




set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        broadcast_receiver.cpp
        broadcast_receiver.hpp
        monitoring_station.cpp
        monitoring_station.hpp
        listitemwidget.h
        listitemwidget.cpp
        car.hpp
        car.cpp
        unicast_sender.hpp
        unicast_sender.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MonitoringStation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        broadcast_receiver.hpp broadcast_receiver.cpp
        ListItemWidget.h
        listitemwidget.h listitemwidget.cpp

        monitoring_station.hpp
        car.hpp car.cpp
        unicast_sender.hpp unicast_sender.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MonitoringStation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MonitoringStation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MonitoringStation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MonitoringStation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MonitoringStation PRIVATE Ws2_32)
target_link_libraries(MonitoringStation PRIVATE Boost::json)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MonitoringStation)
endif()
set_target_properties(MonitoringStation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MonitoringStation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MonitoringStation)
endif()

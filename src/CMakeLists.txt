cmake_minimum_required(VERSION 3.5)

project(TameCalc VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_ARCH_TARGET "amd64")

set(PROJECT_SOURCES
        main.cc
        view/mainwindow.cc
        view/mainwindow.h
        view/mainwindow.ui
        controller/controller.h
        model/main_model.cc
        model/main_model.h
        )

set(PROJECT_BUILD_OUTPUT ${CMAKE_SOURCE_DIR}/build/output/${PROJECT_ARCH_TARGET}/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BUILD_OUTPUT}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/resources)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/resources)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/resources)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TameCalc
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET TameCalc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TameCalc SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TameCalc
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(TameCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TameCalc PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

install(TARGETS TameCalc
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TameCalc)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE qcustomplot)

# Compile needed definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_USE_LIBRARY)

add_subdirectory(resources)

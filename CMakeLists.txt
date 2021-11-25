cmake_minimum_required(VERSION 3.14)

project(QtHotReloadTemplate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets LinguistTools REQUIRED)
find_package(Qt6 COMPONENTS Core Quick Widgets LinguistTools REQUIRED)

set(TS_FILES QtHotReloadTemplate_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        interceptor.h
        interceptor.cpp
        qml.qrc
        file_watcher.cpp
        file_watcher.h
        qml_engine.cpp
        qml_engine.h
        ${TS_FILES}
)
    qt_add_executable(QtHotReloadTemplate
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})   

target_compile_definitions(QtHotReloadTemplate
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QtHotReloadTemplate
  PRIVATE Qt6::Core Qt6::Quick  Qt6::Widgets Qt6::Qml)

set_target_properties(QtHotReloadTemplate PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
add_custom_command(
    TARGET QtHotReloadTemplate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Quick>
        $<TARGET_FILE:Qt6::Qml>
        $<TARGET_FILE:Qt6::Gui>
        $<TARGET_FILE:Qt6::Network>
        $<TARGET_FILE_DIR:QtHotReloadTemplate>
)
qt_import_qml_plugins(QtHotReloadTemplate)
qt_finalize_executable(QtHotReloadTemplate)

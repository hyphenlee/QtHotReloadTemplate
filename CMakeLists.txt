cmake_minimum_required(VERSION 4.2)
project(QtHotReloadTemplate VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
add_compile_definitions("$<$<CONFIG:Debug>:DEBUG=1> QT_DEBUG_PLUGINS")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick Widgets LinguistTools Quick3D REQUIRED)

set(TS_FILES QtHotReloadTemplate_zh_CN.ts)
set(PROJECT_SOURCES
        main.cpp
        qml.qrc
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
  PRIVATE qhotreload)

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
        $<TARGET_FILE:Qt6::Quick3D>
        $<TARGET_FILE_DIR:QtHotReloadTemplate>
)
qt_import_qml_plugins(QtHotReloadTemplate)
qt_finalize_executable(QtHotReloadTemplate)
add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")
subdirs(lib)
# Get the Qt plugins/platforms directory
get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QT_ROOT_DIR "${QT_BIN_DIR}/.." ABSOLUTE)
set(QT_PLUGIN_DIR "${QT_ROOT_DIR}/plugins")
set(QT_PLATFORMS_DIR "${QT_PLUGIN_DIR}/platforms")
add_custom_command(TARGET QtHotReloadTemplate POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:QtHotReloadTemplate>/platforms"
  COMMAND ${CMAKE_COMMAND} -E copy_if_newer
  "${QT_PLATFORMS_DIR}/qwindows$<$<CONFIG:Debug>:d>.dll"
  "$<TARGET_FILE_DIR:QtHotReloadTemplate>/platforms"
)
set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT QtHotReloadTemplate)

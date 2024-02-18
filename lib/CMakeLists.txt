qt_add_library(qhotreload
  file_watcher.h
  file_watcher.cpp
  interceptor.h
  interceptor.cpp
  qml_engine.h
  qml_engine.cpp
)
target_link_libraries(qhotreload Qt6::Core Qt6::Quick  Qt6::Widgets Qt6::Qml Qt6::Quick3D )

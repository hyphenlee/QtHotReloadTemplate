#include "interceptor.h"
#include <qglobal.h>

Interceptor::Interceptor() {}

Interceptor &Interceptor::get_instance() {
  static Interceptor self;
  return self;
}

QUrl Interceptor::intercept(const QUrl &path, DataType type) {
  if (type == DataType::QmlFile) {
    auto str = path.toString();
    auto contain = str.contains("file:///"); // filter out qrc file
    if (contain && AddWatchFile) {
      AddWatchFile(path.toString());
      qDebug() << "add watch file:" << path.toString();
    }
  }
  return path;
}

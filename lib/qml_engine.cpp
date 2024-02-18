#include "qml_engine.h"
#include "interceptor.h"
#include <qstringliteral.h>
#include <qurl.h>
QmlEngine::QmlEngine() {
  auto &interceptor = Interceptor::get_instance();
  interceptor.AddWatchFile = [this](QString url) {
    qDebug() << "add file:" << url;
    this->watcher_.AddFile(url);
  };
  watcher_.CleanEngine = [this]() {
    qDebug() << "clear engine";
    this->trimComponentCache();
    this->clearComponentCache();
    auto *obj = this->rootObjects().at(0);
    QMetaObject::invokeMethod(obj, "reload");
  };
  this->addUrlInterceptor(&interceptor);
}

QmlEngine::QmlEngine(QObject *parent) : QQmlApplicationEngine(parent) {}

QmlEngine &QmlEngine::get_instance() {
  static QmlEngine engine;
  return engine;
}

void QmlEngine::loadRelativePath(const QString &filePath) {
  qDebug()<<"load file:"<<filePath;
  QUrl url;
#ifdef DEBUG
  qDebug() << "debug mode";
  url = project_root_ + QString("/") + filePath;
#else
  qDebug() << "release mode";
  url = QString("qrc:/") + filePath;
#endif
  QQmlApplicationEngine::load(url);
}

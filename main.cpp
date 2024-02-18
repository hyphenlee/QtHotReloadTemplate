#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "lib/qml_engine.h"
#include <QLocale>
#include <QTranslator>
#include <qglobal.h>
#ifndef PROJECT_ROOT
#define PROJECT_ROOT ""
#endif
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QTranslator translator;
  QString project_root = PROJECT_ROOT;
  qDebug() << "project root:" << project_root;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "QtHotReloadTemplate_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      app.installTranslator(&translator);
      break;
    }
  }
  QmlEngine engine;
  engine.setProjectRoot(project_root);
  QString relative_path = "main.qml";
  // QObject::connect(
  //     &engine, &QQmlApplicationEngine::objectCreated, &app,
  //     [url](QObject *obj, const QUrl &objUrl) {
  //       if (!obj && url == objUrl)
  //         QCoreApplication::exit(-1);
  //     },
  //     Qt::QueuedConnection);
  engine.loadRelativePath(relative_path);
  return app.exec();
}

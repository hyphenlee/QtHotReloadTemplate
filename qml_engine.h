#pragma once
#include <QQmlApplicationEngine>
#include"file_watcher.h"
class QmlEngine:public QQmlApplicationEngine
{
    Q_OBJECT
public:
    QmlEngine();
    QmlEngine(QObject*parent);
    QmlEngine&get_instance();

//    void load(const QString &filePath);
private:
    FileWatcher watcher_;
};

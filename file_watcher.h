#pragma once

#include <QObject>
#include <QString>
#include <QFileSystemWatcher>
#include <QQmlApplicationEngine>
#include<functional>

class FileWatcher:public QObject
{
    Q_OBJECT
public:
    FileWatcher();
    void AddFile(QString file_path);
    std::function<void()> CleanEngine;
public slots:
    void onFileChanged(QString file);
signals:
    void statusChanged();
private:
        QFileSystemWatcher watcher_;
        QStringList file_list_;

};

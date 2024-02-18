#include "file_watcher.h"
#include <QFileInfo>
FileWatcher::FileWatcher()
{
    connect(&watcher_, SIGNAL(fileChanged(QString)), this, SLOT(onFileChanged(QString)));
}

void FileWatcher::AddFile(QString file_path)
{
    QString file = file_path;
  #ifdef Q_OS_WIN
      QFileInfo fileInfo(file.remove("file:///"));
  #endif

  #ifdef Q_OS_UNIX
      QFileInfo fileInfo(file.remove("file://"));
  #endif

      if (fileInfo.isFile()) {
          watcher_.addPath(file);
          if (!file_list_.contains(file))
              file_list_.append(file);
          emit statusChanged();
      }
}

void FileWatcher::onFileChanged(QString file)
{
    qDebug()<<"file changed:"<<file;
    if(CleanEngine)CleanEngine();
}

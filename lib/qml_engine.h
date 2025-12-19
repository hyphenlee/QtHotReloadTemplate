#pragma once
#include "file_watcher.h"
#include <QQmlApplicationEngine>
class QmlEngine : public QQmlApplicationEngine {
	Q_OBJECT
public:
	QmlEngine();
	QmlEngine(QObject* parent);
	QmlEngine& get_instance();
	void loadRelativePath(const QString& filePath);
	Q_INVOKABLE QString GetRootPath() const { return "file:///"+project_root_; }
	void setProjectRoot(QString project_root) { project_root_ = project_root; }

private:
	FileWatcher watcher_;
	QString project_root_;

	QUrl root_url_;
};

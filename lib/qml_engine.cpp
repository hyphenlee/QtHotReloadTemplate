#include "qml_engine.h"

#include <qcoreapplication.h>

#include "interceptor.h"
#include <qstringliteral.h>
#include <qurl.h>
#include<qdir.h>
#include <QJSEngine>
#include <QQmlContext>
#include <QProcessEnvironment>
QmlEngine::QmlEngine() {
	auto& interceptor = Interceptor::get_instance();
	interceptor.AddWatchFile = [this](QString url) {
		qDebug() << "add file:" << url;
		this->watcher_.AddFile(url);
		};
	watcher_.CleanEngine = [this]() {
		qDebug() << "clear engine";
		//for (auto obj:rootObjects())
		//{
		//	obj->deleteLater();
		//}
		auto* obj = this->rootObjects().at(0);
		QMetaObject::invokeMethod(obj, "clear");
		//obj->deleteLater();
//		this->trimComponentCache();
		QCoreApplication::processEvents();
		this->clearComponentCache();
		QCoreApplication::processEvents();
		QMetaObject::invokeMethod(obj, "reload");
		//		QQmlApplicationEngine::load(root_url_);
		};
	this->addUrlInterceptor(&interceptor);

	// Expose environment access to QML as a context property named "Env"
	this->rootContext()->setContextProperty("Env", this);
}

QmlEngine::QmlEngine(QObject* parent) : QQmlApplicationEngine(parent) {}

QmlEngine& QmlEngine::get_instance() {
	static QmlEngine engine;
	return engine;
}

void QmlEngine::loadRelativePath(const QString& filePath) {
	qDebug() << "load file:" << filePath;
#ifdef DEBUG
	qDebug() << "debug mode";
	root_url_ = QUrl::fromLocalFile(project_root_ + QDir::separator() + filePath);
#else
	qDebug() << "release mode";
	url = QString("qrc:/") + filePath;
#endif
	//url = QString("file:///c:/work/QtHotReloadTemplate/main.qml");
	QQmlApplicationEngine::load(root_url_);
}

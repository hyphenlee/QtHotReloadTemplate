#include "qml_engine.h"
#include"interceptor.h"
QmlEngine::QmlEngine()
{
    auto&interceptor=Interceptor::get_instance();
    interceptor.AddWatchFile=[this](QString url){
        qDebug()<<"add file:"<<url;
        this->watcher_.AddFile(url);
    };
    watcher_.CleanEngine=[this](){
        qDebug()<<"clear engine";
         this->trimComponentCache();
        this->clearComponentCache();
        auto *obj=this->rootObjects().at(0);
        QMetaObject::invokeMethod(obj, "reload");
    };
    this->addUrlInterceptor(&interceptor);

}

QmlEngine::QmlEngine(QObject*parent)
    :QQmlApplicationEngine(parent)
{

}

QmlEngine &QmlEngine::get_instance()
{
static QmlEngine engine;
return engine;
}

//void QmlEngine::load(const QString &filePath)
//{
//    QQmlApplicationEngine::load(filePath);


//}

#include "interceptor.h"

Interceptor::Interceptor()
{

}

Interceptor &Interceptor::get_instance()
{
    static Interceptor self;
    return self;
}

QUrl Interceptor::intercept(const QUrl &path, DataType type)
{
    if(type==DataType::QmlFile){
        qDebug()<<"add path:"<<path;
        if(AddWatchFile)AddWatchFile(path.toString());
    }
    return path;
}

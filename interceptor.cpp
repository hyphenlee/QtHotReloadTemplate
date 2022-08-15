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
        auto str = path.toString();
        auto contain = str.contains("file:///");
        if(contain&&AddWatchFile)AddWatchFile(path.toString());
    }
    return path;
}

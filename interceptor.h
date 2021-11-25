#pragma once

#include <QQmlAbstractUrlInterceptor>
#include <QQmlEngine>
class Interceptor:public QObject, public QQmlAbstractUrlInterceptor
{
    Q_OBJECT
public:
    Interceptor();
    static Interceptor& get_instance();
    virtual QUrl intercept(const QUrl &path, DataType type) override;
    std::function<void(QString) >AddWatchFile;
};


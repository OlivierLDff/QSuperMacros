#ifndef QQMLSINGLETONHELPER_H
#define QQMLSINGLETONHELPER_H

#include <QObject>
#include <QJSEngine>
#include <QQmlEngine>

#define QML_SINGLETON_IMPL(CLASS) \
    Q_OBJECT \
    public: \
        static CLASS & instance (void) { \
            static CLASS ret; \
            return ret; \
        } \
        static QObject * qmlSingletonFactory (QQmlEngine * qmlEngine, QJSEngine * jsEngine) { \
            Q_UNUSED (jsEngine) \
            Q_UNUSED (qmlEngine) \
            QObject * ret = &instance (); \
            QQmlEngine::setObjectOwnership (ret, QQmlEngine::CppOwnership); \
            return ret; \
        } \
        static void registerQmlModule (const char * uri, const int majorVersion, const int minorVersion, const char * name) { \
            qmlRegisterSingletonType<CLASS> (uri, majorVersion, minorVersion, name, &CLASS::qmlSingletonFactory); \
        } \
    private: \
        explicit CLASS (void);

class _test_QmlSingleton_ : public QObject {
    QML_SINGLETON_IMPL (_test_QmlSingleton_)
};

#endif // QQMLSINGLETONHELPER_H

/**
 * \file QQmlSingletonHelper.h
 * \brief Declare Singleton Instancier Helper 
 */
#ifndef QQMLSINGLETONHELPER_H
#define QQMLSINGLETONHELPER_H

#include <QObject>
#include <QJSEngine>
#include <QQmlEngine>
#include <qqml.h>

#include <QSuperMacros.h>
#include <QQmlHelpersCommon.h>

QSUPERMACROS_NAMESPACE_START

/**
 * \defgroup QSM_SINGLETON_HELPER Singleton Properties
 * \brief Macros to generate Singleton properties without the need to handle the factory
 */
/** 
 * Generate a singleton
 * \ingroup QSM_SINGLETON_HELPER
 * \hideinitializer
 * \param Class Singleton class to generate
 * \param Name Name used to generate unique function for the singleton
 * 
 *  The code generated look like that:
 *  \code
 *  public:
 *      static Class& GetName(void)
 *      {
 *          static Class res;
 *          return res;
 *      }
 *      static QObject* SetNameFactory(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
 *      {
 *          QObject* res = &GetName();
 *          QQmlEngine::setObjectOwnership (ret, QQmlEngine::CppOwnership);
 *          return res;
 *      }
 *      static void registerNameQmlModule (const char * uri, const int majorVersion, const int minorVersion, const char * name)
 *      {
 *          qmlRegisterSingletonType<Class> (uri, majorVersion, minorVersion, name, &Class::SetNameFactory);
 *      }
 *  \endcode
 *
 * It can then be used like that :
 *  \code
 *      // Declare a singleton
 *      class SingletonHandler 
 *      { 
 *          Q_OBJECT
 *          QSM_SINGLETON_IMPL(MyClass, instance, Instance) ; 
 *      }
 * 
 *      // Register the singleton
 *      SingletonHandler::registerInstanceQmlModule("Library", 1, 0, "SingletonName");
 *
 *      // Get the instnace
 *      MyClass& instance = SingletonHandler::GetInstance();
 *  \endcode
 */
#define QSM_SINGLETON_IMPL(Class, name, Name) \
    public: \
        static Class & QSM_MAKE_GETTER_NAME(name, Name) (void) { \
            static Class ret; \
            return ret; \
        } \
        static QObject * QSM_MAKE_SETTER_NAME(name, Name)##Factory (QQmlEngine * qmlEngine, QJSEngine * jsEngine) { \
            Q_UNUSED (jsEngine) \
            Q_UNUSED (qmlEngine) \
            QObject * ret = &QSM_MAKE_GETTER_NAME(name, Name) (); \
            QQmlEngine::setObjectOwnership (ret, QQmlEngine::CppOwnership); \
            return ret; \
        } \
        static void registerSingleton (const char * uri, const int majorVersion, const int minorVersion, const char * n = #Class) { \
            qmlRegisterSingletonType<Class> (uri, majorVersion, minorVersion, n, &Class::QSM_MAKE_SETTER_NAME(name, Name)##Factory); \
        } \

/**
 * \internal _Test_QmlSingleton_
 */
class _Test_QmlSingleton_ : public QObject 
{
	Q_OBJECT
	/**
	 * \internal _Test_QmlSingleton_
	 */
	QSM_SINGLETON_IMPL(_Test_QmlSingleton_, instance, Instance);
};

QSUPERMACROS_NAMESPACE_END

#endif // QQMLSINGLETONHELPER_H

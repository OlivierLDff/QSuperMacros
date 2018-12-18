/**
 * \file QQmlEnumClassHelper.h
 * \brief Declare Enum Class Helper
 */
#ifndef QQMLENUMCLASS
#define QQMLENUMCLASS

#include <QObject>
#include <QString>
#include <QQmlEngine>
#include <QMetaEnum>
#include <QMetaObject>
#include <qqml.h>

#include "QSuperMacros.h"

 /**
  * \defgroup QSM_ENUM_HELPER Enum Class
  * \brief Macros to generate an Enum Class exposed to Qml Engine
  */

/** \def QSM_EXPORT_ENUM Export Enum for qt moc
 * \ingroup QSM_ENUM_HELPER */
#ifdef Q_ENUM
#   define QSM_EXPORT_ENUM Q_ENUM
#else
#   define QSM_EXPORT_ENUM Q_ENUMS
#endif

/**
 * \def QSM_ENUM_CLASS(Name, Namespace, ...)
 * \ingroup QSM_ENUM_HELPER_NAMESPACE
 * \hideinitializer
 * \details Creates a class that contains a C++ enum that can be exposed to QML.
 * \param Name The name for the class
 * \param Namespace The namespace that is going to be auto append to the qml type name when setting default name
 * \param ... The variadic list of values for the enum (comma-separated)
 * 
 * It generates for this goal :
 * * The \c {name} C++ QObject-derived class
 * * The \c {name}::Type enumeration containing the values list
 * * The \c Q_ENUMS macro call to allow QML usage
 *
 * Example in use :
 * \code
 *      // Declare the enum
 *      QSM_ENUM_CLASS_NAMESPACE (DaysOfWeek, WkNamespace, Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday)
 *      
 *      // Register to the qml engine
 *      WkNamespace::DaysOfWeek::RegisterToQml("MyUri", 1, 0, "Name") 
 *      
 *      // Register with the name WkNamespaceDaysOfWeek
 *      WkNamespace::DaysOfWeek::RegisterToQml("MyUri", 1, 0) 
 *
 *      // Get Value as string
 *      QString val = WkNamespace::DaysOfWeek::AsString(Monday); // Return "Monday"
 * \endcode
 * 
 * Then in QML you can to
 * \code
 * import MyUri 1.0
 * 
 * property int foo = WkNamespaceDaysOfWeek.Monday // foo === 1
 * \endcode
 * 
 * \note The QML registration using \c qmlRegisterUncreatableType() will still be needed.
 */
#define QSM_ENUM_CREATE_TYPE_NAME(Name, Namespace) #Namespace #Name
#define QSM_ENUM_CLASS_NAMESPACE(Name, Namespace, ...) \
    struct Name { \
        Q_GADGET \
        public: \
			/** Enum Type */ \
            enum Type { \
                __VA_ARGS__ \
            }; \
            QSM_EXPORT_ENUM (Type) \
            static QString AsString (const int value) { \
                return QString::fromLatin1 (staticMetaObject.enumerator (0).valueToKey (value)); \
            } \
            static void RegisterToQml (const char * uri, const int majorVersion, const int minorVersion, const char * name, const char* enumName) { \
                qmlRegisterUncreatableType<Name> (uri, majorVersion, minorVersion, name, "Enum class, can't be instanciated !"); \
            } \
            static void RegisterToQml (const char * uri, const int majorVersion, const int minorVersion) { \
                qmlRegisterUncreatableType<Name> (uri, majorVersion, minorVersion, QSM_ENUM_CREATE_TYPE_NAME(Name, Namespace), "Enum class, can't be instanciated !"); \
            } \
        public: \
            explicit Name (void) { } \
            Name (const Name &); \
            Name & operator= (const Name &); \
    }; \

/**
 * \def QSM_ENUM_CLASS(Name, ...)
 * \ingroup QSM_ENUM_HELPER
 * \hideinitializer
 * \details Creates a class that contains a C++ enum that can be exposed to QML.
 * \param Name The name for the class
 * \param ... The variadic list of values for the enum (comma-separated)
 *
 * It generates for this goal :
 * * The \c {name} C++ QObject-derived class
 * * The \c {name}::Type enumeration containing the values list
 * * The \c Q_ENUMS macro call to allow QML usage
 *
 * Example in use :
 * \code
 *      // Declare the enum
 *      QSM_ENUM_CLASS (DaysOfWeek, Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday)
 *
 *      // Register to the qml engine
 *      DaysOfWeek::RegisterToQml("MyUri", 1, 0, "Name")
 *      
 *      // Register with the name DaysOfWeek
 *      DaysOfWeek::RegisterToQml("MyUri", 1, 0)
 *
 *      // Get Value as string
 *      QString val = DaysOfWeek::AsString(Monday); // Return "Monday"
 * \endcode
 *
 * Then in QML you can to
 * \code
 * import MyUri 1.0
 *
 * property int foo = DaysOfWeek.Monday // foo === 1
 * \endcode
 *
 * \note The QML registration using \c qmlRegisterUncreatableType() will still be needed.
 */
#define QSM_ENUM_CLASS(Name, ...) QSM_ENUM_CLASS_NAMESPACE(Name, , __VA_ARGS__)

QSUPER_MACROS_NAMESPACE_START

/**
 * \internal
 */
QSM_ENUM_CLASS_NAMESPACE(_Test_QmlNamespaceEnumClass_, QSUPER_MACROS_NAMESPACE, Value0, Value1, Value3=3) // NOTE : to avoid "no suitable class found" MOC note
QSM_ENUM_CLASS(_Test_QmlEnumClass_, Value0, Value1, Value3 = 3); // NOTE : to avoid "no suitable class found" MOC note

QSUPER_MACROS_NAMESPACE_END

#endif // QQMLENUMCLASS


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
 *      QML_ENUM_CLASS (DaysOfWeek, Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday)
 *      
 *      // Register to the qml engine
 *      DaysOfWeek::RegisterToQml("Library", 1, 0, "Name")   
 *
 *      // Get Value as string
 *      QString val = DaysOfWeek::AsString(Monday); // Return "Monday"
 * \endcode
 * 
 * \note The QML registration using \c qmlRegisterUncreatableType() will still be needed.
 */
#define QSM_ENUM_CLASS(Name, ...) \
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
            static void RegisterToQml (const char * uri, const int majorVersion, const int minorVersion, const char * name) { \
                qmlRegisterUncreatableType<Name> (uri, majorVersion, minorVersion, name, "Enum class, can't be instanciated !"); \
            } \
        private: \
            explicit Name (void) { } \
            Name (const Name &); \
            Name & operator= (const Name &); \
    }; \
    Q_DECLARE_METATYPE (Name::Type)

QSM_ENUM_CLASS (_Test_QmlEnumClass_) // NOTE : to avoid "no suitable class found" MOC note

#endif // QQMLENUMCLASS


/**
 * \file QQmlAutoPropertyHelpers.h
 * \brief Declare Auto Properties Helper
 */
#ifndef QQMLAUTOPROPERTYHELPERS_H
#define QQMLAUTOPROPERTYHELPERS_H

#include <QObject>

#include "QQmlHelpersCommon.h"

QSUPER_MACROS_NAMESPACE_START

 /**
  * \defgroup QSM_AUTO_HELPER Auto Properties
  * \brief Macros to generate Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
  * deciding itself which type is the cheapest (using some template trickery internally).
  */

// NOTE : individual macros for getter, setter, notifier, and member

/** 
 * Generate a Getter in the form `Get<Name>`
 * To have a Qt-ish Getter (ie `<name>()`), define `QSUPER_MACROS_USE_QT_GETTERS` in your build system
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      CheapestType<type>::type_def GetName(void) const { return _name; }
 *
 *      // Qt Naming Convention
 *      CheapestType<type>::type_def name(void) const { return m_name; }
 *  \endcode
 */
#define QSM_AUTO_GETTER(type, name, Name) \
    QSUPER_MACROS_NAMESPACE::CheapestType<type>::type_def QSM_MAKE_GETTER_NAME(name, Name) (void) const \
    { \
        return QSM_MAKE_ATTRIBUTE_NAME(name, Name); \
    }

/** Generate a Setter in the form `Set<Name>`
 * To have a Qt-ish Setter (ie `set<Name>()`), define `QSUPER_MACROS_USE_QT_SETTERS` in your build system
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      bool SetName(CheapestType<type>::type_def name) 
 *      {
 *          if(_name != name)
 *          {
 *              _name = name;
 *              emit NameChanged();
 *          }
 *          else 
 *              return false;
 *      }
 *
 *      // Qt Naming Convention
 *      bool setName(CheapestType<type>::type_def name) 
 *      {
 *          if(m_name != name)
 *          {
 *              m_name = name;
 *              emit nameChanged();
 *          }
 *          else 
 *              return false;
 *      }
 *  \endcode
 */
#define QSM_AUTO_SETTER(type, name, Name) \
    bool QSM_MAKE_SETTER_NAME(name, Name) (QSUPER_MACROS_NAMESPACE::CheapestType<type>::type_def name) \
    { \
        if (QSM_MAKE_ATTRIBUTE_NAME(name, Name) != name) { \
            QSM_MAKE_ATTRIBUTE_NAME(name, Name) = name; \
            emit QSM_MAKE_SIGNAL_NAME(name, Name) (); \
            return true; \
        } \
        else \
            return false; \
    }

/** 
 * Generate a Signal in the form `<Name>Changed()`
 * To have a Qt-ish Signal (ie `<name>Changed()`), define `QSUPER_MACROS_USE_QT_SIGNALS` in your build system
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase 
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      void NameChanged();
 *
 *      // Qt Naming Convention
 *      void nameChanged();
 *  \endcode
 */
#define QSM_AUTO_NOTIFIER(type, name, Name) \
    void QSM_MAKE_SIGNAL_NAME(name, Name) (void);

/** Generate a member in the form `_<name>`
 * To have a Qt-ish member (ie `m_<name>`), define `QSUPER_MACROS_USE_QT_PREFIX` in your build system
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      type _name = def;
 *
 *      // Qt Naming Convention
 *      type m_name = def;
 *  \endcode
 */
#define QSM_AUTO_MEMBER(type, name, Name, def) \
    type QSM_MAKE_ATTRIBUTE_NAME(name, Name) = def;

// NOTE : Actual Helpers

/** Generate a **Writable** Auto Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *           Q_PROPERTY (type name READ GetName WRITE SetName NOTIFY NameChanged)
 *      private:
 *             type _name = def;
 *      public:
 *          CheapestType<type>::type_def GetName() const { return _name; }
 *          bool SetName(CheapestType<type>::type_def name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *			void NameChanged();
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name WRITE setName NOTIFY nameChanged)
 *      private:
 *          type m_name = def;
 *      public:
 *          CheapestType<type>::type_def name() const { return m_name; }
 *          bool setName(CheapestType<type>::type_def name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged();
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a pointer to a QObject, default to nullptr
 *  QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT(QObject*, myObject, MyObject, nullptr);
 *  \endcode 
 */
#define QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
        Q_PROPERTY (type name READ QSM_MAKE_GETTER_NAME(name, Name) WRITE QSM_MAKE_SETTER_NAME(name, Name) NOTIFY QSM_MAKE_SIGNAL_NAME(name, Name)) \
    private: \
        QSM_AUTO_MEMBER (type, name, Name, def) \
    public: \
        QSM_AUTO_GETTER (type, name, Name) \
        QSM_AUTO_SETTER (type, name, Name) \
    Q_SIGNALS: \
        QSM_AUTO_NOTIFIER (type, name, Name) \
    private:

/** Generate a **Writable** Auto Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName WRITE SetName NOTIFY NameChanged)
 *      private:
 *          type _name = {}};
 *      public:
 *          CheapestType<type>::type_def GetName() const { return _name; }
 *          bool SetName(CheapestType<type>::type_def name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged();
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name WRITE setName NOTIFY nameChanged)
 *      private:
 *          type m_name = {};
 *      public:
 *          CheapestType<type>::type_def name() const { return m_name; }
 *          bool setName(CheapestType<type>::type_def name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged();
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default to {}
 *  QSM_WRITABLE_AUTO_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default to {}
 *  QSM_WRITABLE_AUTO_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a pointer to a QObject default to {}
 *  QSM_WRITABLE_AUTO_PROPERTY(QObject*, myObject, MyObject);
 *  \endcode 
 */
#define QSM_WRITABLE_AUTO_PROPERTY(type, name, Name) \
        QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT(type, name, Name, {})

/** Generate a **Read-Only** Auto Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName NOTIFY NameChanged)
 *      private:
 *          type _name = def;
 *      public:
 *          CheapestType<type>::type_def GetName() const { return _name; }
 *          bool SetName(CheapestType<type>::type_def name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged();
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name NOTIFY nameChanged)
 *      private:
 *          type m_name = def;
 *      public:
 *          CheapestType<type>::type_def name() const { return m_name; }
 *          bool setName(CheapestType<type>::type_def name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged();
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_READONLY_AUTO_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_READONLY_AUTO_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a pointer to a QObject, default to nullptr
 *  QSM_READONLY_AUTO_PROPERTY_WDEFAULT(QObject*, myObject, MyObject, nullptr);
 *  \endcode 
 */
#define QSM_READONLY_AUTO_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
        Q_PROPERTY (type name READ QSM_MAKE_GETTER_NAME(name, Name) NOTIFY QSM_MAKE_SIGNAL_NAME(name, Name)) \
    private: \
        QSM_AUTO_MEMBER (type, name, Name, def) \
    public: \
        QSM_AUTO_GETTER (type, name, Name) \
        QSM_AUTO_SETTER (type, name, Name) \
    Q_SIGNALS: \
        QSM_AUTO_NOTIFIER (type, name, Name) \
    private:

/** Generate a **Read-Only** Auto Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName NOTIFY NameChanged)
 *      private:
 *          type _name = {};
 *      public:
 *          CheapestType<type>::type_def GetName() const { return _name; }
 *          bool SetName(CheapestType<type>::type_def name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged();
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name NOTIFY nameChanged)
 *      private:
 *          type m_name = {};
 *      public:
 *          CheapestType<type>::type_def name() const { return m_name; }
 *          bool setName(CheapestType<type>::type_def name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged();
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default to {}
 *  QSM_READONLY_AUTO_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default to {}
 *  QSM_READONLY_AUTO_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a pointer to a QObject default to {}
 *  QSM_READONLY_AUTO_PROPERTY(QObject*, myObject, MyObject);
 *  \endcode 
 */
#define QSM_READONLY_AUTO_PROPERTY(type, name, Name) \
        QSM_READONLY_AUTO_PROPERTY_WDEFAULT(type, name, Name, {})

/** Generate a **Const** Auto Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName CONSTANT)
 *      private:
 *          type _name = def;
 *      public:
 *          CheapestType<type>::type_def GetName() const { return _name; }
 *          bool SetName(CheapestType<type>::type_def name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged();
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name CONSTANT)
 *      private:
 *          type m_name = def;
 *      public:
 *          CheapestType<type>::type_def name() const { return m_name; }
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a pointer to a QObject, default to nullptr
 *  QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT(QObject*, myObject, MyObject, nullptr);
 *      private:
 *  \endcode 
 */
#define QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
        Q_PROPERTY (type name READ QSM_MAKE_GETTER_NAME(name, Name) CONSTANT) \
    private: \
        QSM_AUTO_MEMBER (type, name, Name, def) \
    public: \
        QSM_AUTO_GETTER (type, name, Name) \
    private:

/** Generate a **Const** Auto Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_AUTO_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName CONSTANT)
 *      private:
 *          type _name = {};
 *      public:
 *          CheapestType<type>::type_def GetName() const { return _name; }
 *          bool SetName(CheapestType<type>::type_def name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged();
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged();
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name CONSTANT)
 *      private:
 *          type m_name = {};
 *      public:
 *          CheapestType<type>::type_def name() const { return m_name; }
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default to {}
 *  QSM_CONSTANT_AUTO_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default to {}
 *  QSM_CONSTANT_AUTO_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a pointer to a QObject default to {}
 *  QSM_CONSTANT_AUTO_PROPERTY(QObject*, myObject, MyObject);
 *  \endcode
 */
#define QSM_CONSTANT_AUTO_PROPERTY(type, name, Name) \
        QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT(type, name, Name, {})

// NOTE : test class for all cases

/**
 * Test class for auto properties
 * \internal
 */
class QSUPER_MACROS_API_ _Test_QmlAutoProperty_ : public QObject 
{
	Q_OBJECT

	QSM_WRITABLE_AUTO_PROPERTY(bool,       var1, Var1);
	QSM_WRITABLE_AUTO_PROPERTY(QString,    var2, Var2);
	QSM_WRITABLE_AUTO_PROPERTY(QObject *,  var3, Var3);

    QSM_READONLY_AUTO_PROPERTY (bool,      var4, Var4)
    QSM_READONLY_AUTO_PROPERTY (QString,   var5, Var5)
    QSM_READONLY_AUTO_PROPERTY (QObject *, var6, Var6)

    QSM_CONSTANT_AUTO_PROPERTY (bool,      var7, Var7)
    QSM_CONSTANT_AUTO_PROPERTY (QString,   var8, Var8)
    QSM_CONSTANT_AUTO_PROPERTY (QObject *, var9, Var9)

    QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT (bool,      var10, Var11, false)
    QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT (QString,   var11, Var12, "Test String")
    QSM_WRITABLE_AUTO_PROPERTY_WDEFAULT (QObject *, var13, Var13, nullptr)

    QSM_READONLY_AUTO_PROPERTY_WDEFAULT (bool,      var14, Var14, false)
    QSM_READONLY_AUTO_PROPERTY_WDEFAULT (QString,   var15, Var15, "Test String")
    QSM_READONLY_AUTO_PROPERTY_WDEFAULT (QObject *, var16, Var16, nullptr)

    QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT (bool,      var17, Var17, false)
    QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT (QString,   var18, Var18, "Test String")
    QSM_CONSTANT_AUTO_PROPERTY_WDEFAULT (QObject *, var19, Var19, nullptr)
};

QSUPER_MACROS_NAMESPACE_END

#endif // QQMLAUTOPROPERTYHELPERS_H

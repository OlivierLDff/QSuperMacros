/**
 * \file QQmlVarPropertyHelpers.h
 * \brief Declare Var Properties Helper 
 */
#ifndef QQMLVARPROPERTYHELPERS
#define QQMLVARPROPERTYHELPERS

#include <QObject>

#include "QQmlHelpersCommon.h"

QSUPER_MACROS_NAMESPACE_START

/**
 * \defgroup QSM_VAR_HELPER Var Properties
 * \brief Macros to generate Var Property that use `T`. `none` will be added where required.
 */

// NOTE : individual macros for getter, setter, notifier, and member

/** 
 * Generate a Getter in the form `Get<Name>`
 * To have a Qt-ish Getter (ie `<name>()`), define `QSUPER_MACROS_USE_QT_GETTERS` in your build system
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      type GetName(void) const { return _name; }
 *
 *      // Qt Naming Convention
 *      type name(void) const { return m_name; }
 *  \endcode
 */
#define QSM_VAR_GETTER(type, name, Name) \
    type QSM_MAKE_GETTER_NAME(name, Name) (void) const { return QSM_MAKE_ATTRIBUTE_NAME(name, Name); }

/** Generate a Setter in the form `Set<Name>`
 * To have a Qt-ish Setter (ie `set<Name>()`), define `QSUPER_MACROS_USE_QT_SETTERS` in your build system
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      bool SetName(const type name) 
 *      {
 *          if(_name != name)
 *          {
 *              _name = name;
 *              emit NameChanged(_name);
 *          }
 *          else 
 *              return false;
 *      }
 *
 *      // Qt Naming Convention
 *      bool setName(const type name) 
 *      {
 *          if(m_name != name)
 *          {
 *              m_name = name;
 *              emit nameChanged(m_name);
 *          }
 *          else 
 *              return false;
 *      }
 *  \endcode
 */
#define QSM_VAR_SETTER(type, name, Name) \
    bool QSM_MAKE_SETTER_NAME(name, Name) (const type name) \
    { \
        if (QSM_MAKE_ATTRIBUTE_NAME(name, Name) != name) { \
            QSM_MAKE_ATTRIBUTE_NAME(name, Name) = name; \
            emit QSM_MAKE_SIGNAL_NAME(name, Name) (QSM_MAKE_ATTRIBUTE_NAME(name, Name)); \
            return true; \
        } \
        else \
            return false; \
    }

/** 
 * Generate a Signal in the form `<Name>Changed(const type <name>)`
 * To have a Qt-ish Signal (ie `<name>Changed(const type <name>)`), define `QSUPER_MACROS_USE_QT_SIGNALS` in your build system
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase 
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      void NameChanged(const type name);
 *
 *      // Qt Naming Convention
 *      void nameChanged(const type name);
 *  \endcode
 */
#define QSM_VAR_NOTIFIER(type, name, Name) \
    void QSM_MAKE_SIGNAL_NAME(name, Name) (const type name);

/** Generate a member in the form `_<name>`
 * To have a Qt-ish member (ie `m_<name>`), define `QSUPER_MACROS_USE_QT_PREFIX` in your build system
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
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
#define QSM_VAR_MEMBER(type, name, Name, def) \
    type QSM_MAKE_ATTRIBUTE_NAME(name, Name) = def;

/** Generate a **Writable** Var Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName WRITE SetName NOTIFY NameChanged)
 *      private:
 *          type _name = def;
 *      public:
 *          const type GetName() const { return _name; }
 *          bool SetName(const type name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged(const type name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name WRITE setName NOTIFY nameChanged)
 *      private:
 *          type m_name = def;
 *      public:
 *          const type name() const { return m_name; }
 *          bool setName(const type name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged(const type name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_WRITABLE_VAR_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_WRITABLE_VAR_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a bool with default value false
 *  QSM_WRITABLE_VAR_PROPERTY_WDEFAULT(bool, myBool, MyBool, false);
 *  \endcode 
 */
#define QSM_WRITABLE_VAR_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
         Q_PROPERTY (type name READ QSM_MAKE_GETTER_NAME(name, Name) WRITE QSM_MAKE_SETTER_NAME(name, Name) NOTIFY QSM_MAKE_SIGNAL_NAME(name, Name)) \
    private: \
        QSM_VAR_MEMBER (type, name, Name, def) \
    public: \
        QSM_VAR_GETTER (type, name, Name) \
        QSM_VAR_SETTER (type, name, Name) \
    Q_SIGNALS: \
        QSM_VAR_NOTIFIER (type, name, Name) \
    private:

/** Generate a **Writable** Var Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName WRITE SetName NOTIFY NameChanged)
 *      private:
 *          type _name = {};
 *      public:
 *          const type GetName() const { return _name; }
 *          bool SetName(const type name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged(const type name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name WRITE setName NOTIFY nameChanged)
 *      private:
 *          type m_name = {};
 *      public:
 *          const type name() const { return m_name; }
 *          bool setName(const type name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged(const type name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value {}
 *  QSM_WRITABLE_VAR_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default value {}
 *  QSM_WRITABLE_VAR_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a bool with default value {}
 *  QSM_WRITABLE_VAR_PROPERTY(bool, myBool, MyBool);
 *  \endcode 
 */
#define QSM_WRITABLE_VAR_PROPERTY(type, name, Name) \
    QSM_WRITABLE_VAR_PROPERTY_WDEFAULT(type, name, Name, {} )

/** Generate a **Read-Only** Var Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
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
 *          const type GetName() const { return _name; }
 *          bool SetName(const type name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged(const type name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name NOTIFY nameChanged)
 *      private:
 *          type m_name = def;
 *      public:
 *          const type name() const { return m_name; }
 *          bool setName(const type name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged(const type name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_READONLY_VAR_PROPERTY(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_READONLY_VAR_PROPERTY(QString, myString, MyString, "MyString");
 * 
 *  // Create a bool with default value false
 *  QSM_READONLY_VAR_PROPERTY(bool, myBool, MyBool, false);
 *  \endcode 
 */
#define QSM_READONLY_VAR_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
         Q_PROPERTY (type name READ QSM_MAKE_GETTER_NAME(name, Name) NOTIFY QSM_MAKE_SIGNAL_NAME(name, Name)) \
    private: \
        QSM_VAR_MEMBER (type, name, Name, def) \
    public: \
        QSM_VAR_GETTER (type, name, Name) \
        QSM_VAR_SETTER (type, name, Name) \
    Q_SIGNALS: \
        QSM_VAR_NOTIFIER (type, name, Name) \
    private:

/** Generate a **Read-Only** Var Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
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
 *          const type GetName() const { return _name; }
 *          bool SetName(const type name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void NameChanged(const type name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name NOTIFY nameChanged)
 *      private:
 *          type m_name = {};
 *      public:
 *          const type name() const { return m_name; }
 *          bool setName(const type name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *      signals:
 *          void nameChanged(const type name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value {}
 *  QSM_READONLY_VAR_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default value {}
 *  QSM_READONLY_VAR_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a bool with default value {}
 *  QSM_READONLY_VAR_PROPERTY(bool, myBool, MyBool);
 *  \endcode 
 */
#define QSM_READONLY_VAR_PROPERTY(type, name, Name) \
    QSM_READONLY_VAR_PROPERTY_WDEFAULT(type, name, Name, {})

/** Generate a **Constant** Var Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
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
 *          const type GetName() const { return _name; }
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name CONSTANT)
 *      private:
 *          type m_name = def;
 *      public:
 *          const type name() const { return m_name; }
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_CONSTANT_VAR_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_CONSTANT_VAR_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a bool with default value false
 *  QSM_CONSTANT_VAR_PROPERTY_WDEFAULT(bool, myBool, MyBool, false);
 *  \endcode 
 */
#define QSM_CONSTANT_VAR_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
        Q_PROPERTY (type name READ QSM_MAKE_GETTER_NAME(name, Name) CONSTANT) \
    private: \
        QSM_VAR_MEMBER (type, name, Name, def) \
    public: \
        QSM_VAR_GETTER (type, name, Name) \
    private:

/** Generate a **Constant** Var Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_VAR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
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
 *          const type GetName() const { return _name; }
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name CONSTANT)
 *      private:
 *          type m_name = {};
 *      public:
 *          const type name() const { return m_name; }
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value {}
 *  QSM_CONSTANT_VAR_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default value {}
 *  QSM_CONSTANT_VAR_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a bool with default value {}
 *  QSM_CONSTANT_VAR_PROPERTY(bool, myBool, MyBool);
 *  \endcode 
 */
#define QSM_CONSTANT_VAR_PROPERTY(type, name, Name) \
        QSM_CONSTANT_VAR_PROPERTY_WDEFAULT(type, name, Name, {})

/**
 * \internal
 */
class QSUPER_MACROS_API_ _Tes_QmlVarProperty_ : public QObject 
{
    Q_OBJECT

    QSM_WRITABLE_VAR_PROPERTY (int,     var1, Var1)
    QSM_READONLY_VAR_PROPERTY (bool,    var2, Var2)
    QSM_CONSTANT_VAR_PROPERTY (QString, var3, Var3)

    QSM_WRITABLE_VAR_PROPERTY_WDEFAULT (int,     var4, Var4, 1)
    QSM_READONLY_VAR_PROPERTY_WDEFAULT (bool,    var5, Var5, false)
    QSM_CONSTANT_VAR_PROPERTY_WDEFAULT (QString, var6, Var6, "MyString")
};

QSUPER_MACROS_NAMESPACE_END

#endif // QQMLVARPROPERTYHELPERS

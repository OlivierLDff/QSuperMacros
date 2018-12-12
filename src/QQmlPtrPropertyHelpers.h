/**
 * \file QQmlPtrPropertyHelpers.h
 * \brief Declare Ptr Properties Helper 
 */
#ifndef QQMLPTRPROPERTYHELPERS
#define QQMLPTRPROPERTYHELPERS

#include <QObject>

#include "QQmlHelpersCommon.h"

QSUPER_MACROS_NAMESPACE_START

/**
 * \defgroup QSM_PTR_HELPER Ptr Properties
 * \brief Macros to generate Ptr Property that use `T`. `*` will be added where required.
 */

// NOTE : individual macros for getter, setter, notifier, and member

/** 
 * Generate a Getter in the form `Get<Name>`
 * To have a Qt-ish Getter (ie `<name>()`), define `QSUPER_MACROS_USE_QT_GETTERS` in your build system
 * \ingroup QSM_PTR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      type * GetName(void) const { return _name; }
 *
 *      // Qt Naming Convention
 *      type * name(void) const { return m_name; }
 *  \endcode
 */
#define QSM_PTR_GETTER(type, name, Name) \
    type * QSM_MAKE_GETTER_NAME(name, Name) (void) const { return QSM_MAKE_ATTRIBUTE_NAME(name, Name); }

/** Generate a Setter in the form `Set<Name>`
 * To have a Qt-ish Setter (ie `set<Name>()`), define `QSUPER_MACROS_USE_QT_SETTERS` in your build system
 * \ingroup QSM_PTR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      bool SetName(type * name) 
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
 *      bool setName(type * name) 
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
#define QSM_PTR_SETTER(type, name, Name) \
    bool QSM_MAKE_SETTER_NAME(name, Name) (type * name) \
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
 * Generate a Signal in the form `<Name>Changed(const type & <name>)`
 * To have a Qt-ish Signal (ie `<name>Changed(const type & <name>)`), define `QSUPER_MACROS_USE_QT_SIGNALS` in your build system
 * \ingroup QSM_PTR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase 
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      void NameChanged(type* name);
 *
 *      // Qt Naming Convention
 *      void nameChanged(type* name);
 *  \endcode
 */
#define QSM_PTR_NOTIFIER(type, name, Name) \
    void QSM_MAKE_SIGNAL_NAME(name, Name) (type * name);

/** Generate a member in the form `_<name>`
 * To have a Qt-ish member (ie `m_<name>`), define `QSUPER_MACROS_USE_QT_PREFIX` in your build system
 * \ingroup QSM_PTR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      type * _name = def;
 *
 *      // Qt Naming Convention
 *      type * m_name = def;
 *  \endcode
 */
#define QSM_PTR_MEMBER(type, name, Name, def) \
    type * QSM_MAKE_ATTRIBUTE_NAME(name, Name) = def;

/** Reset the member to the default value def
 * \ingroup QSM_PTR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QObject*`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \param def Default value of the members. If you want to let the type choose default value just use `{}`
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      bool ResetName() { return SetName(def); }
 *
 *      // Qt Naming Convention
 *      bool resetName() { return setName(def); }
 *  \endcode
 */
#define QSM_PTR_RESET(type, name, Name, def) \
    bool QSM_MAKE_RESET_NAME(name, Name)() { return QSM_MAKE_SETTER_NAME(name, Name)(def); }

/** Generate a **Writable** Ptr Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_PTR_HELPER
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
 *          Q_PROPERTY (type name READ GetName WRITE SetName RESET ResetName NOTIFY NameChanged)
 *      private:
 *          type _name = def;
 *      public:
 *          const type& GetName() const { return _name; }
 *          bool SetName(const type& name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool ResetName() { return SetName(def); }
 *      signals:
 *          void NameChanged(const type& name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name WRITE setName RESET resetName NOTIFY nameChanged)
 *      private:
 *          type m_name = def;
 *      public:
 *          const type& name() const { return m_name; }
 *          bool setName(const type& name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool resetName() { return setName(def); }
 *      signals:
 *          void nameChanged(const type& name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_WRITABLE_PTR_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_WRITABLE_PTR_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a bool with default value false
 *  QSM_WRITABLE_PTR_PROPERTY_WDEFAULT(bool, myBool, MyBool, false);
 *  \endcode 
 */
#define QSM_WRITABLE_PTR_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
         Q_PROPERTY (type * name READ QSM_MAKE_GETTER_NAME(name, Name) WRITE QSM_MAKE_SETTER_NAME(name, Name) RESET QSM_MAKE_RESET_NAME(name, Name) NOTIFY QSM_MAKE_SIGNAL_NAME(name, Name)) \
    private: \
        QSM_PTR_MEMBER (type, name, Name, def) \
    public: \
        QSM_PTR_GETTER (type, name, Name) \
        QSM_PTR_SETTER (type, name, Name) \
        QSM_PTR_RESET (type, name, Name, def) \
    Q_SIGNALS: \
        QSM_PTR_NOTIFIER (type, name, Name) \
    private:

/** Generate a **Writable** Ptr Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_PTR_HELPER
 * \hideinitializer
 * \param type Type of the attribute (`int`, `quint32`, `QString`, etc...)
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * 
 * It generates for this goal :
 *  \code
 *      // Default Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ GetName WRITE SetName RESET ResetName NOTIFY NameChanged)
 *      private:
 *          type _name = {};
 *      public:
 *          const type& GetName() const { return _name; }
 *          bool SetName(const type& name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool ResetName() { return SetName({}); }
 *      signals:
 *          void NameChanged(const type& name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name WRITE setName RESET resetName NOTIFY nameChanged)
 *      private:
 *          type m_name = {};
 *      public:
 *          const type& name() const { return m_name; }
 *          bool setName(const type& name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool ResetName() { return SetName({}); }
 *      signals:
 *          void nameChanged(const type& name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value {}
 *  QSM_WRITABLE_PTR_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default value {}
 *  QSM_WRITABLE_PTR_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a bool with default value {}
 *  QSM_WRITABLE_PTR_PROPERTY(bool, myBool, MyBool);
 *  \endcode 
 */
#define QSM_WRITABLE_PTR_PROPERTY(type, name, Name) \
    QSM_WRITABLE_PTR_PROPERTY_WDEFAULT(type, name, Name, {} )

/** Generate a **Read-Only** Ptr Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_PTR_HELPER
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
 *          const type& GetName() const { return _name; }
 *          bool SetName(const type& name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool ResetName() { return SetName(def); }
 *      signals:
 *          void NameChanged(const type& name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name NOTIFY nameChanged)
 *      private:
 *          type m_name = def;
 *      public:
 *          const type& name() const { return m_name; }
 *          bool setName(const type& name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool resetName() { return setName(def); }
 *      signals:
 *          void nameChanged(const type& name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_READONLY_PTR_PROPERTY(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_READONLY_PTR_PROPERTY(QString, myString, MyString, "MyString");
 * 
 *  // Create a bool with default value false
 *  QSM_READONLY_PTR_PROPERTY(bool, myBool, MyBool, false);
 *  \endcode 
 */
#define QSM_READONLY_PTR_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
         Q_PROPERTY (type * name READ QSM_MAKE_GETTER_NAME(name, Name) NOTIFY QSM_MAKE_SIGNAL_NAME(name, Name)) \
    private: \
        QSM_PTR_MEMBER (type, name, Name, def) \
    public: \
        QSM_PTR_GETTER (type, name, Name) \
        QSM_PTR_SETTER (type, name, Name) \
         QSM_PTR_RESET (type, name, Name, def) \
    Q_SIGNALS: \
        QSM_PTR_NOTIFIER (type, name, Name) \
    private:

/** Generate a **Read-Only** Ptr Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_PTR_HELPER
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
 *          const type& GetName() const { return _name; }
 *          bool SetName(const type& name) 
 *          {
 *              if(_name != name)
 *              {
 *                  _name = name;
 *                  emit NameChanged(_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool ResetName() { return SetName(def); }
 *      signals:
 *          void NameChanged(const type& name);
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name NOTIFY nameChanged)
 *      private:
 *          type m_name = {};
 *      public:
 *          const type& name() const { return m_name; }
 *          bool setName(const type& name) 
 *          {
 *              if(m_name != name)
 *              {
 *                  m_name = name;
 *                  emit nameChanged(m_name);
 *              }
 *              else 
 *                  return false;
 *          }
 *          bool resetName() { return setName(def); }
 *      signals:
 *          void nameChanged(const type& name);
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value {}
 *  QSM_READONLY_PTR_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default value {}
 *  QSM_READONLY_PTR_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a bool with default value {}
 *  QSM_READONLY_PTR_PROPERTY(bool, myBool, MyBool);
 *  \endcode 
 */
#define QSM_READONLY_PTR_PROPERTY(type, name, Name) \
    QSM_READONLY_PTR_PROPERTY_WDEFAULT(type, name, Name, {})

/** Generate a **Constant** Ptr Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_PTR_HELPER
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
 *          const type& GetName() const { return _name; }
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name CONSTANT)
 *      private:
 *          type m_name = def;
 *      public:
 *          const type& name() const { return m_name; }
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value 23
 *  QSM_CONSTANT_PTR_PROPERTY_WDEFAULT(int, myInt, MyInt, 23);
 * 
 *  // Create a QString with default value "MyString"
 *  QSM_CONSTANT_PTR_PROPERTY_WDEFAULT(QString, myString, MyString, "MyString");
 * 
 *  // Create a bool with default value false
 *  QSM_CONSTANT_PTR_PROPERTY_WDEFAULT(bool, myBool, MyBool, false);
 *  \endcode 
 */
#define QSM_CONSTANT_PTR_PROPERTY_WDEFAULT(type, name, Name, def) \
    protected: \
        Q_PROPERTY (type * name READ QSM_MAKE_GETTER_NAME(name, Name) CONSTANT) \
    private: \
        QSM_PTR_MEMBER (type, name, Name, def) \
    public: \
        QSM_PTR_GETTER (type, name, Name) \
    private:

/** Generate a **Constant** Ptr Property
 * Auto Property uses either `T` or `T*` and is capable of adding constant-reference by 
 * deciding itself which type is the cheapest (using some template trickery internally).
 * \ingroup QSM_PTR_HELPER
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
 *          const type& GetName() const { return _name; }
 *      private:
 *
 *      // Qt Naming Convention
 *      protected:
 *          Q_PROPERTY (type name READ name CONSTANT)
 *      private:
 *          type m_name = {};
 *      public:
 *          const type& name() const { return m_name; }
 *      private:
 *  \endcode 
 *
 *  You can declare a property in your QObject like this
 *  \code 
 *  // Create an integer with default value {}
 *  QSM_CONSTANT_PTR_PROPERTY(int, myInt, MyInt);
 * 
 *  // Create a QString with default value {}
 *  QSM_CONSTANT_PTR_PROPERTY(QString, myString, MyString);
 * 
 *  // Create a bool with default value {}
 *  QSM_CONSTANT_PTR_PROPERTY(bool, myBool, MyBool);
 *  \endcode 
 */
#define QSM_CONSTANT_PTR_PROPERTY(type, name, Name) \
        QSM_CONSTANT_PTR_PROPERTY_WDEFAULT(type, name, Name, {})

/**
 * \internal
 */
class QSUPER_MACROS_API_ _Test_QmlPtrProperty_ : public QObject 
{
    Q_OBJECT

    QSM_WRITABLE_PTR_PROPERTY (int,     var1, Var1)
    QSM_READONLY_PTR_PROPERTY (bool,    var2, Var2)
    QSM_CONSTANT_PTR_PROPERTY (QString, var3, Var3)

    QSM_WRITABLE_PTR_PROPERTY_WDEFAULT (int,     var4, Var4, nullptr)
    QSM_READONLY_PTR_PROPERTY_WDEFAULT (bool,    var5, Var5, nullptr)
    QSM_CONSTANT_PTR_PROPERTY_WDEFAULT (QString, var6, Var6, nullptr)
};

QSUPER_MACROS_NAMESPACE_END

#endif // QQMLPTRPROPERTYHELPERS


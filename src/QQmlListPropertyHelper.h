/**
 * \file QQmlListPropertyHelper.h
 * \brief Declare List Property Helper
 */
#ifndef QQMLLISTPROPERTYHELPER
#define QQMLLISTPROPERTYHELPER

#include <QVector>
#include <QQmlListProperty>

#include "QQmlHelpersCommon.h"

QSUPER_MACROS_NAMESPACE_START

/**
 * \defgroup QSM_LIST_HELPER List Properties
 * \brief Macros to generate a Smart List
 */

/**
 * Smart List template class. Used to create a QML list property that maps to an internal 
 * QList of objects, without having to declare and implement all static function pointers...
 * \ingroup QSM_LIST_HELPER
 */
template<class ObjType> class QQmlSmartListWrapper : public QQmlListProperty<ObjType> {
public:
    typedef QVector<ObjType *>            CppListType;
    typedef QQmlListProperty<ObjType>     QmlListPropertyType;
    typedef QQmlSmartListWrapper<ObjType> SmartListWrapperType;

    typedef typename CppListType::const_iterator const_iterator;

    explicit QQmlSmartListWrapper (QObject * object, const int reserve = 0)
        : QmlListPropertyType
          (object,
           &m_items,
           &SmartListWrapperType::callbackAppend,
           &SmartListWrapperType::callbackCount,
           &SmartListWrapperType::callbackAt,
           &SmartListWrapperType::callbackClear)
    {
        if (reserve > 0) {
            m_items.reserve (reserve);
        }
    }

    const CppListType & items (void) const {
        return m_items;
    }

    const_iterator begin (void) const {
        return m_items.begin ();
    }

    const_iterator end (void) const {
        return m_items.end ();
    }

    const_iterator constBegin (void) const {
        return m_items.constBegin ();
    }

    const_iterator constEnd (void) const {
        return m_items.constEnd ();
    }

    static int callbackCount (QmlListPropertyType * prop) {
        return static_cast<CppListType *> (prop->data)->count ();
    }

    static void callbackClear (QmlListPropertyType * prop) {
        static_cast<CppListType *> (prop->data)->clear ();
    }

    static void callbackAppend (QmlListPropertyType * prop, ObjType * obj) {
        static_cast<CppListType *> (prop->data)->append (obj);
    }

    static ObjType * callbackAt (QmlListPropertyType * prop, int idx) {
        return static_cast<CppListType *> (prop->data)->at (idx);
    }

private:
    CppListType m_items;
};

/**
 * A really handy macro to create a QML list property that maps to an internal 
 * QList of objects, without having to declare and implement all static function pointers...
 * \ingroup QSM_LIST_HELPER
 * \hideinitializer
 * \param type Type Contain in the list
 * \param name Name of the list in lowerCamelCase
 * \param Name Name of the list in UpperCamelCase
 */
#define QSM_LIST_PROPERTY(type, name, Name) \
    private: \
        Q_PROPERTY (QQmlListProperty<type> name READ QSM_MAKE_GETTER_NAME(name, Name) CONSTANT) \
    public: \
        const QQmlSmartListWrapper<type> & QSM_MAKE_GETTER_NAME(name, Name) (void) const { \
            return QSM_MAKE_ATTRIBUTE_NAME(name, Name);; \
        } \
    private: \
        QQmlSmartListWrapper<type> QSM_MAKE_ATTRIBUTE_NAME(name, Name);

/**
 * \internal
 */
class QSUPER_MACROS_API_ _Test_QmlStartListWrapper : public QObject
{
	Q_OBJECT
	QSM_LIST_PROPERTY(QString, myStringList, MyStringList);
};

QSUPER_MACROS_NAMESPACE_END

#endif // QQMLLISTPROPERTYHELPER


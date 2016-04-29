#ifndef QQMLLISTPROPERTYHELPER
#define QQMLLISTPROPERTYHELPER

#include <QList>
#include <QQmlListProperty>

template<class ObjType> class QQmlSmartList : public QQmlListProperty<ObjType> {
public:
    explicit QQmlSmartList (QObject * object)
        : QQmlListProperty<ObjType>
          (object,
           this,
           &QQmlSmartList<ObjType>::callbackAppend,
           &QQmlSmartList<ObjType>::callbackCount,
           &QQmlSmartList<ObjType>::callbackAt,
           &QQmlSmartList<ObjType>::callbackClear)
    { }

    typedef QList<ObjType *>          CppListType;
    typedef QQmlSmartList<ObjType>    SmartListType;
    typedef QQmlListProperty<ObjType> QmlListPropertyType;

    CppListType list;

    static int callbackCount (QmlListPropertyType * prop) {
        SmartListType * self = static_cast<SmartListType *> (prop->data);
        return (self != Q_NULLPTR ? self->list.count () : 0);
    }

    static void callbackClear (QmlListPropertyType * prop) {
        SmartListType * self = static_cast<SmartListType *> (prop->data);
        if (self != Q_NULLPTR) {
            self->list.clear ();
        }
    }

    static void callbackAppend (QmlListPropertyType * prop, ObjType * obj) {
        SmartListType * self = static_cast<SmartListType *> (prop->data);
        if (self != Q_NULLPTR && obj != Q_NULLPTR) {
            self->list.append (obj);
        }
    }

    static ObjType * callbackAt (QmlListPropertyType * prop, int idx) {
        SmartListType * self = static_cast<SmartListType *> (prop->data);
        return (self != Q_NULLPTR ? self->list.at (idx) : Q_NULLPTR);
    }
};

#define QML_LIST_PROPERTY(TYPE, NAME) \
    private: \
        Q_PROPERTY (QQmlListProperty<TYPE> NAME READ get_##NAME CONSTANT) \
    public: \
        QQmlSmartList<TYPE> & get_##NAME (void) { \
            return m_##NAME; \
        } \
    private: \
        QQmlSmartList<TYPE> m_##NAME;


#endif // QQMLLISTPROPERTYHELPER


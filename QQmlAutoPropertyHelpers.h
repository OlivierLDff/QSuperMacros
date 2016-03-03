#ifndef QQMLAUTOPROPERTYHELPERS_H
#define QQMLAUTOPROPERTYHELPERS_H

#include <QObject>

// NOTE : SFINAE trickery to find which type is the cheapest between T and const T &

template<typename T> struct CheapestType          { typedef const T & type_def; };
template<>           struct CheapestType<bool>    { typedef bool      type_def; };
template<>           struct CheapestType<quint8>  { typedef quint8    type_def; };
template<>           struct CheapestType<quint16> { typedef quint16   type_def; };
template<>           struct CheapestType<quint32> { typedef quint32   type_def; };
template<>           struct CheapestType<quint64> { typedef quint64   type_def; };
template<>           struct CheapestType<qint8>   { typedef qint8     type_def; };
template<>           struct CheapestType<qint16>  { typedef qint16    type_def; };
template<>           struct CheapestType<qint32>  { typedef qint32    type_def; };
template<>           struct CheapestType<qint64>  { typedef qint64    type_def; };
template<>           struct CheapestType<float>   { typedef float     type_def; };
template<>           struct CheapestType<double>  { typedef double    type_def; };
template<typename T> struct CheapestType<T *>     { typedef T *       type_def; };

// NOTE : individual macros for getter, setter, notifier, and member

#define QML_AUTO_GETTER(type, name) \
    CheapestType<type>::type_def get_##name (void) const { \
        return m_##name; \
    }

#define QML_AUTO_SETTER(type, name, prefix) \
    bool prefix##name (CheapestType<type>::type_def name) { \
        bool ret = false; \
        if ((ret = m_##name != name)) { \
            m_##name = name; \
            emit name##Changed (); \
        } \
        return ret; \
    }

#define QML_AUTO_NOTIFIER(type, name) \
    void name##Changed (void);

#define QML_AUTO_MEMBER(type, name) \
    type m_##name;

// NOTE : actual auto-property helpers

#define QML_WRITABLE_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
        QML_AUTO_MEMBER (type, name) \
    public: \
        QML_AUTO_GETTER (type, name) \
        QML_AUTO_SETTER (type, name, set_) \
    Q_SIGNALS: \
        QML_AUTO_NOTIFIER (type, name) \
    private:

#define QML_READONLY_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name NOTIFY name##Changed) \
    private: \
        QML_AUTO_MEMBER (type, name) \
    public: \
        QML_AUTO_GETTER (type, name) \
        QML_AUTO_SETTER (type, name, update_) \
    Q_SIGNALS: \
        QML_AUTO_NOTIFIER (type, name) \
    private:

#define QML_CONSTANT_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name CONSTANT) \
    private: \
        QML_AUTO_MEMBER (type, name) \
    public: \
        QML_AUTO_GETTER (type, name) \
    private:

// NOTE : test class for all cases

class _QmlAutoProperty_ : public QObject {
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY (bool,      var1)
    QML_WRITABLE_AUTO_PROPERTY (QString,   var2)
    QML_WRITABLE_AUTO_PROPERTY (QObject *, var3)

    QML_READONLY_AUTO_PROPERTY (bool,      var4)
    QML_READONLY_AUTO_PROPERTY (QString,   var5)
    QML_READONLY_AUTO_PROPERTY (QObject *, var6)

    QML_CONSTANT_AUTO_PROPERTY (bool,      var7)
    QML_CONSTANT_AUTO_PROPERTY (QString,   var8)
    QML_CONSTANT_AUTO_PROPERTY (QObject *, var9)
};

#endif // QQMLAUTOPROPERTYHELPERS_H

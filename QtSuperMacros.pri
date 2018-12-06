
# Qt super-macros

QT += core qml

INCLUDEPATH += $$PWD/src

HEADERS += \
    $$PWD/src/QQmlVarPropertyHelpers.h \
    $$PWD/src/QQmlPtrPropertyHelpers.h \
    $$PWD/src/QQmlEnumClassHelper.h \
    $$PWD/src/QQmlConstRefPropertyHelpers.h \
    $$PWD/src/QQmlListPropertyHelper.h \
    $$PWD/src/QQmlAutoPropertyHelpers.h \
    $$PWD/src/QQmlHelpersCommon.h \
    $$PWD/src/QQmlSingletonHelper.h

SOURCES += \
    $$PWD/src/QQmlHelpers.cpp

DISTFILES += \
    $$PWD/README.md \
    $$PWD/LICENSE.md


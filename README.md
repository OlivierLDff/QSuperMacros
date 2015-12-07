Qt Super-Macros
===============

A set of one-line C++ macros to simplify the creation of reccurent things (like Qt Meta Properties) so that doing them in C++ is not harder than in QML, and requires no boilerplate glue-code.

* `QML_WRITABLE_PROPERTY` : a macro that takes a type and a name, and creates automatically the member attribute, the public getter and setter, and the Qt signal for notifier, and allow use in QML by exposing a read/write `Q_PROPERTY`.

* `QML_READONLY_PROPERTY` : another macro that does almost the same as `QML_WRITABLE_PROPERTY` except that the property is not modifiable from the QML side, only C++ can access the setter.

* `QML_CONSTANT_PROPERTY` : a simplified version of the previous macros, that exposes a constant property with no getter and no setter, from C++ or QML side.

* `QML_LIST_PROPERTY` : a really handy macro to create a QML list property that maps to an internal `QList` of objects, without having to declare and implement all static function pointers...

* `QML_ENUM_CLASS` : a macro to declare a `QObject` class that only contains a `Q_ENUM` and can be exposed as is to QML.


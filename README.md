Qt Super-Macros
===============

A set of one-line C++ macros to simplify the creation of reccurent things (like Qt Meta Properties) so that doing them in C++ is not harder than in QML, and requires no boilerplate glue-code.

*This fork aim is too add CMake support to this library. It also change the macros to match my naming convention.*

## Dependencies

- [Doxygen](https://github.com/doxygen/doxygen) : To generate the documentation.
- [DoxygenBootstrapped](https://github.com/OlivierLDff/DoxygenBootstrapped) : Integrate doxygen with CMake. *v1.3.2*.

## API

* The documentation can be found [here](https://olivierldff.github.io/QSuperMacrosDoc/)

## Release

* `1.0.0` : Initial work
* `1.1.0` : Reset functions

## Convention

* Class attribute are `_<property>`.
* Getter and Setter are `Get<Property>`, `Set<Property>`.
* Reset are `Reset<Property>`.
* Signals are `<property>Changed`.

## For one-line creation of QML properties

* `QSM_WRITABLE_***_PROPERTY` : a macro that takes a type and a name, and creates automatically the member attribute, the public getter and setter, and the Qt signal for notifier, and allow use in QML by exposing a read/write `Q_PROPERTY`.

* `QSM_READONLY_***_PROPERTY` : another macro that does almost the same as `QSM_WRITABLE_PROPERTY` except that the property is not modifiable from the QML side, only C++ can access the setter.

* `QSM_CONSTANT_***_PROPERTY` : a simplified version of the previous macros, that exposes a constant property with no getter and no setter, from C++ or QML side.

The `***` can be either `VAR`, `PTR`, `CSTREF`, or `AUTO`. The three first are simple macros that you use by simply passing the non-qualified type (`T`) and it'll add the qualifiers for var (none), pointer (`*`), or constant-reference (`const &`) where needed. The last one in the other hand, uses either `T` or `T*` and it's capable of adding constant-reference by deciding itself which type is the cheapest (using some template trickery internally).

> INFO : by default, getters are named `Get<PropertyName>`, but if you want more Qt-compliant naming (no prefix) you can set the `QSUPER_MACROS_USE_QT_GETTERS` flag in QMake or QBS or CMake.
>
> The same for setters that are named `Set<PropertyName>`. With the flag `QSUPER_MACROS_USE_QT_SETTERS` the will be set as `set<PropertyName>`.
>
> Same for signals they are default to `<PropertyName>Changed`. With the flag `QSUPER_MACROS_USE_QT_SIGNALS` the will be set to `<propertyName>Changed`. It is recommended for better to use the Qt-ish form of signals (they are default in CMake) because QML connections don't support signals starting with a Capital letter.
>
> The Prefix of member variable is default to nothing. So the attribute is `_attribute`. You can set `QSUPER_MACROS_USE_QT_PREFIX` to `m` to have a more Qt-ish naming convention.

### Using default values for attribute

It is possible to set a default value for the attribute by using the macros `<MACROS>_WDEFAULT`.


## For easier QQmlListProperty from QList

* `QSM_LIST_PROPERTY` : a really handy macro to create a QML list property that maps to an internal `QList` of objects, without having to declare and implement all static function pointers...


## For simple enum class that can be used in C++ and QML

* `QSM_ENUM_CLASS` : a macro to declare a `QObject` class that only contains a `Q_ENUM` and can be exposed as is to QML.

## For single property

* `QSM_SINGLETON_PROPERTY` : Macros to generate Singleton properties without the need to handle the factory.

## CMake

### Build

```bash
git clone https://github.com/OlivierLDff/QSuperMacros
cd QSuperMacros && mkdir build && cd build
cmake -DQT_DIR="path/to/Qt/toolchain" -DQSUPER_MACROS_BUILD_SHARED=ON -DQSUPER_MACROS_USE_NAMESPACE=ON -DQSUPER_MACROS_BUILD_DOC=ON ..
make
```

### Input

- **QSUPER_MACROS_TARGET** : Name of the library target. *Default : "QSuperMacros"*
- **QSUPER_MACROS_PROJECT** : Name of the project. *Default : "QSuperMacros"*
- **QSUPER_MACROS_BUILD_SHARED** : Build shared library [ON OFF]. *Default: OFF.*
- **QSUPER_MACROS_BUILD_STATIC** : Build static library [ON OFF]. *Default: ON.*
- **QSUPER_MACROS_USE_NAMESPACE** : If the library compile with a namespace [ON OFF]. *Default: ON.*
- **QSUPER_MACROS_NAMESPACE** : Namespace for the library. Only relevant if QSUPER_MACROS_USE_NAMESPACE is ON. *Default: "Qsm".*
- **QSUPER_MACROS_BUILD_DOC** : Build the QSuperMacros Doc [ON OFF]. *Default: OFF.*

### Naming Convention

* **QSUPER_MACROS_USE_QT_PREFIX** : Use Qt-ish internal attribute prefix `m_attribute `[ON OFF]. *Default = OFF.*
* **QSUPER_MACROS_USE_QT_GETTERS** : Use Qt-ish Getter naming convention `attribute()` [ON OFF]. *Default = OFF.*
* **QSUPER_MACROS_USE_QT_SETTERS** : Use Qt-ish Setter naming convention `setAttribute` [ON OFF]. *Default = OFF.*
* **QSUPER_MACROS_USE_QT_RESETS** : Use Qt-ish Setter naming convention resetAttribute [ON OFF]. *Default = OFF.*
* **QSUPER_MACROS_USE_QT_SIGNALS** : Use Qt-ish signal naming convention `attributeChanged`. It is really recommended to leave this option ON because QML Connections don't handle signals starting with Capital Letter [ON OFF]. *Default = ON.*

### Dependencies

- **QSUPER_MACROS_DOXYGEN_BT_REPOSITORY** : Repository of DoxygenBt. *Default : "https://github.com/OlivierLDff/DoxygenBootstrapped.git"*
- **QSUPER_MACROS_DOXYGEN_BT_TAG** : Git Tag of DoxygenBt. *Default : "v1.3.2"*

### Output

- **QSUPER_MACROS_TARGET** : Output target to link to.
- **QSUPER_MACROS_VERSION** : Current version of the library

### Integration in CMake project

The main goal of this CMake project is to big included into another CMake project.

```cmake
SET( QSUPER_MACROS_TARGET QSuperMacros )
SET( QSUPER_MACROS_PROJECT QSuperMacros )
SET( QSUPER_MACROS_BUILD_SHARED OFF )
SET( QSUPER_MACROS_BUILD_STATIC ON )
SET( QSUPER_MACROS_BUILD_DOC OFF )
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/path/to/QSuperMacros ${CMAKE_CURRENT_BINARY_DIR}/QSuperMacros_Build)
```

It is also possible to download the repository with the scripts inside `cmake/`. folder Simply call `BuildQSuperMacros.cmake`.

You will need:

- `DownloadProject.cmake`
- `DownloadProject.CMakeLists.cmake.in`
- `BuildQSuperMacros.cmake`

```cmake
SET( QSUPER_MACROS_TARGET QSuperMacros )
SET( QSUPER_MACROS_PROJECT QSuperMacros )
SET( QSUPER_MACROS_BUILD_SHARED OFF )
SET( QSUPER_MACROS_BUILD_STATIC ON )
SET( QSUPER_MACROS_BUILD_DOC OFF )
SET( QSUPER_MACROS_USE_NAMESPACE ON )
SET( QSUPER_MACROS_REPOSITORY "https://github.com/OlivierLDff/QSuperMacros.git" )
SET( QSUPER_MACROS_TAG v1.0.1 )
INCLUDE(path/to/BuildQSuperMacros.cmake)
```



> NOTE : If you want to donate to Thomas Boutroue, use this link : [![Flattr this](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=thebootroo&url=http://gitlab.unique-conception.org/qt-qml-tricks/qt-supermacros)

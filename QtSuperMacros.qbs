import qbs;

Project {
    name: "Qt super-macros";

    Product {
        name: "libqtqmltricks-qtsupermacros";
        type: "staticlibrary";
        targetName: "QtSuperMacros";

        Export {
            cpp.includePaths: "./src";

            Depends { name: "cpp"; }
            Depends {
                name: "Qt";
                submodules: ["core", "qml"];
            }
        }
        Depends { name: "cpp"; }
        Depends {
            name: "Qt";
                submodules: ["core", "qml"];
        }
        Group {
            name: "C++ sources";
            files: [
                "QQmlHelpers.cpp",
            ]
        }
        Group {
            name: "C++ headers";
            files: [
                "src/QQmlConstRefPropertyHelpers.h",
                "src/QQmlEnumClassHelper.h",
                "src/QQmlListPropertyHelper.h",
                "src/QQmlPtrPropertyHelpers.h",
                "src/QQmlSingletonHelper.h",
                "src/QQmlVarPropertyHelpers.h",
            ]
        }
        Group {
            qbs.install: (product.type === "dynamiclibrary");
            fileTagsFilter: product.type;
        }
    }
}

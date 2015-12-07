import qbs;

Project {
    name: "Qt super-macros";

    Product {
        name: "qt-super-macros";
        type: "staticlibrary";
        targetName: "QtSuperMacros";

        Export {
            cpp.includePaths: ".";

            Depends { name: "cpp"; }
            Depends {
                name: "Qt";
                submodules: ["core"];
            }
        }
        Depends { name: "cpp"; }
        Depends {
            name: "Qt";
                submodules: ["core"];
        }
        Group {
            name: "C++ sources";
            files: [
                "qqmlhelpers.cpp",
            ]
        }
        Group {
            name: "C++ headers";
            files: [
                "qqmlhelpers.h",
            ]
        }
        Group {
            qbs.install: true;
            fileTagsFilter: product.type;
        }
    }
}

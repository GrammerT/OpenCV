
INCLUDEPATH += "$$PWD/../depend/opencv/include"

CONFIG(debug, debug|release){
    DESTDIR=$$PWD/../debug_/
win32{
    contains(QMAKE_TARGET.arch, x86){
        LIBS += "$$PWD/../depend/opencv/libs/debug/*.lib"
        }
    contains(QMAKE_TARGET.arch, x86_64){
        LIBS += "$$PWD/../depend/opencv/libs/debug/*.lib"
    }
}
}


CONFIG(release, debug|release){
    DESTDIR=$$PWD/../release_/
win32{
    contains(QMAKE_TARGET.arch, x86){
        LIBS += "$$PWD/../depend/opencv/libs/release/*.lib"
        }
    contains(QMAKE_TARGET.arch, x86_64){
        LIBS += "$$PWD/../depend/opencv/libs/release/*.lib"
    }
}
}

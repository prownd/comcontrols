
#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T14:29:35
#
#-------------------------------------------------

#QT       += webkit

TEMPLATE = lib

DEFINES += LCONTROLS_LIBRARY

UI_DIR = ./tmp
MOC_DIR = ./tmp
OBJECTS_DIR = ./tmp
RCC_DIR = ./tmp

INCLUDEPATH += "include/comcontrols"
CONFIG+=debug_and_release
QT += network xml
CONFIG(debug,debug|release) {
    TARGET = comcontrols
    DESTDIR = lib/debug
}
else {
    TARGET = comcontrols
    DESTDIR = lib/release
}


SOURCES += \
    src/comcontrols.cpp \
    src/vmcontrol.cpp \
    src/pagenodesitem.cpp \
    src/ipeditor.cpp \
    src/graphicstextitem.cpp \
    src/graphicstablesubitem.cpp \
    src/graphicstablerow.cpp \
    src/graphicstableitem.cpp \
    src/graphicstablecolumn.cpp \
    src/graphicspixmapitem.cpp \
    src/graphicsitembutton.cpp \
    src/graphicsemptynoteitem.cpp \
    src/gifproxyitem.cpp \
    src/pagenumbercontrol.cpp \
    src/faderitem.cpp \
    src/downloader.cpp \
    src/custombtn.cpp \
    src/curvewidget.cpp \
    src/custompagenumber.cpp \
    src/heartbeattimer.cpp \
    src/customlineedit.cpp \
    src/rotatewarnningitem.cpp

HEADERS += include/comcontrols/vmcontrol.h \
    include/comcontrols/pagenumbercontrol.h \
    include/comcontrols/pagenodesitem.h \
    include/comcontrols/comcontrols_global.h \
    include/comcontrols/comcontrols.h \
    include/comcontrols/ipeditor.h \
    include/comcontrols/graphicstextitem.h \
    include/comcontrols/graphicstablesubitem.h \
    include/comcontrols/graphicstablerow.h \
    include/comcontrols/graphicstableitem.h \
    include/comcontrols/graphicstablecolumn.h \
    include/comcontrols/graphicspixmapitem.h \
    include/comcontrols/graphicsitembutton.h \
    include/comcontrols/graphicsemptynoteitem.h \
    include/comcontrols/gifproxyitem.h \
    include/comcontrols/faderitem.h \
    include/comcontrols/downloader.h \
    include/comcontrols/custombtn.h \
    include/comcontrols/curvewidget.h \
    include/comcontrols/custompagenumber.h \
    include/comcontrols/heartbeattimer.h \
    include/comcontrols/customlineedit.h \
    include/comcontrols/rotatewarnningitem.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE3DB7DFA
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = comcontrols.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    comcontrols.qrc


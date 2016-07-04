TEMPLATE = app

INCLUDEPATH += "../include/comcontrols"
LIBS +=  -L../lib/release/  -lcomcontrols

SOURCES += \
    controls_item_test.cpp
#HEADERS += \ 
#    custombtn.h



RESOURCES += \
    ../comcontrols.qrc

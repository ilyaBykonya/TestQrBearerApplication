include($${PWD}/../../../Execution.pri) {}
else { error("No Execution.pri in $${_PRO_FILE_}") }
include($${PWD}/../../../Execution.pri) {}
else { error("No Execution.pri in $${_PRO_FILE_}") }


QT += core gui widgets

HEADERS +=

SOURCES += \
    main.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/../../../build/src/Libraries/qt-qrcode/lib/ -lqtqrcode
INCLUDEPATH += $$PWD/../../Libraries/qt-qrcode/lib
DEPENDPATH += $$PWD/../../Libraries/qt-qrcode/lib

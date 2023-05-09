include($${PWD}/../../../Execution.pri) {}
else { error("No Execution.pri in $${_PRO_FILE_}") }
QT += core gui widgets network
include($${PWD}/../../Libraries/qt-qrcode/lib/qt-qrcode-app.pri)

HEADERS += \
    TokenModel/TokenModel.h \
    View/QrCode/QrCodeDialog.h \
    View/QrCode/QrCodeWidget.h \
    View/TokenView.h

SOURCES += \
    TokenModel/TokenModel.cpp \
    View/QrCode/QrCodeDialog.cpp \
    View/QrCode/QrCodeWidget.cpp \
    View/TokenView.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


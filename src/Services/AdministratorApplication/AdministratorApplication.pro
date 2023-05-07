include($${PWD}/../../../Execution.pri) {}
else { error("No Execution.pri in $${_PRO_FILE_}") }
QT += core gui widgets network
include($${PWD}/../../Libraries/qt-qrcode/lib/qt-qrcode-app.pri)

HEADERS += \
    UserBearersModel/UserBearersModel.h \
    View/BearerQrCore/BearerQrCodeMessageBox.h \
    View/BearerQrCore/QrCodeWidget.h \
    View/UserBearersView.h

SOURCES += \
    UserBearersModel/UserBearersModel.cpp \
    View/BearerQrCore/BearerQrCodeMessageBox.cpp \
    View/BearerQrCore/QrCodeWidget.cpp \
    View/UserBearersView.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


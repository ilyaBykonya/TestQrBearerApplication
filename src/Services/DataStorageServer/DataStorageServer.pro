include($${PWD}/../../../Execution.pri) {}
else { error("No Execution.pri in $${_PRO_FILE_}") }
QT += core httpserver
CONFIG += cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Controllers/ImageController.h \
    Controllers/TokenController.h \
    Storages/TokenRepository.h \
    Utils/Http/AbstractHttpController.h \
    Storages/ImageRepository.h \
    Utils/Http/TokenAuthorizator.h

SOURCES += \
    Controllers/ImageController.cpp \
    Controllers/TokenController.cpp \
    Storages/ImageRepository.cpp \
    Storages/TokenRepository.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

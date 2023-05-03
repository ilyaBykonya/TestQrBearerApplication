include($${PWD}/../../../Execution.pri) {}
else { error("No Execution.pri in $${_PRO_FILE_}") }
QT += core httpserver
CONFIG += cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Controllers/BearersController.h \
    Controllers/ImagesController.h \
    Storages/UserBearersRepository.h \
    Utils/Http/QAbstractHttpController.h \
    Utils/Http/QHttpAdminAuthorizator.h \
    Utils/Http/QHttpServerMiddleware.h \
    Storages/ImageRepository.h

SOURCES += \
    Controllers/BearersController.cpp \
    Controllers/ImagesController.cpp \
    Storages/ImageRepository.cpp \
    Storages/UserBearersRepository.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

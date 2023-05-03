#include(Common.pri)
#include(Library.pri)
#include(Execution.pri)

TEMPLATE = subdirs

SUBDIRS += \
    Libraries \
    Services

Libraries.subdir = src/Libraries
Services.subdir = src/Services
Services.depends = Libraries

PROJECT_ROOT_PATH = $${PWD}/

win32: OS_SUFFIX = win32
unix: OS_SUFFIX = linux
linux-g++: OS_SUFFIX = linux

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/
LIBS_PATH = $${PROJECT_ROOT_PATH}/lib/$${OS_SUFFIX}/
INTERNAL_INCLUDE_PATH = $${PROJECT_ROOT_PATH}/src/
EXTERNAL_INCLUDE_PATH = $${PROJECT_ROOT_PATH}/import/

BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

LIBS += -L$${LIBS_PATH}/
INCLUDEPATH += $${INTERNAL_INCLUDE_PATH}/
INCLUDEPATH += $${EXTERNAL_INCLUDE_PATH}/

CONFIG += c++17
linux-g++: QMAKE_CXXFLAGS += -std=c++17

######################################################################
# Automatically generated by qmake (2.01a) Sun Jul 3 23:45:05 2011
######################################################################

TARGET = eduweb-core
TEMPLATE = lib
QT += xml

unix:LIBS += -lzip
win32:LIBS += -lzip

DEFINES += EDUWEB_CORE_LIBRARY

MOC_DIR = ../../tmp/$${TARGET}
OBJECTS_DIR = ../../tmp/$${TARGET}

unix:DESTDIR = ../../lib/linux
win32:DESTDIR = ../../lib/win32

win32:DLLDESTDIR = ../../release/win32

# Input
HEADERS += eduweb-core.h \
    iplugin.h \
    ireusable.h \
    iprojectdescription.h \
    iproject.h \
    ideployer.h \
    iconfigurable.h \
    iprojectcontainer.h \
    iprojectcanbecontained.h \
	filesystemutils.h \
	pluginmanager.h \
	projectdescription.h \
	settingsmanager.h \
	workspace.h \
    zipfile.h
	

SOURCES += filesystemutils.cpp \
	pluginmanager.cpp \
	projectdescription.cpp \
	settingsmanager.cpp \
	workspace.cpp \
    zipfile.cpp
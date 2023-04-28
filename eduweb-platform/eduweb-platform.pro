######################################################################
# Automatically generated by qmake (2.01a) Sun Jul 3 22:30:21 2011
######################################################################

TEMPLATE = app
TARGET = eduweb
QT += xml

INCLUDEPATH += ../eduweb-core \
	../eduweb-widgets
unix:LIBS += -L../../lib/linux -leduweb-core -leduweb-widgets 
win32:LIBS += -L../../lib/win32 -leduweb-core -leduweb-widgets

unix:DESTDIR = ../../release/linux
win32:DESTDIR = ../../release/win32

MOC_DIR = ../../tmp/$${TARGET}
OBJECTS_DIR = ../../tmp/$${TARGET}
UI_DIR = ../../tmp/$${TARGET}/ui

# Input
HEADERS += mainwindow.h \
    mainformpage.h \
    myprojectspage.h \
	newprojectpage.h \
    deployprojectspage.h \
    applicationsettingspage.h \
	applicationaboutpage.h \
	plugindetailsdialog.h \
	newprojectdialog.h \
	deployprojectdialog.h \
	exportprojectsdialog.h \
	syncprojectsdialog.h \
	linkprojectsdialog.h

SOURCES += main.cpp \
    mainwindow.cpp \
    mainformpage.cpp \
    myprojectspage.cpp \
	newprojectpage.cpp \
    deployprojectspage.cpp \
    applicationsettingspage.cpp \
	applicationaboutpage.cpp \
	plugindetailsdialog.cpp \
	newprojectdialog.cpp \
	deployprojectdialog.cpp \
	exportprojectsdialog.cpp \
	syncprojectsdialog.cpp \
	linkprojectsdialog.cpp

FORMS += mainwindow.ui \
    myprojectspage.ui \
	newprojectpage.ui \
    deployprojectspage.ui \
    applicationsettingspage.ui \
	applicationaboutpage.ui \
	plugindetailsdialog.ui \
	newprojectdialog.ui \
	deployprojectdialog.ui \
	exportprojectsdialog.ui \
	syncprojectsdialog.ui \
	linkprojectsdialog.ui

RESOURCES += resources.qrc
win32:RC_FILE = resources-win32.rc

OTHER_FILES += LICENSE.txt
	
TRANSLATIONS = translations/$${TARGET}_es.ts \
    translations/$${TARGET}_en.ts
	
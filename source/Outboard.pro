#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T10:58:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Outboard
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    user.cpp \
    qlabelbutton.cpp \
    updatestatusdialog.cpp \
    adduserdialog.cpp

HEADERS  += mainwindow.h \
    user.h \
    DECLARATIONS.h \
    qlabelbutton.h \
    updatestatusdialog.h \
    adduserdialog.h

FORMS    += mainwindow.ui \
    updatestatusdialog.ui \
    adduserdialog.ui

OTHER_FILES +=

copydata.commands = $(COPY_DIR) \"$$PWD/PROFILEPICS\" \"$$OUT_PWD/PROFILEPICS\"
copyconfig.commands = $(COPY_DIR) \"$$PWD/CONFIG\" \"$$OUT_PWD/CONFIG\"
first.depends = $(first) copydata copyconfig
export(first.depends)
export(copydata.commands)
export(copyconfig.commands)

QMAKE_EXTRA_TARGETS += first copydata copyconfig

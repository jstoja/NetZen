CONFIG += debug
DESTDIR = ../bin

OBJECTS_DIR = ../obj/$$TARGET
MOC_DIR = gen
RCC_DIR = gen
UI_DIR = gen

DEPENDPATH += src hdr ui
INCLUDEPATH += hdr ../nzlib/hdr

QMAKE		 = ${shell which qmake-qt4 2> /dev/null || which qmake 2>/dev/null}
QMAKE_OPT	 = -makefile -o qmake.mk

ifeq "${shell uname -s}" "Darwin"
QMAKE_OPT	+= -spec macx-g++
endif

all:		qmake $(TARGET)

qmake:		qmake.mk

qmake.mk:	$(TARGET).pro
	$(QMAKE) $(QMAKE_OPT)

$(TARGET):
	$(MAKE) -f qmake.mk

clean:		qmake
	$(MAKE) -f qmake.mk clean

reset:		clean

new:		clean $(TARGET)

.PHONY:		all qmake $(TARGET) clean reset new

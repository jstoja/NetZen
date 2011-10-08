all:		md5 nzlib nzgui

md5:
	$(MAKE) -C md5

nzlib:		md5
	$(MAKE) -C nzlib

nzgui:
	$(MAKE) -C nzgui

clean:
	$(MAKE) -C md5 clean
	$(MAKE) -C nzlib clean
	$(MAKE) -C nzgui clean

reset:
	$(MAKE) -C md5 reset
	$(MAKE) -C nzlib reset
	$(MAKE) -C nzgui clean

new:
	$(MAKE) -C md5 new
	$(MAKE) -C nzlib new
	$(MAKE) -C nzgui clean all

.PHONY:		all md5 nzlib nzgui clean reset new

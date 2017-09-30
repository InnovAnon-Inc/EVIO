include $(top_srcdir)/restart/src/Makefile-LIBADD.inc
LIBEVIO_LIBADD  = ../restart/src/.libs/librestart.la $(LIBRESTART_LIBADD)
#LIBEVIO_LIBADD += -lev
LIBEVIO_LIBADD += ../libev/.libs/libev.la

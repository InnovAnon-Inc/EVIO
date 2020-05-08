include $(top_srcdir)/restart/src/Makefile-LIBADD.inc

#if USE_SUBMODULES
#LIBEVIO_LIBADD  = ../restart/src/.libs/librestart.la $(LIBRESTART_LIBADD)
#LIBEVIO_LIBADD += ../libev/.libs/libev.la
#else
LIBEVIO_LIBADD  = -lrestart $(LIBRESTART_LIBADD)
LIBEVIO_LIBADD += -lev
#endif

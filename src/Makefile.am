AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
bin_PROGRAMS    =

lib_LTLIBRARIES += libevio.la
include_HEADERS = evio.h
libevio_la_CPPFLAGS = $(GLITTER_CFLAGS) $(RESTART_CFLAGS)
libevio_la_LIBADD   = $(GLITTER_LIBS)   $(RESTART_LIBS) -lev

bin_PROGRAMS += evio-test
evio_test_CPPFLAGS =        $(GLITTER_CFLAGS) $(RESTART_CFLAGS)
evio_test_LDADD    = -levio $(GLITTER_LIBS)   $(RESTART_LIBS) -lev
EXTRA_evio_test_DEPENDENCIES = libevio.la


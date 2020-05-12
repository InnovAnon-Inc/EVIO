AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../restart
#AM_CPPFLAGS += -I $(top_srcdir)/restart/src
#
#SUBDIRS += ../libev
#AM_CPPFLAGS += -I $(top_srcdir)/libev
##libev_CPPFLAGS = -Wno-strict-aliasing
#endif

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libevio_config evio_test_config

lib_LTLIBRARIES = libevio.la
include_HEADERS = evio.h
#libevio_la_LIBADD = $(LIBEVIO_LIBADD)
libevio_la_LIBADD = @LIBEVIO_LIBADD@

bin_PROGRAMS = evio-test
#evio_test_LDADD = libevio.la $(LIBEVIO_LIBADD)
#evio_test_LDADD = $(EVIO_TEST_LIBADD)
evio_test_LDADD = @EVIO_TEST_LIBADD@
EXTRA_evio_test_DEPENENCIES = libevio.la

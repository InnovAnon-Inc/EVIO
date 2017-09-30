AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

SUBDIRS += ../restart
AM_CPPFLAGS += -I $(top_srcdir)/restart/src

SUBDIRS += ../libev
AM_CPPFLAGS += -I $(top_srcdir)/libev
#libev_CPPFLAGS = -Wno-strict-aliasing

include Makefile-LIBADD.inc

lib_LTLIBRARIES = libevio.la
include_HEADERS = evio.h
libevio_la_LIBADD = $(LIBEVIO_LIBADD)

bin_PROGRAMS = evio-test
evio_test_LDADD = libevio.la $(LIBEVIO_LIBADD)

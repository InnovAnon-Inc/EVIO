lib_LTLIBRARIES = libevio.la
libevio_la_SOURCES = evio.c
include_HEADERS = evio.h
libevio_la_LIBADD = -lrestart -lev

bin_PROGRAMS = evio
evio_SOURCES = main.c
evio_LDADD = libevio.la -lrestart -lev

AM_CPPFLAGS = -D__STDC_INT64__

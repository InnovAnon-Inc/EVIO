# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libevio.pc src/evio-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libevio.pc.in src/evio-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4


AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/rapidxml

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = layout

layout_SOURCES = layout.cpp
layout_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
layout_LDADD = $(CUSTOM_LDADD)
layoutdir = $(prefix)/share/egt/samples/layout
dist_layout_DATA = $(wildcard $(top_srcdir)/layout/icons/*.png)

layout_LDFLAGS = $(AM_LDFLAGS)

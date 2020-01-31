AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS)

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = icon

icon_SOURCES = icon.cpp
icon_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
icon_LDADD = $(CUSTOM_LDADD)
icondir = $(prefix)/share/egt/samples/icon/icons
dist_icon_DATA = $(wildcard $(top_srcdir)/icon/*.png)
icon_LDFLAGS = $(AM_LDFLAGS)

AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS)

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = infotain

infotain_SOURCES = infotain.cpp
infotain_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
infotain_LDADD = $(CUSTOM_LDADD)
infotaindir = $(prefix)/share/egt/examples/infotain
dist_infotain_DATA = $(wildcard $(top_srcdir)/infotain/images/*.png)
infotain_LDFLAGS = $(AM_LDFLAGS)

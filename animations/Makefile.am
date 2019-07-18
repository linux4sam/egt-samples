AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS)

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = animations

animations_SOURCES = animations.cpp
animations_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
animations_LDADD = $(CUSTOM_LDADD)
animationsdir = $(prefix)/share/egt/samples/animations
dist_animations_DATA = $(wildcard $(top_srcdir)/animations/*.png)

animations_LDFLAGS = $(AM_LDFLAGS)

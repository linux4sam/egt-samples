AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS)

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = brick

brick_SOURCES = brick.cpp
brick_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
brick_LDADD = $(CUSTOM_LDADD)
brickdir = $(prefix)/share/egt/samples/brick
dist_brick_DATA = $(wildcard $(top_srcdir)/brick/*.png)
brick_LDFLAGS = $(AM_LDFLAGS)

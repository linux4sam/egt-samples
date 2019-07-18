AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/rapidxml

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = newsfeed

newsfeed_SOURCES = newsfeed.cpp
newsfeed_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
newsfeed_LDADD = $(CUSTOM_LDADD)
newsfeeddir = $(prefix)/share/egt/samples/newsfeed
dist_newsfeed_DATA = $(wildcard $(top_srcdir)/newsfeed/*.xml)

newsfeed_LDFLAGS = $(AM_LDFLAGS)

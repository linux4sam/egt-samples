AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/external/Chipmunk2D/include

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = chipdrop

chipdrop_SOURCES = chipdrop.cpp shape.cpp shape.h
chipdrop_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
chipdrop_LDADD = $(top_builddir)/external/libchipmunk2d.la $(CUSTOM_LDADD)
chipdropdir = $(prefix)/share/egt/examples/chipdrop
chipdrop_LDFLAGS = $(AM_LDFLAGS)

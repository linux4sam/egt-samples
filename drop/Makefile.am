AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/external/Box2D

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = drop

drop_SOURCES = drop.cpp shape.cpp shape.h
drop_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
drop_LDADD = $(top_builddir)/external/libbox2d.la $(CUSTOM_LDADD)
dropdir = $(prefix)/share/egt/examples/drop
drop_LDFLAGS = $(AM_LDFLAGS)

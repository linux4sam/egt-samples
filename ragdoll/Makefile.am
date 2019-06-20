AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/external/Box2D

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = ragdoll

ragdoll_SOURCES = ragdoll.cpp hooman.cpp hooman.h
ragdoll_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
ragdoll_LDADD = $(top_builddir)/external/libbox2d.la $(CUSTOM_LDADD)
ragdoll_LDFLAGS = $(AM_LDFLAGS)

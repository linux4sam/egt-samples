AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS)

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = water

water_SOURCES = water.cpp
water_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
water_LDADD = $(CUSTOM_LDADD)
waterdir = $(prefix)/share/egt/samples/water
dist_water_DATA = $(wildcard $(top_srcdir)/water/*.png)

water_LDFLAGS = $(AM_LDFLAGS)

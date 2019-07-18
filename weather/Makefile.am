AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/external/Box2D

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = weather

weather_SOURCES = weather.cpp
weather_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS) $(JSONCPP_CFLAGS)
weather_LDADD = $(CUSTOM_LDADD) $(JSONCPP_LIBS)
weatherdir = $(prefix)/share/egt/samples/weather
dist_weather_DATA = $(wildcard $(top_srcdir)/weather/*.jpg)

weather_LDFLAGS = $(AM_LDFLAGS)

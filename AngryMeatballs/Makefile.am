AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS) \
	-isystem $(top_srcdir)/external/Box2D

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = AngryMeatballs

AngryMeatballs_SOURCES = main.cpp \
	Ball.h Ball.cpp \
	MainWindow.h MainWindow.cpp \
	RotateImageWidget.h RotateImageWidget.cpp
AngryMeatballs_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS) \
	-DASSETDIR=\"$(datadir)/egt/samples/AngryMeatballs\"
AngryMeatballs_LDADD = $(top_builddir)/external/libbox2d.la $(CUSTOM_LDADD)
AngryMeatballsdir = $(prefix)/share/egt/samples/AngryMeatballs
dist_AngryMeatballs_DATA = $(wildcard $(top_srcdir)/AngryMeatballs/*.png) \
	$(wildcard $(top_srcdir)/AngryMeatballs/AngryMeatballs.xml)
AngryMeatballs_LDFLAGS = $(AM_LDFLAGS)

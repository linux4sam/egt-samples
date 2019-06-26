AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = $(WARN_CFLAGS) \
	$(LIBEGT_CFLAGS)

CUSTOM_LDADD = $(LIBEGT_LIBS)

bin_PROGRAMS = gallery

gallery_SOURCES = gallery.cpp
gallery_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
gallery_LDADD = $(CUSTOM_LDADD)
gallerydir = $(prefix)/share/egt/examples/gallery
dist_gallery_DATA = $(wildcard $(top_srcdir)/gallery/*.png) \
	$(wildcard $(top_srcdir)/gallery/movies/*.png) \
	$(wildcard $(top_srcdir)/gallery/movies/*.jpg)
gallery_LDFLAGS = $(AM_LDFLAGS)

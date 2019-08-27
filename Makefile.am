SUBDIRS = \
external \
brick \
icon \
infotain \
drop \
ragdoll \
chipdrop \
water \
animations \
layout

if HAVE_JSONCPP
SUBDIRS += \
weather
endif

if HAVE_EGT_NETWORK_HTTP_H
SUBDIRS += \
newsfeed
endif

if HAVE_EGT_VIDEO_H
SUBDIRS += \
gallery
endif

EXTRA_DIST = \
	README.md \
	COPYING \
	rapidxml

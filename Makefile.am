SUBDIRS = \
external \
AngryMeatballs \
brick \
icon \
drop \
ragdoll \
chipdrop \
water \
layout

if HAVE_EGT_NETWORK_HTTP_H
SUBDIRS += \
newsfeed

if HAVE_JSONCPP
SUBDIRS += \
weather
endif
endif

if HAVE_EGT_VIDEO_H
SUBDIRS += \
gallery
endif

EXTRA_DIST = \
	README.md \
	COPYING \
	rapidxml

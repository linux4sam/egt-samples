# EGT Gallery Sample

This is a sample application that shows a navigable list of video thumbnails
that can be selected to play an associated video.

# Generating Content

The gallery sample does not come with any pre-generated content.

There is a provided encode.sh script with the gallery sample that depends on
imagemagick and the encode.sh script provided with the egt repository at
`examples/video/data/encode.sh`.  You would execute this script in a directory
containing *.jpg and *.mov files.  For example:

```
PATH=~/egt/examples/video/data/:$PATH ./encode.sh
```

This script expects the the current directory to have a list of associated *.jpg
and *.mov files.

For example:
- alpha-trailer-2_h480p.jpg
- alpha-trailer-2_h480p.mov
- a-star-is-born-trailer-1_h480p.jpg
- a-star-is-born-trailer-1_h480p.mov

It will generate:
- alpha-trailer-2_h480p.png
- alpha-trailer-2_h480p.png.avi
- a-star-is-born-trailer-1_h480p.png
- a-star-is-born-trailer-1_h480p.png.avi

Those files generated are the files the gallery sample will expect to
exist in a `movies` directory, which defaults at `/usr/share/samples/gallery/movies`
but you can also specify an alternate directory to find the `movies` directory
with EGT_SEARCH_PATH environment variable.

```
EGT_SEARCH_PATH=/my/custom/path egt_gallery
```
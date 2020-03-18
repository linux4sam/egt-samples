#!/bin/sh

# Must have examples/video/data/encode.sh from the egt repository in the PATH to
# run this script.
#
# Expects the current directory to have a list of associatd *.jpg and *.mov
# files.
#
# For example:
# alpha-trailer-2_h480p.jpg
# alpha-trailer-2_h480p.mov
# a-star-is-born-trailer-1_h480p.jpg
# a-star-is-born-trailer-1_h480p.mov
#
# It will generate:
# alpha-trailer-2_h480p.png
# alpha-trailer-2_h480p.png.avi
# a-star-is-born-trailer-1_h480p.png
# a-star-is-born-trailer-1_h480p.png.avi
#

set -x

# convert original jpg images to png images and resize
for f in *.jpg
do
    base=$(echo "${f}" | cut -f 1 -d '.')
    convert -resize x148 "${f}" "${base}.png"
done

# encode videos
for f in *.png
do
    base=$(echo "${f}" | cut -f 1 -d '.')

    encode.sh -i "${base}.mov" -x 320 -y 192 mpeg1

    mv ${base}_mpeg1.avi ${base}.png.avi

done

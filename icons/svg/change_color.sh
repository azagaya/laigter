#!/bin/bash
color=$1
for icon in ./*.svg; do
	convert -density 192 -background none $icon -alpha off -fill $1 -opaque black -alpha on "$(basename "$icon" .svg).png"
done

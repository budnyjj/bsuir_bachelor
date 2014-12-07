#!/bin/bash

# Merge images together and create video with ffmpeg

MERGE_BIN=merge/bin/merge

INPUT_IMG_DIR_A="input/input_a/img"
INPUT_IMG_DIR_B="input/input_b/img"

OUTPUT_IMG_DIR="output/img"
OUTPUT_VIDEO_DIR="output/video"

echo "Merge images..."
for img_name in $(ls $INPUT_IMG_DIR_A/*morph.png | xargs -n1 basename)
do
    echo "Process $img_name"
    ${MERGE_BIN} -o $OUTPUT_IMG_DIR/$img_name\
                 $INPUT_IMG_DIR_A/$img_name $INPUT_IMG_DIR_B/$img_name
done;

echo "Create video..."
ffmpeg -r 1/2 -i $OUTPUT_IMG_DIR/%05d.morph.png -c:v libx264 -r 30 -pix_fmt yuv420p $OUTPUT_VIDEO_DIR/output.mp4

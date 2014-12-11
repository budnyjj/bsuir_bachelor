#!/bin/bash

# Clear temporary images

INPUT_IMG_DIR_A="input/input_a/img"
INPUT_IMG_DIR_B="input/input_b/img"

OUTPUT_IMG_DIR="output/img"
OUTPUT_VIDEO_DIR="output/video"

rm -rf $INPUT_IMG_DIR_A/*.morph.png
rm -rf $INPUT_IMG_DIR_B/*.morph.png

rm -rf $OUTPUT_IMG_DIR/*.morph.png
rm $OUTPUT_VIDEO_DIR/output.mp4

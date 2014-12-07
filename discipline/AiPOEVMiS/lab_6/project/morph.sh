#!/bin/bash

# Transform images to make video

INPUT_IMG_DIR_A="input/input_a/img"
INPUT_IMG_DIR_B="input/input_b/img"

convert $INPUT_IMG_DIR_A/base_1.png\
        $INPUT_IMG_DIR_A/base_2.png\
        -delay 10 -morph 10\
        $INPUT_IMG_DIR_A/%05d.morph.png

convert $INPUT_IMG_DIR_B/base_1.png\
        $INPUT_IMG_DIR_B/base_2.png\
        -delay 10 -morph 10\
        $INPUT_IMG_DIR_B/%05d.morph.png

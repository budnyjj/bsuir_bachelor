DIR_DRAWINGS:=\
	implementation_cv_training \
	implementation_cv_recognition

DIR_POSTERS:=\
	design_general \
	design_ui \
	implementation_general \
	implementation_ui

OUT_DRAWINGS:=drawings.pdf
OUT_POSTERS:=posters.pdf

SRC_DRAWINGS:=$(foreach dir,$(DIR_DRAWINGS),$(dir)/$(dir).pdf)
SRC_POSTERS:=$(foreach dir,$(DIR_POSTERS),$(dir)/$(dir).pdf)


default: merge_drawings merge_posters

merge_drawings: $(addprefix compile_,$(DIR_DRAWINGS))
	pdfunite $(SRC_DRAWINGS) $(OUT_DRAWINGS)

merge_posters: $(addprefix compile_,$(DIR_POSTERS))
	pdfunite $(SRC_POSTERS) $(OUT_POSTERS)

compile_%:
	make -C "$*" compile

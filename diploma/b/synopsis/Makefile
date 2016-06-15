default: compile

compile:
	$(MAKE) -C include/docs compile
	pdflatex synopsis.tex

bib:
	bibtex8 -B synopsis.aux

clean:
	$(MAKE) -C include/docs clean
	$(RM) *.log
	$(RM) *~
	$(RM) *.dvi
	$(RM) text/*.log
	$(RM) text/*~
	$(RM) text/*.dvi


.PHONY: clean compile

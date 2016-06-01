default: compile

compile:
	$(MAKE) -C include/docs compile
	pdflatex diploma.tex

bib:
	bibtex8 -B diploma.aux

clean:
	$(MAKE) -C include/docs clean
	$(RM) *.log
	$(RM) *~
	$(RM) *.dvi
	$(RM) text/*.log
	$(RM) text/*~
	$(RM) text/*.dvi


.PHONY: clean compile

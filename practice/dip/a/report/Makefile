default: compile

compile:
	pdflatex report.tex

bib:
	bibtex8 -B report.aux

clean:
	$(RM) *.log
	$(RM) *~
	$(RM) *.dvi
	$(RM) text/*.log
	$(RM) text/*~
	$(RM) text/*.dvi


.PHONY: clean bib compile


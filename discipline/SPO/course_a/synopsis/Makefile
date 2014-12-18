default: compile

compile:
	pdflatex course.tex

bib:
	bibtex8 -B course.aux

clean:
	$(RM) *.log
	$(RM) *.out
	$(RM) *.toc
	$(RM) *.aux
	$(RM) *.blg
	$(RM) *.bbl
	$(RM) *~
	$(RM) *.dvi
	$(RM) text/*.log
	$(RM) text/*~
	$(RM) text/*.dvi

.PHONY: clean bib compile

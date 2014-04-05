default: compile

compile:
	pdflatex course.tex

bib:
	bibtex8 -B course.aux

clean:
	$(RM) *.log
	$(RM) *.out
	$(RM) *.aux
	$(RM) *.toc
	$(RM) *.pdf
	$(RM) *~
	$(RM) *.dvi
	$(RM) text/*.log
	$(RM) text/*~
	$(RM) text/*.dvi


.PHONY: clean compile
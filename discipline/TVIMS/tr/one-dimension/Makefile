PYTHON=python2
DATA=data/data.txt

default: calc report

clean:
	rm -rf *.log
	rm -rf *~
	rm -rf *.dvi
	rm -rf *.aux

calc:
	${PYTHON} tr.py ${DATA}

doc:
	cd doc; make doc

report:
	pdflatex report.tex

.PHONY: clean doc

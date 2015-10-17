EXEC="text_processing.py"

default: demonstrate

demonstrate: substring count repeats replace reverse intersection length

substring:
	@echo "Test substring command:"
	./$(EXEC) substring --start 1 --length 3 "wdads"
	@echo

count:
	@echo "Test count command:"
	./$(EXEC) count --target abc "abc abc def abc"
	@echo

repeats:
	@echo "Test repeats command:"
	./$(EXEC) repeats "ads aad ads"
	@echo

replace:
	@echo "Test replace command:"
	./$(EXEC) replace --source "adsf" --target "adsf2" "adsf adfadfwe"
	@echo

reverse:
	@echo "Test reverse command:"
	./$(EXEC) reverse "adsf adsfageg dsfg sd"
	@echo

intersection:
	@echo "Test intersection command:"
	./$(EXEC) intersection "asf asdfg dfg dsfg sd" "asf asdfeargd dfg gad gfa "
	@echo

length:
	@echo "Test length command:"
	./$(EXEC) length "asfasdf"
	@echo

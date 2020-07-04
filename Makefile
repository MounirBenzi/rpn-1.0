rpn.exe: rpnmain.c
	gcc -std=c99 -Wall rpnmain.c -o rpn.exe

test: rpn.exe
	python tests/runtests.py

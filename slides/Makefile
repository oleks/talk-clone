.PHONY: all clean

INCLUDED=../src/fork.c ../src/work.c ../src/clone_simple.c
GENTEX=gen-fork-trace.tex gen-work-su.tex

all: $(INCLUDED) $(GENTEX)
	./latexrun master.tex

gen-fork-trace.tex: ../src/fork.c ../src/Makefile Makefile
	make -C ../src/ fork-trace
	echo "\begin{lstlisting}[language=c]" > $@
	cat ../src/fork-trace | grep -B1 -A2 "clone" >> $@
	echo "\end{lstlisting}" >> $@

gen-work-su.tex: ../src/work.c ../src/Makefile Makefile
	make -C ../src/ work.su
	echo "\begin{verbatim}" > $@
	cat ../src/work.su >> $@
	echo "\end{verbatim}" >> $@

clean:
	rm -f gen-*
	rm -f latex.out/*

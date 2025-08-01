prepro: header_include.o macro_prepro.o
	cc header_include.o macro_prepro.o -o prepro

header_include.o: header_include.c
	cc -c header_include.c

macro_prepro.o: macro_prepro.c
	cc -c macro_prepro.c

clean:
	rm *.o prepro


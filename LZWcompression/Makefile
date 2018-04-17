goal: packR

pack=packR.cc
lzw=lzw.cc
tar=tar.c

flags=-ltar

packR:
	g++ -g -o packR ${pack} ${lzw} ${tar} ${flags}

clean:
	rm -f packR

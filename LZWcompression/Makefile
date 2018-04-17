goal: packR

pack=packR.cc
lzw=lzw.cc
tar=tar.c

flags=-ltar

packR:
	g++ -std=c++17 -g -o packR ${pack} ${lzw} ${tar} ${flags}

clean:
	rm -f packR

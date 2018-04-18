goal: MD5

MD5: MD5checksum.hh MD5checksum.cc
	g++ -g -o testMD5 testing-MD5.cc MD5checksum.cc -lssl -lcrypto

clean:
	rm -f testMD5

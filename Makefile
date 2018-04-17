goal: stress

stress:
	gcc -o stress-test stress-test.c

clean:
	rm -f stress-test

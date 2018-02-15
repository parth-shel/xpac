goal: xpac-server test-client

xpac-server: 	
	g++ -g -std=c++17 -o xpac-server ./src/xpac-server.cc ./src/repo.cc

test-client: 
	g++ -g -std=c++17 -o test-client ./src/test-client.cc

clean:
	rm -f xpac-server
	rm -f test-client

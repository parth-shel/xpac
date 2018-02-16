goal: xpac-server test-client

server=./src/xpac-server.cc
repo=./src/repo.cc
log=./src/server-log.cc
test=./src/test-client.cc

xpac-server: ${server} ${repo} ${log}	
	g++ -g -std=c++17 -o xpac-server ${server} ${repo} ${log}

test-client: ${test}
	g++ -g -std=c++17 -o test-client ${test}

clean:
	rm -f xpac-server
	rm -f test-client

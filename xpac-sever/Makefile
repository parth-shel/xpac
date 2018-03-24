goal: xpac-server test-client generate-universe generate-metadata

server=./src/xpac-server.cc
repo=./src/repo.cc
log=./src/server-log.cc
test=./src/test-client.cc
universe=./scripts/generate_universe.cc
metadata=./scripts/generate_metadata.cc

xpac-server: ${server} ${repo} ${log}	
	g++ -g -std=c++11 -o xpac-server ${server} ${repo} ${log}

test-client: ${test}
	g++ -g -std=c++11 -o test-client ${test}

generate-universe: ${universe}
	g++ -g -std=c++11 -o generate-universe ${universe}

generate-metadata: ${metadata}
	g++ -g -std=c++11 -o generate-metadata ${metadata}

clean:
	rm -f xpac-server
	rm -f test-client
	rm -f generate-universe
	rm -f generate-metadata

goal: xpac-server test-client generate-universe generate-metadata

server=./src/xpac-server.cc
repo=./src/repo.cc
log=./src/server-log.cc
test=./src/test-client.cc
universe=./scripts/generate_universe.cc
metadata=./scripts/generate_metadata.cc

xpac-server: ${server} ${repo} ${log}	
	g++ -g -std=c++17 -o xpac-server ${server} ${repo} ${log}

test-client: ${test}
	g++ -g -std=c++17 -o test-client ${test}

generate-universe: ${universe}
	g++ -g -std=c++17 -o generate-universe ${universe}

genrate-metadata: ${metadata}
	g++ -g -std=c++17 -o generate-metadata ${metadata}

clean:
	rm -f xpac-server
	rm -f test-client

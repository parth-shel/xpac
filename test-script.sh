#!/bin/bash

#testing script for the client

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;36m'
NC='\033[0m'

#compile xpac for testing
printf "${BLUE} compiling xpac client for testing ${NC}\n"
(make clean; make) || exit 1 

#clean up the stored metadata
printf "${BLUE} cleaning up cached metadata ${NC}\n"
rm -rf ${HOME}/.xpac

#test 0 - bad command
printf "${YELLOW} trying to execute a bad command ${NC}\n"
./xpac -bad_command > /dev/null
	
	if (( $? != 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 1 - update the repo
printf "${YELLOW} trying to update the repo ${NC}\n"
./xpac -update > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 2 - install a package
printf "${YELLOW} trying to install a package ${NC}\n"
./xpac -install D > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 2 - install a non existing package
printf "${YELLOW} trying to install a non existing package ${NC}\n"
./xpac -install bad_name > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi


#test 3 - try installing a package again
printf "${YELLOW} trying to install a package again ${NC}\n"
./xpac -install D > /dev/null

	if (( $? != 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 4 - try installing a composite package
printf "${YELLOW} trying to install a composite package ${NC}\n"
./xpac -install A > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 5 - try removing a package that is a dependency
printf "${YELLOW} trying to remove a package that breaks the dependency tree ${NC}\n"
./xpac -remove B > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 6 - try removing a package
printf "${YELLOW} trying to remove a package ${NC}\n"
./xpac -remove A > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi

#test 7 - try removing a package that has already been removed
printf "${YELLOW} trying to remove a package that has already been removed ${NC}\n"
./xpac -remove A > /dev/null

	if (( $? == 0 ));then
		printf "${GREEN} test passed ${NC}\n"
	else
		printf "${RED} test failed ${NC}\n"
	fi


#cleanup
printf "${BLUE} done! cleaning up.. ${NC}\n"
(make clean) || exit 1

#done
exit 0

#include <iostream>

extern void print_err() {
	cout<<"These are common xpac commands used in various situations:"<<endl<<endl;
	cout<<"xpac -install <package_name>\t\tInstall a package including its required dependencies"<<endl;
	cout<<"xpac <package_name>\t\tDisplay package information and prompt user for installation"<<endl;
	cout<<"xpac -install --version <package-name>\t\tInstall specified version of the package for backward compatibility"<<endl;
	cout<<"xpac -install --compile <package-name>\t\tInstall a package by fetching source code and manually compiling it"<<endl;
	cout<<"xpac -update\t\tFetch the most current listing of packages available"<<endl;
	cout<<"xpac -upgrade\t\tUpgrade every installed package and dependencies to most recent version"<<endl;
	cout<<"xpac -list\t\tList all packages available for installation"<<endl;
	cout<<"xpac -remove <package-name>\t\tDelete specified package and orphaned packages"<<endl;
	cout<<"xpac -remove --cleanup\t\tDelete orphaned packages or obsolete dependencies to optimize disk space"<<endl;
	return;
}
#include<iostream>
#include<functional>

using namespace std;

int main(int argc, char** argv){
	hash<string> str_hash;
	cout<<to_string(str_hash(argv[1]))<<endl;
}

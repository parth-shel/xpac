#include <iostream>
#include <fstream>
#include <ctime>

#include "server-log.hh"

using namespace std;

namespace log {
	// initialize log file if it does not exist and record server start time
	extern int initialize_log(const char * file_name) {
		log_file_name = string(file_name);
		if(file_exists(file_name)) { // log file exists
			ofstream log_file(file_name, ios::out | ios::app);
			if(log_file.is_open()) {
				log_file << get_current_time() << "\t---.---.---.---\t\tserver started\n";
				log_file.close();
			}
			else {
				return -1;
			}
		}
		else { // need to create a new file
			ofstream log_file(file_name, ios::out | ios::trunc);
			if(log_file.is_open()) {
				log_file << "TIME\t\t\t\tIP\t\t\tREQUEST\n";
				log_file << get_current_time() << "\t---.---.---.---\t\tserver started\n";
				log_file.close();
			}
			else {
				return -1;
			}			
		}
		return 0;
	}

	// record time of request and IP of client
	extern int log_event(char * IP, char * request) {
		if(file_exists(log_file_name.c_str())) {
			ofstream log_file(log_file_name.c_str(), ios::out | ios::app);
			if(log_file.is_open()) {
				log_file << get_current_time() << "\t" << IP << "\t\t" << request << "\n";
				log_file.close();
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
		return 0;
	}
	
	// record time of request and IP of client
	extern int log_event(char * IP, char * request, char * resolved_file) {
		if(file_exists(log_file_name.c_str())) {
			ofstream log_file(log_file_name.c_str(), ios::out | ios::app);
			if(log_file.is_open()) {
				log_file << get_current_time() << "\t" << IP << "\t\t" << request << " : " << resolved_file << "\n";
				log_file.close();
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
		return 0;
	}
	
	inline bool file_exists(const char * file_name) {
		std::ifstream f(file_name);
		return f.good();
	}

	inline string get_current_time() {
		// current date/time based on current system
   		time_t now = time(0);
   
		string time_string = ctime(&now);
		time_string.erase(time_string.length()-1, 1);

   		// convert now to string form
   		return time_string;
	}
}

#ifndef log_hh
#define log_hh

#include <string>

namespace log {
	static std::string log_file_name;

	extern int initialize_log(const char * file_name);

	extern int log_event(char * IP, char * request);
	
	extern int log_event(char * IP, char * request, char * resolved_file);
	
	inline bool file_exists(const char * file_name);

	inline std::string get_current_time();
}

#endif

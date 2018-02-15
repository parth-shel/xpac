#ifndef repo_hh
#define repo_hh

namespace repo {
	extern int build_symbol_table(const char * file_name);

	extern int parse_request(char * request, char * file_name);
}

#endif

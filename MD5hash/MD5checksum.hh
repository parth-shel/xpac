#ifndef md5_hh
#define md5_hh

#include <vector>

class MD5checksum {
	private:
		std::string file_path;
		unsigned long file_size;
		unsigned long get_file_size(int fd);
		std::vector<unsigned char> result_hash;

	public:
		MD5checksum(std::string file_path);
		void generate_hash();
		// std::vector get_hash();
		bool compare_hashes(MD5checksum* that);
		~MD5checksum();
};

#endif

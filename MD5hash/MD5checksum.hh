#ifndef md5_hh
#define md5_hh

class MD5checksum {
	private:
		std::string file_path;
		std::string result_hash;
		unsigned long file_size;
		unsigned long get_file_size(int fd);

	public:
		MD5checksum(std::string file_path);
		void generate_hash();
		std::string get_hash();
};

#endif

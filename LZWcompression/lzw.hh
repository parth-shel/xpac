#ifndef lzw_hh
#define lzw_hh

std::string convert_int_to_bin(int number);
void compress(std::string input, int size, std::string filename);
void decompress(std::string input, int size, std::string filename);
std::string convert_char_to_string(const char *pCh, int arraysize);
bool compress_file(std::string filename);
bool decompress_file(std::string filename);

#endif

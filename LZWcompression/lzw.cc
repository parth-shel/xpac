#include <string>
#include <map>

// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
	// Build the dictionary.
	int dictSize = 256;
	std::map<std::string,int> dictionary;
	for (int i = 0; i < 256; i++)
		dictionary[std::string(1, i)] = i;

	std::string w;
	for (std::string::const_iterator it = uncompressed.begin();
			it != uncompressed.end(); ++it) {
		char c = *it;
		std::string wc = w + c;
		if (dictionary.count(wc))
			w = wc;
		else {
			*result++ = dictionary[w];
			// Add wc to the dictionary.
			dictionary[wc] = dictSize++;
			w = std::string(1, c);
		}
	}

	// Output the code for w.
	if (!w.empty())
		*result++ = dictionary[w];
	return result;
}

// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
	// Build the dictionary.
	int dictSize = 256;
	std::map<int,std::string> dictionary;
	for (int i = 0; i < 256; i++)
		dictionary[i] = std::string(1, i);

	std::string w(1, *begin++);
	std::string result = w;
	std::string entry;
	for ( ; begin != end; begin++) {
		int k = *begin;
		if (dictionary.count(k))
			entry = dictionary[k];
		else if (k == dictSize)
			entry = w + w[0];
		else
			throw "Bad compressed k";

		result += entry;

		// Add w+entry[0] to the dictionary.
		dictionary[dictSize++] = w + entry[0];

		w = entry;
	}
	return result;
}

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cout << "usage: lzw <file_name>" << std::endl;
		return -1;
	}
	std::string file_path(argv[1]);
	std::ifstream input_file(file_path, std::ios::in | std::ios::binary);
	if(!input_file.good()) {
		std::cout << "file error!" << std::endl;
	}
	std::string* buf;
	if(input_file.is_open()) {
		buf = new std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	}
	input_file.close();
	std::vector<int> compressed;
	compress(*buf, std::back_inserter(compressed));
	std::string compressed_path (file_path);
	compressed_path.append(".lzw");
	std::ofstream compressed_file(compressed_path, std::ios::out | std::ios::trunc);
	copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(compressed_file));
	compressed_file.close();
	// compressed.clear();
	std::cout  << "compressed: "  << compressed.size() << std::endl;
	std::string decompressed_path(file_path);
	decompressed_path.append(".wzl");
	std::ofstream decompressed_file(decompressed_path, std::ios::out | std::ios::trunc);
	std::string decompressed = decompress(compressed.begin(), compressed.end());
	decompressed_file << decompressed;
	decompressed_file.close();
	std::cout << "decompressed: " << decompressed.length() << std::endl;

	return 0;
}

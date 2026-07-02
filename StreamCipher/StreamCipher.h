#ifndef STREAMCIPHER_H
#define STREAMCIPHER_H
#include <string>

class StreamCipher {
	public:
		void encode(const std::string& plain_text, std::string& cipher_text, const std::string& char_key);
};
#endif

#ifndef STREAMCIPHER_H
#define STREAMCIPHER_H
#include <string>

using namespace std;

class StreamCipher {
	public:
		void encode(const string& plain_text, string& cipher_text, const string& char_key);
};
#endif

#ifndef STREAMCIPHER_H
#define STREAMCIPHER_H
#include <string>

using namespace std;

class StreamCipher {
	public:
		void encode(const string& plainText, string& cipherText, const string& charKey);
};
#endif

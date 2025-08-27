#ifndef STREAMCIPHER_H
#define STREAMCIPHER_H

class StreamCipher {
	public:
		void encode(char* plain_text, char* cipher_text, char* char_key);
};
#endif
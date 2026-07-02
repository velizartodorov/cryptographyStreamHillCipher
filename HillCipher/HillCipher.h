#include <string>
#include "Matrix.h"

using namespace std;

class HillCipher {
	public:
		void encode(string& plain_txt, const Matrix& matrix_key);
};

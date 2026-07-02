#include <string>
#include "Matrix.h"

using namespace std;

class HillCipher {
	public:
		// throws invalid_argument if matrixKey is empty or not square
		void encode(string& plainTxt, const Matrix& matrixKey);
};

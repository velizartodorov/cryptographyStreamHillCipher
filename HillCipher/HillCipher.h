#include <string>
#include "Matrix.h"

using namespace std;

class HillCipher {
	public:
		void encode(string& plainTxt, const Matrix& matrixKey);
};

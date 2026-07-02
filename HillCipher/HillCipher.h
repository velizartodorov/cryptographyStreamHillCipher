#include <string>
#include <vector>

using namespace std;

class HillCipher {
	public:
		void encode(string& plain_txt, const vector<vector<int>>& matrix_key);
};

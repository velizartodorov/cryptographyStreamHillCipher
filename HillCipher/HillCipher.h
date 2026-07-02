#include <string>
#include <vector>

class HillCipher {
	public:
		void encode(std::string& plain_txt, const std::vector<std::vector<int>>& matrix_key);
};

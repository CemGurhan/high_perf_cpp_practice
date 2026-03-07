#include <vector>

class DataProvider {
    std::vector<int> large_data;

    public:
        std::vector<int> get_data() && {
            return large_data;
        }

        // const means the func cannot modify objects, 
        // & means only lvalues can call (non-temp).
        std::vector<int> get_data() const & {
            return large_data;
        }
};

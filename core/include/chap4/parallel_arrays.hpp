#include <string>
#include <vector>


// User is a relatively small struct, so if the following functions
// were to iterate over millions of user entries, the user structs being small
// ensures decent spatial locality. This would improve the efficiency of these
// loops quite massively.
struct User {
    std::string name;
    bool is_playing;
    int level;
};

// pass vector by ref to avoid copy
int get_users_playing(const std::vector<User>& users) {
    int num_playing;
    for (const auto& u : users) 
        if (u.is_playing) {
            ++num_playing;
        }
    
    return num_playing;
}

int get_users_at_level(const std::vector<User>& users, int level) {
    int num_at_level;
    return std::count_if(users.begin(), users.end(), [level](const User& u) {
        return u.level == level;
    });
}

// However, imagine we stored user data in parallel arrays, where each indexable value in the array
// would correspond to another array with the corresponding user. The small size of each data value
// in these arrays would ensure amazing spatial locality. The book sites that the time for these
// functions to complete with a million users is 0.7ms, as opposed to the 3ms the previous functions took
// with the same sample size.

// The boolean array supposedly was even faster, at 0.03 ms. This is because std::vector<bool> is actually a 
// bit array under the hood. These are evry efficient to loop through.

int get_users_playing(std::vector<bool> is_playing_users) {
    return std::count(is_playing_users.begin(), is_playing_users.end(), true);
}

int get_users_at_level(std::vector<int> users_at_level, int level) {
    return std::count(users_at_level.begin(), users_at_level.end(), level);
}

// The drawbacks of this parallel arrays approach is the data is nto as structured and easy to reason with.
// If we needed to access multiple fields via these arrays, then the cost of doing so might not be worth
// splitting fields up into arrays in the first place. Always start simple with your classes and divide up
// as necessary.

#include <sstream>

template<typename ...Ts>
std::string to_string(const Ts&&... value) {
    std::stringstream ss;
    (ss << ... << value);
    return ss.str();
}

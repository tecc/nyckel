#include <nyckel/DomainMatcher.hpp>
#include <nyckel/Util.hpp>
#include <vector>

static std::string delim{"."};

bool nyckel::dpm::matches(const std::string& input, const std::string& pattern, MatcherOptions opts) {
    std::vector<std::string> patternParts = nyckel::util::split(pattern, delim);
    std::vector<std::string> inputParts = nyckel::util::split(input, delim);

    if (!opts.allowSubdomains && patternParts.size() != inputParts.size()) {
        return false;
    }

    for (size_t i = 0; i < patternParts.size(); i++) {
        size_t patternI = patternParts.size() - i;
        if (i > inputParts.size()) {
            return false;
        }
        size_t inputI = inputParts.size() - i;
        if (patternParts[patternI] != inputParts[inputI]) {
            return false;
        }
    }
    return true;
}
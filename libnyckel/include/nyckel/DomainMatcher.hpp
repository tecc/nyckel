#ifndef NYCKEL_DOMAINMATCHER_HPP
#define NYCKEL_DOMAINMATCHER_HPP

#include <string>
namespace nyckel::dpm {
    struct MatcherOptions {
        bool allowSubdomains = true;
    };
    bool matches(const std::string& input, const std::string& pattern, MatcherOptions opts = {});
}

#endif

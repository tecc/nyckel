#ifndef NYCKEL_CONFIGURATION_HPP
#define NYCKEL_CONFIGURATION_HPP

#include <nyckel/Util.hpp>

namespace nyckel {
    struct Configuration {
    private:
        std::string salt{};

    public:
        Configuration() : salt("CHANGE ME") {};

        std::basic_string_view<std::byte> getSalt();
    };

    std::shared_ptr<Configuration> getConfiguration();
    void setConfiguration(const Configuration& config);
}

#endif

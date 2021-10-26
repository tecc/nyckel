#include <nyckel/Configuration.hpp>
#include <utility>

std::basic_string_view<std::byte> nyckel::Configuration::getSalt() {
    // make sure salt constant is at least 8 characters
    if (this->salt.size() < 8) {
        std::string current = this->salt;
        size_t length = current.size();
        this->salt = {8};
        while (length < 8) {
            this->salt += current;
            length += current.size();
        }
    }

    return {(const std::byte*) this->salt.c_str(), this->salt.size()};
}

static nyckel::Configuration globalConfig;
static std::shared_ptr<nyckel::Configuration> configPtr = std::make_shared<nyckel::Configuration>();



std::shared_ptr<nyckel::Configuration> nyckel::getConfiguration() {
    return configPtr;
}
void nyckel::setConfiguration(const nyckel::Configuration& config) {
    globalConfig = config;
    configPtr.reset(&globalConfig);
}

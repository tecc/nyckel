#ifndef NYCKEL_KEYRING_HPP
#define NYCKEL_KEYRING_HPP

#include "Util.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <uuid.h>
#include <vector>

namespace nyckel {

    struct MasterKey {
        uint8_t key[32];
        uint8_t iv[32];
    };

    class Password {
    private:
        std::string domainPattern;
        uint8_t* dataSource;
        util::ByteView data;
        uuids::uuid id;

    public:
        Password(const std::string& domainPattern, util::ByteView blocks);
        Password(const std::string& domainPattern, std::u32string_view view, const MasterKey&);

        util::ByteView getData();
        std::u32string decode(const MasterKey& masterKey);
        void update(const MasterKey& masterKey, const std::u32string_view& password);
    };
    class Keyring {
    private:
        std::vector<std::shared_ptr<Password>> passwords;
        uuids::uuid id;

    public:
        Keyring();

        MasterKey getMasterKey(const std::u32string_view& input);
    };
}// namespace nyckel

#endif

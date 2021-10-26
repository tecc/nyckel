#include <atomic>
#include <nyckel/Keyring.hpp>
#include <openssl/evp.h>
#include <nyckel/Configuration.hpp>
#include <cstring>
#define MASTER_KEY_GEN_ROUNDS 16
#define BUFFER_SIZE 8192
#define MAX_PASSWORD_LENGTH 536870912

std::u32string nyckel::Password::decode(const MasterKey& masterKey) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, masterKey.key, masterKey.iv);
    unsigned char buffer[BUFFER_SIZE];
    int outLength, tempLength;
    if (!EVP_DecryptUpdate(ctx, buffer, &outLength, this->data.data(), (int) this->data.size())) {
        throw std::exception();
    }
    if (!EVP_DecryptFinal_ex(ctx, buffer + outLength, &tempLength)) {
        throw std::exception();
    }
    int completeLength = tempLength + outLength;
    EVP_CIPHER_CTX_free(ctx);
    auto idData = this->id.as_bytes();
    for (int i = 0; i < completeLength; i++) {
        buffer[i] -= (unsigned char) idData[i % idData.size()];
    }
    return {(const char32_t*) buffer, (size_t) completeLength};
}
void nyckel::Password::update(const MasterKey& masterKey, const std::u32string_view& password) {
    if (password.length() > BUFFER_SIZE) {
        throw std::exception();
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, masterKey.key, masterKey.iv);

    int passLengthBytes = (int) (password.length() * 4);
    auto* input = new unsigned char[passLengthBytes];
    const auto* rawData = (const unsigned char*) password.data();
    auto idData = this->id.as_bytes();
    for (int i = 0; i < passLengthBytes; i++) {
        input[i] = rawData[i] + (unsigned char) idData[i % idData.size()];
    }

    int outLength, tmpLength;
    auto* buffer = new unsigned char[BUFFER_SIZE];
    if (!EVP_EncryptUpdate(ctx, buffer, &outLength, input, passLengthBytes)) {
        throw std::exception();
    }

    if (!EVP_EncryptFinal_ex(ctx, buffer + outLength, &tmpLength)) {
        throw std::exception();
    }


    int totalLength = outLength + tmpLength;
    delete[] this->dataSource;
    this->dataSource = new uint8_t[totalLength];
    memcpy(this->dataSource, buffer, totalLength);

    this->data = util::ByteView(this->dataSource, totalLength);

    EVP_CIPHER_CTX_free(ctx);

}
nyckel::util::ByteView nyckel::Password::getData() {
    return this->data;
}
nyckel::Password::Password(const std::string& domainPattern, std::u32string_view view, const MasterKey& masterKey) : domainPattern(domainPattern) {
    update(masterKey, view);
}
nyckel::Password::Password(const std::string& domainPattern, util::ByteView data) : domainPattern(domainPattern), data({data}) {
}

nyckel::Keyring::Keyring() {
    this->id = util::generateUuid();
}
nyckel::MasterKey nyckel::Keyring::getMasterKey(const std::u32string_view& input) {
    if (input.length() > MAX_PASSWORD_LENGTH) {
        throw std::exception();
    }
    MasterKey masterKey{};
    gsl::span<const std::byte, 16> id = this->id.as_bytes();
    std::basic_string_view<std::byte> globalSalt = getConfiguration()->getSalt();
    auto* data = new unsigned char[id.size_bytes() + globalSalt.size()];
    memcpy(data, id.data(), id.size_bytes());
    memcpy(data + id.size_bytes(), globalSalt.data(), globalSalt.size());
    EVP_BytesToKey(
            EVP_aes_256_cbc(), EVP_sha3_512(), // algorithms
            (const unsigned char*) data, // salt
            (const unsigned char*) input.data(), (int) input.length() * 4, // data & data length
            MASTER_KEY_GEN_ROUNDS, // round count
            masterKey.key, masterKey.iv // pointers to key and IV
    );
    return masterKey;
}

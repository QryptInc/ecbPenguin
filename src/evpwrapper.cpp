// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "evpwrapper.h"
#include <functional>
#include <memory>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdexcept>

void throwError(const std::string &text) {
  std::string error{ERR_error_string(ERR_get_error(), NULL)};
  throw std::runtime_error(text + ": " + error);
}

std::vector<uint8_t> evpwrapper::runECB(const std::vector<uint8_t> &bytes,
                                        const std::string &key, bool encrypt) {
  constexpr int AES_128_BLOCK_SIZE = 16;
  std::unique_ptr<EVP_CIPHER_CTX, std::function<void(EVP_CIPHER_CTX *)>> ctx(
      EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);

  if (!ctx.get()) {
    throwError("couldn't initialize openssl");
  }

  if (!EVP_CipherInit_ex(ctx.get(), EVP_get_cipherbyname("aes-128-ecb"), NULL,
                         NULL, NULL, encrypt)) {
    throwError("Couldn't initialize Cipeher");
  }

  if (!EVP_CipherInit_ex(ctx.get(), NULL, NULL,
                         reinterpret_cast<const unsigned char *>(key.c_str()),
                         NULL, encrypt)) {
    throwError("Failed to set key!");
  }

  auto sizeNeeded = AES_128_BLOCK_SIZE *
                    (bytes.size() / AES_128_BLOCK_SIZE + (encrypt ? 1 : 0));
  std::vector<uint8_t> buffer(sizeNeeded);
  int out_len = static_cast<int>(buffer.size());
  if (!EVP_CipherUpdate(ctx.get(), buffer.data(), &out_len, bytes.data(),
                        static_cast<int>(bytes.size()))) {
    throwError("Failed to Encrypt Data");
  }
  auto first_round = out_len;
  out_len = static_cast<int>(buffer.size()) - first_round;
  if (!EVP_CipherFinal_ex(ctx.get(), buffer.data() + first_round, &out_len)) {
    throwError("Couldn't finalize Cipher.");
  }

  if (!encrypt) {
    // need to clear padding
    auto final_byte = buffer.back();
    if (final_byte && final_byte <= AES_128_BLOCK_SIZE &&
        final_byte < buffer.size()) {
      auto padding_start = buffer.end() - final_byte;
      bool match = final_byte == *padding_start;
      for (auto i = padding_start; match && (i < buffer.end()); ++i) {
        match = match && (*i == final_byte);
      }
      if (match) {
        buffer.erase(padding_start, buffer.end());
      }
    }
  }

  return buffer;
}

std::vector<uint8_t> evpwrapper::encrypt(const std::vector<uint8_t> &bytes,
                                         const std::string &key) {
  return runECB(bytes, key, true);
}

std::vector<uint8_t> evpwrapper::decrypt(const std::vector<uint8_t> &bytes,
                                         const std::string &key) {
  return runECB(bytes, key, false);
}

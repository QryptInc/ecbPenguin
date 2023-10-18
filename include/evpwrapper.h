// Copyright © 2020, Qrypt, Inc., All rights reserved.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

class evpwrapper {
private:
  std::vector<uint8_t> runECB(const std::vector<uint8_t> &bytes,
                              const std::string &key, bool encrypt);

public:
  evpwrapper() {}
  virtual ~evpwrapper() = default;
  virtual std::vector<uint8_t> encrypt(const std::vector<uint8_t> &bytes,
                                       const std::string &key);
  virtual std::vector<uint8_t> decrypt(const std::vector<uint8_t> &bytes,
                                       const std::string &key);
};

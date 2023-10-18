// Copyright © 2020, Qrypt, Inc., All rights reserved.
#pragma once

#include "bitmapreader.h"
#include "evpwrapper.h"
#include "filewriter.h"
#include <string>

class ecbencryptor {
private:
  evpwrapper &_ew;

public:
  ecbencryptor(evpwrapper &ew) : _ew{ew} {}
  virtual ~ecbencryptor() = default;
  virtual void encrypt(bitmapreader &in, const std::string &key,
                       filewriter &out);
};

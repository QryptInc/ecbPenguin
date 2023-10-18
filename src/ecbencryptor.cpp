// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "ecbencryptor.h"

void ecbencryptor::encrypt(bitmapreader &in, const std::string &key,
                           filewriter &out) {
  out.write(in.getHeader());
  out.write(_ew.encrypt(in.getBody(), key));
}

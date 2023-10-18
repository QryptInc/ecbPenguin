// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "filewriter.h"

void filewriter::open(const std::string &filename) {
  _file.open(filename, std::ios::binary);
}

void filewriter::write(const std::vector<uint8_t> &bytes) {
  if (!_file.is_open()) {
    throw std::runtime_error("No File Opened.");
  }
  _file.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
  _file.flush();
}

// Copyright © 2020, Qrypt, Inc., All rights reserved.
#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

class filewriter {
private:
  std::ofstream _file;

public:
  filewriter() {}
  virtual ~filewriter() = default;
  virtual void open(const std::string &filename);
  virtual void write(const std::vector<uint8_t> &bytes);
};

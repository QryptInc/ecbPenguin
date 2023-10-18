// Copyright © 2020, Qrypt, Inc., All rights reserved.
#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

class bitmapreader {
private:
  constexpr static size_t BMP_HEADER_SIZE{0x36};
  std::vector<uint8_t> _header;
  std::vector<uint8_t> _body;
  std::string _filename;
  void readFile();
  void checkFile();
  void fileReady();

public:
  bitmapreader() {}
  virtual ~bitmapreader() = default;
  virtual void open(const std::string &bmpFile);
  virtual const std::vector<uint8_t> &getHeader();
  virtual const std::vector<uint8_t> &getBody();
};
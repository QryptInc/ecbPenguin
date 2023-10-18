// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "bitmapreader.h"
#include <iostream>
#include <iterator>

void bitmapreader::readFile() {
  // read the file
  std::ifstream file(_filename, std::ios::binary);
  file >> std::noskipws;
  std::istream_iterator<uint8_t> begin(file), end;
  std::vector<uint8_t> buffer(begin, end);

  // see that we got what we expected.
  if (buffer.size() < BMP_HEADER_SIZE) {
    throw std::runtime_error("file is not large enough to have a header");
  }

  // distribute the bytes
  auto middle = buffer.begin() + BMP_HEADER_SIZE;
  _header.insert(_header.begin(), buffer.begin(), middle);
  _body.insert(_body.begin(), middle, buffer.end());
}

void bitmapreader::checkFile() {
  std::ifstream file(_filename);
  if (!file.is_open()) {
    throw std::runtime_error("Bitmap is not open.");
  }
}

void bitmapreader::open(const std::string &bmpFile) {
  _filename = bmpFile;
  checkFile();
}

void bitmapreader::fileReady() {
  if (_filename.size() == 0) {
    throw std::runtime_error("No file opened.");
  }
}

const std::vector<uint8_t> &bitmapreader::getHeader() {
  fileReady();
  if (_header.size() == 0) {
    readFile();
  }
  return _header;
}

const std::vector<uint8_t> &bitmapreader::getBody() {
  fileReady();
  if (_body.size() == 0) {
    readFile();
  }
  return _body;
}
// Copyright © 2020, Qrypt, Inc., All rights reserved.
#pragma once

#include "bitmapreader.h"
#include "evpwrapper.h"
#include "filewriter.h"
#include <gmock/gmock.h>

class MockReader : public bitmapreader {
public:
  MockReader() : bitmapreader() {}
  MOCK_METHOD(void, open, (const std::string &bmpFile), (override));
  MOCK_METHOD(const std::vector<uint8_t> &, getHeader, (), (override));
  MOCK_METHOD(const std::vector<uint8_t> &, getBody, (), (override));
};

class MockWriter : public filewriter {
public:
  MockWriter() : filewriter() {}
  MOCK_METHOD(void, open, (const std::string &filename), (override));
  MOCK_METHOD(void, write, (const std::vector<uint8_t> &bytes), (override));
};

class MockEVP : public evpwrapper {
public:
  MockEVP() : evpwrapper() {}
  MOCK_METHOD(std::vector<uint8_t>, encrypt,
              (const std::vector<uint8_t> &bytes, const std::string &key),
              (override));
  MOCK_METHOD(std::vector<uint8_t>, decrypt,
              (const std::vector<uint8_t> &bytes, const std::string &key),
              (override));
};

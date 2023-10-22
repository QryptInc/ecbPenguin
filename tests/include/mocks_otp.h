#pragma once

#include "bitmapreader.h"
#include "filewriter.h"
#include "qrngprocessor.h"
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

class MockProcessor : public qrngprocessor{
public:
    MockProcessor() : qrngprocessor() {}
    MOCK_METHOD(std::vector<uint8_t>, processqrngfile, (bitmapreader &in, const std::string &qrngfile), (override));
};
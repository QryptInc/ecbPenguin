// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "filewriter.h"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

bool fileExists(std::string &filename) {
  std::ifstream file(filename);
  return file.is_open();
}

size_t calculateFileSize(std::string &filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("file does not exist");
  }
  return file.tellg();
}

TEST(filewriter, canary) { EXPECT_EQ(1, 1); }

TEST(filewriter, startFile) {
  std::string filename("startFile");
  std::remove(filename.c_str());
  filewriter fw;
  fw.open(filename);
  EXPECT_TRUE(fileExists(filename));
  std::remove(filename.c_str());
}

TEST(filewriter, writeBytes) {
  std::string filename("writeBytes");
  std::remove(filename.c_str());
  filewriter fw;
  fw.open(filename);
  std::vector<uint8_t> bytes{0, 1, 2, 3, 4, 5, 6, 7};
  fw.write(bytes);
  EXPECT_EQ(bytes.size(), calculateFileSize(filename));
}

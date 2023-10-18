// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "bitmapreader.h"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

TEST(bitmapreader, canary) { EXPECT_EQ(1, 1); }

TEST(bitmapreader, test_DataReady) {
  bitmapreader bmr;
  EXPECT_NO_THROW(bmr.open("Tux.bmp"));
}

TEST(bitmapreader, test_getHeader) {
  std::vector<uint8_t> expected{
      0x42, 0x4d, 0x56, 0xf0, 0x1,  0, 0, 0, 0,    0, 0x36, 0,   0,   0,
      0x28, 0,    0,    0,    0xc4, 0, 0, 0, 0xd8, 0, 0,    0,   0x1, 0,
      0x18, 0,    0,    0,    0,    0, 0, 0, 0,    0, 0xc4, 0xe, 0,   0,
      0xc4, 0xe,  0,    0,    0,    0, 0, 0, 0,    0, 0,    0};
  bitmapreader test_bitmap;
  test_bitmap.open("Tux.bmp");
  auto output = test_bitmap.getHeader();
  EXPECT_EQ(output, expected);
}

TEST(bitmapreader, test_getBody) {
  size_t expected = 127008;
  bitmapreader test_bitmap;
  test_bitmap.open("Tux.bmp");
  auto output = test_bitmap.getBody().size();
  EXPECT_EQ(output, expected);
}

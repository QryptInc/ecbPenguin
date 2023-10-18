// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "evpwrapper.h"
#include <gtest/gtest.h>

TEST(evpwrapper, canary) { EXPECT_EQ(1, 1); };

TEST(evpwrapper, encrypt16) {
  evpwrapper ew;
  std::vector<uint8_t> expected{0, 1, 2,  3,  4,  5,  6,  7,
                                8, 9, 10, 11, 12, 13, 14, 15};
  std::string key{"YELLOW SUBMARINE"};
  auto output = ew.decrypt(ew.encrypt(expected, key), key);
  EXPECT_EQ(output, expected);
}

TEST(evpwrapper, encrypt1) {
  evpwrapper ew;
  std::vector<uint8_t> expected{0};
  std::string key{"YELLOW SUBMARINE"};
  auto output = ew.decrypt(ew.encrypt(expected, key), key);
  EXPECT_EQ(output, expected);
}

TEST(evpwrapper, encrypt17) {
  evpwrapper ew;
  std::vector<uint8_t> expected{0, 1,  2,  3,  4,  5,  6,  7, 8,
                                9, 10, 11, 12, 13, 14, 15, 16};
  std::string key{"YELLOW SUBMARINE"};
  auto output = ew.decrypt(ew.encrypt(expected, key), key);
  EXPECT_EQ(output, expected);
}

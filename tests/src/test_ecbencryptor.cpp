// Copyright © 2020, Qrypt, Inc., All rights reserved.
#include "mocks.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ecbencryptor.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::SaveArg;
using ::testing::StrictMock;

TEST(ecbencryptor, canary) { EXPECT_EQ(1, 1); }

TEST(ecbencryptor, constructor) {
  StrictMock<MockEVP> me;
  ecbencryptor test(me);
}

TEST(ecbencryptor, encrypt) {
  std::vector<uint8_t> header(0x36, 1);
  std::vector<uint8_t> body(1000, 2);
  std::vector<uint8_t> out1{};
  std::vector<uint8_t> out2{};
  MockEVP me;
  MockReader mr;
  MockWriter mw;
  InSequence seq;
  EXPECT_CALL(mr, getHeader()).WillOnce(ReturnRef(header));
  EXPECT_CALL(mw, write).WillOnce(SaveArg<0>(&out1));
  EXPECT_CALL(mr, getBody()).WillOnce(ReturnRef(body));
  EXPECT_CALL(me, encrypt).WillOnce(Return(body));
  EXPECT_CALL(mw, write).WillOnce(SaveArg<0>(&out2));
  ecbencryptor ee(me);
  ee.encrypt(mr, "foo", mw);
  EXPECT_EQ(header.size(), out1.size());
  EXPECT_EQ(body.size(), out2.size());
}

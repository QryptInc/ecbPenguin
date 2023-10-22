#include "mocks_otp.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "onetimepad.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::SaveArg;

TEST(otpencryptor, encrypt) {
  
  std::vector<uint8_t> header(0x36, 1);
  std::vector<uint8_t> body(1000, 2);
  std::vector<uint8_t> out1{};
  std::vector<uint8_t> out2{};
  MockProcessor mp;
  MockReader mr;
  MockWriter mw;
  InSequence seq;
  EXPECT_CALL(mr, getHeader()).WillOnce(ReturnRef(header));
  EXPECT_CALL(mw, write).WillOnce(SaveArg<0>(&out1));
  EXPECT_CALL(mp, processqrngfile).WillOnce(Return(body));
  EXPECT_CALL(mr, getBody()).WillOnce(ReturnRef(body));
  EXPECT_CALL(mw, write).WillOnce(SaveArg<0>(&out2));
  otpencryptor otp(mp);
  otp.otpencrypt(mr, "/workspaces/ecbPenguin/tests/data/quantum.qrand", mw);
  EXPECT_EQ(header.size(), out1.size());
  EXPECT_EQ(body.size(), out2.size());
}

// Copyright © 2020, Qrypt, Inc., All rights reserved.

/*
* There is an option to pass command ./penguinify --bitmap Tux.bmp --key 0123456789abcdef --out bar.bmp 
* There is an option to pass command ./penguinify --bitmap Tux.bmp --otp quantum.qrand --out bar.bmp
* We differentiate based on the identifier "key" vs "otp" 
*/


#include <iostream>
#include <string>
#include <vector>

#include "bitmapreader.h"
#include "ecbencryptor.h"
#include "evpwrapper.h"
#include "filewriter.h"
#include "onetimepad.h"
#include "qrngprocessor.h"

void printUsage() {
  std::cout << "penguinify.exe" << std::endl;
  std::cout
      << "Creates encrypted bitmaps that leave the file header intact."
      << std::endl
      << std::endl;
  std::cout << "Usage:" << std::endl;
  std::cout << "penguinify --bitmap <in_file_name>  --<encryption identifier> <16-char string> "
               "--out <out_file_name>"
            << std::endl;
}

bool surroundedByQuotes(const std::string &arg) {
  return (arg.back() == arg.front()) &&
         (arg.front() == '\'' || arg.front() == '\"');
}

int main(int argc, char **argv) {
  if (argc != 7) {
    printUsage();
    return 1;
  }

  std::string bitmap_name{argv[2]};
  std::string identifier{argv[3]};
  std::string key{argv[4]};
  std::string out_name{argv[6]};
  
  if (identifier.substr(2) == "key") {

    if (18 == key.size() && surroundedByQuotes(key)) {
      key.erase(key.begin(), key.begin() + 1);
      key.erase(key.end() - 1, key.end());
    }

    if (key.size() != 16) {
      printUsage();
      return 1;
    }

    try {
      bitmapreader bmrIn;
      evpwrapper evp;
      filewriter fwOut;
      ecbencryptor ecb(evp);
      bmrIn.open(bitmap_name);
      fwOut.open(out_name);
      ecb.encrypt(bmrIn, key, fwOut);
      } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        printUsage();
        return 1;
    }
  }

  if (identifier.substr(2) == "otp") {
    try {
      bitmapreader bmrIn;
      filewriter fwOut;
      qrngprocessor QRNG;
      otpencryptor OTP(QRNG);
      bmrIn.open(bitmap_name);
      fwOut.open(out_name);
      OTP.otpencrypt(bmrIn, key, fwOut);
    } catch (std::exception e) {
      std::cout << e.what() << std::endl;
      printUsage();
      return 1;
    }
  }

}
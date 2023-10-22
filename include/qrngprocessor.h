#pragma once

#include "bitmapreader.h"

#include <string>
#include <cstdint>
#include <fstream>
#include <vector>


/*
* qrngprocessor class processes files containing qrng by opening and reading them, then returns a sufficient quantity of random bytes from qrng file, that corresponds to the body size of the corresponding bitmap files to be encrypted
* qrngprocessor class contains processqrngfile as a public method that takes as input a bitmap file to be encrypted along with a qrng file, and returns random bytes from qrng file equal in size to the body of the input bitmap file intended for encryption
*/

class qrngprocessor {

public:
    qrngprocessor() {}
    virtual ~qrngprocessor() = default;
    virtual std::vector<uint8_t> processqrngfile(bitmapreader &in, const std::string &qrngfile);
};

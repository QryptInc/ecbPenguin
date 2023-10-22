#pragma once

#include "bitmapreader.h"
#include "filewriter.h"
#include "qrngprocessor.h"

#include <string>


/*
* otpencryptor class that facilitates One-Time Pad encryption of a given bitmap file, while keeping the header unchanged
* otpencryptor class contains qrngprocessor class as a private member, and q_xor as a private method (q_xor method computes and returns XOR result of two inputs)
* otpencryptor class contains otpencrypt as a public method that encrypts a body of a given bitmap file using One-Time Pad encryption, leaving the header intact, and writing the header and the encrypted result into an output file
*/
class otpencryptor {

private: 
    qrngprocessor &_processor;
    std::vector<uint8_t> q_xor(const std::vector<uint8_t> &bytes,
                                       const std::vector<uint8_t> &qrng);

public:
    otpencryptor(qrngprocessor &processor) : _processor{processor} {}
    virtual ~otpencryptor() = default;
    virtual void otpencrypt(bitmapreader &in, const std::string &qrngfile,
                       filewriter &out);
};

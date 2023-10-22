#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "onetimepad.h"
#include "qrngprocessor.h"

/*
* Function computes and returns XOR of two inputs 
* INPUT: two constant vectors of unsigned 8-bit integers
* OUTPUT: vector of unsigned 8-bit integers
*/
std::vector<uint8_t> otpencryptor::q_xor(const std::vector<uint8_t> &bytes, const std::vector<uint8_t> &qrng){
    //first want to make sure the inputs have the same size 
    if(bytes.size() != qrng.size()){
        throw std::runtime_error("Inputs provided must have the same size.");
    }
    //initialize an output vector 
    std::vector<uint8_t> cipher(bytes.size());
    //cipher = bytes XOR qrng
    std::transform(bytes.begin(), bytes.end(), qrng.begin(), cipher.begin(), std::bit_xor<uint8_t>());

    return cipher;

}

/*
* Function performs One-Time Pad encryption of an input bitmap file, while keeping the header intact, and writing the header as well as encrypted body into an output file 
* INPUT: an instance of a bitmapreader, name of the qrng file, an instance of a filewriter
* OUTPUT: none
*/
void otpencryptor::otpencrypt(bitmapreader &in, const std::string &qrngfile,
                           filewriter &out) {

    out.write(in.getHeader());  //writing the header unchanged 
    out.write(q_xor(in.getBody(), _processor.processqrngfile(in, qrngfile)));  //writing the OTP encrypted version of the bitmap file body 
}

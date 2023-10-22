#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>

#include "qrngprocessor.h"

/*
* Function takes a name of the qrng file and a bitmap file for encryption, and returns random from qrng file of the same size as the body of the bitmap file to be encrypted  
* INPUT: a bitmap file for encryption, and a name of the qrng file containing quantum randomness 
* OUTPUT: vector of unsigned 8-bit integers from the qrng file, with the same size as the body of the bitmap file for encryption 
*/
std::vector<uint8_t> qrngprocessor::processqrngfile(bitmapreader &in, const std::string &qrngfile) {

    //get the size of the bitmap file body 
    std::vector<uint8_t> file_body = in.getBody();
    size_t size_body = file_body.size();

    //open and read the qrng file
    std::ifstream file(qrngfile, std::ios::binary);
    file >> std::noskipws;
    if (!file.is_open()) {
        throw std::runtime_error("Error opening QRNG file.");
    }
    std::istream_iterator<uint8_t> begin(file), end;
    std::vector<uint8_t> buffer(begin, end);

    //check that the qrng file is large enough to contain enough random sufficient for encryption of the bitmap body 
    if (buffer.size() < size_body) {
        throw std::runtime_error("QRNG file is too small.");
    }

    //initialize the qrng vector and store the random from qrng in it, with the same size as the bitmap file body
    std::vector<uint8_t> qrng;
    qrng.insert(qrng.begin(), buffer.begin(), buffer.begin() + size_body);

    return qrng;

}


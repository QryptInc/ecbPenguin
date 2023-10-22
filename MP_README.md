# Qrypt One-Time Pad Penguinify challenge 


_Maria Perepechaenko_

## Notes: 

- The current program supports both, AES ECB encryption as well as One-Time Pad(OTP) encryption with QRNG random used as a key.
    - To produce an encrypted version of the bitmap file `Tux.bmp` using AES ECB run 
    `./penguinify --bitmap Tux.bmp --key 0123456789abcdef --out ecb_out.bmp`
    - To produce an encrypted version of the bitmap file `Tux.bmp` using OTP with QRNG random run 
    `./penguinify --bitmap Tux.bmp --otp quantum.qrand --out otp_out.bmp`
    - The program distinguishes between AES ECB and OTP based on the keyword "key" or "otp". 


- Encryption of the bitmap file is performed using `otpencrypt` method of the `otpencryptor` class. The main functionality is as follows:
    1. Get the header of the bitmap file to be encrypted, and write it into the output file without any changes to the header
    2. Get the body of the bitmap file, and a qrng file that contains quantum randomness, and return the content of the qrng file equal in size to the body of the bitmap file. 
    3. XOR the body of the bitmap file with the content of the qrng file returned by the above described method. 
    4. Write the encrypted body of the bitmap file into the output file. 


- A new `mocks_otp.h` and `test_otpencryptor.cpp` files are available for convenience and are used for testing. 

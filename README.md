// Copyright © 2023, Qrypt, Inc., All rights reserved.
# Introduction

Penguinify is a tool that replicates the famous "ECB Penguin."

Currently it uses OpenSSL BIO tools and ECB methods to replicate this picture on any bitmap.

# Getting Started

## Option 1: VSCode Devcontainer
If you use vscode and Docker, simply clone this project and open it in its devcontainer: https://code.visualstudio.com/docs/devcontainers/containers

## Option 2: Github Codespaces
Github codespaces can also be used to run devcontainers for in-browser development: https://github.com/features/codespaces

## Option 3: Install Native Tools for Local Development
1. Install build tools for CXX development:
   - Windows: Developer tools @ Microsoft.com
   - Mac: Install XCode from the app store.
2. Install CMake: https://cmake.org/
3. Install Conan: https://conan.io
   - This project's conan recipe was designed for conan 1.60.1; using that specific version is highly recommended (ie `pip install conan==1.60.1`)

# Build and Test

After performing the setup steps above:

1. `mkdir build && cd build`
2. `conan install ..`
3. `conan build ..`
4. `ctest -V -C Release`

# Overview
The ECB Penguin is a famous example of cryptography failing to properly hide information.  It has its own Wikipedia page.  

In this project is a simple command line tool that will allow you to create your own ECB penguin.

The program:

- Reads in a bitmap file.
- Separates the image header from the image body.
- Writes the unencrypted header to the output file.
- Encrypts the image body using OpenSSL AES algorithm in ECB mode.
- Writes the encrypted body to the output file.

At this point you can view it in any image viewer that supports bitmaps.

## Your mission
Your mission is to replace the flawed ECB algorithm and demonstrate how secure One-Time Pads are by comparison.

There are two files in the `tests/data` directory:
- Tux.bmp: An input bitmap that can be used for testing the program.
- quantum.qrand: A file of pure quantum generated randomness.

We want you to:
- Apply a one-time pad to the image body instead of encrypting with AES ECB.
- Add a command line option to pass the name of the \*.qrand file to use as a one-time pad.

Example commands:

To generate an ECB image:
`./penguinify --bitmap Tux.bmp --key 0123456789abcdef --out bar.bmp`

To generate an OTP image:
`./penguinify --bitmap Tux.bmp --otp quantum.qrand --out bar.bmp`

Applying a one-time pad is a simple byte-for-byte XOR operation. The random file itself is the key. It can be decrypted using the exact same operation. For this task, assume that quantum.qrand is high quality and suitable for use directly as a one-time pad.

A typical one-time pad algorithm might use the following operations:
- Read a sufficient quantity of random bytes from quantum.qrand.
- For each byte in the image body, XOR it with a byte from your random buffer.
- Output the encrypted result to the file in the same manner as before.

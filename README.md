# Intro
A project to extract saved browser credentials of various browsers i.e. Chrome, Firefox, Brave, Edge, Opera.

This project has two modules i.e. 1) Extract Master Keys  2) Decrypt data

This data extraction and decryption process employs a two-module design for enhanced organization and potential security benefits.  A Red Teamer, during a security assessment, will typically utilize the first module, written in C++ for improved portability across different operating systems, to extracts the master key and essential files without requiring additional dependency on the target. This separation also reduces the risk of detection by various security solutions.
The second module which are written in Python, typically run on the Red Teamer's machine, decrypts data using the extracted elements i.e. Master key and extracted file(s)


## 1) Extract Master Keys
This module is writted in C++; when run on the target machine, It which extract the "Master key" which is used to encrypt the browsers data.

## 2) Decrypt data
A python module to decrypt the encrypted data using master key (These scripts are the modified form of https://github.com/unode/firefox_decrypt).

## How to build

```
cd "Extract Master Keys" && mkdir build && cd build
cmake ..
cmake --build .
```

## 32/64 build

```
cmake -A x64 ..
cmake -A Win32 ..
```

You can specify the [cmake-generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) to create configuration files for your build system e.g. To generate VS19 project files for a 64-bit build

```
cmake -G "Visual Studio 16 2019" -A x64 ..

```
## Usage
```
extractMasterKeys.exe [path/to/output/dir]
```


## Screenshots
I have currently four browsers installed so four keys are extracted, these keys are also stored in [path/to/output/dir/keys.txt].

For clarity and ease of use, the keys are stored in the hexadecimal (HEX) format. It's important to note that these keys are currently implemented using the AES-256 algorithm, with a key size of 256 bits, which translates to 32 bytes

![Alt text](/screenshots/1.JPG?raw=true "Optional Title")

Encrypted data files of each browser are extracted and placed it their respective folders [path/to/output/dir]

![Alt text](/screenshots/2.JPG?raw=true "Optional Title")

[path/to/output/dir/keys.txt]

![Alt text](/screenshots/3.JPG?raw=true "Optional Title")


## Disclaimer

This software is intended for educational and research purposes, particularly in offensive security (offsec) R&D. It is your responsibility to use it ethically and at your own risk. The developer is not liable for any misuse or consequences of using this software.

## License

[MIT](https://choosealicense.com/licenses/mit/)
# Intro
A utility extract the Master Key (use to encrypt browsers saved credentials) and important file(s) of various browsers (i.e. Chrome, Brave, Edge, Opera) in order to extract the saved credentials.

A Red Teamer, during a security assessment, can utilize this module to extract the master key and essential files without requiring additional dependency on the target. By focusing solely on key extraction, keeps the software footprint small and also reduces its likelihood to appear as suspicious to various security solutions.


## How to build

```
cd "Extract Master Keys" && mkdir build && cd build
cmake ..
cmake --build . --config Release
```

You can specify the [cmake-generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) to create configuration files for your build system e.g.

## 32/64 build

```
cmake -A x64 ..
cmake -A Win32 ..
```

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

This software is intended for educational and research purposes, particularly in offensive security (offsec). It is your responsibility to use it ethically and at your own risk. The developer is not liable for any misuse or consequences of using this software.
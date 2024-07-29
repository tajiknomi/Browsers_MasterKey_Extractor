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

#include "utility.h"
#include <iostream>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Lmcons.h>

bool file_exist_check(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string extractFileNameFromPath(const std::string &path) {
	if (path.empty()) {
		std::cerr << __FUNCTIONW__ << std::endl;
		return std::string();
	}
	const std::size_t found = path.find_last_of("/\\");
	return path.substr(found + 1);
}

std::string getusername(void) {
	char username_arr[UNLEN + 1] = {};
	DWORD username_len = UNLEN + 1;
	GetUserNameA(username_arr, &username_len);
	return std::string(username_arr);
}

std::vector<std::string> makeAbsolutePaths(const std::string & username, const std::vector<std::string> & relativePaths) {

	unsigned int NumOfPaths = relativePaths.size();
	std::vector<std::string> absolutePaths;

	for (unsigned int i = 0; i < NumOfPaths; ++i) {
		absolutePaths.push_back("C:/Users/" + username + relativePaths[i]);
	}
	return absolutePaths;
}

std::string extractPathsForSpecificBrowser(std::vector<std::string> & absoluteBrowserPath, const std::string & browserNameTag) {

	unsigned int NumOfPaths = absoluteBrowserPath.size();
	std::vector<std::string> extractedPaths;
	for (unsigned int i = 0; i < NumOfPaths; ++i) {
		if (file_exist_check(absoluteBrowserPath[i])) {
			if ((absoluteBrowserPath[i].find(browserNameTag) != std::string::npos) || (absoluteBrowserPath[i].find(browserNameTag) != std::string::npos)) {
				return absoluteBrowserPath[i];
			}
		}
	}
	return std::string("");
}
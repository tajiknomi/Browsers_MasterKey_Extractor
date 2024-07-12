#pragma once
#include <string>
#include <vector>


std::string getusername(void);
std::string extractFileNameFromPath(const std::string& path);
std::vector<std::string> makeAbsolutePaths(const std::string& username, const std::vector<std::string>& relativePaths);
std::string extractPathsForSpecificBrowser(std::vector<std::string>& absoluteBrowserPath, const std::string& browserNameTag);
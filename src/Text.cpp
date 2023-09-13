
#include "UTL_Text.h"

namespace utl {
	namespace txt {
		std::string readUntilString(std::string& text, const char limit) {
			std::string bufferText;

			// Ignore delimiter, once a string is found return it
			int charRead{ 0 };
			for (char& c : text) {
				++charRead;

				if (c != limit && charRead < text.length()) { bufferText += c; }	//Make sure c is not the limit, and that it does not go over the end of the string.
				else {
					if (c != limit) { bufferText += c; }
					text.erase(0, charRead);										// Deletes read characters
					return bufferText;
				}
			}

			return bufferText;
		}

		void ensureBackslash(std::string& input){
			// Ensure there is a backslash at the end
			if (input.back() != '\\' && input.back() != '/') {
				input += "\\";
			}
		}

		std::string toUpper(std::string text) {
			if (text == "") {
				return "";
			}
			else {
				std::transform(text.begin(), text.end(), text.begin(), ::toupper);
				return text;
			}
			
		}
		std::string toLower(std::string text) {
			if (text == "") {
				return "";
			}
			else {
				std::transform(text.begin(), text.end(), text.begin(), ::tolower);
				return text;
			}
		}
	}
}
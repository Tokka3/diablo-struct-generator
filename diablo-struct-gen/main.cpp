#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <sstream>


std::string int_to_hex(int i)
{
	std::stringstream stream;
	stream << std::hex << i;
	return stream.str();
}
void copyStringToClipboard(std::string str) {

    // Open the clipboard
    if (!OpenClipboard(NULL)) {
        std::cout << "Could not open clipboard" << std::endl;
        return;
    }

    // Clear the clipboard
    if (!EmptyClipboard()) {
        std::cout << "Could not clear clipboard" << std::endl;
        return;
    }

    // Allocate memory for the string
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
    if (!hg) {
        std::cout << "Could not allocate memory" << std::endl;
        return;
    }

    // Copy the string to the allocated memory
    memcpy(GlobalLock(hg), str.c_str(), str.size() + 1);
    GlobalUnlock(hg);

    // Set the clipboard data
    if (!SetClipboardData(CF_TEXT, hg)) {
        std::cout << "Could not set clipboard data" << std::endl;
        return;
    }

    // Close the clipboard
    CloseClipboard();
}
int main(int argc, char** argv) {

	std::string structName = argv[1];
	int structSize = std::stoi(argv[2]);



	if (structSize > 1000) exit(0);

	std::string result;


	result += "struct " + structName + " { \n";

	for (int i = 0; i <= structSize; i+=4) {
		
		result += "int field_" + int_to_hex(i) + ";\n";

	
	}
	result += "};";
	
	std::cout << result << std::endl;
    copyStringToClipboard(result);

	return 0;





}
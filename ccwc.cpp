#include <iostream>
#include <fstream>
#include <cstring>
using std::cout, std::ifstream, std::endl, std::string, std::cerr;

unsigned int getBytes(const string &fileName) {
    unsigned int bytes = 0;
    ifstream inFS(fileName, std::ios::binary);
    if (!inFS) {
        cerr << "Error opening " << fileName << endl;
        return 0;
    }
    char data;
    while (inFS.get(data)) {
        bytes++;
    }
    return bytes;
}

unsigned int getLines(const string &fileName) {
    unsigned int lines = 0;
    ifstream inFS(fileName);
    if (!inFS) {
        cerr << "Error opening " << fileName << endl;
        return 0;
    }
    string data;
    while(getline(inFS, data)) {
        lines++;
    }
    return lines;
}

unsigned int getWords(const string &fileName) {
    unsigned int words = 0;
    ifstream inFS(fileName);
    if (!inFS) {
        cerr << "Error opening " << fileName << endl;
        return 0;
    }
    string data;
    while (inFS >> data) {
        words++;
    }
    return words;
}

unsigned int getChars(const string &fileName) {
    unsigned int chars = 0;
    ifstream inFS(fileName, std::ios::binary);
    if (!inFS) {
        cerr << "Error opening " << fileName << endl;
        return 0;
    }
    char data;
    while (inFS.get(data)) {
        // Check if the byte is the start of a UTF-8 character
        if ((data & 0xC0) != 0x80) {
            chars++;
        }
    }
    return chars;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [-c|-l|-w|-m] file_name\n";
        return 1;
    }

    string fileName;
    bool countBytes = false, countLines = false, countWords = false, countChars = false;

    // Determine the position of fileName arguement
    int fileNameIndex = -1;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            fileNameIndex = i;
            fileName = argv[i];
            break;
        }
    }

    // Error handling if no file name is provided
    if (fileNameIndex == -1) {
        cerr << "Error: No file name provided\n";
        return 1;
    }

    // Checking for process flags
    for (unsigned int i = 1; i < argc; i++) {
        if (i == fileNameIndex) {
            continue;
        }
        if (strcmp(argv[i], "-c") == 0) {
            countBytes = true;
        } else if (strcmp(argv[i], "-l") == 0) {
            countLines = true;
        } else if (strcmp(argv[i], "-w") == 0) {
            countWords = true;
        } else if (strcmp(argv[i], "-m") == 0) {
            countChars = true;
        }
    }

    // Default options
    if (!(countBytes || countLines || countWords || countChars)) {
        countLines = true;
        countWords = true;
        countBytes = true;
    }

    // Ouput results
    if (countLines) {
        cout << getLines(fileName) << " ";
    }
    if (countWords) {
        cout << getWords(fileName) << " ";
    }
    if (countChars) {
        cout << getChars(fileName) << " ";
    }
    if (countBytes) {
        cout << getBytes(fileName) << " ";
    }

    cout << fileName << endl;

    return 0;
}

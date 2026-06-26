#include "filehandler.h"

// Reads file and collects all tokens sequentially into a flat vector using a character loop
vector<string> readTXT(const string& filename) {
    vector<string> tokens;
    ifstream file(filename);
    if (!file.is_open()) return tokens;

    string line;
    bool isHeader = true;

    while (getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue; // Skip the first line (header)
        }

        string currentToken = "";
        bool insideQuotes = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];

            if (c == '"') {
                insideQuotes = !insideQuotes; // Handle quoted text containing commas
            } else if (c == ',' && !insideQuotes) {
                tokens.push_back(currentToken);
                currentToken = "";
            } else {
                currentToken += c;
            }
        }
        tokens.push_back(currentToken); // Push final token of the line
    }
    file.close();
    return tokens;
}

// Overwrites file with a fresh header row followed by items compiled with commas
void writeTXT(const string& filename, const string& header, const vector<string>& rows) {
    ofstream file(filename);
    if (!file.is_open()) return;

    file << header << "\n";
    for (size_t i = 0; i < rows.size(); ++i) {
        file << rows[i] << "\n";
    }
    file.close();
}

// Seamlessly appends a row directly to the end of a file
void appendTXT(const string& filename, const string& row) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) return;
    file << row << "\n";
    file.close();
}

// Linear search scanning raw rows via step increments based on column count
vector<string> findRow(const string& filename, const string& searchValue, int colIndex) {
    vector<string> result;
    ifstream file(filename);
    if (!file.is_open()) return result;

    string line;
    bool isHeader = true;

    while (getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }

        vector<string> rowTokens;
        string currentToken = "";
        bool insideQuotes = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (c == '"') {
                insideQuotes = !insideQuotes;
            } else if (c == ',' && !insideQuotes) {
                rowTokens.push_back(currentToken);
                currentToken = "";
            } else {
                currentToken += c;
            }
        }
        rowTokens.push_back(currentToken);

        // Check if the specific column matches our search value
        if (colIndex < (int)rowTokens.size() && rowTokens[colIndex] == searchValue) {
            file.close();
            return rowTokens;
        }
    }
    file.close();
    return result;
}

// Verifies if a given key exists inside a target file column
bool rowExists(const string& filename, const string& searchValue, int colIndex) {
    vector<string> found = findRow(filename, searchValue, colIndex);
    return !found.empty();
}
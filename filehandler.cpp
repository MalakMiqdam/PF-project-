#include "filehandler.h"

vector<vector<string>> readTXT(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    if (!file.is_open()) {
        return data;
    }

    string line;
    // Skip the mandatory header row
    if (!getline(file, line)) {
        return data;
    }

    // Read data rows using character parsing loop (no high-level splitting)
    while (getline(file, line)) {
        vector<string> row;
        string currentField = "";
        bool inQuotes = false;

        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];

            if (c == '"') {
                inQuotes = !inQuotes; // Toggle quote state
            } else if (c == ',' && !inQuotes) {
                row.push_back(currentField);
                currentField = "";
            } else {
                currentField += c;
            }
        }
        row.push_back(currentField); // Push final field of the line
        data.push_back(row);
    }

    file.close();
    return data;
}

void writeTXT(const string& filename, const vector<string>& header, const vector<vector<string>>& data) {
    ofstream file(filename);
    if (!file.is_open()) return;

    // Write header
    for (size_t i = 0; i < header.size(); i++) {
        file << header[i] << (i == header.size() - 1 ? "" : ",");
    }
    file << "\n";

    // Write data rows with comma separation and quote handling
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            string field = data[i][j];
            // If field contains a comma, wrap it in quotes as specified
            if (field.find(',') != string::npos) {
                file << "\"" << field << "\"";
            } else {
                file << field;
            }
            file << (j == data[i].size() - 1 ? "" : ",");
        }
        file << "\n";
    }
    file.close();
}

void appendTXT(const string& filename, const vector<string>& row) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) return;

    for (size_t i = 0; i < row.size(); i++) {
        string field = row[i];
        if (field.find(',') != string::npos) {
            file << "\"" << field << "\"";
        } else {
            file << field;
        }
        file << (i == row.size() - 1 ? "" : ",");
    }
    file << "\n";
    file.close();
}

vector<string> findRow(const string& filename, const string& key, int colIndex) {
    vector<vector<string>> data = readTXT(filename);
    for (size_t i = 0; i < data.size(); i++) {
        if (colIndex < data[i].size() && data[i][colIndex] == key) {
            return data[i];
        }
    }
    return vector<string>(); // Return empty vector if not found
}

bool rowExists(const string& filename, const string& value, int colIndex) {
    vector<vector<string>> data = readTXT(filename);
    for (size_t i = 0; i < data.size(); i++) {
        if (colIndex < data[i].size() && data[i][colIndex] == value) {
            return true;
        }
    }
    return false;
}
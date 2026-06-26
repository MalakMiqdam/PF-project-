 #include "filehandler.h"

vector<vector<string>> readTXT(const string& filename) {
    vector<vector<string>> result;
    ifstream file(filename);
    if (!file.is_open()) return result;

    string line;
    bool firstLine = true;

    while (getline(file, line)) {
        if (firstLine) { firstLine = false; continue; }
        
        vector<string> row;
        string field = "";
        bool inQuotes = false;

        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                row.push_back(field);
                field = "";
            } else {
                field += c;
            }
        }
        row.push_back(field);
        if (!row.empty()) result.push_back(row);
    }

    file.close();
    return result;
}

void writeTXT(const string& filename, const vector<string>& header, const vector<vector<string>>& rows) {
    ofstream file(filename);
    
    for (int i = 0; i < header.size(); i++) {
        if (i != 0) file << ",";
        file << header[i];
    }
    file << "\n";

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            if (j != 0) file << ",";
            if (rows[i][j].find(',') != string::npos) {
                file << '"' << rows[i][j] << '"';
            } else {
                file << rows[i][j];
            }
        }
        file << "\n";
    }
    file.close();
}

void appendTXT(const string& filename, const vector<string>& row) {
    ofstream file(filename, ios::app);
    for (int i = 0; i < row.size(); i++) {
        if (i != 0) file << ",";
        if (row[i].find(',') != string::npos) {
            file << '"' << row[i] << '"';
        } else {
            file << row[i];
        }
    }
    file << "\n";
    file.close();
}

vector<string> findRow(const vector<vector<string>>& data, int colIndex, const string& value) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() > colIndex && data[i][colIndex] == value) {
            return data[i];
        }
    }
    return vector<string>();
}

bool rowExists(const vector<vector<string>>& data, int colIndex, const string& value) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() > colIndex && data[i][colIndex] == value) {
            return true;
        }
    }
    return false;
}
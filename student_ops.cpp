#include "student_ops.h"

// Validate roll format: BSAI-YY-XXX
bool isValidRoll(const string& roll) {
    if (roll.length() != 11) return false;
    if (roll.substr(0, 5) != "BSAI-") return false;
    if (!isdigit(roll[5]) || !isdigit(roll[6])) return false;
    if (roll[7] != '-') return false;
    if (!isdigit(roll[8]) || !isdigit(roll[9]) || !isdigit(roll[10])) return false;
    return true;
}

// Name must have no digits
bool isValidName(const string& name) {
    for (int i = 0; i < name.length(); i++) {
        if (isdigit(name[i])) return false;
    }
    return name.length() > 0;
}

// CGPA must be between 0.0 and 4.0
bool isValidCGPA(const string& cgpa) {
    double val = 0;
    bool dot = false;
    for (int i = 0; i < cgpa.length(); i++) {
        if (cgpa[i] == '.' && !dot) { dot = true; continue; }
        if (!isdigit(cgpa[i])) return false;
    }
    val = stod(cgpa);
    return val >= 0.0 && val <= 4.0;
}

void addStudent(const string& roll, const string& name, const string& dept, const string& cgpa) {
    if (!isValidRoll(roll)) { cout << "Invalid roll format! Use BSAI-YY-XXX\n"; return; }
    if (!isValidName(name)) { cout << "Invalid name! No digits allowed.\n"; return; }
    if (!isValidCGPA(cgpa)) { cout << "Invalid CGPA! Must be 0.0 to 4.0\n"; return; }

    vector<vector<string>> data = readTXT("students.txt");
    if (rowExists(data, 0, roll)) { cout << "Student already exists!\n"; return; }

    vector<string> row = {roll, name, dept, cgpa, "active"};
    appendTXT("students.txt", row);
    cout << "Student added successfully!\n";
}

vector<string> searchByRoll(const string& roll) {
    vector<vector<string>> data = readTXT("students.txt");
    return findRow(data, 0, roll);
}

vector<vector<string>> searchByName(const string& name) {
    vector<vector<string>> data = readTXT("students.txt");
    vector<vector<string>> result;
    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() > 1 && data[i][1].find(name) != string::npos) {
            result.push_back(data[i]);
        }
    }
    return result;
}

void updateStudent(const string& roll, int fieldIndex, const string& newValue) {
    vector<vector<string>> data = readTXT("students.txt");
    bool found = false;
    for (int i = 0; i < data.size(); i++) {
        if (data[i][0] == roll) {
            data[i][fieldIndex] = newValue;
            found = true;
            break;
        }
    }
    if (!found) { cout << "Student not found!\n"; return; }
    vector<string> header = {"roll", "name", "dept", "cgpa", "status"};
    writeTXT("students.txt", header, data);
    cout << "Student updated successfully!\n";
}

void softDelete(const string& roll) {
    updateStudent(roll, 4, "inactive");
    cout << "Student deactivated.\n";
}

vector<vector<string>> listActiveStudents() {
    vector<vector<string>> data = readTXT("students.txt");
    vector<vector<string>> active;
    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() > 4 && data[i][4] == "active") {
            active.push_back(data[i]);
        }
    }
    // Selection sort by roll number
    for (int i = 0; i < active.size() - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < active.size(); j++) {
            if (active[j][0] < active[minIdx][0]) minIdx = j;
        }
        if (minIdx != i) swap(active[i], active[minIdx]);
    }
    return active;
}
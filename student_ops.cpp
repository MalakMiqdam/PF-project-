#include "student_ops.h"

void addStudent(const string& roll, const string& name, const string& dept, double cgpa) {
    if (roll.length() != 11) {
        cout << "Error: Invalid Roll Number length! Format must be BSAI-YY-XXX\n";
        return;
    }
    if (roll.substr(0, 5) != "BSAI-" || roll[7] != '-') {
        cout << "Error: Format prefix mismatch! Must be BSAI-YY-XXX\n";
        return;
    }
    if (roll[5] < '0' || roll[5] > '9' || roll[6] < '0' || roll[6] > '9' ||
        roll[8] < '0' || roll[8] > '9' || roll[9] < '0' || roll[9] > '9' || roll[10] < '0' || roll[10] > '9') {
        cout << "Error: Roll year or identifier must be numeric digits!\n";
        return;
    }

    for (size_t i = 0; i < name.length(); i++) {
        if (name[i] >= '0' && name[i] <= '9') {
            cout << "Error: Student name cannot contain digits!\n";
            return;
        }
    }

    if (cgpa < 0.0 || cgpa > 4.0) {
        cout << "Error: CGPA value must be strictly between 0.0 and 4.0!\n";
        return;
    }

    if (rowExists("students.txt", roll, 0)) {
        cout << "Error: A student with Roll Number " << roll << " already exists!\n";
        return;
    }

    vector<string> newStudent = {roll, name, dept, to_string(cgpa), "active"};
    appendTXT("students.txt", newStudent);
    cout << "Student added successfully.\n";
}

void searchByRoll(const string& roll) {
    vector<string> student = findRow("students.txt", roll, 0);
    if (student.empty() || student[4] == "inactive") {
        cout << "Record Not Found\n";
        return;
    }
    cout << "\nRoll No: " << student[0] << "\n";
    cout << "Name: " << student[1] << "\n";
    cout << "Department: " << student[2] << "\n";
    cout << "CGPA: " << student[3] << "\n---------------------\n";
}

void searchByName(const string& name) {
    vector<vector<string>> allStudents = readTXT("students.txt");
    bool found = false;
    
    for (size_t i = 0; i < allStudents.size(); i++) {
        if (allStudents[i][4] == "active") {
            string currentName = allStudents[i][1];
            if (currentName.find(name) != string::npos) {
                cout << "[" << allStudents[i][0] << "] " << allStudents[i][1] << "\n";
                found = true;
            }
        }
    }
    if (!found) cout << "No matching records found\n";
}

void updateStudent(const string& roll, const string& name, const string& dept, double cgpa) {
    vector<vector<string>> data = readTXT("students.txt");
    bool found = false;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i][0] == roll) {
            if (data[i][4] == "inactive") break;
            data[i][1] = name;
            data[i][2] = dept;
            data[i][3] = to_string(cgpa);
            found = true;
            break;
        }
    }

    if (found) {
        vector<string> header = {"roll", "name", "dept", "cgpa", "status"};
        writeTXT("students.txt", header, data);
        cout << "Profile updated successfully.\n";
    } else {
        cout << "Error: Active profile could not be located.\n";
    }
}

void softDelete(const string& roll) {
    vector<vector<string>> data = readTXT("students.txt");
    bool found = false;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i][0] == roll && data[i][4] == "active") {
            data[i][4] = "inactive";
            found = true;
            break;
        }
    }

    if (found) {
        vector<string> header = {"roll", "name", "dept", "cgpa", "status"};
        writeTXT("students.txt", header, data);
        cout << "Student deactivated successfully.\n";
    } else {
        cout << "Error: Active entry not found.\n";
    }
}

vector<vector<string>> listActiveStudents() {
    vector<vector<string>> data = readTXT("students.txt");
    vector<vector<string>> activeList;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].size() > 4 && data[i][4] == "active") {
            activeList.push_back(data[i]);
        }
    }

    if (!activeList.empty()) {
        for (size_t i = 0; i < activeList.size() - 1; i++) {
            size_t minIndex = i;
            for (size_t j = i + 1; j < activeList.size(); j++) {
                if (activeList[j][0] < activeList[minIndex][0]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                vector<string> temp = activeList[i];
                activeList[i] = activeList[minIndex];
                activeList[minIndex] = temp;
            }
        }
    }
    return activeList;
}

void searchAsYouType() {
    cout << "\nEnter characters (. to stop): ";
    string prefix = "";
    
    while (true) {
        string input;
        cin >> input;
        if (input == ".") break;
        prefix += input;
        
        vector<vector<string>> data = readTXT("students.txt");
        size_t pLen = prefix.length();
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i][4] == "active" && data[i][1].length() >= pLen) {
                if (data[i][1].substr(0, pLen) == prefix) {
                    cout << " -> " << data[i][0] << " : " << data[i][1] << "\n";
                }
            }
        }
    }
}
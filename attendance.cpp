#include "attendance.h"

void markAttendance(const string& courseCode, const string& semester, const string& date) {
    vector<vector<string>> enrolled = listEnrolledStudents(courseCode, semester);
    if (enrolled.empty()) {
        cout << "No students enrolled in this course for this semester.\n";
        return;
    }

    vector<vector<string>> data = readTXT("attendance_log.txt");
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i][1] == courseCode && data[i][2] == semester && data[i][3] == date) {
            cout << "Error: Attendance for this date has already been marked.\n";
            return;
        }
    }

    for (size_t i = 0; i < enrolled.size(); i++) {
        string roll = enrolled[i][0];
        cout << "Mark attendance for " << roll << " (P/A/L): ";
        string status;
        cin >> status;
        while (status != "P" && status != "A" && status != "L") {
            cout << "Invalid input. Enter P, A, or L: ";
            cin >> status;
        }
        vector<string> row = {roll, courseCode, semester, date, status};
        appendTXT("attendance_log.txt", row);
    }
    cout << "Attendance logs populated successfully.\n";
}

double getAttendancePct(const string& roll, const string& courseCode, const string& semester) {
    vector<vector<string>> data = readTXT("attendance_log.txt");
    int total = 0;
    double presentWeight = 0.0;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i][0] == roll && data[i][1] == courseCode && data[i][2] == semester) {
            total++;
            if (data[i][4] == "P") {
                presentWeight += 1.0;
            } else if (data[i][4] == "L") {
                presentWeight += 0.5;
            }
        }
    }
    if (total == 0) return 0.0;
    return (presentWeight / total) * 100.0;
}

vector<vector<string>> getShortageList(const string& courseCode, const string& semester) {
    vector<vector<string>> enrolled = listEnrolledStudents(courseCode, semester);
    vector<vector<string>> shortage;

    for (size_t i = 0; i < enrolled.size(); i++) {
        string roll = enrolled[i][0];
        double pct = getAttendancePct(roll, courseCode, semester);
        if (pct < 75.0) {
            vector<string> entry = {roll, enrolled[i][1], to_string(pct)};
            shortage.push_back(entry);
        }
    }
    return shortage;
}

bool undoLastSession(const string& courseCode, const string& semester, const string& date) {
    vector<vector<string>> data = readTXT("attendance_log.txt");
    vector<vector<string>> remainingData;
    bool found = false;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i][1] == courseCode && data[i][2] == semester && data[i][3] == date) {
            found = true;
        } else {
            remainingData.push_back(data[i]);
        }
    }

    if (!found) {
        return false;
    }

    vector<string> header = {"roll", "course_code", "semester", "date", "status"};
    writeTXT("attendance_log.txt", header, remainingData);
    return true;
}

void printDailySheet(const string& courseCode, const string& semester, const string& date) {
    vector<vector<string>> data = readTXT("attendance_log.txt");
    cout << "\n--- Daily Attendance Sheet ---\n";
    cout << "Course: " << courseCode << " | Sem: " << semester << " | Date: " << date << "\n";
    cout << "Roll No\t\tStatus\n";
    cout << "------------------------\n";
    
    bool recordFound = false;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i][1] == courseCode && data[i][2] == semester && data[i][3] == date) {
            cout << data[i][0] << "\t\t" << data[i][4] << "\n";
            recordFound = true;
        }
    }
    if (!recordFound) {
        cout << "No logs found matching parameters.\n";
    }
}
#include "attendance.h"

static vector<vector<string>> attendanceBackup;

void markAttendance(const string& courseCode, const string& date) {
    vector<vector<string>> enrolled = listEnrolledStudents(courseCode);
    if (enrolled.empty()) { cout << "No students enrolled in this course.\n"; return; }

    // Save backup before writing
    attendanceBackup = readTXT("attendance_log.txt");

    for (int i = 0; i < enrolled.size(); i++) {
        string roll = enrolled[i][0];
        cout << "Mark attendance for " << roll << " (P/A/L): ";
        string status;
        cin >> status;
        if (status != "P" && status != "A" && status != "L") {
            cout << "Invalid input, marking as A.\n";
            status = "A";
        }
        vector<string> row = {roll, courseCode, date, status};
        appendTXT("attendance_log.txt", row);
    }
    cout << "Attendance marked for " << date << "\n";
}

double getAttendancePct(const string& roll, const string& courseCode) {
    vector<vector<string>> data = readTXT("attendance_log.txt");
    int total = 0, present = 0, late = 0;
    for (int i = 0; i < data.size(); i++) {
        if (data[i][0] == roll && data[i][1] == courseCode) {
            total++;
            if (data[i][3] == "P") present++;
            else if (data[i][3] == "L") late++;
        }
    }
    if (total == 0) return 0.0;
    return (present + 0.5 * late) / total * 100.0;
}

vector<vector<string>> getShortageList(const string& courseCode) {
    vector<vector<string>> enrolled = listEnrolledStudents(courseCode);
    vector<vector<string>> shortage;
    for (int i = 0; i < enrolled.size(); i++) {
        string roll = enrolled[i][0];
        double pct = getAttendancePct(roll, courseCode);
        if (pct < 75.0) {
            vector<string> entry = {roll, courseCode, to_string(pct)};
            shortage.push_back(entry);
        }
    }
    return shortage;
}

bool undoLastSession(const string& courseCode) {
    if (attendanceBackup.empty()) return false;
    vector<string> header = {"roll", "course_code", "date", "status"};
    writeTXT("attendance_log.txt", header, attendanceBackup);
    cout << "Last session undone successfully.\n";
    return true;
}

void printDailySheet(const string& courseCode, const string& date) {
    vector<vector<string>> data = readTXT("attendance_log.txt");
    cout << "\n--- Daily Attendance Sheet ---\n";
    cout << "Course: " << courseCode << " | Date: " << date << "\n";
    cout << "Roll\t\tStatus\n";
    cout << "------------------------\n";
    for (int i = 0; i < data.size(); i++) {
        if (data[i][1] == courseCode && data[i][2] == date) {
            cout << data[i][0] << "\t\t" << data[i][3] << "\n";
        }
    }
}
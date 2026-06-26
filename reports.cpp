#include "report.h"

void generateStudentTranscript(const string& roll) {
    vector<vector<string>> students = readTXT("students.txt");
    string name = "";
    for (int i = 0; i < students.size(); i++) {
        if (students[i][0] == roll) {
            name = students[i][1];
            break;
        }
    }

    if (name == "") {
        cout << "Student with Roll Number " << roll << " not found.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "           STUDENT TRANSCRIPT            \n";
    cout << "=========================================\n";
    cout << "Roll No: " << roll << "\n";
    cout << "Name   : " << name << "\n";
    cout << "-----------------------------------------\n";
    cout << "Course Code\tAttendance %\n";
    cout << "-----------------------------------------\n";

    vector<vector<string>> courses = readTXT("courses.txt");
    bool hasRegistrations = false;

    // Read enrollment data directly from registrations.txt to find courses for this student
    vector<vector<string>> regs = readTXT("registrations.txt");
    for (int i = 0; i < regs.size(); i++) {
        if (regs[i][0] == roll) {
            string courseCode = regs[i][1];
            double pct = getAttendancePct(roll, courseCode);
            cout << courseCode << "\t\t" << pct << "%\n";
            hasRegistrations = true;
        }
    }

    if (!hasRegistrations) {
        cout << "(No courses registered yet)\n";
    }
    cout << "=========================================\n\n";
}

void generateCourseReport(const string& courseCode) {
    vector<vector<string>> courses = readTXT("courses.txt");
    bool courseExists = false;
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i][0] == courseCode) {
            courseExists = true;
            break;
        }
    }

    if (!courseExists) {
        cout << "Course with Code " << courseCode << " not found.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "             COURSE REPORT               \n";
    cout << "=========================================\n";
    cout << "Course Code: " << courseCode << "\n";
    cout << "-----------------------------------------\n";

    vector<vector<string>> enrolled = listEnrolledStudents(courseCode);
    cout << "Total Enrolled Students: " << enrolled.size() << "\n\n";
    
    cout << "Roll No\t\tAttendance %\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < enrolled.size(); i++) {
        string roll = enrolled[i][0];
        double pct = getAttendancePct(roll, courseCode);
        cout << roll << "\t\t" << pct << "%\n";
    }

    cout << "\n--- Students with Shortage (< 75%) ---\n";
    vector<vector<string>> shortage = getShortageList(courseCode);
    if (shortage.empty()) {
        cout << "None! All students have clear attendance.\n";
    } else {
        for (int i = 0; i < shortage.size(); i++) {
            cout << shortage[i][0] << " (" << shortage[i][2] << "%)\n";
        }
    }
    cout << "=========================================\n\n";
}
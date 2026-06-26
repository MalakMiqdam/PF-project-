#include "reports.h"

void printStudentTranscript(const string& roll, const string& semester) {
    vector<string> student = findRow("students.txt", roll, 0);
    if (student.empty() || student[4] != "active") {
        cout << "Error: No active student found with this roll number.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "           STUDENT TRANSCRIPT            \n";
    cout << "=========================================\n";
    cout << "Roll No   : " << student[0] << "\n";
    cout << "Name      : " << student[1] << "\n";
    cout << "Dept      : " << student[2] << "\n";
    cout << "Semester  : " << semester << "\n";
    cout << "-----------------------------------------\n";
    cout << "Course\t\tAttendance\tMarks\tGrade\n";
    cout << "-----------------------------------------\n";

    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    vector<vector<string>> grades = readTXT("grades.txt");
    bool registered = false;

    for (size_t i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][2] == semester && enrollments[i][3] == "enrolled") {
            string cCode = enrollments[i][1];
            double attPct = getAttendancePct(roll, cCode, semester);
            
            string marksStr = "N/A";
            string gradeStr = "N/A";
            
            for (size_t j = 0; j < grades.size(); j++) {
                if (grades[j][0] == roll && grades[j][1] == cCode && grades[j][2] == semester) {
                    marksStr = grades[j][3];
                    gradeStr = grades[j][4];
                    break;
                }
            }
            cout << cCode << "\t\t" << attPct << "%\t\t" << marksStr << "\t" << gradeStr << "\n";
            registered = true;
        }
    }

    if (!registered) {
        cout << "No courses registered for this semester.\n";
    }
    cout << "=========================================\n\n";
}

void printAttendanceDefaulters(const string& courseCode, const string& semester) {
    vector<vector<string>> shortage = getShortageList(courseCode, semester);
    cout << "\n--- Attendance Defaulters (< 75%) ---\n";
    cout << "Course: " << courseCode << " | Semester: " << semester << "\n";
    cout << "Roll No\t\tAttendance Percentage\n";
    cout << "-------------------------------------\n";
    
    if (shortage.empty()) {
        cout << "No attendance defaulters found for this course configuration.\n";
    } else {
        for (size_t i = 0; i < shortage.size(); i++) {
            cout << shortage[i][0] << "\t\t" << shortage[i][2] << "%\n";
        }
    }
    cout << "-------------------------------------\n\n";
}

void printFeeDefaulters() {
    vector<vector<string>> defaulters = getDefaulters();
    cout << "\n--- Outstanding Fee Defaulters Roster ---\n";
    cout << "Roll No\t\tPending Balance\tDeadline\n";
    cout << "-----------------------------------------\n";
    
    if (defaulters.empty()) {
        cout << "No active accounts show pending arrears.\n";
    } else {
        for (size_t i = 0; i < defaulters.size(); i++) {
            cout << defaulters[i][0] << "\t\t" << defaulters[i][1] << "\t" << defaulters[i][2] << "\n";
        }
    }
    cout << "-----------------------------------------\n\n";
}

void printDepartmentSummary() {
    vector<vector<string>> students = readTXT("students.txt");
    
    vector<string> depts;
    vector<int> counts;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i][4] == "active") {
            string dName = students[i][2];
            bool found = false;
            for (size_t j = 0; j < depts.size(); j++) {
                if (depts[j] == dName) {
                    counts[j]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                depts.push_back(dName);
                counts.push_back(1);
            }
        }
    }

    cout << "\n--- Department Enrollment Statistics Summary ---\n";
    cout << "Department\tActive Student Base\n";
    cout << "------------------------------------------------\n";
    if (depts.empty()) {
        cout << "No active system entries currently recorded.\n";
    } else {
        for (size_t i = 0; i < depts.size(); i++) {
            cout << depts[i] << "\t\t" << counts[i] << "\n";
        }
    }
    cout << "------------------------------------------------\n\n";
}
#include "grades.h"

void assignGrade(const string& roll, const string& courseCode, double marks) {
    // Verify enrollment first
    vector<vector<string>> enrolled = listEnrolledStudents(courseCode);
    bool isEnrolled = false;
    for (int i = 0; i < enrolled.size(); i++) {
        if (enrolled[i][0] == roll) {
            isEnrolled = true;
            break;
        }
    }

    if (!isEnrolled) {
        cout << "Error: Student " << roll << " is not enrolled in course " << courseCode << ".\n";
        return;
    }

    // Read existing grades to update if duplicate, otherwise append
    vector<vector<string>> gradesData = readTXT("grades.txt");
    bool updated = false;
    
    for (int i = 0; i < gradesData.size(); i++) {
        if (gradesData[i][0] == roll && gradesData[i][1] == courseCode) {
            gradesData[i][2] = to_string(marks);
            gradesData[i][3] = calculateGPA(marks);
            updated = true;
            break;
        }
    }

    if (updated) {
        vector<string> header = {"roll", "course_code", "marks", "grade"};
        writeTXT("grades.txt", header, gradesData);
        cout << "Grade updated successfully.\n";
    } else {
        vector<string> row = {roll, courseCode, to_string(marks), calculateGPA(marks)};
        appendTXT("grades.txt", row);
        cout << "Grade assigned successfully.\n";
    }
}

string calculateGPA(double marks) {
    if (marks >= 85.0) return "A";
    if (marks >= 75.0) return "B";
    if (marks >= 65.0) return "C";
    if (marks >= 50.0) return "D";
    return "F";
}

vector<vector<string>> getClassGrades(const string& courseCode) {
    vector<vector<string>> allGrades = readTXT("grades.txt");
    vector<vector<string>> classGrades;
    for (int i = 0; i < allGrades.size(); i++) {
        if (allGrades[i][1] == courseCode) {
            classGrades.push_back(allGrades[i]);
        }
    }
    return classGrades;
}
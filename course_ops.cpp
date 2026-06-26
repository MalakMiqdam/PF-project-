#include "course_ops.h"

EnrollResult enrollStudent(const string& roll, const string& courseCode, const string& semester) {
    // Check student is active
    vector<string> student = searchByRoll(roll);
    if (student.empty() || student[4] != "active") return ENROLL_STUDENT_INACTIVE;

    // Check course exists
    vector<vector<string>> courses = readTXT("courses.txt");
    vector<string> course = findRow(courses, 0, courseCode);
    if (course.empty()) return ENROLL_COURSE_NOT_FOUND;

    // Check seats
    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    int enrolled = 0;
    for (int i = 0; i < enrollments.size(); i++) {
        if (enrollments[i].size() > 3 && enrollments[i][1] == courseCode && enrollments[i][3] == "enrolled")
            enrolled++;
    }
    int seats = stoi(course[3]);
    if (enrolled >= seats) return ENROLL_NO_SEATS;

    // Check not already enrolled
    for (int i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][1] == courseCode && enrollments[i][3] == "enrolled")
            return ENROLL_ALREADY_ENROLLED;
    }

    // Check credit load
    int credits = stoi(course[2]);
    if (getCreditLoad(roll, semester) + credits > 21) return ENROLL_CREDIT_OVERLOAD;

    // Check prerequisite
    if (!checkPrerequisite(roll, courseCode)) return ENROLL_PREREQ_NOT_MET;

    // Enroll
    vector<string> row = {roll, courseCode, semester, "enrolled"};
    appendTXT("enrollments.txt", row);
    return ENROLL_SUCCESS;
}

bool dropCourse(const string& roll, const string& courseCode, const string& semester) {
    // Check no attendance exists
    vector<vector<string>> attendance = readTXT("attendance_log.txt");
    for (int i = 0; i < attendance.size(); i++) {
        if (attendance[i][0] == roll && attendance[i][1] == courseCode)
            return false;
    }

    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    bool found = false;
    for (int i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][1] == courseCode && enrollments[i][2] == semester) {
            enrollments[i][3] = "dropped";
            found = true;
        }
    }
    if (!found) return false;
    vector<string> header = {"roll", "course_code", "semester", "status"};
    writeTXT("enrollments.txt", header, enrollments);
    return true;
}

int getCreditLoad(const string& roll, const string& semester) {
    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    vector<vector<string>> courses = readTXT("courses.txt");
    int total = 0;
    for (int i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][2] == semester && enrollments[i][3] == "enrolled") {
            for (int j = 0; j < courses.size(); j++) {
                if (courses[j][0] == enrollments[i][1]) {
                    total += stoi(courses[j][2]);
                    break;
                }
            }
        }
    }
    return total;
}

bool checkPrerequisite(const string& roll, const string& courseCode) {
    vector<vector<string>> courses = readTXT("courses.txt");
    vector<string> course = findRow(courses, 0, courseCode);
    if (course.empty()) return false;
    if (course[4] == "NONE") return true;

    string prereq = course[4];
    vector<vector<string>> grades = readTXT("grades.txt");
    for (int i = 0; i < grades.size(); i++) {
        if (grades[i][0] == roll && grades[i][1] == prereq && grades[i][5] != "F")
            return true;
    }
    return false;
}

vector<vector<string>> listEnrolledStudents(const string& courseCode) {
    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    vector<vector<string>> result;
    for (int i = 0; i < enrollments.size(); i++) {
        if (enrollments[i].size() > 3 && enrollments[i][1] == courseCode && enrollments[i][3] == "enrolled")
            result.push_back(enrollments[i]);
    }
    return result;
}
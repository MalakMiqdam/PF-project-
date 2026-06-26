#include "course_ops.h"

EnrollResult enrollStudent(const string& roll, const string& courseCode, const string& semester) {
    vector<string> student = findRow("students.txt", roll, 0);
    if (student.empty() || student[4] != "active") {
        return STUDENT_INACTIVE;
    }

    vector<string> course = findRow("courses.txt", courseCode, 0);
    if (course.empty()) {
        return COURSE_NOT_FOUND;
    }

    int maxSeats = stoi(course[3]);
    vector<vector<string>> allEnrollments = readTXT("enrollments.txt");
    int currentEnrolledCount = 0;
    bool alreadyEnrolled = false;

    for (size_t i = 0; i < allEnrollments.size(); i++) {
        if (allEnrollments[i][1] == courseCode && allEnrollments[i][2] == semester && allEnrollments[i][3] == "enrolled") {
            currentEnrolledCount++;
        }
        if (allEnrollments[i][0] == roll && allEnrollments[i][1] == courseCode && allEnrollments[i][2] == semester && allEnrollments[i][3] == "enrolled") {
            alreadyEnrolled = true;
        }
    }

    if (alreadyEnrolled) {
        return ALREADY_ENROLLED;
    }

    if (currentEnrolledCount >= maxSeats) {
        return NO_SEATS;
    }

    int currentCredits = getCreditLoad(roll, semester);
    int courseCredits = stoi(course[2]);
    if (currentCredits + courseCredits > 21) {
        return MAX_CREDITS_EXCEEDED;
    }

    if (!checkPrerequisite(roll, courseCode)) {
        return PREREQ_FAILED;
    }

    vector<string> newEnrollment = {roll, courseCode, semester, "enrolled"};
    appendTXT("enrollments.txt", newEnrollment);
    return SUCCESS;
}

void dropCourse(const string& roll, const string& courseCode, const string& semester) {
    vector<vector<string>> attLog = readTXT("attendance_log.txt");
    for (size_t i = 0; i < attLog.size(); i++) {
        if (attLog[i][0] == roll && attLog[i][1] == courseCode) {
            cout << "Error: Cannot drop course. Attendance records already exist.\n";
            return;
        }
    }

    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    bool updated = false;

    for (size_t i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][1] == courseCode && enrollments[i][2] == semester && enrollments[i][3] == "enrolled") {
            enrollments[i][3] = "dropped";
            updated = true;
            break;
        }
    }

    if (updated) {
        vector<string> header = {"roll", "course_code", "semester", "status"};
        writeTXT("enrollments.txt", header, enrollments);
        cout << "Course dropped successfully.\n";
    } else {
        cout << "Error: Registration matching parameters not found.\n";
    }
}

int getCreditLoad(const string& roll, const string& semester) {
    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    vector<vector<string>> courses = readTXT("courses.txt");
    int totalLoad = 0;

    for (size_t i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][2] == semester && enrollments[i][3] == "enrolled") {
            string courseCode = enrollments[i][1];
            for (size_t j = 0; j < courses.size(); j++) {
                if (courses[j][0] == courseCode) {
                    totalLoad += stoi(courses[j][2]);
                    break;
                }
            }
        }
    }
    return totalLoad;
}

bool checkPrerequisite(const string& roll, const string& courseCode) {
    vector<string> course = findRow("courses.txt", courseCode, 0);
    if (course.empty()) return false;

    string prereq = course[4];
    if (prereq == "NONE") return true;

    vector<vector<string>> grades = readTXT("grades.txt");
    for (size_t i = 0; i < grades.size(); i++) {
        if (grades[i][0] == roll && grades[i][1] == prereq) {
            string letterGrade = grades[i][3];
            if (letterGrade != "F") {
                return true;
            }
        }
    }
    return false;
}

vector<vector<string>> listEnrolledStudents(const string& courseCode, const string& semester) {
    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    vector<vector<string>> studentRows;

    for (size_t i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][1] == courseCode && enrollments[i][2] == semester && enrollments[i][3] == "enrolled") {
            vector<string> sRow = findRow("students.txt", enrollments[i][0], 0);
            if (!sRow.empty()) {
                studentRows.push_back(sRow);
            }
        }
    }
    return studentRows;
}
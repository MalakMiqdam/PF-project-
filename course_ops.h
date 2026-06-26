#ifndef COURSE_OPS_H
#define COURSE_OPS_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"

using namespace std;

enum EnrollResult {
    SUCCESS,
    STUDENT_INACTIVE,
    COURSE_NOT_FOUND,
    NO_SEATS,
    ALREADY_ENROLLED,
    MAX_CREDITS_EXCEEDED,
    PREREQ_FAILED
};

EnrollResult enrollStudent(const string& roll, const string& courseCode, const string& semester);
void dropCourse(const string& roll, const string& courseCode, const string& semester);
int getCreditLoad(const string& roll, const string& semester);
bool checkPrerequisite(const string& roll, const string& courseCode);
vector<vector<string>> listEnrolledStudents(const string& courseCode, const string& semester);

#endif
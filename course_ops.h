#ifndef COURSE_OPS_H
#define COURSE_OPS_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "student_ops.h"

using namespace std;

enum EnrollResult {
    ENROLL_SUCCESS,
    ENROLL_STUDENT_INACTIVE,
    ENROLL_COURSE_NOT_FOUND,
    ENROLL_NO_SEATS,
    ENROLL_ALREADY_ENROLLED,
    ENROLL_CREDIT_OVERLOAD,
    ENROLL_PREREQ_NOT_MET
};

EnrollResult enrollStudent(const string& roll, const string& courseCode, const string& semester);
bool dropCourse(const string& roll, const string& courseCode, const string& semester);
int getCreditLoad(const string& roll, const string& semester);
bool checkPrerequisite(const string& roll, const string& courseCode);
vector<vector<string>> listEnrolledStudents(const string& courseCode);

#endif
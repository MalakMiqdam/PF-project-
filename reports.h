#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "student_ops.h"
#include "course_ops.h"
#include "attendance.h"

using namespace std;

void generateStudentTranscript(const string& roll);
void generateCourseReport(const string& courseCode);

#endif
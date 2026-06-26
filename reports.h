#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "student_ops.h"
#include "course_ops.h"
#include "attendance.h"
#include "grades.h"
#include "fee_tracker.h"

using namespace std;

void generateStudentTranscript(const string& roll);
void generateCourseReport(const string& courseCode);

#endif
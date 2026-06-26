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

void printStudentTranscript(const string& roll, const string& semester);
void printAttendanceDefaulters(const string& courseCode, const string& semester);
void printFeeDefaulters();
void printDepartmentSummary();

#endif
#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "course_ops.h"

using namespace std;

void markAttendance(const string& courseCode, const string& semester, const string& date);
double getAttendancePct(const string& roll, const string& courseCode, const string& semester);
vector<vector<string>> getShortageList(const string& courseCode, const string& semester);
bool undoLastSession(const string& courseCode, const string& semester, const string& date);
void printDailySheet(const string& courseCode, const string& semester, const string& date);

#endif
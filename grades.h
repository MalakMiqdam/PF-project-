#ifndef GRADES_H
#define GRADES_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "course_ops.h"

using namespace std;

void assignGrade(const string& roll, const string& courseCode, double marks);
string calculateGPA(double marks);
vector<vector<string>> getClassGrades(const string& courseCode);

#endif
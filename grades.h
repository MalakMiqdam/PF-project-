#ifndef GRADES_H
#define GRADES_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "course_ops.h"
#include "attendance.h"

using namespace std;

void enterMarks(const string& roll, const string& courseCode, const string& semester);
double bestThreeOfFive(double q1, double q2, double q3, double q4, double q5);
double computeWeightedTotal(double quizTotal, double assignment, double midterm, double finalExam);
string getLetterGrade(double totalMarks);
double computeGPA(const string& letterGrade);
void applyAttendancePenalty(const string& roll, const string& courseCode, const string& semester, double& totalMarks, string& letterGrade);
vector<vector<string>> getClassGrades(const string& courseCode, const string& semester);

#endif
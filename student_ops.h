#ifndef STUDENT_OPS_H
#define STUDENT_OPS_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"

using namespace std;

bool isValidRoll(const string& roll);
bool isValidName(const string& name);
bool isValidCGPA(const string& cgpa);
void addStudent(const string& roll, const string& name, const string& dept, const string& cgpa);
vector<string> searchByRoll(const string& roll);
vector<vector<string>> searchByName(const string& name);
void updateStudent(const string& roll, int fieldIndex, const string& newValue);
void softDelete(const string& roll);
vector<vector<string>> listActiveStudents();

#endif
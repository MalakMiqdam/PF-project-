#ifndef STUDENT_OPS_H
#define STUDENT_OPS_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"

using namespace std;

void addStudent(const string& roll, const string& name, const string& dept, double cgpa);
void searchByRoll(const string& roll);
void searchByName(const string& name);
void updateStudent(const string& roll, const string& name, const string& dept, double cgpa);
void softDelete(const string& roll);
vector<vector<string>> listActiveStudents();
void searchAsYouType();

#endif
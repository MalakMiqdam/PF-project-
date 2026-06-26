#ifndef FEE_TRACKER_H
#define FEE_TRACKER_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "student_ops.h"

using namespace std;

void recordChallan(const string& roll, double baseAmount, const string& dueDate);
void processPayment(const string& roll, double amountPaid, const string& paymentDate);
int daysBetween(const string& date1, const string& date2);
bool parseDate(const string& dateStr, int& d, int& m, int& y);
vector<vector<string>> getDefaulters();

#endif
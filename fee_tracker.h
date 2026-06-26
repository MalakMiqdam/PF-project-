#ifndef FEE_TRACKER_H
#define FEE_TRACKER_H

#include <iostream>
#include <string>
#include <vector>
#include "filehandler.h"
#include "student_ops.h"

using namespace std;

void recordChallan(const string& roll, double amount, const string& dueDate);
void payFee(const string& roll, double amountPaid);
void printFeeStatus(const string& roll);

#endif
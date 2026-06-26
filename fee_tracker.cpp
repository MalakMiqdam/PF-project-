#include "fee_tracker.h"

void recordChallan(const string& roll, double amount, const string& dueDate) {
    // Check if student exists
    vector<vector<string>> students = readTXT("students.txt");
    bool exists = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i][0] == roll) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        cout << "Error: Student with Roll Number " << roll << " does not exist.\n";
        return;
    }

    // Check if a fee record already exists to append/update balance
    vector<vector<string>> feesData = readTXT("fees.txt");
    bool updated = false;

    for (int i = 0; i < feesData.size(); i++) {
        if (feesData[i][0] == roll) {
            double currentTotal = stod(feesData[i][1]);
            feesData[i][1] = to_string(currentTotal + amount);
            feesData[i][3] = dueDate;
            updated = true;
            break;
        }
    }

    if (updated) {
        vector<string> header = {"roll", "total_due", "amount_paid", "due_date"};
        writeTXT("fees.txt", header, feesData);
    } else {
        vector<string> row = {roll, to_string(amount), "0.000000", dueDate};
        appendTXT("fees.txt", row);
    }
    cout << "Fee challan of " << amount << " recorded for " << roll << ".\n";
}

void payFee(const string& roll, double amountPaid) {
    vector<vector<string>> feesData = readTXT("fees.txt");
    bool found = false;

    for (int i = 0; i < feesData.size(); i++) {
        if (feesData[i][0] == roll) {
            double currentPaid = stod(feesData[i][2]);
            feesData[i][2] = to_string(currentPaid + amountPaid);
            found = true;
            break;
        }
    }

    if (found) {
        vector<string> header = {"roll", "total_due", "amount_paid", "due_date"};
        writeTXT("fees.txt", header, feesData);
        cout << "Payment of " << amountPaid << " successfully processed for " << roll << ".\n";
    } else {
        cout << "No fee record found for student " << roll << ". Generate a challan first.\n";
    }
}

void printFeeStatus(const string& roll) {
    vector<vector<string>> feesData = readTXT("fees.txt");
    for (int i = 0; i < feesData.size(); i++) {
        if (feesData[i][0] == roll) {
            double total = stod(feesData[i][1]);
            double paid = stod(feesData[i][2]);
            double balance = total - paid;
            
            cout << "\n--- Fee Status for " << roll << " ---\n";
            cout << "Total Due   : " << total << "\n";
            cout << "Amount Paid : " << paid << "\n";
            cout << "Outstanding : " << balance << "\n";
            cout << "Due Date    : " << feesData[i][3] << "\n";
            cout << "--------------------------------\n";
            return;
        }
    }
    cout << "No active financial records found for Roll Number " << roll << ".\n";
}
#include "fee_tracker.h"

bool parseDate(const string& dateStr, int& d, int& m, int& y) {
    if (dateStr.length() != 10 || dateStr[2] != '-' || dateStr[5] != '-') {
        return false;
    }
    d = stoi(dateStr.substr(0, 2));
    m = stoi(dateStr.substr(3, 2));
    y = stoi(dateStr.substr(6, 4));
    return true;
}

int daysBetween(const string& date1, const string& date2) {
    int d1, m1, y1;
    int d2, m2, y2;
    if (!parseDate(date1, d1, m1, y1) || !parseDate(date2, d2, m2, y2)) {
        return 0;
    }

    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long long totalDays1 = d1;
    for (int i = 0; i < m1 - 1; i++) {
        totalDays1 += months[i];
    }
    totalDays1 += y1 * 365LL;

    long long totalDays2 = d2;
    for (int i = 0; i < m2 - 1; i++) {
        totalDays2 += months[i];
    }
    totalDays2 += y2 * 365LL;

    return static_cast<int>(totalDays2 - totalDays1);
}

void recordChallan(const string& roll, double baseAmount, const string& dueDate) {
    vector<string> student = findRow("students.txt", roll, 0);
    if (student.empty() || student[4] != "active") {
        cout << "Error: No active student found with this roll number.\n";
        return;
    }

    vector<vector<string>> feeData = readTXT("fees.txt");
    bool updated = false;

    for (size_t i = 0; i < feeData.size(); i++) {
        if (feeData[i][0] == roll) {
            feeData[i][1] = to_string(stod(feeData[i][1]) + baseAmount);
            feeData[i][4] = dueDate;
            updated = true;
            break;
        }
    }

    if (updated) {
        vector<string> header = {"roll", "total_due", "amount_paid", "late_penalty", "due_date"};
        writeTXT("fees.txt", header, feeData);
    } else {
        vector<string> row = {roll, to_string(baseAmount), "0.000000", "0.000000", dueDate};
        appendTXT("fees.txt", row);
    }
    cout << "Challan registered successfully.\n";
}

void processPayment(const string& roll, double amountPaid, const string& paymentDate) {
    vector<vector<string>> feeData = readTXT("fees.txt");
    bool found = false;

    for (size_t i = 0; i < feeData.size(); i++) {
        if (feeData[i][0] == roll) {
            string dueDate = feeData[i][4];
            double penalty = 0.0;

            int diff = daysBetween(dueDate, paymentDate);
            if (diff > 0) {
                penalty = diff * 50.0;
            }

            double totalDue = stod(feeData[i][1]) + penalty;
            double currentPaid = stod(feeData[i][2]) + amountPaid;

            feeData[i][1] = to_string(totalDue);
            feeData[i][2] = to_string(currentPaid);
            feeData[i][3] = to_string(stod(feeData[i][3]) + penalty);
            found = true;
            break;
        }
    }

    if (found) {
        vector<string> header = {"roll", "total_due", "amount_paid", "late_penalty", "due_date"};
        writeTXT("fees.txt", header, feeData);
        cout << "Payment registered successfully.\n";
    } else {
        cout << "Error: Financial statement not found for this account.\n";
    }
}

vector<vector<string>> getDefaulters() {
    vector<vector<string>> feeData = readTXT("fees.txt");
    vector<vector<string>> defaulters;

    for (size_t i = 0; i < feeData.size(); i++) {
        double due = stod(feeData[i][1]);
        double paid = stod(feeData[i][2]);
        double balance = due - paid;
        if (balance > 0.0) {
            vector<string> row = {feeData[i][0], to_string(balance), feeData[i][4]};
            defaulters.push_back(row);
        }
    }

    if (!defaulters.empty()) {
        for (size_t i = 0; i < defaulters.size() - 1; i++) {
            for (size_t j = 0; j < defaulters.size() - i - 1; j++) {
                if (stod(defaulters[j][1]) < stod(defaulters[j + 1][1])) {
                    vector<string> temp = defaulters[j];
                    defaulters[j] = defaulters[j + 1];
                    defaulters[j + 1] = temp;
                }
            }
        }
    }
    return defaulters;
}
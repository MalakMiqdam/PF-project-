#include <iostream>
#include <string>
#include "student_ops.h"
#include "course_ops.h"
#include "attendance.h"
#include "grades.h"
#include "fee_tracker.h"
#include "reports.h"

using namespace std;

void studentMenu() {
    while (true) {
        cout << "\n--- Student Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Search by Roll Number\n";
        cout << "3. Search by Name Content\n";
        cout << "4. Update Student Details\n";
        cout << "5. Soft Delete Student\n";
        cout << "6. Interactive Search-as-you-type\n";
        cout << "7. Return to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 7) break;

        string roll, name, dept;
        double cgpa;

        switch (choice) {
            case 1:
                cout << "Enter Roll No (BSAI-YY-XXX): "; cin >> roll;
                cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Department: "; getline(cin, dept);
                cout << "Enter CGPA: "; cin >> cgpa;
                addStudent(roll, name, dept, cgpa);
                break;
            case 2:
                cout << "Enter Roll No: "; cin >> roll;
                searchByRoll(roll);
                break;
            case 3:
                cout << "Enter Name substring: "; cin.ignore(); getline(cin, name);
                searchByName(name);
                break;
            case 4:
                cout << "Enter Roll No to update: "; cin >> roll;
                cout << "Enter New Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter New Department: "; getline(cin, dept);
                cout << "Enter New CGPA: "; cin >> cgpa;
                updateStudent(roll, name, dept, cgpa);
                break;
            case 5:
                cout << "Enter Roll No to delete: "; cin >> roll;
                softDelete(roll);
                break;
            case 6:
                searchAsYouType();
                break;
            default:
                cout << "Invalid entry.\n";
        }
    }
}

void courseMenu() {
    while (true) {
        cout << "\n--- Course & Enrollments ---\n";
        cout << "1. Enroll Student in Course\n";
        cout << "2. Drop Student from Course\n";
        cout << "3. View Course Roster\n";
        cout << "4. Return to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) break;

        string roll, courseCode, semester;
        switch (choice) {
            case 1:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                {
                    EnrollResult res = enrollStudent(roll, courseCode, semester);
                    if (res == SUCCESS) cout << "Enrolled successfully.\n";
                    else if (res == STUDENT_INACTIVE) cout << "Error: Student profile is inactive.\n";
                    else if (res == COURSE_NOT_FOUND) cout << "Error: Course code does not exist.\n";
                    else if (res == NO_SEATS) cout << "Error: No available seats.\n";
                    else if (res == ALREADY_ENROLLED) cout << "Error: Already registered.\n";
                    else if (res == MAX_CREDITS_EXCEEDED) cout << "Error: Registration exceeds credit limit.\n";
                    else if (res == PREREQ_FAILED) cout << "Error: Failed course prerequisite rules.\n";
                }
                break;
            case 2:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                dropCourse(roll, courseCode, semester);
                break;
            case 3:
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                {
                    vector<vector<string>> roster = listEnrolledStudents(courseCode, semester);
                    cout << "\n--- Registered Students ---\n";
                    for (size_t i = 0; i < roster.size(); i++) {
                        cout << roster[i][0] << "\t" << roster[i][1] << "\n";
                    }
                }
                break;
            default:
                cout << "Invalid entry.\n";
        }
    }
}

void attendanceMenu() {
    while (true) {
        cout << "\n--- Attendance Records ---\n";
        cout << "1. Log New Session Attendance\n";
        cout << "2. Print Daily Sheet Logs\n";
        cout << "3. Rollback Session Logs\n";
        cout << "4. Return to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) break;

        string courseCode, semester, date;
        switch (choice) {
            case 1:
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                cout << "Enter Date (DD-MM-YYYY): "; cin >> date;
                markAttendance(courseCode, semester, date);
                break;
            case 2:
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                cout << "Enter Date (DD-MM-YYYY): "; cin >> date;
                printDailySheet(courseCode, semester, date);
                break;
            case 3:
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                cout << "Enter Date (DD-MM-YYYY): "; cin >> date;
                if (undoLastSession(courseCode, semester, date)) {
                    cout << "Session logs rolled back.\n";
                } else {
                    cout << "No matching session logs located.\n";
                }
                break;
            default:
                cout << "Invalid entry.\n";
        }
    }
}

void gradesMenu() {
    while (true) {
        cout << "\n--- Performance & Grading ---\n";
        cout << "1. Enter Student Evaluation Marks\n";
        cout << "2. Return to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 2) break;

        string roll, courseCode, semester;
        switch (choice) {
            case 1:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Semester: "; cin >> semester;
                enterMarks(roll, courseCode, semester);
                break;
            default:
                cout << "Invalid entry.\n";
        }
    }
}

void feeMenu() {
    while (true) {
        cout << "\n--- Financial Records ---\n";
        cout << "1. Issue New Base Challan\n";
        cout << "2. Process Accounts Payment\n";
        cout << "3. Return to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 3) break;

        string roll, date, dueDate;
        double amount;
        switch (choice) {
            case 1:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Base Amount: "; cin >> amount;
                cout << "Enter Due Date (DD-MM-YYYY): "; cin >> dueDate;
                recordChallan(roll, amount, dueDate);
                break;
            case 2:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Amount Paid: "; cin >> amount;
                cout << "Enter Payment Date (DD-MM-YYYY): "; cin >> date;
                processPayment(roll, amount, date);
                break;
            default:
                cout << "Invalid entry.\n";
        }
    }
}

void analyticsMenu() {
    while (true) {
        cout << "\n--- System Reports & Analytics ---\n";
        cout << "1. Generate Student Transcript\n";
        cout << "2. View Course Attendance Defaulters\n";
        cout << "3. View Sorted Financial Defaulters\n";
        cout << "4. Display Department Base Matrices\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 5) break;

        string target, semester;
        switch (choice) {
            case 1:
                cout << "Enter Student Roll No: "; cin >> target;
                cout << "Enter Semester: "; cin >> semester;
                printStudentTranscript(target, semester);
                break;
            case 2:
                cout << "Enter Course Code: "; cin >> target;
                cout << "Enter Semester: "; cin >> semester;
                printAttendanceDefaulters(target, semester);
                break;
            case 3:
                printFeeDefaulters();
                break;
            case 4:
                printDepartmentSummary();
                break;
            default:
                cout << "Invalid entry.\n";
        }
    }
}

int main() {
    while (true) {
        cout << "\n=========================================\n";
        cout << "         CAMPUS ANALYTICS ENGINE         \n";
        cout << "=========================================\n";
        cout << "1. Student Management\n";
        cout << "2. Course Registration\n";
        cout << "3. Attendance Systems\n";
        cout << "4. Evaluation Grading\n";
        cout << "5. Financial Tracking\n";
        cout << "6. Engine Reports Summary\n";
        cout << "7. Terminate System Application\n";
        cout << "=========================================\n";
        cout << "Enter primary menu selection: ";
        
        int selection;
        cin >> selection;

        if (selection == 7) {
            cout << "Closing system application execution connection. System terminated.\n";
            break;
        }

        switch (selection) {
            case 1: studentMenu(); break;
            case 2: courseMenu(); break;
            case 3: attendanceMenu(); break;
            case 4: gradesMenu(); break;
            case 5: feeMenu(); break;
            case 6: analyticsMenu(); break;
            default: cout << "Selection index not found. Try again.\n";
        }
    }
    return 0;
}
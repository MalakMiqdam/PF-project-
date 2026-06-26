#include <iostream>
#include <string>
#include "student_ops.h"
#include "course_ops.h"
#include "attendance.h"
#include "grades.h"
#include "fee_tracker.h"
#include "reports.h"

using namespace std;

void showMenu() {
    cout << "=========================================\n";
    cout << "      STUDENT ATTENDANCE & ERP SYSTEM    \n";
    cout << "=========================================\n";
    cout << "1. Manage Students\n";
    cout << "2. Manage Courses & Enrollments\n";
    cout << "3. Attendance Management\n";
    cout << "4. Grades Management\n";
    cout << "5. Fee & Financial Tracker\n";
    cout << "6. Reporting & Transcripts System\n";
    cout << "7. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
}

void studentSubMenu() {
    while (true) {
        cout << "\n--- Student Management Sub-Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student by Roll Number\n";
        cout << "3. Search Students by Name\n";
        cout << "4. Update Student Details\n";
        cout << "5. Delete Student (Soft Delete)\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 6) break;

        string roll, name, dept;
        switch (choice) {
            case 1:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Department: "; getline(cin, dept);
                addStudent(roll, name, dept);
                break;
            case 2:
                cout << "Enter Roll No: "; cin >> roll;
                searchByRoll(roll);
                break;
            case 3:
                cout << "Enter Name to search: "; cin.ignore(); getline(cin, name);
                searchByName(name);
                break;
            case 4:
                cout << "Enter Roll No to update: "; cin >> roll;
                cout << "Enter New Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter New Department: "; getline(cin, dept);
                updateStudent(roll, name, dept);
                break;
            case 5:
                cout << "Enter Roll No to delete: "; cin >> roll;
                softDeleteStudent(roll);
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void courseSubMenu() {
    while (true) {
        cout << "\n--- Course & Enrollment Sub-Menu ---\n";
        cout << "1. Enroll Student in Course\n";
        cout << "2. Drop Student from Course\n";
        cout << "3. View Course Enrolled Students\n";
        cout << "4. Check Student Credit Load\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 5) break;

        string roll, courseCode;
        switch (choice) {
            case 1:
                cout << "Enter Student Roll No: "; cin >> roll;
                cout << "Enter Course Code: "; cin >> courseCode;
                enrollStudent(roll, courseCode);
                break;
            case 2:
                cout << "Enter Student Roll No: "; cin >> roll;
                cout << "Enter Course Code: "; cin >> courseCode;
                dropCourse(roll, courseCode);
                break;
            case 3:
                cout << "Enter Course Code: "; cin >> courseCode;
                {
                    vector<vector<string>> enrolled = listEnrolledStudents(courseCode);
                    if(!enrolled.empty()) {
                        cout << "\nEnrolled Students:\nRoll No\n---------\n";
                        for(int i=0; i<enrolled.size(); i++) {
                            cout << enrolled[i][0] << "\n";
                        }
                    }
                }
                break;
            case 4:
                cout << "Enter Student Roll No: "; cin >> roll;
                cout << "Current Credit Load: " << getCreditLoad(roll) << " credits\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void attendanceSubMenu() {
    while (true) {
        cout << "\n--- Attendance Management Sub-Menu ---\n";
        cout << "1. Mark Attendance for a Class\n";
        cout << "2. View Daily Attendance Sheet\n";
        cout << "3. Undo Last Attendance Session\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) break;

        string courseCode, date;
        switch (choice) {
            case 1:
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Date (DD-MM-YYYY): "; cin >> date;
                markAttendance(courseCode, date);
                break;
            case 2:
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Date (DD-MM-YYYY): "; cin >> date;
                printDailySheet(courseCode, date);
                break;
            case 3:
                cout << "Enter Course Code (for confirmation): "; cin >> courseCode;
                undoLastSession(courseCode);
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void gradesSubMenu() {
    while (true) {
        cout << "\n--- Grades Management Sub-Menu ---\n";
        cout << "1. Assign / Update Grade for Student\n";
        cout << "2. View Grades Breakdown for a Course\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 3) break;

        string roll, courseCode;
        double marks;

        switch (choice) {
            case 1:
                cout << "Enter Student Roll No: "; cin >> roll;
                cout << "Enter Course Code: "; cin >> courseCode;
                cout << "Enter Marks Obtained: "; cin >> marks;
                assignGrade(roll, courseCode, marks);
                break;
            case 2:
                cout << "Enter Course Code: "; cin >> courseCode;
                {
                    vector<vector<string>> data = getClassGrades(courseCode);
                    cout << "\n--- Grades for Course " << courseCode << " ---\n";
                    cout << "Roll No\t\tMarks\tGrade\n";
                    cout << "------------------------------------\n";
                    for (int i = 0; i < data.size(); i++) {
                        cout << data[i][0] << "\t\t" << data[i][2] << "\t" << data[i][3] << "\n";
                    }
                }
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void feeSubMenu() {
    while (true) {
        cout << "\n--- Fee & Financial Tracker Sub-Menu ---\n";
        cout << "1. Record New Fee Challan\n";
        cout << "2. Process Student Fee Payment\n";
        cout << "3. Check Individual Financial Status\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) break;

        string roll, dueDate;
        double amount;

        switch (choice) {
            case 1:
                cout << "Enter Student Roll No: "; cin >> roll;
                cout << "Enter Challan Amount: "; cin >> amount;
                cout << "Enter Due Date (DD-MM-YYYY): "; cin >> dueDate;
                recordChallan(roll, amount, dueDate);
                break;
            case 2:
                cout << "Enter Student Roll No: "; cin >> roll;
                cout << "Enter Amount Paid: "; cin >> amount;
                payFee(roll, amount);
                break;
            case 3:
                cout << "Enter Student Roll No: "; cin >> roll;
                printFeeStatus(roll);
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void reportSubMenu() {
    while (true) {
        cout << "\n--- Reporting & Transcripts Sub-Menu ---\n";
        cout << "1. Generate Complete Student Transcript\n";
        cout << "2. Generate Course Statistics Report\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 3) break;

        string target;
        switch (choice) {
            case 1:
                cout << "Enter Student Roll No: "; cin >> target;
                generateStudentTranscript(target);
                break;
            case 2:
                cout << "Enter Course Code: "; cin >> target;
                generateCourseReport(target);
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

int main() {
    while (true) {
        showMenu();
        int mainChoice;
        cin >> mainChoice;

        if (mainChoice == 7) {
            cout << "Exiting ERP system. Goodbye!\n";
            break;
        }

        switch (mainChoice) {
            case 1: studentSubMenu(); break;
            case 2: courseSubMenu(); break;
            case 3: attendanceSubMenu(); break;
            case 4: gradesSubMenu(); break;
            case 5: feeSubMenu(); break;
            case 6: reportSubMenu(); break;
            default: cout << "Invalid Selection. Please try again.\n";
        }
    }
    return 0;
}
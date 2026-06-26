#include "grades.h"

void enterMarks(const string& roll, const string& courseCode, const string& semester) {
    vector<vector<string>> enrollments = readTXT("enrollments.txt");
    bool isEnrolled = false;
    for (size_t i = 0; i < enrollments.size(); i++) {
        if (enrollments[i][0] == roll && enrollments[i][1] == courseCode && enrollments[i][2] == semester && enrollments[i][3] == "enrolled") {
            isEnrolled = true;
            break;
        }
    }

    if (!isEnrolled) {
        cout << "Error: Student is not registered in this course.\n";
        return;
    }

    double q1, q2, q3, q4, q5, assign, mid, fin;
    cout << "Enter 5 Quiz marks separated by spaces: ";
    cin >> q1 >> q2 >> q3 >> q4 >> q5;
    cout << "Enter Assignment marks (out of 100): ";
    cin >> assign;
    cout << "Enter Midterm marks (out of 100): ";
    cin >> mid;
    cout << "Enter Final Exam marks (out of 100): ";
    cin >> fin;

    double quizBest = bestThreeOfFive(q1, q2, q3, q4, q5);
    double totalMarks = computeWeightedTotal(quizBest, assign, mid, fin);
    string letterGrade = getLetterGrade(totalMarks);

    applyAttendancePenalty(roll, courseCode, semester, totalMarks, letterGrade);
    double gpaPoints = computeGPA(letterGrade);

    vector<vector<string>> gradesData = readTXT("grades.txt");
    bool updated = false;

    for (size_t i = 0; i < gradesData.size(); i++) {
        if (gradesData[i][0] == roll && gradesData[i][1] == courseCode && gradesData[i][2] == semester) {
            gradesData[i][3] = to_string(totalMarks);
            gradesData[i][4] = letterGrade;
            gradesData[i][5] = to_string(gpaPoints);
            updated = true;
            break;
        }
    }

    if (updated) {
        vector<string> header = {"roll", "course_code", "semester", "total_marks", "grade", "gpa"};
        writeTXT("grades.txt", header, gradesData);
    } else {
        vector<string> row = {roll, courseCode, semester, to_string(totalMarks), letterGrade, to_string(gpaPoints)};
        appendTXT("grades.txt", row);
    }
    cout << "Marks recorded successfully.\n";
}

double bestThreeOfFive(double q1, double q2, double q3, double q4, double q5) {
    double arr[5] = {q1, q2, q3, q4, q5};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr[2] + arr[3] + arr[4];
}

double computeWeightedTotal(double quizTotal, double assignment, double midterm, double finalExam) {
    double quizComponent = (quizTotal / 30.0) * 15.0;
    double assignComponent = (assignment / 100.0) * 15.0;
    double midComponent = (midterm / 100.0) * 30.0;
    double finalComponent = (finalExam / 100.0) * 40.0;
    return quizComponent + assignComponent + midComponent + finalComponent;
}

string getLetterGrade(double totalMarks) {
    if (totalMarks >= 85.0) return "A";
    if (totalMarks >= 80.0) return "A-";
    if (totalMarks >= 75.0) return "B+";
    if (totalMarks >= 71.0) return "B";
    if (totalMarks >= 68.0) return "B-";
    if (totalMarks >= 64.0) return "C+";
    if (totalMarks >= 61.0) return "C";
    if (totalMarks >= 58.0) return "C-";
    if (totalMarks >= 54.0) return "D+";
    if (totalMarks >= 50.0) return "D";
    return "F";
}

double computeGPA(const string& letterGrade) {
    if (letterGrade == "A") return 4.0;
    if (letterGrade == "A-") return 3.67;
    if (letterGrade == "B+") return 3.33;
    if (letterGrade == "B") return 3.0;
    if (letterGrade == "B-") return 2.67;
    if (letterGrade == "C+") return 2.33;
    if (letterGrade == "C") return 2.0;
    if (letterGrade == "C-") return 1.67;
    if (letterGrade == "D+") return 1.33;
    if (letterGrade == "D") return 1.0;
    return 0.0;
}

void applyAttendancePenalty(const string& roll, const string& courseCode, const string& semester, double& totalMarks, string& letterGrade) {
    double attendancePct = getAttendancePct(roll, courseCode, semester);
    if (attendancePct < 75.0) {
        totalMarks -= 5.0;
        if (totalMarks < 0.0) totalMarks = 0.0;
        letterGrade = getLetterGrade(totalMarks);
    }
}

vector<vector<string>> getClassGrades(const string& courseCode, const string& semester) {
    vector<vector<string>> allGrades = readTXT("grades.txt");
    vector<vector<string>> classGrades;
    for (size_t i = 0; i < allGrades.size(); i++) {
        if (allGrades[i][1] == courseCode && allGrades[i][2] == semester) {
            classGrades.push_back(allGrades[i]);
        }
    }
    return classGrades;
}
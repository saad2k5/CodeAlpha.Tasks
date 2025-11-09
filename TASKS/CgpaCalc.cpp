#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
void runCGPACalculator() {
    int numCourses;
    int totalCreditHours = 0;
    double totalGradePoints = 0.0;
    cout << "\n---|| CGPA Calculator ||---\n";
    cout << "Enter the number of courses taken: ";
    cin >> numCourses;
    if (numCourses <= 0) {
        cout << "Invalid number of courses!!!\n";
        return;
    }
    for (int i = 1; i <= numCourses; ++i) {
        string courseName;
        int grade;
        int creditHours;
        cout << "\nCourse " << i << ":\n";
        cout << "Enter credit hours (e.g:- 2): ";
        cin >> creditHours;
        cout << "Enter grade (e.g., 4 for A): ";
        cin >> grade;
        double coursePoints = grade * creditHours;
        cout << fixed << setprecision(2);
        cout << "Course Grade Points: " << coursePoints << " (Grade: " << grade << " * Credits: " << creditHours << ")\n";
        totalCreditHours = totalCreditHours + creditHours;
        totalGradePoints = totalGradePoints + coursePoints;
    }
    if (totalCreditHours > 0) {
        double cgpa = totalGradePoints / totalCreditHours;
        cout << "Total Credit Hours: " << totalCreditHours << "\n";
        cout << "Total Grade Points: " << totalGradePoints << "\n";
        cout << fixed << setprecision(3);
        cout << "Final CGPA: " << cgpa << "\n";
    } else {
        cout << "\nNo credits earned. CGPA cannot be calculated!\n";
    }
}
int main() {
    runCGPACalculator();
    return 0;
}
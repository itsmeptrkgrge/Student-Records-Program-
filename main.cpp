#include <iostream>
#include <string>
#include <iomanip> // for formatted output
using namespace std;

const int MAX_STUDENTS = 100;

struct Student {
    int id;
    string firstName;
    string lastName;
    string course;
    float gpa;
};

void addStudent(Student students[], int &numStudents);
void editStudent(Student students[], int numStudents);
void deleteStudent(Student students[], int &numStudents);
void viewStudents(const Student students[], int numStudents);
int findStudentById(const Student students[], int numStudents, int id);

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    do {
        cout << "\n-- Menu --\n";
        cout << "[1] Add Student\n[2] Edit Student\n[3] Delete Student\n[4] View Students\n[5] Exit Program\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, numStudents);
                break;
            case 2:
                editStudent(students, numStudents);
                break;
            case 3:
                deleteStudent(students, numStudents);
                break;
            case 4:
                viewStudents(students, numStudents);
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void addStudent(Student students[], int &numStudents) {
    int id;
    cout << "Enter student ID: ";
    cin >> id;

    if (findStudentById(students, numStudents, id) != -1) {
        cout << "Student ID already exists! Duplicate ID not allowed.\n";
        return;
    }

    students[numStudents].id = id;
    cout << "Enter first name: ";
    cin >> students[numStudents].firstName;
    cout << "Enter last name: ";
    cin >> students[numStudents].lastName;
    cout << "Enter course: ";
    cin >> students[numStudents].course;
    cout << "Enter previous semestral GPA: ";
    cin >> students[numStudents].gpa;

    numStudents++;
    cout << "Student added successfully!\n";
}

void editStudent(Student students[], int numStudents) {
    int id;
    cout << "Enter student ID to edit: ";
    cin >> id;

    int index = findStudentById(students, numStudents, id);
    if (index == -1) {
        cout << "No record found for this ID.\n";
        return;
    }

    cout << "Editing student details...\n";
    cout << "Enter new first name: ";
    cin >> students[index].firstName;
    cout << "Enter new last name: ";
    cin >> students[index].lastName;
    cout << "Enter new course: ";
    cin >> students[index].course;
    cout << "Enter new GPA: ";
    cin >> students[index].gpa;

    cout << "Student record updated successfully!\n";
}

void deleteStudent(Student students[], int &numStudents) {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    int index = findStudentById(students, numStudents, id);
    if (index == -1) {
        cout << "No record found for this ID.\n";
        return;
    }

    for (int i = index; i < numStudents - 1; i++) {
        students[i] = students[i + 1];
    }
    numStudents--;
    cout << "Student deleted successfully!\n";
}

void viewStudents(const Student students[], int numStudents) {
    if (numStudents == 0) {
        cout << "No student records to display.\n";
        return;
    }

    cout << "Choose viewing option:\n";
    cout << "[1] Alphabetically by Last Name\n[2] By GPA (ascending)\n";
    int option;
    cin >> option;

    // Simple bubble sort based on user's choice
    Student sortedStudents[MAX_STUDENTS];
    for (int i = 0; i < numStudents; i++) {
        sortedStudents[i] = students[i];
    }

    if (option == 1) {
        for (int i = 0; i < numStudents - 1; i++) {
            for (int j = 0; j < numStudents - i - 1; j++) {
                if (sortedStudents[j].lastName > sortedStudents[j + 1].lastName) {
                    swap(sortedStudents[j], sortedStudents[j + 1]);
                }
            }
        }
    } else if (option == 2) {
        for (int i = 0; i < numStudents - 1; i++) {
            for (int j = 0; j < numStudents - i - 1; j++) {
                if (sortedStudents[j].gpa > sortedStudents[j + 1].gpa) {
                    swap(sortedStudents[j], sortedStudents[j + 1]);
                }
            }
        }
    } else {
        cout << "Invalid viewing option.\n";
        return;
    }

    cout << setw(10) << "ID" << setw(15) << "First Name" << setw(15) << "Last Name"
         << setw(15) << "Course" << setw(10) << "GPA" << endl;
    for (int i = 0; i < numStudents; i++) {
        cout << setw(10) << sortedStudents[i].id
             << setw(15) << sortedStudents[i].firstName
             << setw(15) << sortedStudents[i].lastName
             << setw(15) << sortedStudents[i].course
             << setw(10) << fixed << setprecision(2) << sortedStudents[i].gpa << endl;
    }
}

int findStudentById(const Student students[], int numStudents, int id) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

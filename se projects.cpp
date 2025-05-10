
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Define a structure to store student information 
struct Student {
    string Id;     // Registration ID
    string fName;   // First name
    string lName;   // Last name
    string classes; // Class information
    string number;  // Mobile number
};

// Function to register a new student
void newStudentRegistration() {
    // Open the file in append mode to add new students
    ofstream file("studentInfo.txt", ios::app);
    if (!file) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }

    Student s;
    cout << "Enter Registration ID: ";
    cin >> s.Id;

    // Collect other student details
    cout << "Enter First Name: ";
    cin >> s.fName;
    cout << "Enter Last Name: ";
    cin >> s.lName;
    cout << "Enter Class: ";
    cin >> s.classes;
    cout << "Enter Mobile Number: ";
    cin >> s.number;
 
    // Write student information to the file
    file << s.Id << " " << s.fName << " " << s.lName << " " << s.classes << " " << s.number << endl;
    cout << "Successfully Added" << endl;

    file.close();
}

// Function to update an existing student's information
void updateStudentInformation() {
    string rId;
    cout << "Enter Registration ID to update: ";
    cin >> rId;

    ifstream infile("studentInfo.txt");
    ofstream tempfile("tempInfo.txt");
    if (!infile.is_open() || !tempfile.is_open()) {
        cout << "Error: Unable to open files!" << endl;
        return;
    }

    Student s;
    string line;
    bool found = false;

    while (getline(infile, line)) {
        // Read student data from the file
        istringstream ss(line);
        ss >> s.Id >> s.fName >> s.lName >> s.classes >> s.number;

        if (s.Id == rId) {
            found = true;
            // If student found, update details
            cout << "Enter new First Name: ";
            cin >> s.fName;
            cout << "Enter new Last Name: ";
            cin >> s.lName;
            cout << "Enter new Class: ";
            cin >> s.classes;
            cout << "Enter new Mobile Number: ";
            cin >> s.number;
        }

        // Write the updated student information to the temporary file
        tempfile << s.Id << " " << s.fName << " " << s.lName << " " << s.classes << " " << s.number << endl;
    }

    if (!found) {
        cout << "Student with ID '" << rId << "' not found!" << endl;
    } else {
        cout << "Successfully Updated" << endl;
    }

    infile.close();
    tempfile.close();

    // Replace the original file with the updated one
    remove("studentInfo.txt");
    rename("tempInfo.txt", "studentInfo.txt");
}

// Function to delete a student's information
void deleteStudentInformation() {
    string rId;
    cout << "Enter Registration ID to delete: ";
    cin >> rId;

    ifstream infile("studentInfo.txt");
    ofstream tempfile("tempInfo.txt");
    if (!infile.is_open() || !tempfile.is_open()) {
        cout << "Error: Unable to open files!" << endl;
        return;
    }

    Student s;
    string line;
    bool found = false;

    while (getline(infile, line)) {
        // Read student data from the file
        istringstream ss(line);
        ss >> s.Id >> s.fName >> s.lName >> s.classes >> s.number;

        if (s.Id != rId) {
            // Write to the temporary file if the student ID does not match
            tempfile << s.Id << " " << s.fName << " " << s.lName << " " << s.classes << " " << s.number << endl;
        } else {
            found = true;
            cout << "Student deleted successfully" << endl;
        }
    }

    if (!found) {
        cout << "Student with ID '" << rId << "' not found!" << endl;
    }

    infile.close();
    tempfile.close();

    // Replace the original file with the updated one
    remove("studentInfo.txt");
    rename("tempInfo.txt", "studentInfo.txt");
}

// Function to list all students
void listOfStudents() {
    ifstream file("studentInfo.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    cout << "\nStudent List:" << endl;
    cout << setw(15) << "Reg. ID" << setw(15) << "First Name" << setw(15) << "Last Name" << setw(15) << "Class" << setw(15) << "Mobile Number" << endl;

    Student s;
    // Read and print student details from the file
    while (file >> s.Id >> s.fName >> s.lName >> s.classes >> s.number) {
        cout << setw(15) << s.Id << setw(15) << s.fName << setw(15) << s.lName << setw(15) << s.classes << setw(15) << s.number << endl;
    }

    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n1. New Student Registration" << endl;
        cout << "2. Update Student Information" << endl;
        cout << "3. Delete Student Information" << endl;
        cout << "4. List of Students" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                newStudentRegistration();
                break;
            case 2:
                updateStudentInformation();
                break;
            case 3:
                deleteStudentInformation();
                break;
            case 4:
                listOfStudents();
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    } while (choice != 5);

    return 0;
}

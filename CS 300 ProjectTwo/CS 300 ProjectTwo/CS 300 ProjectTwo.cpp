// CS 300 ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ::::::::::::::::::::::::::::
// :: Author -- Thomas Cheek ::
// ::::::::::::::::::::::::::::

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>  // For stringstream

using namespace std;

// Define the Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    // Function to display course details
    void displayCourseInfo() const {
        cout << "Course Number: " << courseNumber << endl;
        cout << "Course Title: " << courseTitle << endl;
        cout << "Prerequisites: ";
        if (prerequisites.empty()) {
            cout << "None";
        }
        else {
            for (const auto& prereq : prerequisites) {
                cout << prereq << " ";
            }
        }
        cout << endl;
    }
};

// Function to load courses from a file
bool LoadCoursesFromFile(const string& filename, unordered_map<string, Course>& courses) {
    ifstream file(filename);  // Attempt to open the file

    // Check if the file opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        // Get the course number (first element)
        if (!getline(ss, courseNumber, ',')) continue;

        // Get the course title (second element)
        if (!getline(ss, courseTitle, ',')) continue;

        // Initialize a new Course object
        Course newCourse;
        newCourse.courseNumber = courseNumber;
        newCourse.courseTitle = courseTitle;

        // Get prerequisites, if any
        while (getline(ss, prereq, ',')) {
            newCourse.prerequisites.push_back(prereq);
        }

        // Insert the new course into the hash table
        courses[courseNumber] = newCourse;
    }

    file.close();  // Close the file after reading
    return true;   // Indicate successful loading
}

// Function to display all courses in the hash table
void PrintCourseList(const unordered_map<string, Course>& courses) {
    cout << "\nCourse List:" << endl;

    // Loop through each course in the hash table
    for (const auto& pair : courses) {
        const Course& course = pair.second;
        cout << "---------------------------------" << endl;
        course.displayCourseInfo();  // Call the display function of each Course object
    }
}

// Function to search for and display a specific course by its course number
void SearchCourse(const unordered_map<string, Course>& courses, const string& courseNumber) {
    // Check if the course exists in the hash table
    auto it = courses.find(courseNumber);

    if (it != courses.end()) {
        // Course found, display its information
        cout << "Course found:" << endl;
        it->second.displayCourseInfo();
    }
    else {
        // Course not found
        cout << "Course " << courseNumber << " not found in the data." << endl;
    }
}

// Main function to execute the program
int main() {
    unordered_map<string, Course> courses;
    int choice;

    cout << "Welcome to the course planner." << endl;

    // Main program loop using a do-while loop
    do {
        // Display menu options
        cout << "\n1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Check for invalid input
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();                // Clear the error flag on cin
            cin.ignore(1000, '\n');     // Discard invalid input
            continue;                   // Skip to the next loop iteration
        }

        // Handle menu selection
        if (choice == 1) {
            // Load data from the fixed file name
            string filename = "CS 300 ABCU_Advising_Program_Input.csv";
            if (LoadCoursesFromFile(filename, courses)) {
                cout << "Courses loaded successfully." << endl;
            }
            else {
                cout << "Error loading courses. Please check the file format or filename." << endl;
            }

        }
        else if (choice == 2) {
            PrintCourseList(courses);

        }
        else if (choice == 3) {
            string courseNumber;
            cout << "Your input is case-sensitive, please ensure proper capitalization for course IDs." << endl;
            cout << "Enter the course number: ";
            cin >> courseNumber;
            SearchCourse(courses, courseNumber);

        }
        else if (choice == 9) {
            cout << "Exiting the program. Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

        // Clear any remaining input and reset for the next loop
        cin.ignore(1000, '\n');

    } while (choice != 9);  // Continue looping until the user selects 9 to exit

    return 0;
}

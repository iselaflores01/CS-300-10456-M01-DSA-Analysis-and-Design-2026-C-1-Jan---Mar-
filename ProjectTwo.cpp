#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Struct to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Trim leading/trailing whitespace
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Check if token looks like a course ID, e.g., CSCI101, MATH201
bool isCourseId(const string& token) {
    bool hasLetter = false;
    bool hasDigit = false;
    for (char c : token) {
        if (isalpha(static_cast<unsigned char>(c))) hasLetter = true;
        else if (isdigit(static_cast<unsigned char>(c))) hasDigit = true;
        else return false;
    }
    return hasLetter && hasDigit;
}

// Load data from file into the map
bool loadDataStructure(map<string, Course>& courses) {
    string filename;
    cout << "Enter the filename containing course data: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file \"" << filename << "\"." << endl;
        return false;
    }

    courses.clear();

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        line = trim(line);
        if (line.empty()) continue;

        // Tokenize by whitespace (matches your CSV file)
        stringstream ss(line);
        vector<string> tokens;
        string tok;
        while (ss >> tok) {
            tokens.push_back(tok);
        }

        if (tokens.size() < 2) {
            cout << "Warning: Line " << lineNumber
                 << " does not contain enough fields. Skipping." << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];

        // Find where prerequisites start (from the end)
        int idx = static_cast<int>(tokens.size()) - 1;
        while (idx >= 1 && isCourseId(tokens[idx])) {
            idx--;
        }
        int titleStart = 1;
        int titleEnd = idx; // inclusive

        // Build title from tokens[1..titleEnd]
        string title;
        for (int i = titleStart; i <= titleEnd; ++i) {
            if (!title.empty()) title += " ";
            title += tokens[i];
        }
        course.courseTitle = title;

        // Remaining tokens after titleEnd are prerequisites
        for (size_t i = static_cast<size_t>(titleEnd + 1); i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        courses[course.courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully. Total courses: " << courses.size() << endl;
    return true;
}

// Print all courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No course data loaded. Please load the data first." << endl;
        return;
    }

    cout << "Here is a sample schedule:" << endl;
    for (const auto& pair : courses) {
        const Course& course = pair.second;
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Print detailed information about a specific course
void printCourseInformation(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No course data loaded. Please load the data first." << endl;
        return;
    }

    cout << "What course do you want to know about? ";
    string courseNumber;
    cin >> courseNumber;

    // Normalize to uppercase so csci400 works
    for (char& c : courseNumber) {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }

    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.courseTitle << endl;

    cout << "Prerequisites: ";
    if (course.prerequisites.empty()) {
        cout << "None";
    } else {
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            const string& prereqId = course.prerequisites[i];
            cout << prereqId;
            if (i + 1 < course.prerequisites.size()) {
                cout << ", ";
            }
        }
    }
    cout << endl;
}

// Display the main menu
void printMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    map<string, Course> courses;
    bool dataLoaded = false;

    cout << "Welcome to the course planner." << endl;

    int choice = 0;
    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from the menu." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            if (loadDataStructure(courses)) {
                dataLoaded = true;
            } else {
                dataLoaded = false;
            }
            break;

        case 2:
            if (!dataLoaded) {
                cout << "Error: Course data not loaded. Please select option 1 first." << endl;
            } else {
                printCourseList(courses);
            }
            break;

        case 3:
            if (!dataLoaded) {
                cout << "Error: Course data not loaded. Please select option 1 first." << endl;
            } else {
                printCourseInformation(courses);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}

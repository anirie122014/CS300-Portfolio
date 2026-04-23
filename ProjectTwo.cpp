// Name:  Project ABCU Adivising Program
// Arthur: Aniri Estrella


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// store information

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};
// each node holds a course and pointers to left and right children
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// organzie and store courses
// allows insertion, search, and printing in sorted order
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Course search(Node* node, string courseNumber);

public:
    BinarySearchTree();
    void Insert(Course course);
    void PrintAllCourses();
    Course Search(string courseNumber);
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}
// insert a course into the Binary Search Tree
// Smallest course number to the left, largest to the right
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}
// Finds correct position in the tree
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}
// Prints all courses in sorted order, uses in order traversal
void BinarySearchTree::PrintAllCourses() {
    inOrder(root);
}
// this prints sorted data
void BinarySearchTree::inOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    inOrder(node->left);
    cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
    inOrder(node->right);
}
// searches for a course by course number 
Course BinarySearchTree::Search(string courseNumber) {
    return search(root, courseNumber);
}

Course BinarySearchTree::search(Node* node, string courseNumber) {
    if (node == nullptr) {
        return Course();
    }

    if (node->course.courseNumber == courseNumber) {
        return node->course;
    }

    if (courseNumber < node->course.courseNumber) {
        return search(node->left, courseNumber);
    }
    else {
        return search(node->right, courseNumber);
    }
}

void loadCourses(string fileName, BinarySearchTree& bst) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: File could not be opened." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string token;

        Course course;

        // Course Number
        getline(ss, token, ',');
        course.courseNumber = token;

        // Course Title
        getline(ss, token, ',');
        course.courseTitle = token;

        // Prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        bst.Insert(course);
    }

    file.close();

    cout << "Courses loaded successfully." << endl;
}

int main() {  //prompt user for file name, loads course data and prints all
        BinarySearchTree bst;
        string fileName;
        int choice = 0;
        bool dataLoaded = false;

        while (choice != 9) {
            cout << "\nMenu:" << endl;
            cout << "  1. Load Data Structure" << endl;
            cout << "  2. Print Course List" << endl;
            cout << "  3. Print Course" << endl;
            cout << "  9. Exit" << endl;
            cout << "What would you like to do? ";
            cin >> choice;

            if (choice == 1) {
                if (dataLoaded) {
                    cout << "Data has already been loaded." << endl;
                }
                else {
                    cout << "Enter file name: ";
                    cin >> ws;
                    getline(cin, fileName);

                    loadCourses(fileName, bst);
                    dataLoaded = true;
                }
            }
            else if (choice == 2) {
                if (!dataLoaded) {
                    cout << "Please load the data file first." << endl;
                }
                else {
                    cout << "\nCourse List:" << endl;
                    bst.PrintAllCourses();
                }
            }
            else if (choice == 3) {
                if (!dataLoaded) {
                    cout << "Please load the data file first." << endl;
                }
                else {
                    string courseNumber;
                    cout << "What course do you want to know about? ";
                    cin >> courseNumber;

                    Course course = bst.Search(courseNumber);

                    if (course.courseNumber == "") {
                        cout << "Course not found." << endl;
                    }
                    else {
                        cout << course.courseNumber << ", " << course.courseTitle << endl;

                        cout << "Prerequisites: ";
                        if (course.prerequisites.size() == 0) {
                            cout << "None";
                        }
                        else {
                            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                                cout << course.prerequisites[i];
                                if (i < course.prerequisites.size() - 1) {
                                    cout << ", ";
                                }
                            }
                        }
                        cout << endl;
                    }
                }
            }
            else if (choice == 9) {
                cout << "Thank you!" << endl;
            }
            else {
                cout << choice << " is not a valid option." << endl;
            }
        }

        return 0;
    }

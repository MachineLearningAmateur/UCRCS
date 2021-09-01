#include "Student.h"

#include<iostream>
#include <vector>
using namespace std;

int main(int argc,char* argv[1]) {
    if (argc < 2) {
        cerr << "Proper usage: " << argv[0] << " <input>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open \"" << argv[1] << "\"." << endl;
        return 1;
    }

    vector<Student*> students;
    string first_name,last_name;
    int sid;
    while(ifs>>first_name) {
        ifs >> last_name >> sid;
        students.push_back(new Student(first_name+" "s+last_name,sid));
    }

    int unique_students = 0;
    int comparisons = 0;
    // Overall runtime complexity: O(n^2), n = input size
    // Overall space complexity: O(n), n = input size
    for (unsigned i = 0;i < students.size();++i) { // O(n), n = input size
        bool already_counted = false; // O(1)
        for (unsigned j = 0;j < i;++j) { // O(n)
            comparisons++; // O(1)
            if (*students.at(j) == *students.at(i)) {  // O(1)
                already_counted = true; // O(1)
            }
        }
        if (!already_counted) { // O(1)
            unique_students++; // O(1)
        } 
    }
    cout << "Unique students: " << unique_students << endl;
    cout << "\tComparisons made: " << comparisons << endl;

    /* Insert solution here */
    //watashi no kotae!!!
    HashTable _students(students.size());
    for (unsigned int i = 0; i < students.size(); i++) {
        _students.insert(students.at(i));
    }
    cout << "Unique students: " << _students.unique_students << endl;
    cout << "\tComparisons made: " << _students.comparisons << endl;

    return 0;
}
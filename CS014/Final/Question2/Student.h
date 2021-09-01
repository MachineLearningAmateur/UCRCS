#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Student {
    private:
        std::string _name;
        int _sid;
    public:
        Student() : _name(""), _sid(0) { }
        Student(std::string name,int sid) : _name(name),_sid(sid) { }

        /* Accessors */
        int sid() const { return _sid; }
        std::string name() const { return _name; }
        bool operator==(const Student &rhs) const { return rhs._sid == this->_sid; }

        friend std::ostream& operator<<(std::ostream&,const Student&);
};

class HashTable {
    private:
        Student* hashTable;
        int size;
    public:
        HashTable(int size);
        void insert(Student* student);
        void erase(Student* student);
        int rehash(Student* student);
        void count(string dataType); 
        int unique_students;
        int comparisons;
};

#endif // __STUDENT_H__

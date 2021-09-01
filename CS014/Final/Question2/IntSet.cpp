// HashTable::HashTable(int size) {
//     hashTable = new Student[size];
//     unique_students = 0;
//     comparisons = 0;
//     this->size = size;
// }

// void HashTable::insert(Student* student) {
//     string type = "student";
//     int key = rehash(student);
//     if (hashTable[key] != nullptr) {
//         type = "comparison";
//         count(type);
//         return;
//     }
//     hashTable[key] = student;
//     count(type);
// }

// void HashTable::erase(Student* student) {
//     int key = rehash(student);
//     hashTable[key] = nullptr;
// }

// //used multiplicative string hash formula
// int HashTable::rehash(Student* student) {
//     string sid = student->name();
//     int stringHash = 5381;
//     for (char c : sid) {
//         stringHash = (stringHash * 7) + c;
//     }
//     return stringHash%size;
// }

// void HashTable::count(string dataType) {
//     if (dataType == "student") {
//         unique_students++;
//     } else {
//         comparisons++;
//     }
// }
#include "IntSet.h"

IntSet::IntSet() {

}

IntSet::IntSet(int n) {

}

IntSet::IntSet(const IntSet &passBy) {
    
}

IntSet& IntSet::operator=(const IntSet &copy) {

}

void IntSet::insert(int) {

}
void IntSet::erase(int) {

}

void IntSet::rehash(size_t size) {
    
}

int IntSet::comparisons() {
    return this->_comparisons;
}

size_t IntSet::size() const {
    return this->_size;
}

size_t IntSet::capacity() const {
    return this->_capacity;
}

bool IntSet::empty() const {
    if (_size == 0) {
        return true;
    } else
    {
        return false;
    }
}

int IntSet::count(int) {

} 

int IntSet::find_or_insert(int) {

}

int IntSet::probe(int) const {

}

int IntSet::hash(int,int=0) const {

}

int IntSet::hash_map(int) const {
    
}
int IntSet::compression_map(int) const {

}
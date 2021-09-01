#include "Student.h"

using namespace std;

ostream& operator<<(ostream& out,const Student& rhs) {
    out << rhs._name << " (" << rhs._sid << ")";
    return out;
}

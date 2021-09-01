#include "Patient.h"

using namespace std;

ostream &operator<<(ostream &out,const Patient &rhs) {
    out << rhs._name << " (" << rhs._patient_id << "): ";
    switch (rhs._urgency) {
        case Low:
            out << "Low";
            break;
        case Med:
            out << "Medium";
            break;
        case High:
            out << "High";
            break;
    }
    return out;
}
    

#include "Patient.h"

#include <iostream>
#include <utility>

#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

// Describe any additional functions that are needed for part III
/*class Urgency Queue {
    private:
     queue<Patient*> highUrgency;
     queue<Patient*> medUrgency;
     queue<Patient*> lowUrgency;
     bool highEmpty; //set to true initially, but will be set false when push_urgency pushes in a high urgency patient.
     bool medEmpty; //set to true initially, but will be set false when push_urgency pushes in a med urgency patient.
     int sz; //sz = highUrgency.size() + medUrgency.size() + lowUrgency.size() 
    public:
     void push_urgency(Patient* patient_record);
     Patient* front();
     void dequeue();
     void print();
};

/* Implement a function that decides which of the three queues to push patient_record into. 
 void UrgencyQueue::push_urgency(Patient* patient_record) {
    Urgency urgency = patient_record->urgency();
    if statements to determine which level of urgency and then push into respective level of urgency queue
    ...
    if Urgency::High == urgency {
        highEmpty->true
        highUrgency.push(patient_record)
        sz++
    }
    if Urgency::Med == urgency {
        medEmtpy->true
        medUrgency.push(patient_record)
        sz++
    } 
    if Urgency::Low...

//}
//Implement another function called front that returns the patient with the highest urgency available. 
// Patient* UrgencyQueue::front() {
    check bool statements
    if (!highEmpty)
        return highUrgency.front();
    else if (!medEmpty)
        return medUrgency.front();
    else
        return lowUrgency.front();
//}
    //Implement a function called dequeue that dequeues the patient with the highest urgency available; assuming it is implemented
    correctly, sorting is not necessary
    void UrgencyQueue::dequeue() { 
      sz--
      if (!highEmpty)
        highUrgency.pop();
      else if (!medEmpty)
        medUrgency.pop();
      else
        lowUrgency.pop();
    }
    //Implement a function called print that prints out the current patients within Urgency queue (stored within all 3 queues).
    void UrgencyQueue::print() {
        either 3 for loops, one for each queue: starting from high to low
        or 
        perhaps, implement an iterator pointer for each queue. Traverse from highUrgency iterator to lowUrgency iterator. Although, I am not too sure on how to properly
        implement that. It is just an idea because 3 for loops seem tedious. 
    
*/

class MinHeap
{
private:
    pair<int, int> *intake_times;
    int sz;
    int cap;
    void trickleDown(int index);

public:
    MinHeap()
    {
        cap = 10;
        intake_times = new pair<int, int>[cap];
        sz = 0;
    }
    void enqueue(pair<int, int> pData);
    void dequeue();
    int size();
    pair<int, int> priority();
};

void MinHeap::enqueue(pair<int, int> pData)
{
    if (sz < (2 * cap) / 3)
    { //70%~ threshold rule
        int cIndex = sz;
        sz++;
        intake_times[cIndex] = pData;
        while (cIndex > 0)
        {
            int pIndex = (cIndex - 1) / 2;
            pair<int, int> temp = intake_times[pIndex];
            if (intake_times[cIndex].first < temp.first)
            {
                intake_times[pIndex] = pData;
                intake_times[cIndex] = temp;
                cIndex = pIndex;
            }
            else
            {
                break;
            }
        }
    }
    else    
    {   //resize when the 70% threshold is met
        pair<int, int> *temp = new pair<int, int>[cap * 2];
        cap = cap * 2;
        for (int i = 0; i < sz; i++)
        {
            temp[i] = intake_times[i];
        }
        delete[] intake_times;
        intake_times = temp;
        int cIndex = sz;
        sz++;
        intake_times[cIndex] = pData;
        while (cIndex != 0)
        {
            int pIndex = (cIndex - 1) / 2;
            pair<int, int> temp = intake_times[pIndex];
            if (intake_times[cIndex].first < temp.first)
            {
                intake_times[pIndex] = pData;
                intake_times[cIndex] = temp;
                cIndex = pIndex;
            }
            else
            {
                break;
            }
        }
    }
}

void MinHeap::dequeue()
{
    if (sz == 0)
    {
        return;
    }
    else
    {
        intake_times[0] = intake_times[sz - 1];
        sz--;
         trickleDown(0);
    }
}

void MinHeap::trickleDown(int index)
{
     int sib1 = (2 * index) + 1;
    int sib2 = (2 * index) + 2;
    int smallJuan;
    //when sib1 or sib2 goes past sz (num of pairs)
    if (sz - 1 <= sib1 || sz - 1 <= sib2)
    {
        return;
    }
    // when sz = 2 and there is no sib2
    if (sib2 >= sz - 1)
    {
        smallJuan = sib1;
    }
    else if (intake_times[sib1].first <= intake_times[sib2].first)
    {
        smallJuan = sib1;
    }
    else
    {
        smallJuan = sib2;
    }
    //here
    if (intake_times[smallJuan].first <= intake_times[index].first)
    {
        pair<int, int> temp = intake_times[index];
        intake_times[index] = intake_times[smallJuan];
        intake_times[smallJuan] = temp;
    }
    trickleDown(smallJuan);
}

pair<int, int> MinHeap::priority()
{
    return intake_times[0];
}

int MinHeap::size() {
    return sz;
}
Patient *search(pair<int, int> patient, vector<Patient *> records)
{
    int id = patient.second;
    Patient *temp = nullptr;
    for (unsigned int i = 0; i < records.size(); i++)
    {
        if (records.at(i)->patient_id() == id)
        {
            temp = records.at(i);
            return temp;
        }
    }
    return temp;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Proper usage: " << argv[0] << " <patients_file>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open())
    {
        cerr << "Error: Unable to open " << argv[1] << endl;
        return 1;
    }

    MinHeap intake_times; // Part I, what data structure should be used here and why? (implement) A: A minHeap should be implemented because building a heap is O(n) and
                          // sorting it is O(logn), thus a heapsort is O(nlogn). Also, finding patient with smallest intake_take is O(1). 
                          //However, there is an amoritized runtime of O(logn) for enqueue when number of patients exceed array size. MinHeap is a wrapper class that
                          //contains an array following the structure of a complete tree; compact array without spaces. 

     unordered_map<int, Patient*> patients; // Part II, what data structure should be used here and why? (implement) A: An unordered map should be implemented when accessing 
     //unique ids. Assuming there is a perfect hash for unique ids then finding an unique id of a patient is O(1). 
     //However, it is unlikely to create the perfect hash for large numbers of unique ids, so on average 
     //the run time is O(a), where a = load factor (number of keys stored by the hashtable). On the otherhand, worst case runtime is O(n) but hashtables
     //a = load factor. On the otherhand, worst case runtime is O(n) but hashtables are not meant for worst case runtime. The key will be unique ID and patient_record will
     //be returned. Nevertheless, best case scenario is O(1) which is the speed we need for locating a patient's identity amongst many others.

    //UrgencyQueue urgency; // Part III, what data structure should be used here and why? (comments only) a wrappper class called Urgency queue that contains 3 queues,
    //one for each level of urgency (low, med, high) *also, I would implement this UrgencyQueue as a template class, but I don't know how; I only know that the possibility exists.
    /* For this question, it is important to use a first in first out type of data structure. The sorting is based on the level of urgency (low, med, high). One way
    to approach this question is to create 3 queues implemented by STL in the wrapper class. Each queue is designated for one level of urgency (queue<Patient*> highUrgency, 
    queue<Patient*> medUrgency, queue<Patient*> lowUrgency). This implementation will be a wrapper class called UrgencyQueue containing the 3 queues implemented. 
    */
    string first_name, last_name;
    int intake_time, urgency, id;
    vector<Patient*> patientRecord;

    // Overall runtime complexity: O(nlogn), n = input size of patients
    // Overall space complexity: O(n), n = number of patients
    while (ifs >> id)
    {                                                                             //O(n), n = input size
        ifs >> first_name >> last_name >> intake_time >> urgency;                 // O(1)
        Patient *patient_record = new Patient(id, first_name + " "s + last_name); // O(1)
        patient_record->urgency(urgency);                                         // O(1)
        patientRecord.push_back(patient_record); //O(1)
        intake_times.enqueue(make_pair(intake_time, id)); // amoritized cost of O(logn) when the array does not require to be expanded. Non-amoritized cost: O(nlogn)
        patients.insert(make_pair(id,patient_record)); // O(1)
        // patient_urgencies.push(patient_record) // O(1)
    }

    // Output Patients sorted by oldest intake_time (smallest) to newest intake_time (largest) (Implement)
    cout << "Sorted by intake times: " << endl;
    int sz = intake_times.size();
    Patient *patient = nullptr;
    for (int i = 0; i < sz; i++)
    {
        patient = search(intake_times.priority(), patientRecord);
        intake_times.dequeue();
        cout << *patient << endl;
    }

    // Output Patients ID's sorted by most urgent to least urgent
    // In comments describe how this would work.
    /*
    By creating 3 queues, insertion worst case runtime will become O(1) because it will only require one check (O(1)) on the urgency 
    level of patient and then insert(O(1)) the patient into their respective queue of urgency. Furthermore, the worst case runtime for dequeuing a patient is also O(1).
    This could be achieved by creating two booleans or flags (bool highEmpty, medEmpty). If highEmpty is false (O(1)), then only dequeue from queue<Patient*> highUrgency until empty. 
    If highEmpty is true and medEmpty is false (O(1)), then dequeue from queue<Patient*> medUrgency until empty. Once, both bools are false O(1), then dequeue from lowUrgency.
    Assuming, patients are inserted into queue based on the time they're admitted into the hospital, then the ones with high urgency and first admitted will be attended to
    first. To print out, 3 for loops can be used, one for each level of urgency queue. 
    */

    return 0;
}

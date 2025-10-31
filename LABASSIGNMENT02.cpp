#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

// 1. Patient Record ADT
struct PatientNode {
    int id; string name, date, details; PatientNode* next;
    PatientNode(int i, string n, string d, string dt) : id(i), name(n), date(d), details(dt), next(nullptr) {}
};

// 4. Billing (Polynomial) Node
struct TermNode {
    int coeff, exp; TermNode* next;
    TermNode(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

// 2. Patient Management System
class HospitalSystem {
    PatientNode* patientListHead;
    int nextID;
    stack<PatientNode*> undoStack; // b) UndoStack
    static const int MAX_Q = 5;
    string emergencyQ[MAX_Q]; // c) EmergencyQueue
    int front, rear;

public:
    HospitalSystem() : patientListHead(nullptr), nextID(1001), front(-1), rear(-1) {}

    // a) addPatientRecord
    void addPatientRecord(string n, string d, string dt) {
        PatientNode* p = new PatientNode(nextID++, n, d, dt);
        p->next = patientListHead;
        patientListHead = p;
        undoStack.push(p);
        cout << "Added: " << n << endl;
    }

    // (Helper for ADT) deletePatient
    bool deletePatient(int id) {
        PatientNode* curr = patientListHead, *prev = nullptr;
        if (curr != nullptr && curr->id == id) {
            patientListHead = curr->next;
            cout << "Deleted: " << curr->name << endl;
            delete curr; return true;
        }
        while (curr != nullptr && curr->id != id) {
            prev = curr; curr = curr->next;
        }
        if (curr == nullptr) { cout << "Delete failed." << endl; return false; }
        prev->next = curr->next;
        cout << "Deleted: " << curr->name << endl;
        delete curr; return true;
    }

    // (Helper for ADT) retrievePatient
    void retrievePatient(int id) {
        PatientNode* curr = patientListHead;
        while (curr != nullptr) {
            if (curr->id == id) {
                cout << "Found: " << curr->name << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Not found: " << id << endl;
    }

    // b) undoAdmission
    void undoAdmission() {
        if (undoStack.empty()) { cout << "Undo empty." << endl; return; }
        PatientNode* p = undoStack.top();
        undoStack.pop();
        cout << "Undoing " << p->name << endl;
        deletePatient(p->id);
    }

    // c) manageEmergencyQueue (Enqueue)
    void addEmergency(string name) {
        if ((front == 0 && rear == MAX_Q - 1) || (front == rear + 1)) {
            cout << "Q full." << endl; return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % MAX_Q;
        emergencyQ[rear] = name;
        cout << "Q Add: " << name << endl;
    }

    // c) manageEmergencyQueue (Dequeue)
    void seeNextEmergency() {
        if (front == -1) { cout << "Q empty." << endl; return; }
        string name = emergencyQ[front];
        if (front == rear) { front = -1; rear = -1; }
        else { front = (front + 1) % MAX_Q; }
        cout << "Q See: " << name << endl;
    }

    // (Helper for Billing)
    void printPoly(TermNode* p) {
        while (p) {
            cout << p->coeff << "x^" << p->exp;
            if (p->next) cout << " + ";
            p = p->next;
        }
    }
    
    // d) calculateBilling
    void calculateBilling() {
        cout << "\nBilling:" << endl;
        TermNode* b1 = new TermNode(1500, 0); b1->next = new TermNode(200, 1);
        TermNode* b2 = new TermNode(50, 1); b2->next = new TermNode(1000, 2);
        TermNode* totalH = nullptr, *totalT = nullptr;
        while (b1 || b2) {
            TermNode* n = nullptr;
            if (!b1) { n = new TermNode(b2->coeff, b2->exp); b2 = b2->next; }
            else if (!b2) { n = new TermNode(b1->coeff, b1->exp); b1 = b1->next; }
            else {
                if (b1->exp > b2->exp) { n = new TermNode(b1->coeff, b1->exp); b1 = b1->next; }
                else if (b2->exp > b1->exp) { n = new TermNode(b2->coeff, b2->exp); b2 = b2->next; }
                else { n = new TermNode(b1->coeff + b2->coeff, b1->exp); b1 = b1->next; b2 = b2->next; }
            }
            if (!totalH) { totalH = totalT = n; }
            else { totalT->next = n; totalT = n; }
        }
        cout << "Total: "; printPoly(totalH); cout << endl;
        while (totalH) { TermNode* t = totalH; totalH = totalH->next; delete t; }
    }

    // e) evaluateInventory
    void evaluateInventory() {
        cout << "\nInventory:" << endl;
        string exp = "100 50 + 10 3 * -"; // (100+50) - (10*3)
        cout << "Postfix: " << exp << endl;
        stack<int> s; stringstream ss(exp); string token;
        while (ss >> token) {
            if (token == "+" || token == "-" || token == "*") {
                int op2 = s.top(); s.pop(); int op1 = s.top(); s.pop();
                if (token == "+") s.push(op1 + op2);
                else if (token == "-") s.push(op1 - op2);
                else if (token == "*") s.push(op1 * op2);
            } else { s.push(stoi(token)); }
        }
        cout << "Final: " << s.top() << endl;
    }
};

// --- Main Function (Demonstration) ---
int main() {
    HospitalSystem hs;
    cout << "--- Patient & Undo ---" << endl;
    hs.addPatientRecord("Alice", "D1", "Fever");
    hs.addPatientRecord("Bob", "D2", "Arm");
    hs.retrievePatient(1001);
    hs.undoAdmission();
    hs.retrievePatient(1002);
    hs.deletePatient(1001);

    cout << "\n--- Emergency Q ---" << endl;
    hs.addEmergency("Charlie");
    hs.seeNextEmergency();
    hs.seeNextEmergency();

    cout << "\n--- Ops Demos ---" << endl;
    hs.calculateBilling();
    hs.evaluateInventory();
    return 0;
}
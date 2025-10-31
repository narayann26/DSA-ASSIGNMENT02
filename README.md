# 🏥 Hospital Management System (DSA Assignment)

This is a C++ console application built for a Data Structures and Algorithms (DSA) course. The project simulates a basic hospital management system and demonstrates the practical application of several key data structures:

* **Singly Linked Lists** (for patient database)
* **Stacks** (for an "Undo" feature and Postfix evaluation)
* **Circular Queues** (for an emergency room triage)
* **Polynomials as Linked Lists** (for a billing system)

---

## Features

* **Add Patient Record**: Add a new patient to the hospital database.
* **Delete Patient Record**: Remove a patient's record using their unique ID.
* **Retrieve Patient Record**: Find and display a patient's details using their ID.
* **Undo Admission**: Instantly undo the last patient admission, removing them from the system.
* **Emergency Triage Queue**: A fixed-size (FIFO) queue to manage critical patients.
* **Dynamic Billing System**: Calculates a patient's total bill by adding multiple service costs, represented as polynomials.
* **Inventory Calculator**: Evaluates inventory stock levels using a postfix expression.

---

## 🛠️ Data Structures Implemented

This project is a hands-on demonstration of how different data structures are suitable for different problems.

### 1. Singly Linked List (Patient Database)
* **Purpose**: Used as the primary database for storing all patient records (`PatientNode`). It's a dynamic structure, perfect for when you don't know how many patients will be admitted.
* **How it works**:
    * `patientListHead` points to the most recently added patient.
    * `addPatientRecord` inserts a new node at the **head** of the list (O(1) time complexity).
    * `deletePatient` and `retrievePatient` traverse the list (O(n) time complexity).
* **Code Snippet (`struct`)**:
    ```cpp
    struct PatientNode {
        int id;
        string name, date, details;
        PatientNode* next;
    };
    ```

### 2. Stack (Undo Admission)
* **Purpose**: To implement an "Undo" feature for the last patient admission. Stacks are LIFO (Last-In, First-Out), which perfectly maps to the "undo last action" concept.
* **How it works**:
    * Uses the standard C++ `<stack>` library (`stack<PatientNode*> undoStack`).
    * When `addPatientRecord` is called, a pointer to the newly created `PatientNode` is **pushed** onto the `undoStack`.
    * When `undoAdmission` is called, it **pops** the top node from the stack and then uses its `id` to call `deletePatient`, effectively reversing the admission.
* **Code Snippet (function)**:
    ```cpp
    void undoAdmission() {
        if (undoStack.empty()) { /* ... */ return; }
        PatientNode* p = undoStack.top();
        undoStack.pop();
        deletePatient(p->id);
    }
    ```

### 3. Circular Queue (Emergency Room)
* **Purpose**: To manage a fixed-size emergency room waiting list. A queue is FIFO (First-In, First-Out), ensuring the patient who has been waiting the longest is seen first.
* **How it works**:
    * Implemented using a fixed-size array (`string emergencyQ[MAX_Q]`).
    * Uses `front` and `rear` indices with **modulo arithmetic** (`% MAX_Q`) to wrap around the array, making it circular.
    * This is far more efficient than shifting all elements in a standard array.
* **Code Snippet (function)**:
    ```cpp
    void addEmergency(string name) {
        if ((front == 0 && rear == MAX_Q - 1) || (front == rear + 1)) {
            // Queue is full
        }
        // ... logic to add using % MAX_Q
    }
    ```

### 4. Linked List (Polynomial Billing)
* **Purpose**: To represent and add different billing charges (e.g., room cost, service fees, medicine) as mathematical polynomials.
* **How it works**:
    * A separate linked list (`TermNode`) is used, where each node holds a **coefficient** and an **exponent**.
    * Example: `1500x^0` (a $1500 room charge) + `200x^1` (200 units of a $1 service).
    * The `calculateBilling` function performs **polynomial addition** by merging two sorted linked lists, combining terms with the same exponent.
* **Code Snippet (`struct`)**:
    ```cpp
    struct TermNode {
        int coeff, exp;
        TermNode* next;
    };
    ```

### 5. Stack (Postfix Evaluation)
* **Purpose**: To calculate the total inventory from a string expression written in **Postfix (Reverse Polish) Notation**.
* **How it works**:
    * The `evaluateInventory` function processes the expression string `100 50 + 10 3 * -`.
    * It uses a `stack<int>`:
        1.  If it sees a number (operand), it's **pushed** onto the stack.
        2.  If it sees an operator (`+`, `-`, `*`), it **pops** the top two operands, performs the operation, and **pushes** the result back onto the stack.
    * The final number left on the stack is the result.

---

## 🚀 How to Compile and Run

1.  **Clone the repository**:
    ```bash
    git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
    cd your-repo-name
    ```

2.  **Compile the code**:
    (Assuming you have `g++` or a similar C++ compiler)
    ```bash
    g++ main.cpp -o hospital_system
    ```
    *(Note: You may need to rename your `.cpp` file to `main.cpp`)*

3.  **Run the executable**:
    ```bash
    ./hospital_system
    ```

---

## 📜 Example Output

Running the `main()` function in the code will produce the following output, demonstrating all features:

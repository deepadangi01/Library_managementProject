#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Employee class (Base class)
class Employee {
protected:
    int id;
    string name;
    string department;
    double salary;

public:
    Employee(int i, string n, string d, double s) : id(i), name(n), department(d), salary(s) {}

    // Virtual function for displaying employee details
    virtual void display() {
        cout << "ID: " << id << ", Name: " << name << ", Department: " << department << ", Salary: $" << salary << endl;
    }

    int getId() { return id; }
    string getName() { return name; }
    string getDepartment() { return department; }
    double getSalary() { return salary; }
    void setSalary(double s) { salary = s; }
};

// Manager class (Derived class)
class Manager : public Employee {
private:
    double bonus;

public:
    Manager(int i, string n, string d, double s, double b) : Employee(i, n, d, s), bonus(b) {}

    void display() override {
        cout << "Manager - ID: " << id << ", Name: " << name << ", Department: " << department
             << ", Salary: $" << salary << ", Bonus: $" << bonus << endl;
    }
};

// Employee Database using Linked List (for DSA)
class EmployeeDatabase {
private:
    struct Node {
        Employee* emp;
        Node* next;
        Node(Employee* e) : emp(e), next(nullptr) {}
    };

    Node* head;

public:
    EmployeeDatabase() : head(nullptr) {}

    // Add Employee (Insert at end)
    void addEmployee(Employee* e) {
        Node* newNode = new Node(e);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "Employee added successfully!\n";
    }

    // Search Employee using Binary Search (after sorting)
    Employee* searchEmployee(int id) {
        vector<Employee*> empList = getAllEmployees();
        sort(empList.begin(), empList.end(), [](Employee* a, Employee* b) { return a->getId() < b->getId(); });

        int left = 0, right = empList.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (empList[mid]->getId() == id) return empList[mid];
            if (empList[mid]->getId() < id) left = mid + 1;
            else right = mid - 1;
        }
        return nullptr;
    }

    // Display Employees
    void displayEmployees() {
        Node* temp = head;
        while (temp) {
            temp->emp->display();
            temp = temp->next;
        }
    }

    // Get All Employees (for Sorting & Searching)
    vector<Employee*> getAllEmployees() {
        vector<Employee*> employees;
        Node* temp = head;
        while (temp) {
            employees.push_back(temp->emp);
            temp = temp->next;
        }
        return employees;
    }

    // Save Employees to File
    void saveToFile() {
        ofstream file("employees.txt");
        Node* temp = head;
        while (temp) {
            file << temp->emp->getId() << "," << temp->emp->getName() << "," << temp->emp->getDepartment() << "," << temp->emp->getSalary() << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Data saved successfully!\n";
    }

    // Destructor to free memory
    ~EmployeeDatabase() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->emp;
            delete temp;
        }
    }
};

// Menu Function
void menu() {
    EmployeeDatabase db;
    int choice;

    do {
        cout << "\n=== Company Management System ===\n";
        cout << "1. Add Employee\n2. Add Manager\n3. Display Employees\n4. Search Employee\n5. Save to File\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, dept;
                double salary;
                cout << "Enter ID, Name, Department, Salary: ";
                cin >> id >> name >> dept >> salary;
                db.addEmployee(new Employee(id, name, dept, salary));
                break;
            }
            case 2: {
                int id;
                string name, dept;
                double salary, bonus;
                cout << "Enter ID, Name, Department, Salary, Bonus: ";
                cin >> id >> name >> dept >> salary >> bonus;
                db.addEmployee(new Manager(id, name, dept, salary, bonus));
                break;
            }
            case 3:
                db.displayEmployees();
                break;
            case 4: {
                int id;
                cout << "Enter Employee ID to search: ";
                cin >> id;
                Employee* emp = db.searchEmployee(id);
                if (emp) emp->display();
                else cout << "Employee not found!\n";
                break;
            }
            case 5:
                db.saveToFile();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again!\n";
        }
    } while (choice != 6);
}

// Main Function
int main() {
    menu();
    return 0;
}

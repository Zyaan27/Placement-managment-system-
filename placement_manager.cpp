#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    Student(const string& name, int rollNumber)
        : name(name), rollNumber(rollNumber), isPlaced(false) {}

    string getName() const { return name; }
    int getRollNumber() const { return rollNumber; }
    bool isPlacedInCompany() const { return isPlaced; }
    void placeInCompany() { isPlaced = true; }

private:
    string name;
    int rollNumber;
    bool isPlaced;
};

class Company {
public:
    Company(const string& name) : name(name), employeeCount(0) {}

    string getName() const { return name; }
    int getEmployeeCount() const { return employeeCount; }
    void addEmployee() { employeeCount++; }

private:
    string name;
    int employeeCount;
};

class PlacementManager {
public:
    PlacementManager() : studentCount(0), companyCount(0) {}

    void addStudent(const string& name, int rollNumber) {
        if (studentCount < MAX_STUDENTS) {
            students[studentCount++] = new Student(name, rollNumber);
            cout << "✅ Student added successfully.\n";
        } else {
            cout << "❌ Max student capacity reached!\n";
        }
    }

    void addCompany(const string& name) {
        if (companyCount < MAX_COMPANIES) {
            companies[companyCount++] = new Company(name);
            cout << "✅ Company added successfully.\n";
        } else {
            cout << "❌ Max company capacity reached!\n";
        }
    }

    void displayStudents() const {
        cout << "\n📋 Students:\n";
        if (studentCount == 0) {
            cout << "No students found.\n";
            return;
        }
        for (int i = 0; i < studentCount; ++i) {
            cout << "Name: " << students[i]->getName()
                 << ", Roll Number: " << students[i]->getRollNumber()
                 << (students[i]->isPlacedInCompany() ? " (Placed)\n" : " (Not Placed)\n");
        }
    }

    void displayCompanies() const {
        cout << "\n🏢 Companies:\n";
        if (companyCount == 0) {
            cout << "No companies found.\n";
            return;
        }
        for (int i = 0; i < companyCount; ++i) {
            cout << "Name: " << companies[i]->getName()
                 << ", Number of Employees: " << companies[i]->getEmployeeCount() << endl;
        }
    }

    void placeStudent(int studentRollNumber, const string& companyName) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i]->getRollNumber() == studentRollNumber) {
                students[i]->placeInCompany();
                for (int j = 0; j < companyCount; ++j) {
                    if (companies[j]->getName() == companyName) {
                        companies[j]->addEmployee();
                        cout << "✅ Student " << students[i]->getName()
                             << " placed in " << companies[j]->getName() << ".\n";
                        return;
                    }
                }
                cout << "❌ Company not found.\n";
                return;
            }
        }
        cout << "❌ Student not found.\n";
    }

    ~PlacementManager() {
        for (int i = 0; i < studentCount; ++i) delete students[i];
        for (int i = 0; i < companyCount; ++i) delete companies[i];
    }

private:
    static const int MAX_STUDENTS = 100;
    static const int MAX_COMPANIES = 100;
    Student* students[MAX_STUDENTS];
    Company* companies[MAX_COMPANIES];
    int studentCount;
    int companyCount;
};

int main() {
    PlacementManager manager;
    int choice;

    while (true) {
        cout << "\n===== 📌 Placement Management Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Company\n";
        cout << "3. Display Students\n";
        cout << "4. Display Companies\n";
        cout << "5. Place Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int rollNumber;
            cin.ignore();
            cout << "Enter student name: ";
            getline(cin, name);
            cout << "Enter roll number: ";
            cin >> rollNumber;
            manager.addStudent(name, rollNumber);
            break;
        }
        case 2: {
            string name;
            cin.ignore();
            cout << "Enter company name: ";
            getline(cin, name);
            manager.addCompany(name);
            break;
        }
        case 3:
            manager.displayStudents();
            break;
        case 4:
            manager.displayCompanies();
            break;
        case 5: {
            int rollNumber;
            string companyName;
            cout << "Enter student's roll number: ";
            cin >> rollNumber;
            cin.ignore();
            cout << "Enter company name: ";
            getline(cin, companyName);
            manager.placeStudent(rollNumber, companyName);
            break;
        }
        case 6:
            cout << "👋 Exiting the system. Goodbye!\n";
            return 0;
        default:
            cout << "❌ Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

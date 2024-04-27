#include <iostream>
#include <string>
using namespace std;

//FORWARD DECLARATION
class Project;
class Employee;
class Department;


//NAME CLASS
class Name {
	string fname;
	string lname;
public:
	Name(string f, string l) {
		fname = f;
		lname = l;
	}
	void displayName() {
		cout << "Name: " << fname << " " << lname << endl;
	}
};


//ADDRESS CLASS
class Address {
	int houseNo;
	char block;
	int streetNo;
	string city;
public:
	Address(int h, char b, int s, string c){
		houseNo = h;
		block = b;
		streetNo = s;
		city = c;
	}
	void displayAddress() {
		cout << "Address: " << houseNo << ", " << block << ", " << streetNo << ", " << city << "." << endl;
	}
};


//PROJECT CLASS
class Project {
	int id;
	string projectDescription;
	int employeesWorkingOn;
	Employee* employee[10];
public:
	Project(int ID, string pd) {
		id = ID;
		projectDescription = pd;
		cout << endl << "Object of project has been created" << endl << endl;
		employeesWorkingOn = 0;
	}

	void displayProjectInfo() {
		cout << "Project id: " << id << endl << "Project Description: " << projectDescription << endl << endl;
	}

	int getId() {
		return id;
	}
	void IncEmployeesWorkingOn() {
		employeesWorkingOn++;
	}

	void DecEmployeesWorkingOn() {
		employeesWorkingOn--;
	}

	bool AddEmployee(Employee* emp);
	bool RemoveEmployee(Employee* emp);
	void DisplayAllEmployees();

	
};



//EMPLOYEE CLASS
class Employee {
	int ID;
	Name name;
	Address permanentAddr;
	bool assignedToDept;
	Project* project[3];
	int projectCount;
	Department* Dept;
public:
	Employee(int id, string fn, string l, int h, char b, int s, string c):ID(id), name(fn, l), permanentAddr(h, b, s, c) {
		cout << endl << "Object of employee has been created" << endl << endl;
		projectCount = 0;
		Dept = NULL;
		assignedToDept = false;
	}

	void displayEmployeeInfo() {
		cout << "Employee Id: " << ID << endl;
		name.displayName();
		permanentAddr.displayAddress();
		cout << endl << endl;
	}
	bool AddProject(Project* proj);
	bool RemoveProject(int projectID);
	void displayAllProjects();

	void SetAssignedToDept(bool value) {
		assignedToDept = value;
	}
	bool GetAssignedToDept() {
		return assignedToDept;
	}
	bool SetDept(Department* dept);
	void displayDept();

	int getId() {
		return ID;
	}
	Department* getDepartment() {
		return Dept;
	}
};



//DEPARTMENT CLASS
class Department {
	int ID;
	string name;
	Employee* employee[50];
	int employeeCount;
public:
	Department(int id, string n) : name(n){
		ID = id;
		cout << endl << "Object of department has been created" << endl << endl;
		employeeCount = 0;
	}
	void displayDeptInfo() {
		if (this != nullptr) {
			cout << "Department ID: " << ID << endl << "Department Name: " << name << endl << endl;
		}
		else cout << "No department assigned to this employee." << endl << endl;
	}
	bool AddEmployee(Employee* emp);
	bool RemoveEmployee(int employeeID);
	void DisplayAllEmployees();

	int getid() {
		return ID;
	}
};


//PROJECT MEMBER FUNCTION
bool Project::AddEmployee(Employee* emp) {
	if (employeesWorkingOn < 10) {
		employee[employeesWorkingOn] = emp;
		employeesWorkingOn++;
	}
	else return false;
	return true;
}

bool Project::RemoveEmployee(Employee* emp) {
	bool found = false;
	int n = 0;
	for (int i = 0; i < employeesWorkingOn; i++) {
		if (employee[i] == emp) {
			found = true;
			n = i;
		}
	}
	if (found == true) {
		employeesWorkingOn--;
		for (int i = n; i < employeesWorkingOn; i++) {
			employee[i] = employee[i + 1];
		}
		return true;
	}
	return false;
}

void Project::DisplayAllEmployees() {
	if (employeesWorkingOn > 0) {
		for (int i = 0; i < employeesWorkingOn; i++) {
			employee[i]->displayEmployeeInfo();
		}
	}
	else cout << "There is no employee working on this project." << endl << endl;
}


//EMPLOYEE MEMBER FUNCTION
bool Employee::AddProject(Project* proj) {
	if (projectCount < 3) {
		for (int i = 0; i < projectCount; i++) {
			if (project[i] == proj) {
				return false;
			}
		}
		if (proj->AddEmployee(this) == false) {
			return false;
		}
		else {
			project[projectCount] = proj;
			projectCount++;
			return true;
		}
		
	}
	else return false;
}
bool Employee::RemoveProject(int projectID) {
	int n = 0;
	bool found = false;
	for (int i = 0; i < projectCount; i++) {
		if (project[i]->getId() == projectID) {
			found = true;
			n = i;
			project[i]->RemoveEmployee(this);
			break;
		}
	}
	if (found == true) {
		projectCount--;
		for (int i = n; i < projectCount; i++) {
			project[i] = project[i+1];
		}
		return true;
	}
	return false;
}

void Employee::displayAllProjects() {
	for (int i = 0; i < projectCount; i++) {
		project[i]->displayProjectInfo();
	}
}

bool Employee::SetDept(Department* dept) {
	Dept = dept;
	if (dept != nullptr) {
		this->SetAssignedToDept(true);
		return true;
	}
	else {
		this->SetAssignedToDept(false);
		return false;
	}
}

void Employee::displayDept() {
	Dept->displayDeptInfo();
}


//DEPARTMENT MEMBER FUNCTION
bool Department::AddEmployee(Employee* emp) {
	if (employeeCount < 10) {
		for (int i = 0; i < employeeCount; i++) {
			if (emp == employee[i]) {
				return false;
			}
		}
		if (emp->SetDept(this)==false) {
			return false;
		}
		else {
			employee[employeeCount++] = emp;
			return true;
		}
	}
	else return false;
}

bool Department::RemoveEmployee(int employeeID) {
	bool found = false;
	int n = 0;
	for (int i = 0; i < employeeCount; i++) {
		if (employee[i]->getId() == employeeID) {
			employee[i]->SetDept(nullptr);
			found = true;
			n = i;
		}
	}
	if (found == true) {
		employeeCount--;
		for (int i = n; i < employeeCount; i++) {
			employee[i] = employee[i+1];
		}
		return true;
	}
	else return false;
}

void Department::DisplayAllEmployees() {
	if (employeeCount > 0) {
		for (int i = 0; i < employeeCount; i++) {
			employee[i]->displayEmployeeInfo();
		}
	}
	else cout << "There is no employee in this department." << endl << endl;
}


int main() {
	int option = 0;
	Department* departmentArr[5] = {NULL};
	Employee* employeeArr[50] = {NULL};
	Project* projectArr[10] = {NULL};
	int departmentCount = 0;
	int employeeCount = 0;
	int projectCount = 0;
	while (option != 15) {
		cout << "Select one of these options. " << endl << "1. To create department. \n2. To create employee. \n3. To create project. \n4. Display A Department given its ID, (if it exists). \n5. Display An Employee given its ID, (if it exists). \n6. Display A Project given its ID, (if it exists). \n7. Add an Employee to a Department, provided the IDs. \n8. Add a Project to an Employee, provided the IDs\n9. Display all projects of An Employee given his / her ID.\n10. Display all employees of a Department given its ID.\n11. Remove an Employee from a Department, provided the IDs.\n12. Remove a Project from an Employee, provided the IDs.\n13. Display all Employees working on a project, provided Project ID.\n14. Display the Department of an Employee, provided Employee ID." << endl;
		cin >> option;
		if (option == 1) {
			if (departmentCount < 5) {
				bool duplicate = true;
				int id;
				int ID;
				string name;
				cout << "Enter ID: ";
				while (duplicate == true) {
					duplicate = false;
					cin >> id;
					for (int i = 0; i < departmentCount; i++) {
						if (id == departmentArr[i]->getid()) {
							duplicate = true;
							cout << "Already exists. Enter again!" << endl;
							cout << "Enter ID: ";
							break;
						}
					}
					if (duplicate == false) {
						ID = id;
					}
				}
				cout << "Enter name of the department: ";
				cin.ignore();
				getline(cin, name);
				Department* d = new Department(ID, name);
				departmentArr[departmentCount] = d;
				departmentCount++;
			}
			else cout << "Department objects have reached its maximum count" << endl << endl;
		}
		if (option == 2) {
			if (employeeCount < 50) {
				bool duplicate = true;
				string fname, lname, city;
				int id, houseno, streetno, ID;
				char block;
				cout << "Enter ID: ";
				while (duplicate == true) {
					duplicate = false;
					cin >> id;
					for (int i = 0; i < employeeCount; i++) {
						if (id == employeeArr[i]->getId()) {
							duplicate = true;
							cout << "Already exists. Enter again!" << endl;
							cout << "Enter ID: ";
							break;
						}
					}
					if (duplicate == false) {
						ID = id;
					}
				}
				cout << "Enter first name: ";
				cin.ignore();
				getline(cin, fname);
				cout << "Enter last name: ";
				getline(cin, lname);
				cout << "Enter house number: ";
				cin >> houseno;
				cout << "Enter block: ";
				cin >> block;
				cout << "Enter street number: ";
				cin >> streetno;
				cout << "Enter city: ";
				cin.ignore();
				getline(cin, city);
				Employee* emp = new Employee(ID, fname, lname, houseno, block, streetno, city);
				employeeArr[employeeCount] = emp;
				employeeCount++;
			}
			else cout << "Employee objects have reached its maximum count" << endl << endl;
		}
		if (option == 3) {
			if (projectCount < 10) {
				int id, ID;
				bool duplicate = true;
				string pd;
				cout << "Enter ID: ";
				while (duplicate == true) {
					duplicate = false;
					cin >> id;
					for (int i = 0; i < projectCount; i++) {
						if (id == projectArr[i]->getId()) {
							duplicate = true;
							cout << "Already exists. Enter again!" << endl;
							cout << "Enter ID: ";
							break;
						}
					}
					if (duplicate == false) {
						ID = id;
					}
				}
				cout << "Enter project description: ";
				cin.ignore();
				getline(cin, pd);
				Project* proj = new Project(ID, pd);
				projectArr[projectCount] = proj;
				projectCount++;
			}
			else cout << "Project objects have reached its maximum count" << endl << endl;

		}
		if (option == 4) {
			if (departmentCount > 0) {
				int id;
				cout << "Enter the department ID you want to display for: ";
				cin >> id;
				cout << endl;
				int check = 0;
				for (int i = 0; i < departmentCount; i++) {
					if (departmentArr[i]->getid() == id) {
						departmentArr[i]->displayDeptInfo();
						check = 1;
					}
				}
				if (check == 0) {
					cout << "This ID doesn't exist." << endl << endl;
				}
			}
			else cout << "No department exists." << endl << endl;
		}
		if (option == 5) {
			if (employeeCount > 0) {
				int id;
				cout << "Enter the employee ID you want to display for: ";
				cin >> id;
				cout << endl;
				int check = 0;
				for (int i = 0; i < employeeCount; i++) {
					if (employeeArr[i]->getId() == id) {
						employeeArr[i]->displayEmployeeInfo();
						check = 1;
					}
				}
				if (check == 0) {
					cout << "This ID doesn't exist." << endl << endl;
				}
			}
			else cout << "No employee exists." << endl << endl;
		}
		if (option == 6) {
			if (projectCount > 0) {
				int id;
				cout << "Enter the project ID you want to display for: ";
				cin >> id;
				cout << endl;
				int check = 0;
				for (int i = 0; i < projectCount; i++) {
					if (projectArr[i]->getId() == id) {
						projectArr[i]->displayProjectInfo();
						check = 1;
					}
				}
				if (check == 0) {
					cout << "This ID doesn't exist." << endl << endl;
				}
			}
			else cout << "No project exists." << endl << endl;
		}
		if (option == 7) {
			if ((employeeCount > 0) && (departmentCount > 0)) {
				int id1, id2;
				bool check = false;
				cout << "Enter the id of employee you want to add: ";
				cin >> id1;
				cout << "Enter the id of department you want to add to: ";
				cin >> id2;
				int n = 0;
				for (int i = 0; i < employeeCount; i++) {
					if (employeeArr[i]->getId() == id1) {
						n = i;
						check = true;
						break;
					}
				}
				for (int i = 0; i < departmentCount; i++) {
					if ((departmentArr[i]->getid() == id2) && (check == true)) {
						if (employeeArr[i]->GetAssignedToDept() == true) {
							for (int j = 0; j < departmentCount; j++) {
								if (employeeArr[i]->getDepartment() == departmentArr[j]) {
									departmentArr[j]->RemoveEmployee(employeeArr[i]->getId());
								}
							}
						}
						if (departmentArr[i]->AddEmployee(employeeArr[n]) == false) {
							cout << "Cannot add employee. Either employee already exists or maximum employee limit reached" << endl << endl;
						}
						else cout << "Employee added to the department." << endl << endl;
					}
				}
				if (check == false) {
					cout << "Employee does not exist." << endl;
				}
			}
			else cout << "No object of employee or department." << endl << endl;
		}
		if (option == 8) {
			if ((projectCount > 0) && (employeeCount > 0)) {
				int id1, id2;
				bool check = false;
				cout << "Enter the id of project you want to add: ";
				cin >> id1;
				cout << "Enter the id of employee you want to add to: ";
				cin >> id2;
				int n = 0;
				for (int i = 0; i < projectCount; i++) {
					if (projectArr[i]->getId() == id1) {
						n = i;
						check = true;
						break;
					}
				}
				for (int i = 0; i < employeeCount; i++) {
					if ((employeeArr[i]->getId() == id2) && (check == true)) {
						if (employeeArr[i]->AddProject(projectArr[n]) == false) {
							cout << "Cannot add project. Either project already exists or maximum project limit reached" << endl << endl;
						}
						else  cout << "Project added to the department." << endl << endl;
					}
				}
				if (check == false) {
					cout << "Project ID doesn't exist." << endl;
				}
			}
			else cout << "No object of Employee or Project." << endl << endl;
		}
		if (option == 9) {
			if (employeeCount > 0) {
				int id;
				bool check = false;
				cout << "Enter the employee ID you want to display all projects for: ";
				cin >> id;
				for (int i = 0; i < employeeCount; i++) {
					if (employeeArr[i]->getId() == id) {
						employeeArr[i]->displayAllProjects();
						check = true;
						break;
					}
				}
				if (check = false) {
					cout << "Employee Id not found!" << endl;
				}
			}
			else cout << "No employee exists." << endl << endl;
		}
		if (option == 10) {
			if (departmentCount > 0) {
				int id;
				bool check = false;
				cout << "Enter the department ID you want to display all employees for: ";
				cin >> id;
				for (int i = 0; i < departmentCount; i++) {
					if (departmentArr[i]->getid() == id) {
						departmentArr[i]->DisplayAllEmployees();
						check = true;
						break;
					}
				}
				if (check = false) {
					cout << "Department Id not found!" << endl;
				}
			}
			else cout << "No department exists." << endl << endl;
		}
		if (option == 11) {
			if ((employeeCount > 0) && (departmentCount > 0)) {
				int id1, id2;
				bool check = false;
				cout << "Enter the id of employee you want to remove: ";
				cin >> id1;
				cout << "Enter the id of department you want to remove from: ";
				cin >> id2;
				for (int i = 0; i < departmentCount; i++) {
					if ((departmentArr[i]->getid() == id2) && (departmentArr[i]->RemoveEmployee(id1) == true)) {
						check = true;
						departmentArr[i]->RemoveEmployee(id1);
						break;
					}
				}
				if (check == false) {
					cout << "Employee doesn't exist." << endl;
				}
			}
			else cout << "No object of employee or department." << endl << endl;
		}
		if (option == 12) {
			if ((employeeCount > 0) && (projectCount > 0)) {
				int id1, id2;
				bool check = false;
				cout << "Enter the id of project you want to remove: ";
				cin >> id1;
				cout << "Enter the id of employee you want to remove from: ";
				cin >> id2;
				for (int i = 0; i < employeeCount; i++) {
					if ((employeeArr[i]->getId() == id2) && (employeeArr[i]->RemoveProject(id1) == true)) {
						check = true;
						employeeArr[i]->RemoveProject(id1);
						break;
					}
				}
				if (check == false) {
					cout << "Employee doesn't exist." << endl;
				}
			}
			else cout << "No object of employee or project." << endl << endl;
		}
		if (option == 13) {
			if (projectCount > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter the project ID you want to display all employees for: ";
				cin >> id;
				for (int i = 0; i < projectCount; i++) {
					if (projectArr[i]->getId() == id) {
						projectArr[i]->DisplayAllEmployees();
						check = true;
						break;
					}
				}
				if (check = false) {
					cout << "Project Id not found!" << endl;
				}
			}
			else cout << "No project exists." << endl << endl;
		}
		if (option == 14) {
			if (employeeCount > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter the employee ID you want to display the department for: ";
				cin >> id;
				for (int i = 0; i < employeeCount; i++) {
					if (employeeArr[i]->getId() == id) {
						employeeArr[i]->displayDept();
						check = true;
						break;
					}
				}
				if (check = false) {
					cout << "employee Id not found!" << endl;
				}
			}
			else cout << "No employee exists." << endl << endl;
		}
	}
	return 0;
}
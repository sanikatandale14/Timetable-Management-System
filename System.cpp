/* 
             Micro Project Report 
Project Group ID:MPRJ_CPP_SY_A_02 
Project Title: TIMETABLE SCHEDULING SYSTEM 
_______________________________________________________________________  
Student Name:           1.Tandale Sanika Appaso [2002] 
With Roll Number  2.DesaiPratiksha Sanjay [2007] 
                                 3. Kazi Wasif Mamshadali [2014] 
_______________________________________________________________________  
Supervisor Name:  Dr. Amol Dange 
Institution Name:  Annasaheb Dange College of Engineering and Technology, Ashta. 
Submission Date:  November 30, 2024. 
*/ 
#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <stdexcept> 
#include<limits> 
 
using namespace std; 
 
class Course { 
public: 
    char name[30]; 
    char teacher[30]; 
    char classroom[30]; 
 
    Course() { 
        strcpy(name, ""); 
        strcpy(teacher, ""); 
        strcpy(classroom, ""); 
    } 
 
    void setCourse(const char* cname, const char* tname, const char* room) { 
        strcpy(name, cname); 
        strcpy(teacher, tname); 
        strcpy(classroom, room); 
    } 
}; 
class Timetable { 
private: 
    Course slots[5][8]; // 5 days (Monday to Friday) and 8 time slots each day from 9:15 to 4:30 
    int slotCount[5][8]; // Array to track whether a slot is filled 
public: 
    Timetable() { 
        for (int i = 0; i < 5; i++) { 
            for (int j = 0; j < 8; j++) { 
                slotCount[i][j] = 0; 
            } 
        } 
    } 
bool addCourse(int day, int slot, const char* cname, const char* tname, const char* room) { 
        try { 
            if (slot == 2 || slot == 4) { 
                throw invalid_argument("Cannot add courses during break or lunch."); 
            } 
         if (day < 0 || day >= 5 || slot < 0 || slot >= 8) { 
                throw out_of_range("Invalid day or slot index."); 
            } 
        if (slotCount[day][slot] == 0) { 
                if (strcmp(slots[day][slot].teacher, tname) == 0) { 
                    throw logic_error("Conflict: This teacher is already scheduled at this time."); 
                } 
                if (strcmp(slots[day][slot].classroom, room) == 0) { 
                    throw logic_error("Conflict: This classroom is already scheduled at this time."); 
                } 
      slots[day][slot].setCourse(cname, tname, room); 
                slotCount[day][slot] = 1; 
                cout << "Course added successfully.\n"; 
                return true; 
            } else { 
                throw runtime_error("Slot is already filled. Please choose another time."); 
            } 
        } catch (const exception& e) { 
            cout << "Error: " << e.what() << "\n"; 
            return false; 
        } 
    } 
 
    void displayTimetable() const { 
     try{
        cout << "\n-----------------------------------CLASS SCHEDULE-------------------------------------------------\n";
        cout << "______________________________________________________________________________\n";
        cout << "Time\t   |\tMonday\t    |\tTuesday\t     |\tWednesday     |\tThursday       |\tFriday   |\t\n";
        cout << "______________________________________________________________________________\n";
        const char* timeSlots[] = {
            "09:15-10:15",
            "10:15-11:15",
            "11:15-11:30 (Break)",
            "11:30-12:30",
            "12:30-1:30 (Lunch)",
            "1:30-2:30",
            "2:30-3:30",
            "3:30-4:30"
        };
        for (int i = 0; i < 8; i++) {
            cout << timeSlots[i] << "           | ";
            for (int j = 0; j < 5; j++) {
                if (slotCount[j][i] == 1) {
                    cout << slots[j][i].name << " (" << slots[j][i].teacher << ", " << slots[j][i].classroom << ")| ";
                } else {
                    cout << "  | ";
                }
            }
            cout << endl;
            cout << "______________________________________________________________________________\n";
        }
        cout << "______________________________________________________________________________\n";
    } catch (const exception& e) { 
            cout << "Error displaying timetable: " << e.what() << "\n"; 
        } 
    } 
  void saveToFile(const char* filename) const { 
        try { 
            ofstream file(filename); 
            if (!file) { 
                throw runtime_error("Unable to open file for saving."); 
            } 
 
            const char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}; 
            const char* timeSlots[] = { 
                "9:15-10:15", "10:15-11:15", "11:15-11:30 (Break)", "11:30-12:30", 
                "12:30-1:30 (Lunch)", "1:30-2:30", "2:30-3:30", "3:30-4:30" 
            }; 
         for (int i = 0; i < 8; i++) { 
                file << timeSlots[i] << "\n"; 
                for (int j = 0; j < 5; j++) { 
                    if (slotCount[j][i] == 1) { 
                        file << days[j] << ": " 
                             << slots[j][i].name << " (" << slots[j][i].teacher << ", " << slots[j][i].classroom << ")\n"; 
                    } 
                } 
                file << "\n"; 
            } 
            file.close(); 
            cout << "Timetable saved to " << filename << " successfully.\n"; 
        } catch (const exception& e) { 
            cout << "Error: " << e.what() << "\n"; 
        } 
    } 
  void loadFromFile(const char* filename) { 
        try { 
            ifstream file(filename); 
            if (!file) { 
                throw runtime_error("Unable to open file for loading."); 
            } 
 
            char line[256]; 
            while (file.getline(line, 256)) { 
                cout << line << "\n"; 
            } 
            file.close(); 
            cout << "Timetable loaded from " << filename << " successfully.\n"; 
        } catch (const exception& e) { 
            cout << "Error: " << e.what() << "\n"; 
        } 
    } 
}; 
 
void inputCourseData(Timetable& timetable) { 
    int day, slot; 
    char courseName[30], teacherName[30], classroomName[30]; 
 
    try { 
        cout << "\nEnter the day (0=Monday, 1=Tuesday, 2=Wednesday, 3=Thursday, 4=Friday): "; 
        cin >> day; 
        if (cin.fail() || day < 0 || day >= 5) { 
            throw invalid_argument("Invalid day entered."); 
         
}  cout << "Enter the time slot (0=9:15-10:15, 1=10:15-11:15, ..., 7=3:30-4:30): "; 
        cin >> slot; 
        if (cin.fail() || slot < 0 || slot >= 8) { 
            throw invalid_argument("Invalid time slot entered."); 
        } 
       cout << "Enter course name: "; 
        cin.ignore(); 
        cin.getline(courseName, 30); 
        cout << "Enter teacher name: "; 
        cin.getline(teacherName, 30); 
        cout << "Enter classroom name: "; 
        cin.getline(classroomName, 30); 
 if (!timetable.addCourse(day, slot, courseName, teacherName, classroomName)) { 
            cout << "Error: Could not add course. Try a different slot.\n"; 
        } 
    } catch (const exception& e) { 
        cout << "Error: " << e.what() << "\n"; 
    } 
} 
 
void showMenu() { 
    cout << "\n----- Timetable Management System -----\n"; 
    cout << "1. Load timetable from file\n"; 
    cout << "2. Add a course\n"; 
    cout << "3. Display the timetable\n"; 
    cout << "4. Save timetable to file\n"; 
    cout << "5. Exit\n"; 
    cout << "Choose an option: "; 
} 
 
int main() { 
    const int NUM_YEARS = 4; 
    const char years[NUM_YEARS][30] = {"FY", "SY", "TY", "BTech"}; 
 
    Timetable mechanicalTimetables[NUM_YEARS]; 
    Timetable cseTimetables[NUM_YEARS]; 
    Timetable electricalTimetables[NUM_YEARS]; 
    Timetable aidsTimetables[NUM_YEARS]; 
    Timetable aeronauticalTimetables[NUM_YEARS]; 
    Timetable iotTimetables[NUM_YEARS]; 
    Timetable foodTechTimetables[NUM_YEARS]; 
 
    int choice; 
    char year[30]; 
    char filename[50]; 
    int yearIndex = -1; 
 
    while (true) { 
        try {
            int departmentChoice;
            cout << "\nChoose department:\n";
            cout << "1. Mechanical\n2. CSE\n3. Electrical\n4. AIDS\n5. Aeronautical\n6. IoT\n7. Food Technology\n";
            cout << "Choose an option: "; 
            if (!(cin >> departmentChoice)) { 
                throw invalid_argument("Invalid input! Please enter a number between 1 and 7."); 
            } 
 
            if (departmentChoice < 1 || departmentChoice > 7) { 
                throw out_of_range("Invalid department choice! Please enter a number between 1 and 7."); 
            } 
 
            cout << "Enter year (e.g., FY, SY, TY, BTech): "; 
            cin >> year; 
 
            yearIndex = -1; 
            for (int j =0; j < NUM_YEARS; j++) { 
                if (strcmp(years[j], year) == 0) { 
                    yearIndex = j; 
                    break; 
                } 
            } 
 
            if (yearIndex == -1) { 
                throw invalid_argument("Invalid year! Please enter a valid year (FY, SY, TY, BTech)."); 
            } 
 
            Timetable* selectedTimetable; 
            switch (departmentChoice) { 
                case 1: selectedTimetable = &mechanicalTimetables[yearIndex]; break; 
                case 2: selectedTimetable = &cseTimetables[yearIndex]; break; 
                case 3: selectedTimetable = &electricalTimetables[yearIndex]; break; 
                case 4: selectedTimetable = &aidsTimetables[yearIndex]; break; 
                case 5: selectedTimetable = &aeronauticalTimetables[yearIndex]; break; 
                case 6: selectedTimetable = &iotTimetables[yearIndex]; break; 
                case 7: selectedTimetable = &foodTechTimetables[yearIndex]; break; 
                default: 
                    throw logic_error("Unexpected error in department selection."); 
            } 
 
            showMenu(); 
            if (!(cin >> choice)) { 
                cin.clear(); // Clear the error flag 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input 
                throw invalid_argument("Invalid input! Please enter a number between 1 and 5."); 
            } 
 
            switch (choice) { 
                case 1: 
                    cout << "Enter filename to load timetable: "; 
                    cin >> filename; 
                    selectedTimetable->loadFromFile(filename); 
                    break; 
 
                case 2: 
                    inputCourseData(*selectedTimetable); 
                    break; 
 
                case 3: 
                    selectedTimetable->displayTimetable(); 
                    break; 
 
                case 4: 
                    cout << "Enter filename to save timetable: "; 
                    cin >> filename; 
                    selectedTimetable->saveToFile(filename); 
                    break; 
 
                case 5: 
                    cout << "Exiting program. Goodbye!\n"; 
                    return 0; 
 
                default: 
                    throw out_of_range("Invalid option! Please enter a number between 1 and 5."); 
            } 
        } catch (const invalid_argument& e) { 
            cout << "Error: " << e.what() << " Try again.\n"; 
            cin.clear(); // Clear input stream in case of invalid input 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } catch (const out_of_range& e) { 
            cout << "Error: " << e.what() << " Try again.\n"; 
        } catch (const logic_error& e) { 
            cout << "Logic Error: " << e.what() << " Try again.\n"; 
        } 
    } 
return 0; 
} 
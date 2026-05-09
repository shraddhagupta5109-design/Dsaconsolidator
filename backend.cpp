#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>  // For std::sort (DSA sorting demonstration)

using namespace std;

// ================= STRUCTURE =================
struct Attendee {
    string name;
    string email;
};

// ================= DUPLICATE CHECK (Linear Search - O(n)) =================
bool isDuplicate(vector<Attendee> &attendees, string email) {
    for (int i = 0; i < attendees.size(); i++) {
        if (attendees[i].email == email) {
            return true;
        }
    }
    return false;
}

// ================= ADD ATTENDEE =================
void addAttendee(vector<Attendee> &attendees) {
    Attendee a;

    cin.ignore();  // Clear newline from previous input
    cout << "\nEnter Name: ";
    getline(cin, a.name);

    cout << "Enter Email: ";
    getline(cin, a.email);

    if (isDuplicate(attendees, a.email)) {
        cout << "Duplicate email! Entry not added.\n";
    } else {
        attendees.push_back(a);
        cout << "Attendee added successfully!\n";
    }
}

// ================= DISPLAY ATTENDEES =================
void displayAttendees(vector<Attendee> &attendees) {
    if (attendees.empty()) {
        cout << "\nNo attendees available.\n";
        return;
    }

    cout << "\n========== ATTENDEE LIST (" << attendees.size() << " total) ==========\n";
    for (int i = 0; i < attendees.size(); i++) {
        cout << i + 1 << ". "
             << attendees[i].name << " | "
             << attendees[i].email << endl;
    }
}

// ================= DELETE ATTENDEE =================
void deleteAttendee(vector<Attendee> &attendees) {
    if (attendees.empty()) {
        cout << "\nNo attendees to delete.\n";
        return;
    }

    displayAttendees(attendees);

    int index;
    cout << "\nEnter attendee number to delete: ";
    cin >> index;

    if (index < 1 || index > attendees.size()) {
        cout << "Invalid index!\n";
        return;
    }

    attendees.erase(attendees.begin() + (index - 1));
    cout << "Attendee deleted successfully!\n";
}

// ================= SEARCH ATTENDEE (Linear Search) =================
void searchAttendee(vector<Attendee> &attendees) {
    if (attendees.empty()) {
        cout << "\nNo attendees available.\n";
        return;
    }

    cin.ignore();
    string email;
    cout << "\nEnter email to search: ";
    getline(cin, email);

    for (int i = 0; i < attendees.size(); i++) {
        if (attendees[i].email == email) {
            cout << "\nFound Attendee:\n";
            cout << attendees[i].name << " | "
                 << attendees[i].email << endl;
            return;
        }
    }

    cout << "Attendee not found.\n";
}

// ================= UPDATE ATTENDEE =================
void updateAttendee(vector<Attendee> &attendees) {
    if (attendees.empty()) {
        cout << "\nNo attendees available.\n";
        return;
    }

    displayAttendees(attendees);

    int index;
    cout << "\nEnter attendee number to update: ";
    cin >> index;

    if (index < 1 || index > attendees.size()) {
        cout << "Invalid index!\n";
        return;
    }

    cin.ignore();
    string newName, newEmail;

    cout << "Enter new name: ";
    getline(cin, newName);

    cout << "Enter new email: ";
    getline(cin, newEmail);

    if (isDuplicate(attendees, newEmail) && attendees[index - 1].email != newEmail) {
        cout << "Duplicate email! Update cancelled.\n";
        return;
    }

    attendees[index - 1].name = newName;
    attendees[index - 1].email = newEmail;

    cout << "Attendee updated successfully!\n";
}

// ================= SORT ATTENDEES (DSA: Sorting with std::sort) =================
void sortAttendees(vector<Attendee> &attendees) {
    if (attendees.empty()) {
        cout << "\nNo attendees to sort.\n";
        return;
    }

    // Sort by name (alphabetical) - demonstrates efficient sorting on vector
    sort(attendees.begin(), attendees.end(), [](const Attendee& a, const Attendee& b) {
        return a.name < b.name;
    });

    cout << "Attendees sorted by name successfully!\n";
}

// ================= CONSOLIDATE FROM ANOTHER FILE (DSA: Merge + Duplicate Removal) =================
void consolidateFromFile(vector<Attendee> &attendees) {
    string filename;
    cout << "\nEnter filename to consolidate from (e.g. another_attendees.txt): ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found or unable to open!\n";
        return;
    }

    string name, email;
    int added = 0;

    while (getline(file, name, ',') && getline(file, email)) {
        if (!isDuplicate(attendees, email)) {
            attendees.push_back({name, email});
            added++;
        }
    }

    file.close();
    cout << added << " new attendee(s) consolidated successfully from " << filename << "!\n";
}

// ================= SAVE TO FILE =================
void saveToFile(vector<Attendee> &attendees) {
    ofstream file("attendees.txt");

    for (int i = 0; i < attendees.size(); i++) {
        file << attendees[i].name << "," << attendees[i].email << endl;
    }

    file.close();
    cout << "Data saved successfully to attendees.txt!\n";
}

// ================= LOAD FROM FILE =================
void loadFromFile(vector<Attendee> &attendees) {
    ifstream file("attendees.txt");
    if (!file.is_open()) return;

    string name, email;
    while (getline(file, name, ',') && getline(file, email)) {
        attendees.push_back({name, email});
    }

    file.close();
}

// ================= MAIN FUNCTION =================
int main() {
    vector<Attendee> attendees;
    int choice;

    // Load previous data (persistence)
    loadFromFile(attendees);

    cout << "====================================\n";
    cout << "   EVENT ATTENDEE CONSOLIDATOR\n";
    cout << "   (DSA Project - Vector + Sort + Merge)\n";
    cout << "====================================\n";

    do {
        cout << "\n1. Add Attendee\n";
        cout << "2. Display Attendees\n";
        cout << "3. Delete Attendee\n";
        cout << "4. Search Attendee\n";
        cout << "5. Update Attendee\n";
        cout << "6. Sort Attendees (by Name)\n";
        cout << "7. Consolidate from Another File\n";
        cout << "8. Save to File\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addAttendee(attendees);
                break;
            case 2:
                displayAttendees(attendees);
                break;
            case 3:
                deleteAttendee(attendees);
                break;
            case 4:
                searchAttendee(attendees);
                break;
            case 5:
                updateAttendee(attendees);
                break;
            case 6:
                sortAttendees(attendees);
                break;
            case 7:
                consolidateFromFile(attendees);
                break;
            case 8:
                saveToFile(attendees);
                break;
            case 9:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 9);

    // Auto-save prompt on exit (improved user experience)
    cout << "\nDo you want to save changes to file before exiting? (y/n): ";
    char saveOpt;
    cin >> saveOpt;
    if (saveOpt == 'y' || saveOpt == 'Y') {
        saveToFile(attendees);
    }

    cout << "Thank you for using Event Attendee Consolidator!\n";
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // for stringstream

using namespace std;

// Doctor class representing a doctor
class Doctor {
public:
    string name;
    string specialization;
    int id;

    Doctor(string name, string specialization, int id)
        : name(name), specialization(specialization), id(id) {}

    // Save doctor to file (opened in append mode)
    void saveToFile() {
        ofstream file("doctors.txt", ios::app);
        if (file.is_open()) {
            file << id << " " << name << " " << specialization << endl;
            file.close();
        }
        else {
            cout << "Unable to open file for saving doctor.\n";
        }
    }

    // Delete doctor from file
    static void deleteFromFile(int id) {
        ifstream file("doctors.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            int fileId;
            string name, specialization;
            stringstream ss(line);
            ss >> fileId; // Read the ID
            getline(ss, name, ' '); // Read name
            getline(ss, specialization); // Read specialization
            if (fileId != id) {
                tempFile << line << endl; // If ID does not match, keep the line
            }
            else {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        remove("doctors.txt");
        rename("temp.txt", "doctors.txt");

        if (found) {
            cout << "Doctor deleted successfully.\n";
        }
        else {
            cout << "Doctor not found.\n";
        }
    }

    // Display all doctors from file
    static void displayDoctors() {
        ifstream file("doctors.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cout << "No doctors available.\n";
        }
    }

    // Get doctor by name (returns true if doctor is found)
    static bool getDoctorByName(const string& name, Doctor& doctor) {
        ifstream file("doctors.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string docName, specialization;
            ss >> id;
            ss.ignore();  // To ignore the space between ID and the name
            getline(ss, docName, ' '); // Read name
            getline(ss, specialization); // Read specialization
            if (docName == name) {
                doctor = Doctor(docName, specialization, id);
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
};

// Appointment class representing a patient's appointment
class Patient {
public:
    string name;
    int id;
    string medicalHistory;
    string doctorName;

    Patient(string name, int id, string medicalHistory, string doctorName)
        : name(name), id(id), medicalHistory(medicalHistory), doctorName(doctorName) {}

    // Save patient appointment to file (opened in append mode)
    void saveToFile() {
        ofstream file("appointments.txt", ios::app);
        if (file.is_open()) {
            file << id << " " << name << " " << medicalHistory << " " << doctorName << endl;
            file.close();
        }
        else {
            cout << "Unable to open file for saving appointment.\n";
        }
    }

    // Delete appointment from file
    static void deleteFromFile(int id) {
        ifstream file("appointments.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            int fileId;
            string name, medicalHistory, doctorName;
            stringstream ss(line);
            ss >> fileId; // Read the ID
            getline(ss, name, ' '); // Read name
            getline(ss, medicalHistory, ' '); // Read medical history
            getline(ss, doctorName); // Read doctor name
            if (fileId != id) {
                tempFile << line << endl; // If ID does not match, keep the line
            }
            else {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        remove("appointments.txt");
        rename("temp.txt", "appointments.txt");

        if (found) {
            cout << "Appointment deleted successfully.\n";
        }
        else {
            cout << "Appointment not found.\n";
        }
    }


    static void displayAppointmentsForDoctor(const string& doctorName) {
        ifstream file("appointments.txt");
        string line;
        bool found = false;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                int id;
                string name, medicalHistory, doctorNameInFile;

                // Parse the appointment details
                ss >> id;                        // Read the patient ID
                ss >> name;                      // Read the patient name
                ss >> medicalHistory;            // Read the medical history
                ss >> ws;                        // Consume any leading whitespace
                getline(ss, doctorNameInFile);   // Read the doctor name


                // Trim any extra spaces from the doctor names
                doctorNameInFile = trim(doctorNameInFile);
                string trimmedInputName = trim(doctorName);

                // Check if the doctor's name matches
                if (doctorNameInFile == trimmedInputName) {
                    cout << "Appointment Found: \nID: " << id << ", Patient: " << name
                        << ", Medical History: " << medicalHistory << ", Doctor: " << doctorNameInFile << endl;
                    found = true;
                }
            }
            file.close();

            if (!found) {
                cout << "No appointments found for doctor: " << doctorName << endl;
            }
        }
        else {
            cout << "Error: Could not open appointments file.\n";
        }
    }

    // Helper function to trim whitespace from strings
    static string trim(const string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");

        if (start == string::npos || end == string::npos) {
            return "";
        }

        return str.substr(start, end - start + 1);
    }

    // Display all appointments
    static void displayAppointments() {
        ifstream file("appointments.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cout << "No appointments available.\n";
        }
    }
};

// Emergency case management
class EmergencyCaseList {
public:
    // Add an emergency case (saved to a file)
    static void addEmergencyCase(string name, int id, string medicalHistory) {
        ofstream file("emergency_cases.txt", ios::app);
        if (file.is_open()) {
            file << id << " " << name << " " << medicalHistory << endl;
            file.close();
            cout << "Emergency case added for patient: " << name << endl;
        }
        else {
            cout << "Unable to open file for saving emergency case.\n";
        }
    }

    // Delete emergency case from file
    static void deleteEmergencyCase(int id) {
        ifstream file("emergency_cases.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            int fileId;
            string name, medicalHistory;
            stringstream ss(line);
            ss >> fileId; // Read the ID
            getline(ss, name, ' '); // Read name
            getline(ss, medicalHistory); // Read medical history
            if (fileId != id) {
                tempFile << line << endl; // If ID does not match, keep the line
            }
            else {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        remove("emergency_cases.txt");
        rename("temp.txt", "emergency_cases.txt");

        if (found) {
            cout << "Emergency case deleted successfully.\n";
        }
        else {
            cout << "Emergency case not found.\n";
        }
    }

    // Display all emergency cases from file
    static void displayEmergencyCases() {
        ifstream file("emergency_cases.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cout << "No emergency cases available.\n";
        }
    }
};

// Function to display the main menu
void displayMenu() {
    cout << "\n--- Hospital Management System ---\n";
    cout << "1. Add Doctor\n2. Delete Doctor\n3. Display Doctor\n";
    cout << "4. Add Appointment\n5. Delete Appointment\n6. Display Appointment\n";
    cout << "7. Add Emergency Case\n8. Delete Emergency Case\n9. Display Emergency Cases\n";
    cout << "10. Display Appointments for a Doctor\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Doctor doctor("", "", 0);
    Patient patient("", 0, "", "");
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, specialization;
            int id;
            cout << "Enter doctor name: ";
            cin >> name;
            cout << "Enter specialization: ";
            cin.ignore();  // To clear the newline character
            getline(cin, specialization);
            cout << "Enter doctor ID: ";
            cin >> id;
            doctor = Doctor(name, specialization, id);
            doctor.saveToFile();
            break;
        }
        case 2: {
            int id;
            cout << "Enter doctor ID to delete: ";
            cin >> id;
            Doctor::deleteFromFile(id);
            break;
        }
        case 3:
            Doctor::displayDoctors();
            break;
        case 4: {
            string name, medicalHistory, doctorName;
            int id;
            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter patient ID: ";
            cin >> id;
            cout << "Enter medical history: ";
            cin.ignore();  // Clear buffer
            getline(cin, medicalHistory);
            cout << "Enter doctor name for appointment: ";
            getline(cin, doctorName);

            // Check if the doctor exists
            if (Doctor::getDoctorByName(doctorName, doctor)) {
                patient = Patient(name, id, medicalHistory, doctorName);
                patient.saveToFile();
            }
            else {
                cout << "Doctor not found.\n";
            }
            break;
        }
        case 5: {
            int id;
            cout << "Enter appointment ID to delete: ";
            cin >> id;
            Patient::deleteFromFile(id);
            break;
        }
        case 6:
            Patient::displayAppointments();
            break;
        case 7: {
            string name, medicalHistory;
            int id;
            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter patient ID: ";
            cin >> id;
            cout << "Enter medical history: ";
            cin.ignore();
            getline(cin, medicalHistory);
            EmergencyCaseList::addEmergencyCase(name, id, medicalHistory);
            break;
        }
        case 8: {
            int id;
            cout << "Enter emergency case ID to delete: ";
            cin >> id;
            EmergencyCaseList::deleteEmergencyCase(id);
            break;
        }
        case 9:
            EmergencyCaseList::displayEmergencyCases();
            break;
        case 10: {
            string doctorName;
            cout << "Enter doctor name to display appointments: ";
            cin.ignore();
            getline(cin, doctorName);
            Patient::displayAppointmentsForDoctor(doctorName);
            break;
        }
        case 0:
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}

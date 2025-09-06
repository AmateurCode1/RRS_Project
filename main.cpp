#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Class to represent a Train
class Train {
public:
    int trainNo;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double fare;
    
    Train(int no, string name, string src, string dest, int seats, double price) {
        trainNo = no;
        trainName = name;
        source = src;
        destination = dest;
        totalSeats = seats;
        availableSeats = seats;
        fare = price;
    }
    
    void displayTrain() {
        cout << setw(8) << trainNo 
             << setw(20) << trainName 
             << setw(15) << source 
             << setw(15) << destination 
             << setw(12) << availableSeats 
             << setw(10) << fare << endl;
    }
};

// Class to represent a Passenger
class Passenger {
public:
    string name;
    int age;
    char gender;
    string contact;
    
    Passenger(string n, int a, char g, string c) {
        name = n;
        age = a;
        gender = g;
        contact = c;
    }
    
    void displayPassenger() {
        cout << "Name: " << name << ", Age: " << age 
             << ", Gender: " << gender << ", Contact: " << contact << endl;
    }
};

// Class to represent a Reservation
class Reservation {
public:
    int pnr;
    int trainNo;
    string trainName;
    string passengerName;
    string source;
    string destination;
    int numPassengers;
    vector<Passenger> passengers;
    double totalAmount;
    string status;
    
    Reservation() {
        pnr = 0;
        trainNo = 0;
        numPassengers = 0;
        totalAmount = 0.0;
        status = "Confirmed";
    }
};

// Main Railway Reservation System Class
class RailwayReservationSystem {
private:
    vector<Train> trains;
    vector<Reservation> reservations;
    int nextPNR;
    string adminUsername;
    string adminPassword;
    
public:
    RailwayReservationSystem() {
        nextPNR = 10001;
        adminUsername = "admin";
        adminPassword = "admin123";
        initializeTrains();
    }
    
    // Initialize some sample trains
    void initializeTrains() {
        trains.push_back(Train(12345, "Express Special", "Delhi", "Mumbai", 100, 1500.0));
        trains.push_back(Train(12346, "Rajdhani Express", "Delhi", "Kolkata", 80, 2000.0));
        trains.push_back(Train(12347, "Shatabdi Express", "Mumbai", "Bangalore", 120, 1200.0));
        trains.push_back(Train(12348, "Duronto Express", "Chennai", "Delhi", 90, 1800.0));
    }
    
    // Display all available trains
    void displayTrains() {
        cout << "\n========== AVAILABLE TRAINS ==========\n";
        cout << setw(8) << "Train No" 
             << setw(20) << "Train Name" 
             << setw(15) << "Source" 
             << setw(15) << "Destination" 
             << setw(12) << "Seats" 
             << setw(10) << "Fare" << endl;
        cout << string(80, '-') << endl;
        
        for (int i = 0; i < trains.size(); i++) {
            trains[i].displayTrain();
        }
        cout << string(80, '=') << endl;
    }
    
    // Search trains by source and destination
    void searchTrains(string src, string dest) {
        cout << "\n========== SEARCH RESULTS ==========\n";
        cout << setw(8) << "Train No" 
             << setw(20) << "Train Name" 
             << setw(15) << "Source" 
             << setw(15) << "Destination" 
             << setw(12) << "Seats" 
             << setw(10) << "Fare" << endl;
        cout << string(80, '-') << endl;
        
        bool found = false;
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].source == src && trains[i].destination == dest) {
                trains[i].displayTrain();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No trains found for the given route!\n";
        }
        cout << string(80, '=') << endl;
    }
    
    // Make a reservation
    void makeReservation() {
        int trainNo, numPass;
        cout << "\nEnter Train Number: ";
        cin >> trainNo;
        
        // Find the train
        int trainIndex = -1;
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].trainNo == trainNo) {
                trainIndex = i;
                break;
            }
        }
        
        if (trainIndex == -1) {
            cout << "Train not found!\n";
            return;
        }
        
        cout << "Enter number of passengers: ";
        cin >> numPass;
        
        if (trains[trainIndex].availableSeats < numPass) {
            cout << "Not enough seats available!\n";
            return;
        }
        
        Reservation newReservation;
        newReservation.pnr = nextPNR++;
        newReservation.trainNo = trainNo;
        newReservation.trainName = trains[trainIndex].trainName;
        newReservation.source = trains[trainIndex].source;
        newReservation.destination = trains[trainIndex].destination;
        newReservation.numPassengers = numPass;
        newReservation.totalAmount = numPass * trains[trainIndex].fare;
        
        cin.ignore(); // Clear input buffer
        
        // Get passenger details
        for (int i = 0; i < numPass; i++) {
            string name, contact;
            int age;
            char gender;
            
            cout << "\nEnter details for Passenger " << (i + 1) << ":\n";
            cout << "Name: ";
            getline(cin, name);
            cout << "Age: ";
            cin >> age;
            cout << "Gender (M/F): ";
            cin >> gender;
            cout << "Contact: ";
            cin >> contact;
            cin.ignore();
            
            newReservation.passengers.push_back(Passenger(name, age, gender, contact));
        }
        
        newReservation.passengerName = newReservation.passengers[0].name; // Primary passenger
        
        // Update available seats
        trains[trainIndex].availableSeats -= numPass;
        
        // Add reservation
        reservations.push_back(newReservation);
        
        cout << "\n========== RESERVATION SUCCESSFUL ==========\n";
        cout << "PNR Number: " << newReservation.pnr << endl;
        cout << "Total Amount: Rs. " << newReservation.totalAmount << endl;
        cout << "Status: " << newReservation.status << endl;
        cout << "==========================================\n";
    }
    
    // Check PNR status
    void checkPNRStatus() {
        int pnr;
        cout << "Enter PNR Number: ";
        cin >> pnr;
        
        for (int i = 0; i < reservations.size(); i++) {
            if (reservations[i].pnr == pnr) {
                cout << "\n========== PNR STATUS ==========\n";
                cout << "PNR: " << reservations[i].pnr << endl;
                cout << "Train: " << reservations[i].trainName << " (" << reservations[i].trainNo << ")" << endl;
                cout << "Route: " << reservations[i].source << " to " << reservations[i].destination << endl;
                cout << "Passengers: " << reservations[i].numPassengers << endl;
                cout << "Total Amount: Rs. " << reservations[i].totalAmount << endl;
                cout << "Status: " << reservations[i].status << endl;
                cout << "\nPassenger Details:\n";
                for (int j = 0; j < reservations[i].passengers.size(); j++) {
                    cout << (j + 1) << ". ";
                    reservations[i].passengers[j].displayPassenger();
                }
                cout << "==============================\n";
                return;
            }
        }
        
        cout << "PNR not found!\n";
    }
    
    // Cancel reservation
    void cancelReservation() {
        int pnr;
        cout << "Enter PNR Number to cancel: ";
        cin >> pnr;
        
        for (int i = 0; i < reservations.size(); i++) {
            if (reservations[i].pnr == pnr) {
                // Find the train and restore seats
                for (int j = 0; j < trains.size(); j++) {
                    if (trains[j].trainNo == reservations[i].trainNo) {
                        trains[j].availableSeats += reservations[i].numPassengers;
                        break;
                    }
                }
                
                reservations[i].status = "Cancelled";
                cout << "Reservation cancelled successfully!\n";
                cout << "Refund Amount: Rs. " << (reservations[i].totalAmount * 0.8) << " (20% cancellation charges)\n";
                return;
            }
        }
        
        cout << "PNR not found!\n";
    }
    
    // ADMIN FUNCTIONS START HERE
    
    // Admin authentication
    bool adminLogin() {
        string username, password;
        int attempts = 0;
        
        cout << "\n========== ADMIN LOGIN ==========\n";
        
        while (attempts < 3) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            
            if (username == adminUsername && password == adminPassword) {
                cout << "Login successful!\n";
                cout << "================================\n";
                return true;
            } else {
                attempts++;
                cout << "Invalid credentials! Attempts remaining: " << (3 - attempts) << endl;
            }
        }
        
        cout << "Maximum attempts reached. Access denied!\n";
        cout << "=======================================\n";
        return false;
    }
    
    // Add new train (Admin only)
    void addTrain() {
        int trainNo, seats;
        string trainName, source, destination;
        double fare;
        
        cout << "\n========== ADD NEW TRAIN ==========\n";
        cout << "Enter Train Number: ";
        cin >> trainNo;
        
        // Check if train number already exists
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].trainNo == trainNo) {
                cout << "Train number already exists!\n";
                return;
            }
        }
        
        cin.ignore(); // Clear input buffer
        cout << "Enter Train Name: ";
        getline(cin, trainName);
        cout << "Enter Source Station: ";
        getline(cin, source);
        cout << "Enter Destination Station: ";
        getline(cin, destination);
        cout << "Enter Total Seats: ";
        cin >> seats;
        cout << "Enter Fare (Rs.): ";
        cin >> fare;
        
        trains.push_back(Train(trainNo, trainName, source, destination, seats, fare));
        
        cout << "Train added successfully!\n";
        cout << "==================================\n";
    }
    
    // Modify existing train (Admin only)
    void modifyTrain() {
        int trainNo;
        cout << "\n========== MODIFY TRAIN ==========\n";
        cout << "Enter Train Number to modify: ";
        cin >> trainNo;
        
        int trainIndex = -1;
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].trainNo == trainNo) {
                trainIndex = i;
                break;
            }
        }
        
        if (trainIndex == -1) {
            cout << "Train not found!\n";
            return;
        }
        
        cout << "Current Train Details:\n";
        cout << "Train No: " << trains[trainIndex].trainNo << endl;
        cout << "Name: " << trains[trainIndex].trainName << endl;
        cout << "Source: " << trains[trainIndex].source << endl;
        cout << "Destination: " << trains[trainIndex].destination << endl;
        cout << "Total Seats: " << trains[trainIndex].totalSeats << endl;
        cout << "Available Seats: " << trains[trainIndex].availableSeats << endl;
        cout << "Fare: Rs. " << trains[trainIndex].fare << endl;
        
        cout << "\nWhat would you like to modify?\n";
        cout << "1. Train Name\n";
        cout << "2. Source Station\n";
        cout << "3. Destination Station\n";
        cout << "4. Total Seats\n";
        cout << "5. Fare\n";
        cout << "6. Cancel\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1: {
                string newName;
                cout << "Enter new train name: ";
                getline(cin, newName);
                trains[trainIndex].trainName = newName;
                cout << "Train name updated successfully!\n";
                break;
            }
            case 2: {
                string newSource;
                cout << "Enter new source station: ";
                getline(cin, newSource);
                trains[trainIndex].source = newSource;
                cout << "Source station updated successfully!\n";
                break;
            }
            case 3: {
                string newDest;
                cout << "Enter new destination station: ";
                getline(cin, newDest);
                trains[trainIndex].destination = newDest;
                cout << "Destination station updated successfully!\n";
                break;
            }
            case 4: {
                int newSeats;
                cout << "Enter new total seats: ";
                cin >> newSeats;
                int bookedSeats = trains[trainIndex].totalSeats - trains[trainIndex].availableSeats;
                if (newSeats < bookedSeats) {
                    cout << "Cannot reduce seats below booked seats (" << bookedSeats << ")!\n";
                } else {
                    trains[trainIndex].availableSeats = newSeats - bookedSeats;
                    trains[trainIndex].totalSeats = newSeats;
                    cout << "Total seats updated successfully!\n";
                }
                break;
            }
            case 5: {
                double newFare;
                cout << "Enter new fare: ";
                cin >> newFare;
                trains[trainIndex].fare = newFare;
                cout << "Fare updated successfully!\n";
                break;
            }
            case 6:
                cout << "Modification cancelled.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
        cout << "=================================\n";
    }
    
    // Delete train (Admin only)
    void deleteTrain() {
        int trainNo;
        cout << "\n========== DELETE TRAIN ==========\n";
        cout << "Enter Train Number to delete: ";
        cin >> trainNo;
        
        int trainIndex = -1;
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].trainNo == trainNo) {
                trainIndex = i;
                break;
            }
        }
        
        if (trainIndex == -1) {
            cout << "Train not found!\n";
            return;
        }
        
        // Check if train has active reservations
        bool hasReservations = false;
        for (int i = 0; i < reservations.size(); i++) {
            if (reservations[i].trainNo == trainNo && reservations[i].status == "Confirmed") {
                hasReservations = true;
                break;
            }
        }
        
        if (hasReservations) {
            cout << "Cannot delete train with active reservations!\n";
            cout << "Please cancel all reservations first.\n";
            return;
        }
        
        cout << "Train Details:\n";
        trains[trainIndex].displayTrain();
        
        char confirm;
        cout << "Are you sure you want to delete this train? (y/n): ";
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            trains.erase(trains.begin() + trainIndex);
            cout << "Train deleted successfully!\n";
        } else {
            cout << "Deletion cancelled.\n";
        }
        cout << "=================================\n";
    }
    
    // View all reservations (Admin only)
    void viewAllReservations() {
        cout << "\n========== ALL RESERVATIONS ==========\n";
        
        if (reservations.empty()) {
            cout << "No reservations found!\n";
            cout << "=====================================\n";
            return;
        }
        
        cout << setw(8) << "PNR" 
             << setw(12) << "Train No" 
             << setw(20) << "Passenger" 
             << setw(15) << "Route" 
             << setw(10) << "Seats" 
             << setw(12) << "Amount" 
             << setw(12) << "Status" << endl;
        cout << string(90, '-') << endl;
        
        for (int i = 0; i < reservations.size(); i++) {
            cout << setw(8) << reservations[i].pnr
                 << setw(12) << reservations[i].trainNo
                 << setw(20) << reservations[i].passengerName
                 << setw(15) << (reservations[i].source + "-" + reservations[i].destination)
                 << setw(10) << reservations[i].numPassengers
                 << setw(12) << reservations[i].totalAmount
                 << setw(12) << reservations[i].status << endl;
        }
        cout << "=====================================\n";
    }
    
    // Admin menu
    void showAdminMenu() {
        cout << "\n========== ADMIN PANEL ==========\n";
        cout << "1. Add New Train\n";
        cout << "2. Modify Train Details\n";
        cout << "3. Delete Train\n";
        cout << "4. View All Trains\n";
        cout << "5. View All Reservations\n";
        cout << "6. Back to Main Menu\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
    }
    
    // Admin panel main function
    void adminPanel() {
        if (!adminLogin()) {
            return;
        }
        
        int choice;
        do {
            showAdminMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    addTrain();
                    break;
                    
                case 2:
                    modifyTrain();
                    break;
                    
                case 3:
                    deleteTrain();
                    break;
                    
                case 4:
                    displayTrains();
                    break;
                    
                case 5:
                    viewAllReservations();
                    break;
                    
                case 6:
                    cout << "Returning to main menu...\n";
                    break;
                    
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
            
            if (choice != 6) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
            
        } while (choice != 6);
    }
    
    // ADMIN FUNCTIONS END HERE
    
    // Display main menu
    void showMenu() {
        cout << "\n========== RAILWAY RESERVATION SYSTEM ==========\n";
        cout << "1. Display All Trains\n";
        cout << "2. Search Trains\n";
        cout << "3. Make Reservation\n";
        cout << "4. Check PNR Status\n";
        cout << "5. Cancel Reservation\n";
        cout << "6. Admin Panel\n";
        cout << "7. Exit\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
    }
};

// Main function
int main() {
    RailwayReservationSystem rrs;
    int choice;
    string source, destination;
    
    cout << "Welcome to Railway Reservation System!\n";
    
    do {
        rrs.showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                rrs.displayTrains();
                break;
                
            case 2:
                cout << "Enter Source Station: ";
                cin >> source;
                cout << "Enter Destination Station: ";
                cin >> destination;
                rrs.searchTrains(source, destination);
                break;
                
            case 3:
                rrs.makeReservation();
                break;
                
            case 4:
                rrs.checkPNRStatus();
                break;
                
            case 5:
                rrs.cancelReservation();
                break;
                
            case 6:
                rrs.adminPanel();
                break;
                
            case 7:
                cout << "Thank you for using Railway Reservation System!\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        
        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 7);
    
    return 0;
}
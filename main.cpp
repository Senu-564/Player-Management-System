#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

// Define the Player struct 
struct Player {
    int registrationNumber;  
    string firstName;        
    string lastName;         
    string dateOfBirth;       
    int runsScored;         

    // Constructor to initialize a Player object
    Player(int regNum, const string& fName, const string& lName, const string& dob, int runs)
        : registrationNumber(regNum), firstName(fName), lastName(lName), dateOfBirth(dob), runsScored(runs) {}

    // Convert Player object to a string for file storage
    string toString() const {
        return to_string(registrationNumber) + "," + firstName + "," + lastName + "," + dateOfBirth + "," + to_string(runsScored);
    }

    // Create a Player object from a string
    static Player fromString(const string& str) {
        istringstream ss(str);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return Player(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4]));
    }
};

// Define the Team struct
struct Team {
    int teamId;        
    string teamName;  

    // Constructor to initialize a Team object
    Team(int id, const string& name) : teamId(id), teamName(name) {}

    // Convert Team object to a string for file storage
    string toString() const {
        return to_string(teamId) + "," + teamName;
    }

    // Create a Team object from a string
    static Team fromString(const string& str) {
        istringstream ss(str);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return Team(stoi(tokens[0]), tokens[1]);
    }
};

// Define the User class for handling user login
class User {
    string username;   
    string password;   
    bool loggedIn;     

public:
    User() : loggedIn(false) {}  // Constructor initializing loggedIn to false

    // Method to login a user
    bool login(const string& uname, const string& pwd) {
        if (uname == "admin" && pwd == "password") {  // Hardcoded username and password
            loggedIn = true;
            return true;
        }
        return false;
    }

    // Method to logout a user
    void logout() {
        loggedIn = false;
    }

    // Method to check if a user is logged in
    bool isLoggedIn() const {
        return loggedIn;
    }
};

vector<Player> players;  
vector<Team> teams;     
User currentUser;        

// Function to validate if a number is positive
bool isValidNumber(int num) {
    return num > 0;
}

// Function to validate if a string is non-empty
bool isValidString(const string& str) {
    return !str.empty();
}

// Function to validate the date format (YYYY-MM-DD)
bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

// Function to load players from a file
void loadPlayersFromFile() {
    ifstream infile("players.txt");
    string line;
    while (getline(infile, line)) {
        players.push_back(Player::fromString(line));
    }
}

// Function to save players to a file
void savePlayersToFile() {
    ofstream outfile("players.txt");
    for (const auto& player : players) {
        outfile << player.toString() << endl;
    }
}

// Function to load teams from a file
void loadTeamsFromFile() {
    ifstream infile("teams.txt");
    string line;
    while (getline(infile, line)) {
        teams.push_back(Team::fromString(line));
    }
}

// Function to save teams to a file
void saveTeamsToFile() {
    ofstream outfile("teams.txt");
    for (const auto& team : teams) {
        outfile << team.toString() << endl;
    }
}

// Function to display the list of players
void displayPlayers() {
    cout << "\nPlayer List:\n";
    for (const auto& player : players) {
        cout << "Reg#: " << player.registrationNumber
             << ", Name: " << player.firstName << " " << player.lastName
             << ", DOB: " << player.dateOfBirth
             << ", Runs: " << player.runsScored << "\n";
    }
}

// Function to add a new player
void addNewPlayer() {
    int regNum, runs;
    string fName, lName, dob;

    cout << "Enter registration number: ";
    while (!(cin >> regNum) || !isValidNumber(regNum)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid registration number. Please enter a valid positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character left by cin

    cout << "Enter first name: ";
    while (getline(cin, fName) && !isValidString(fName)) {
        cout << "Invalid first name. Please enter a non-empty name: ";
    }

    cout << "Enter last name: ";
    while (getline(cin, lName) && !isValidString(lName)) {
        cout << "Invalid last name. Please enter a non-empty name: ";
    }

    cout << "Enter date of birth (YYYY-MM-DD): ";
    while (getline(cin, dob) && !isValidDate(dob)) {
        cout << "Invalid date format. Please enter a date in YYYY-MM-DD format: ";
    }

    cout << "Enter runs scored: ";
    while (!(cin >> runs) || !isValidNumber(runs)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid runs scored. Please enter a valid positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    players.push_back(Player(regNum, fName, lName, dob, runs));
    savePlayersToFile(); // Save players to file after adding a new one
    cout << "Player added successfully!\n";
}

// Function to manage teams
void manageTeams() {
    int teamId;
    string teamName;

    cout << "Enter team ID: ";
    while (!(cin >> teamId) || !isValidNumber(teamId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid team ID. Please enter a valid positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter team name: ";
    while (getline(cin, teamName) && !isValidString(teamName)) {
        cout << "Invalid team name. Please enter a non-empty name: ";
    }

    teams.push_back(Team(teamId, teamName));
    saveTeamsToFile(); // Save teams to file after adding a new one
    cout << "Team created successfully!\n";
}

// Function to search for a player by registration number
void searchPlayer() {
    int regNum;
    cout << "Enter player registration number: ";
    while (!(cin >> regNum) || !isValidNumber(regNum)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid registration number. Please enter a valid positive number: ";
    }

    auto it = find_if(players.begin(), players.end(), [regNum](const Player& p) {
        return p.registrationNumber == regNum;
    });

    if (it != players.end()) {
        cout << "Player found: "
             << it->firstName << " " << it->lastName << ", DOB: " << it->dateOfBirth << ", Runs: " << it->runsScored << "\n";
    } else {
        cout << "Player not found.\n";
    }
}

// Function to view team details by team ID
void viewTeamDetails() {
    int teamId;
    cout << "Enter team ID: ";
    while (!(cin >> teamId) || !isValidNumber(teamId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid team ID. Please enter a valid positive number: ";
    }

    auto it = find_if(teams.begin(), teams.end(), [teamId](const Team& t) {
        return t.teamId == teamId;
    });

    if (it != teams.end()) {
        cout << "Team: " << it->teamName << "\n";
    } else {
        cout << "Team not found.\n";
    }
}

// Function to display the main menu and handle user input
void mainMenu() {
    int choice;
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Display Players\n";
        cout << "2. Add New Player\n";
        cout << "3. Manage Teams\n";
        cout << "4. Search Player\n";
        cout << "5. View Team Details\n";
        cout << "6. Logout\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 7: ";
        }

        switch (choice) {
            case 1:
                displayPlayers();
                break;
            case 2:
                addNewPlayer();
                break;
            case 3:
                manageTeams();
                break;
            case 4:
                searchPlayer();
                break;
            case 5:
                viewTeamDetails();
                break;
            case 6:
                currentUser.logout();
                cout << "Logged out successfully.\n";
                return;  // Return to exit the menu loop after logout
            case 7:
                cout << "Exiting...\n";
                return;
        }
    } while (true);
}

// Function to handle user login
void login() {
    string username, password;

    cout << "\nWelcome to Upcountry Warriors Management System\n";
    cout << "Please login to continue.\n";

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (currentUser.login(username, password)) {
        cout << "Login successful!\n";
        mainMenu();
    } else {
        cout << "Login failed. Please try again.\n";
        login();  
    }
}

// Main function to load data and start the login process
int main() {
    loadPlayersFromFile(); // Load players from file
    loadTeamsFromFile();   // Load teams from file
    login();               // Start login process
    return 0;
}


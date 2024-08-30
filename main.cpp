#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm> 


using namespace std;

// User Class
class User {
public:
    string username;
    string password;
    string role;

    User(const string& uname, const string& pwd, const string& r)
        : username(uname), password(pwd), role(r) {}

    string toString() const {
        return username + "," + password + "," + role;
    }

    static User fromString(const string& str) {
        stringstream ss(str);
        string username, password, role;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        return User(username, password, role);
    }
};

// Train Class
class Train {
public:
    int id;
    string name;
    string source;
    string destination;
    int seats;

    Train(int id, const string& name, const string& source, const string& destination, int seats)
        : id(id), name(name), source(source), destination(destination), seats(seats) {}

    string toString() const {
        return to_string(id) + "," + name + "," + source + "," + destination + "," + to_string(seats);
    }

    static Train fromString(const string& str) {
        stringstream ss(str);
        string id, name, source, destination, seats;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, source, ',');
        getline(ss, destination, ',');
        getline(ss, seats, ',');
        return Train(stoi(id), name, source, destination, stoi(seats));
    }
};

// Route Class
class Route {
public:
    int id;
    string source;
    string destination;

    Route(int id, const string& source, const string& destination)
        : id(id), source(source), destination(destination) {}

    string toString() const {
        return to_string(id) + "," + source + "," + destination;
    }

    static Route fromString(const string& str) {
        stringstream ss(str);
        string id, source, destination;
        getline(ss, id, ',');
        getline(ss, source, ',');
        getline(ss, destination, ',');
        return Route(stoi(id), source, destination);
    }
};

// Node for Linked List
template<typename T>
struct ListNode {
    T data;
    ListNode* next;

    ListNode(const T& value) : data(value), next(nullptr) {}
};

// Linked List Class
template<typename T>
class LinkedList {
private:
    ListNode<T>* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void append(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        if (!head) {
            head = newNode;
        }
        else {
            ListNode<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void clear() {
        while (head) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ListNode<T>* getHead() const {
        return head;
    }
};

// BST Node
template<typename K, typename V>
struct BSTNode {
    K key;
    V value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class
template<typename K, typename V>
class BST {
private:
    BSTNode<K, V>* root;

    void insertHelper(BSTNode<K, V>*& node, const K& key, const V& value) {
        if (!node) {
            node = new BSTNode<K, V>(key, value);
        }
        else if (key < node->key) {
            insertHelper(node->left, key, value);
        }
        else if (key > node->key) {
            insertHelper(node->right, key, value);
        }
        else {
            // Key already exists, update value
            node->value = value;
        }
    }

    V* searchHelper(BSTNode<K, V>* node, const K& key) const {
        if (!node) {
            return nullptr;
        }
        else if (key < node->key) {
            return searchHelper(node->left, key);
        }
        else if (key > node->key) {
            return searchHelper(node->right, key);
        }
        else {
            return &(node->value);
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear();
    }

    void insert(const K& key, const V& value) {
        insertHelper(root, key, value);
    }

    V* search(const K& key) const {
        return searchHelper(root, key);
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
    }

private:
    void clearHelper(BSTNode<K, V>* node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }
};

// FileHandler Class
class FileHandler {
public:
    static void saveToFile(const string& filename, const vector<string>& data) {
        ofstream outFile(filename);
        for (const string& line : data) {
            outFile << line << endl;
        }
        outFile.close();
    }

    static vector<string> loadFromFile(const string& filename) {
        vector<string> data;
        ifstream inFile(filename);
        string line;
        while (getline(inFile, line)) {
            data.push_back(line);
        }
        inFile.close();
        return data;
    }
};

// Railway Management System Class
class RailwayManagementSystem {
public:
    vector<User> users;
    vector<Train> trains;
    vector<Route> routes;
    unordered_map<string, vector<Train>> bookings;

    RailwayManagementSystem() {
        loadUsers();
        loadTrains();
        loadRoutes();
        loadBookings();
    }

    ~RailwayManagementSystem() {
        saveUsers();
        saveTrains();
        saveRoutes();
        saveBookings();
    }

    void loadUsers() {
        vector<string> data = FileHandler::loadFromFile("users.txt");
        cout << "Loading user data...\n"; // Debug output
        for (const string& line : data) {
            users.push_back(User::fromString(line));
        }
        cout << "Number of users loaded: " << users.size() << "\n"; // Debug output
    }

    void saveUsers() {
        vector<string> data;
        for (const User& user : users) {
            data.push_back(user.toString());
        }
        cout << "Saving user data...\n"; // Debug output
        FileHandler::saveToFile("users.txt", data);
        cout << "User data saved successfully.\n"; // Debug output
    }
    void loadTrains() {
        vector<string> data = FileHandler::loadFromFile("trains.txt");
        cout << "Loading train data...\n"; // Debug output
        for (const string& line : data) {
            trains.push_back(Train::fromString(line));
        }
        cout << "Number of trains loaded: " << trains.size() << "\n"; // Debug output
    }

    void saveTrains() {
        vector<string> data;
        for (const Train& train : trains) {
            data.push_back(train.toString());
        }
        cout << "Saving train data...\n"; // Debug output
        FileHandler::saveToFile("trains.txt", data);
        cout << "Train data saved successfully.\n"; // Debug output
    }

    void loadRoutes() {
        vector<string> data = FileHandler::loadFromFile("routes.txt");
        cout << "Loading route data...\n"; // Debug output
        for (const string& line : data) {
            routes.push_back(Route::fromString(line));
        }
        cout << "Number of routes loaded: " << routes.size() << "\n"; // Debug output
    }

    void saveRoutes() {
        vector<string> data;
        for (const Route& route : routes) {
            data.push_back(route.toString());
        }
        cout << "Saving route data...\n"; // Debug output
        FileHandler::saveToFile("routes.txt", data);
        cout << "Route data saved successfully.\n"; // Debug output
    }

    void loadBookings() {
        vector<string> data = FileHandler::loadFromFile("bookings.txt");
        cout << "Loading booking data...\n"; // Debug output
        for (const string& line : data) {
            stringstream ss(line);
            string username, trainStr;
            getline(ss, username, ':');
            while (getline(ss, trainStr, ';')) {
                bookings[username].push_back(Train::fromString(trainStr));
            }
        }
        cout << "Number of bookings loaded: " << bookings.size() << "\n"; // Debug output
    }

    void saveBookings() {
        vector<string> data;
        for (const auto& booking : bookings) {
            stringstream ss;
            ss << booking.first << ":";
            for (const Train& train : booking.second) {
                ss << train.toString() << ";";
            }
            data.push_back(ss.str());
        }
        cout << "Saving booking data...\n"; // Debug output
        FileHandler::saveToFile("bookings.txt", data);
        cout << "Booking data saved successfully.\n"; // Debug output
    }


    User* findUser(const string& username) {
        for (auto& user : users) {
            if (user.username == username) {
                return &user;
            }
        }
        return nullptr;
    }

    Train* findTrain(int trainId) {
        for (auto& train : trains) {
            if (train.id == trainId) {
                return &train;
            }
        }
        return nullptr;
    }

    Route* findRoute(int routeId) {
        for (auto& route : routes) {
            if (route.id == routeId) {
                return &route;
            }
        }
        return nullptr;
    }

    void displayMenu() {
        cout << "\n--- Railway Management System Menu ---\n";
        cout << "1. Register User\n2. Login User\n3. Add Train (Admin Only)\n4. Edit Train (Admin Only)\n5. Remove Train (Admin Only)\n6. View Trains\n";
        cout << "7. Book Ticket\n8. View Bookings\n9. Add Route (Admin Only)\n10. Edit Route (Admin Only)\n11. Remove Route (Admin Only)\n";
        cout << "12. View Routes\n13. Dashboard Overview (Admin Only)\n14. Generate Reports (Admin Only)\n15. Exit\n";
    }

    void registerUser(const string& username, const string& password, const string& role = "User") {
        if (findUser(username) != nullptr) {
            cout << "User already exists!\n";
            return;
        }
        users.emplace_back(username, password, role);
        cout << "User registered successfully!\n";
    }

    bool loginUser(const string& username, const string& password) {
        User* user = findUser(username);
        if (user == nullptr || user->password != password) {
            cout << "Invalid username or password!\n";
            return false;
        }
        cout << "Login successful! Welcome, " << user->role << " " << username << "\n";
        return true;
    }

    void addTrain(int id, const string& name, const string& source, const string& destination, int seats) {
        if (findTrain(id) != nullptr) {
            cout << "Train ID already exists!\n";
            return;
        }
        trains.emplace_back(id, name, source, destination, seats);
        cout << "Train added successfully!\n";
    }

    void editTrain(int id, const string& name, const string& source, const string& destination, int seats) {
        Train* train = findTrain(id);
        if (train == nullptr) {
            cout << "Train not found!\n";
            return;
        }
        train->name = name;
        train->source = source;
        train->destination = destination;
        train->seats = seats;
        cout << "Train details updated successfully!\n";
    }

    void removeTrain(int id) {
        auto it = remove_if(trains.begin(), trains.end(), [id](const Train& t) { return t.id == id; });
        if (it == trains.end()) {
            cout << "Train not found!\n";
            return;
        }
        trains.erase(it, trains.end());
        cout << "Train removed successfully!\n";
    }

    void viewTrains() {
        cout << "Available Trains:\n";
        for (const auto& train : trains) {
            cout << "ID: " << train.id << ", Name: " << train.name << ", From: " << train.source << " To: " << train.destination << ", Seats: " << train.seats << "\n";
        }
    }

    void bookTicket(const string& username, int trainId) {
        Train* train = findTrain(trainId);
        if (train == nullptr) {
            cout << "Train not found!\n";
            return;
        }
        if (train->seats == 0) {
            cout << "No seats available!\n";
            return;
        }
        train->seats--;
        bookings[username].push_back(*train);
        cout << "Ticket booked successfully!\n";
    }

    void viewBookings(const string& username) {
        cout << "Bookings for " << username << ":\n";
        if (bookings.find(username) == bookings.end()) {
            cout << "No bookings found!\n";
            return;
        }
        for (const auto& train : bookings[username]) {
            cout << "Train ID: " << train.id << ", Name: " << train.name << ", From: " << train.source << " To: " << train.destination << "\n";
        }
    }

    void addRoute(int id, const string& source, const string& destination) {
        if (findRoute(id) != nullptr) {
            cout << "Route ID already exists!\n";
            return;
        }
        routes.emplace_back(id, source, destination);
        cout << "Route added successfully!\n";
    }

    void editRoute(int id, const string& source, const string& destination) {
        Route* route = findRoute(id);
        if (route == nullptr) {
            cout << "Route not found!\n";
            return;
        }
        route->source = source;
        route->destination = destination;
        cout << "Route details updated successfully!\n";
    }

    void removeRoute(int id) {
        auto it = remove_if(routes.begin(), routes.end(), [id](const Route& r) { return r.id == id; });
        if (it == routes.end()) {
            cout << "Route not found!\n";
            return;
        }
        routes.erase(it, routes.end());
        cout << "Route removed successfully!\n";
    }

    void viewRoutes() {
        cout << "Available Routes:\n";
        for (const auto& route : routes) {
            cout << "ID: " << route.id << ", From: " << route.source << " To: " << route.destination << "\n";

        }
    }
    void dashboardOverview() {
        cout << "Dashboard Overview:\n";
        cout << "Total Users: " << users.size() << "\n";
        cout << "Total Trains: " << trains.size() << "\n";
        cout << "Total Routes: " << routes.size() << "\n";
    }

    void generateReports() {
        cout << "Generating Reports...\n";
        // Some placeholder code for generating reports
        cout << "Reports Generated Successfully!\n";
    }

};
// main function
int main() {
    RailwayManagementSystem rms;
    bool loggedIn = false;
    string currentUser;
    string userRole;

    while (true) {
        cout << "\n--- Railway Management System ---\n";
        cout << "1. Login\n2. Register\n3. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }

        cout << "Are you an Admin or User? (Enter 'admin' or 'user'): ";
        cin >> userRole;
        cin.ignore();

        if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            rms.registerUser(username, password, userRole);
        }
        else if (choice == 1) {
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            loggedIn = rms.loginUser(username, password);
            if (loggedIn) {
                currentUser = username;
            }
        }

        if (loggedIn) {
            while (true) {
                cout << "\n--- Welcome, " << currentUser << "! ---\n";
                if (userRole == "admin") {
                    cout << "1. Add Train\n2. Edit Train\n3. Remove Train\n4. View Trains\n";
                    cout << "5. Add Route\n6. Edit Route\n7. Remove Route\n8. View Routes\n";
                    cout << "9. Dashboard Overview\n10. Generate Reports\n11. Logout\n";
                }
                else if (userRole == "user") {
                    cout << "1. Book Ticket\n2. View Bookings\n3. Logout\n";
                }
                else {
                    cout << "Invalid user role! Exiting...\n";
                    break;
                }

                int userChoice;
                cout << "Enter your choice: ";
                cin >> userChoice;
                cin.ignore(); // Clear the input buffer

                if (userRole == "admin") {
                    switch (userChoice) {
                    case 1: {
                        int trainId;
                        cout << "Enter Train ID: ";
                        cin >> trainId;
                        string name, source, destination;
                        int seats;
                        cout << "Enter Train Name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter Source: ";
                        getline(cin, source);
                        cout << "Enter Destination: ";
                        getline(cin, destination);
                        cout << "Enter Number of Seats: ";
                        cin >> seats;
                        rms.addTrain(trainId, name, source, destination, seats);
                        break;
                    }
                    case 2: {
                        int trainId;
                        cout << "Enter Train ID to edit: ";
                        cin >> trainId;
                        string name, source, destination;
                        int seats;
                        cout << "Enter Train Name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter Source: ";
                        getline(cin, source);
                        cout << "Enter Destination: ";
                        getline(cin, destination);
                        cout << "Enter Number of Seats: ";
                        cin >> seats;
                        rms.editTrain(trainId, name, source, destination, seats);
                        break;
                    }
                    case 3: {
                        int trainId;
                        cout << "Enter Train ID to remove: ";
                        cin >> trainId;
                        rms.removeTrain(trainId);
                        break;
                    }
                    case 4: {
                        rms.viewTrains();
                        break;
                    }
                    case 5: {
                        int routeId;
                        cout << "Enter Route ID: ";
                        cin >> routeId;
                        string source, destination;
                        cout << "Enter Source: ";
                        cin.ignore();
                        getline(cin, source);
                        cout << "Enter Destination: ";
                        getline(cin, destination);
                        rms.addRoute(routeId, source, destination);
                        break;
                    }
                    case 6: {
                        int routeId;
                        cout << "Enter Route ID to edit: ";
                        cin >> routeId;
                        string source, destination;
                        cout << "Enter Source: ";
                        cin.ignore();
                        getline(cin, source);
                        cout << "Enter Destination: ";
                        getline(cin, destination);
                        rms.editRoute(routeId, source, destination);
                        break;
                    }
                    case 7: {
                        int routeId;
                        cout << "Enter Route ID to remove: ";
                        cin >> routeId;
                        rms.removeRoute(routeId);
                        break;
                    }
                    case 8: {
                        rms.viewRoutes();
                        break;
                    }
                    case 9: {
                        rms.dashboardOverview();
                        break;
                    }
                    case 10: {
                        rms.generateReports();
                        break;
                    }
                    case 11: {
                        loggedIn = false;
                        cout << "Logged out successfully!\n";
                        break;
                    }
                    default:
                        cout << "Invalid choice!\n";
                    }
                }
                else if (userRole == "user") {
                    switch (userChoice) {
                    case 1: {
                        int trainId;
                        cout << "Enter Train ID to book: ";
                        cin >> trainId;
                        rms.bookTicket(currentUser, trainId);
                        break;
                    }
                    case 2: {
                        rms.viewBookings(currentUser);
                        break;
                    }
                    case 3: {
                        loggedIn = false;
                        cout << "Logged out successfully!\n";
                        break;
                    }
                    default:
                        cout << "Invalid choice!\n";
                    }
                }

                if (!loggedIn) {
                    break; // Break out of the inner loop
                }
            }
        }
    }

    return 0;
}




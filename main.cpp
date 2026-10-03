#include <iostream>
#include <string>
#include <limits>
#include "Graph.h"

using namespace std;

// -----------------------------------------------------------------------
// Builds the campus graph with fixed locations and roads (edges).
// Weights represent distances in kilometers.
// -----------------------------------------------------------------------
void buildCampusGraph(Graph& campus) {
    // Vertices (campus locations) -- added explicitly so they show up
    // in "Display campus locations" even before any edges are added.
    campus.addLocation("Main Gate");
    campus.addLocation("Library");
    campus.addLocation("CSE Block");
    campus.addLocation("Mechanical Block");
    campus.addLocation("Hostel");
    campus.addLocation("Canteen");
    campus.addLocation("Auditorium");
    campus.addLocation("Sports Complex");

    // Edges (roads) with distances in km
    campus.addEdge("Main Gate", "Library", 2);
    campus.addEdge("Library", "CSE Block", 2);
    campus.addEdge("CSE Block", "Hostel", 2);
    campus.addEdge("Main Gate", "Canteen", 3);
    campus.addEdge("Canteen", "Auditorium", 2);
    campus.addEdge("Auditorium", "Sports Complex", 3);
    campus.addEdge("CSE Block", "Mechanical Block", 1);
    campus.addEdge("Mechanical Block", "Hostel", 3);
    campus.addEdge("Library", "Auditorium", 4);
    campus.addEdge("Hostel", "Sports Complex", 2);
    campus.addEdge("Canteen", "CSE Block", 5);
}

// Reads a full line of input safely (handles multi-word location names)
string readLine() {
    string line;
    getline(cin, line);
    return line;
}

// Reads a valid location index number between 1 and 8
int readLocationNumber(const string& prompt) {
    int num;
    while (true) {
        cout << prompt;
        if (cin >> num) {
            if (num >= 1 && num <= 8) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume newline/leftover characters
                return num;
            } else {
                cout << "\nError: Invalid location number. Please choose from 1 to 8.\n";
            }
        } else {
            cout << "\nError: Invalid input. Please enter a valid number.\n";
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
        }
    }
}


void printMenu() {
    cout << "\n===== CAMPUS ROUTE OPTIMIZER =====\n";
    cout << "1. Display campus locations\n";
    cout << "2. Find shortest route using Dijkstra\n";
    cout << "3. Check connectivity using BFS\n";
    cout << "4. Display graph connections\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Graph campus;
    buildCampusGraph(campus);

    cout << "Welcome to the Campus Route Optimizer!\n";

    int choice;
    while (true) {
        printMenu();

        // ---- Validate menu choice input ----
        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number between 1 and 5.\n";
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume leftover newline

        if (choice == 1) {
            campus.displayLocations();


        } else if (choice == 2) {
            campus.displayLocations();
            int srcNum = readLocationNumber("\nEnter source location number: ");
            int destNum = readLocationNumber("Enter destination location number: ");
            string source = campus.getLocationByIndex(srcNum);
            string destination = campus.getLocationByIndex(destNum);
            campus.findShortestPath(source, destination);

        } else if (choice == 3) {
            campus.displayLocations();
            int srcNum = readLocationNumber("\nEnter source location number: ");
            int destNum = readLocationNumber("Enter destination location number: ");
            string source = campus.getLocationByIndex(srcNum);
            string destination = campus.getLocationByIndex(destNum);
            campus.checkConnectivity(source, destination);

        } else if (choice == 4) {
            campus.displayGraph();

        } else if (choice == 5) {
            cout << "\nExiting Campus Route Optimizer. Goodbye!\n";
            break;

        } else {
            cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
        }
    }

    return 0;
}

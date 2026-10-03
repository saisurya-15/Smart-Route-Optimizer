#include "Graph.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

// -----------------------------------------------------------------------
// Helper: check whether a location already exists as a key in adjList
// -----------------------------------------------------------------------
bool Graph::locationExists(const string& location) const {
    return adjList.find(location) != adjList.end();
}

bool Graph::isValidLocation(const string& location) const {
    return locationExists(location);
}

// -----------------------------------------------------------------------
// Adds a vertex with an empty adjacency list (if it doesn't exist yet)
// -----------------------------------------------------------------------
void Graph::addLocation(const string& location) {
    if (!locationExists(location)) {
        adjList[location] = vector<pair<string, int>>();
    }
}

// -----------------------------------------------------------------------
// Adds an undirected weighted edge between two locations.
// Since campus roads can be walked in both directions, the edge is
// added to BOTH locations' adjacency lists.
// -----------------------------------------------------------------------
void Graph::addEdge(const string& from, const string& to, int distance) {
    // Make sure both endpoints exist as vertices first
    addLocation(from);
    addLocation(to);

    adjList[from].push_back({to, distance});
    adjList[to].push_back({from, distance});
}

// -----------------------------------------------------------------------
// Displays all campus locations (vertices)
// -----------------------------------------------------------------------
void Graph::displayLocations() const {
    cout << "\nAvailable Campus Locations:\n";
    cout << "----------------------------\n";
    int i = 1;
    for (const auto& pair : adjList) {
        cout << i++ << ". " << pair.first << "\n";
    }
}

// -----------------------------------------------------------------------
// Displays the graph: every location and the roads (edges) leading
// out of it, along with their distances.
// -----------------------------------------------------------------------
void Graph::displayGraph() const {
    cout << "\nCampus Graph (Adjacency List):\n";
    cout << "--------------------------------\n";
    for (const auto& pair : adjList) {
        cout << pair.first << " ->";
        if (pair.second.empty()) {
            cout << " (no direct connections)";
        }
        for (const auto& neighbour : pair.second) {
            cout << " [" << neighbour.first << ", " << neighbour.second << " km]";
        }
        cout << "\n";
    }
}

// -----------------------------------------------------------------------
// Dijkstra's Algorithm
// -----------------------------------------------------------------------
// Finds the shortest weighted path from 'source' to 'destination'.
//
// Key idea: repeatedly pick the unvisited location with the smallest
// known distance from the source, and try to "relax" (improve) the
// distances of its neighbours through it.
//
// A MIN-PRIORITY QUEUE (min-heap) is used so that the location with
// the current smallest tentative distance is always processed next,
// without having to linearly scan all locations each time.
//
// We use a min-heap by storing pairs of (distance, location) and
// using greater<> as the comparator so the smallest distance is on top.
// -----------------------------------------------------------------------
void Graph::findShortestPath(const string& source, const string& destination) const {
    // ---- Input validation ----
    if (!locationExists(source) || !locationExists(destination)) {
        cout << "\nError: One or both locations do not exist in the campus graph.\n";
        return;
    }

    if (source == destination) {
        cout << "\nSource and destination are the same location (" << source
             << "). Distance = 0 km.\n";
        return;
    }

    // distance[location] = shortest known distance from source so far
    unordered_map<string, int> distance;
    // previous[location] = the location we came from on the shortest path
    // (used later to reconstruct the path)
    unordered_map<string, string> previous;

    // Initialize all distances to "infinity"
    for (const auto& pair : adjList) {
        distance[pair.first] = numeric_limits<int>::max();
    }
    distance[source] = 0;

    // Min-heap of (distance, location), smallest distance on top
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    pq.push({0, source});

    while (!pq.empty()) {
        pair<int, string> top = pq.top();
        pq.pop();

        int currentDist = top.first;
        string currentLoc = top.second;

        // Skip stale/outdated entries (a shorter path was already found)
        if (currentDist > distance[currentLoc]) {
            continue;
        }

        // We can stop early once we pop the destination itself
        if (currentLoc == destination) {
            break;
        }

        // Relax every neighbour of the current location
        for (const auto& neighbour : adjList.at(currentLoc)) {
            const string& nextLoc = neighbour.first;
            int edgeWeight = neighbour.second;

            int newDist = currentDist + edgeWeight;
            if (newDist < distance[nextLoc]) {
                distance[nextLoc] = newDist;
                previous[nextLoc] = currentLoc;
                pq.push({newDist, nextLoc});
            }
        }
    }

    // ---- Unreachable check ----
    if (distance[destination] == numeric_limits<int>::max()) {
        cout << "\nNo path exists between " << source << " and " << destination
             << ". Destination is unreachable.\n";
        return;
    }

    // ---- Path reconstruction ----
    // Walk backwards from destination to source using 'previous',
    // then reverse the collected path.
    vector<string> path;
    string current = destination;
    while (current != source) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    // ---- Output ----
    cout << "\nShortest Path:\n";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\n\nMinimum Distance: " << distance[destination] << " km\n";
}

// -----------------------------------------------------------------------
// BFS (Breadth-First Search)
// -----------------------------------------------------------------------
// Checks whether 'destination' is reachable from 'source', ignoring
// edge weights entirely (pure connectivity check).
//
// A std::queue is used because BFS explores the graph level by level:
// it must visit all locations at distance 1 hop away before moving on
// to locations 2 hops away, and so on. A queue enforces this
// First-In-First-Out order naturally.
// -----------------------------------------------------------------------
void Graph::checkConnectivity(const string& source, const string& destination) const {
    // ---- Input validation ----
    if (!locationExists(source) || !locationExists(destination)) {
        cout << "\nError: One or both locations do not exist in the campus graph.\n";
        return;
    }

    if (source == destination) {
        cout << "\n" << source << " is trivially reachable from itself.\n";
        return;
    }

    unordered_set<string> visited;
    queue<string> q;

    visited.insert(source);
    q.push(source);

    bool reached = false;

    while (!q.empty()) {
        string currentLoc = q.front();
        q.pop();

        if (currentLoc == destination) {
            reached = true;
            break;
        }

        for (const auto& neighbour : adjList.at(currentLoc)) {
            const string& nextLoc = neighbour.first;
            if (visited.find(nextLoc) == visited.end()) {
                visited.insert(nextLoc);
                q.push(nextLoc);
            }
        }
    }

    if (reached) {
        cout << "\n" << destination << " IS reachable from " << source << ".\n";
    } else {
        cout << "\n" << destination << " is NOT reachable from " << source << ".\n";
    }
}

// -----------------------------------------------------------------------
// Returns the location name at the specified 1-based index based on
// the iteration order of the adjacency list map.
// -----------------------------------------------------------------------
string Graph::getLocationByIndex(int index) const {
    if (index < 1 || index > static_cast<int>(adjList.size())) {
        return "";
    }
    int i = 1;
    for (const auto& pair : adjList) {
        if (i == index) {
            return pair.first;
        }
        i++;
    }
    return "";
}


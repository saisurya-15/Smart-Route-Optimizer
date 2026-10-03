#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

// -----------------------------------------------------------------------
// Graph class
// -----------------------------------------------------------------------
// Represents the campus as a WEIGHTED, UNDIRECTED graph using an
// ADJACENCY LIST.
//
//   - Each campus location (e.g. "Library") is a VERTEX.
//   - Each road connecting two locations is an EDGE.
//   - The EDGE WEIGHT is the distance (in km) between the two locations.
//
// An adjacency list (unordered_map<string, vector<pair<string,int>>>)
// is used instead of an adjacency matrix because:
//   - A campus is a sparse graph (each location connects to only a
//     handful of others, not every other location).
//   - Adjacency lists use O(V + E) space instead of O(V^2), which is
//     much more efficient for sparse graphs.
//   - Iterating over the neighbours of a location (needed constantly by
//     Dijkstra and BFS) is fast and direct with an adjacency list.
// -----------------------------------------------------------------------
class Graph {
private:
    // adjList[location] = list of (neighbourLocation, distance) pairs
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> adjList;

    // Checks if a location name exists in the graph
    bool locationExists(const std::string& location) const;

public:
    // Adds a new vertex (campus location) with no connections yet
    void addLocation(const std::string& location);

    // Adds a bidirectional weighted edge (road) between two locations
    void addEdge(const std::string& from, const std::string& to, int distance);

    // Prints every campus location currently in the graph
    void displayLocations() const;

    // Prints every location along with its direct connections
    void displayGraph() const;

    // Runs Dijkstra's algorithm from 'source' to 'destination'.
    // Prints the shortest path and the total distance.
    // Uses a std::priority_queue as a min-heap so that the location
    // with the smallest known distance is always processed next.
    void findShortestPath(const std::string& source, const std::string& destination) const;

    // Runs BFS starting at 'source' to check whether 'destination'
    // is reachable at all (ignores edge weights, purely connectivity).
    // Uses a std::queue, the defining data structure of BFS.
    void checkConnectivity(const std::string& source, const std::string& destination) const;

    // Public wrapper so main.cpp can validate user input before running
    // Dijkstra/BFS (keeps error handling in one place).
    bool isValidLocation(const std::string& location) const;

    // Returns the location name at the specified 1-based index
    std::string getLocationByIndex(int index) const;
};

#endif // GRAPH_H

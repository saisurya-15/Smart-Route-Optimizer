# SmartRoute

A console-based C++ application that models a college campus as a weighted, undirected graph. It helps find the shortest path between campus locations using **Dijkstra's Algorithm** and checks connectivity between locations using **Breadth-First Search (BFS)**.

## ✨ Features

- **Number-Based Input**: Select campus locations using their index numbers.
- **Input Validation**: Handles invalid and non-numeric input without crashing.
- **Weighted Pathfinding**: Calculates the shortest route and total walking distance.
- **Bidirectional Routing**: Models pathways that can be used in either direction.

---

## 🛠️ Technologies Used

- **Language**: C++ (C++17 standard)
- **Compiler**: GCC (`g++`)

---

## 📦 Data Structures Used

- **Adjacency List**: Stores campus locations, neighboring locations, and edge weights.
- **Min-Priority Queue**: Used by Dijkstra's algorithm to process the location with the smallest tentative distance.
- **Queue**: Used for level-order traversal in BFS.
- **Unordered Set**: Tracks visited locations during BFS.
- **Unordered Maps**: Stores shortest distances and predecessor information for path reconstruction.

---

## 🧭 Algorithms Implemented

### 1. Dijkstra's Algorithm — Shortest Route

Used to find the shortest physical distance between two locations in the weighted graph.

**Steps:**
1. Initialize all distances to infinity except the source, which is set to `0`.
2. Insert the source into a min-priority queue.
3. Process the location with the smallest tentative distance.
4. Relax neighboring locations when a shorter distance is found.
5. Reconstruct the shortest path using the predecessor information.

### 2. Breadth-First Search (BFS) — Connectivity Check

Used to determine whether one location is reachable from another without considering physical distances.

**Steps:**
1. Start from the source location and mark it as visited.
2. Add the source to a FIFO queue.
3. Visit each unvisited neighboring location.
4. Continue until the destination is found or all reachable locations have been explored.

---

## 📈 Complexity Analysis

| Algorithm | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Dijkstra** | $O((V + E) \log V)$ | $O(V + E)$ |
| **BFS** | $O(V + E)$ | $O(V + E)$ |

- **V** = Number of campus locations = 8
- **E** = Number of interconnecting roads = 11

---

## 📂 Project Structure

```text
SmartRoute/
├── .gitignore     # Ignores compiler output/executables
├── Graph.h        # Declaration of the Graph class
├── Graph.cpp      # Implementation of Dijkstra, BFS, and graph display
├── main.cpp       # Graph setup, menu, and input handling
└── README.md      # Project documentation
```

---

## 🚀 How to Compile and Run

### Windows (MinGW/g++)

1. Open PowerShell or Command Prompt.
2. Compile:

```cmd
g++ -std=c++17 -Wall -Wextra -o smartroute.exe main.cpp Graph.cpp
```

3. Run:

```cmd
.\smartroute.exe
```

### Linux / macOS

1. Open a terminal.
2. Compile:

```bash
g++ -std=c++17 -Wall -Wextra -o smartroute main.cpp Graph.cpp
```

3. Run:

```bash
./smartroute
```

---

## 🖥️ Example Usage & Output

```text
===== SMARTROUTE =====
1. Display campus locations
2. Find shortest route using Dijkstra
3. Check connectivity using BFS
4. Display graph connections
5. Exit
Enter your choice: 2

Available Campus Locations:
----------------------------
1. Canteen
2. Sports Complex
3. Main Gate
4. Auditorium
5. Hostel
6. CSE Block
7. Library
8. Mechanical Block

Enter source location number: 5
Enter destination location number: 1

Shortest Path:
Hostel -> CSE Block -> Canteen

Minimum Distance: 7 km
```

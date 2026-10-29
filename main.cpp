
/*
  Name: Utkrista Mardan Basnyat
  Course: COMSC-210 Data Structures
  Lab 29: Project Proposal, Pseudocode, and Mockup
  Project: City Traffic Flow Simulation
  File: main.cpp
*/

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>

using namespace std;

// Each intersection has three lane containing vehicle IDs
typedef map<string, array<list<int>, 3>> TrafficMap;

// Function prototypes
void load_traffic(TrafficMap &traffic);
void display_traffic(const TrafficMap &traffic);
void simulate_traffic(TrafficMap &traffic, int minutes);

int main() {
  // Create a map of intersections with three traffic lanes each
  TrafficMap traffic;

  // Load vehicle information from an external file
  // Future implementation:
  // Open traffic data file
  // Read at least 100 line of vehicle data
  // Store seach vehicle in the correct intersection and lane
  load_traffic(traffic);

  // Display the initial traffic conditions
  cout << "CITY TRAFFIC FLOW SIMULATION\n";
  cout << "Initial Traffic Conditions:\n";
  display_traffic(traffic);

  // Simulate traffic changes for 30 one minute periods
  simulate_traffic(traffic, 30);

  // Display traffic conditions after the simulation
  cout << "\nFinal Traffic Conditions:\n";
  display_traffic(traffic);

  return 0;
}

void load_traffic(TrafficMap &traffic) {
  // Future implementation:
  // Open an external file containing vehicle records
  // Read each vehicle ID, intersection and lane
  // Add vehicles to the appropriate lists

  // Mockup: insert one sample vehicle into lane 1
  traffic["Main Street"][0].push_back(101);

  cout << "Sample traffic data loaded.\n\n";
}

void display_traffic(const TrafficMap &traffic) {
  // Future implementation:
  // Loop through each intersection in the map
  // Loop through all three lanes in its array
  // Display the vehicle IDs stored in each list

  // Mockup: demonstrate that nested structure works
  for (const auto &intersection : traffic) {
    cout << "Intersection: " << intersection.first << endl;

    for (int i = 0; i < 3; i++) {
      cout << "  Lane " << i + 1 << ": ";

      for (int vehicle : intersection.second[i]) {
        cout << vehicle << " ";
      }

      cout << endl;
    }
  }
}

void simulate_traffic(TrafficMap &traffic, int minutes) {
  // Future implementation:
  // Repeat the simulation for the requested number of minutes
  // At each minute:
  // Process vehicles arriving from data file
  // Update the traffic lights for each intersection
  // Allow vehicles to depart from lanes with a green light
  // Display changes and current traffic conditions
  // After at least 25 periods, show the final traffic state

  // Mockup: print a message to confirm the function works
  cout << "\nSimulation function received "
       << minutes << " minutes.\n";

  cout << "Intersections available: "
       << traffic.size() << endl;

  cout << "Minute 1: Sample traffic light change.\n";
  cout << "Minute 2: Sample vehicle arrival.\n";
  cout << "Minute 3: Sample vehicle departure.\n";
}


/*
  Course: COMSC-210 Data Structures
  Lab 30: Alpha Release
  Project: City Traffic Flow Simulation
*/

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

typedef map<string, array<list<int>, 3>> TrafficMap;

// Function prototypes
void load_traffic(TrafficMap &traffic);
void display_traffic(const TrafficMap &traffic);
void simulate_traffic(TrafficMap &traffic, int minutes);

int main() {
  TrafficMap traffic;

  load_traffic(traffic);

  cout << "\nCITY TRAFFIC FLOW SIMULATION\n";
  cout << "Initial Traffic Conditions:\n";
  display_traffic(traffic);

  simulate_traffic(traffic, 30);

  cout << "\nFinal Traffic Conditions:\n";
  display_traffic(traffic);

  return 0;
}

void load_traffic(TrafficMap &traffic) {
  // Open the external data file
  ifstream file("traffic.txt");

  if (!file.is_open()) {
    cout << "Error: Could not open traffic.txt\n";
    return;
  }

  string line;
  int count = 0;

  // Read each traffic record from the file
  while (getline(file, line)) {
    string intersection;
    string laneText;
    string vehicleText;

    stringstream ss(line);

    getline(ss, intersection, ',');
    getline(ss, laneText, ',');
    getline(ss, vehicleText, ',');

    if (intersection.empty() || laneText.empty() || vehicleText.empty()) {
      continue;
    }

    int lane = stoi(laneText);
    int vehicleID = stoi(vehicleText);

    if (lane >= 1 && lane <= 3) {
      traffic[intersection][lane - 1].push_back(vehicleID);
      count++;
    }
  }

  file.close();

  cout << count << " vehicle records loaded from traffic.txt\n";
}

void display_traffic(const TrafficMap &traffic) {
  // Display intersections and their three lanes
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
  // Alpha mockup: show example events
  // Future version will process real arrivals and departures
  // during each of the 30 simulated minutes

  cout << "\nSimulation function received "
       << minutes << " minutes.\n";

  cout << "Intersections available: "
       << traffic.size() << endl;

  cout << "Minute 1: Sample traffic light change.\n";
  cout << "Minute 2: Sample vehicle arrival.\n";
  cout << "Minute 3: Sample vehicle departure.\n";
}

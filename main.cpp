
/*
  Course: COMSC-210 Data Structures
  Lab 31: Beta Release
  Project: City Traffic Flow Simulation
*/

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

typedef map<string, array<list<int>, 3>> TrafficMap;

// Function prototypes
void load_traffic(TrafficMap &traffic);
void display_traffic(const TrafficMap &traffic);
void simulate_traffic(TrafficMap &traffic, int minutes);

int main() {
  TrafficMap traffic;

  load_traffic(traffic);

  // Stop the simulation if no traffic data was loaded
  if (traffic.empty()) {
    cout << "Simulation stopped: No traffic data available.\n";
    return 1;
  }

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

    // Handle invalid numbers without crashing
    try {
      int lane = stoi(laneText);
      int vehicleID = stoi(vehicleText);

      // Only lanes 1, 2, and 3 are valid
      if (lane >= 1 && lane <= 3) {
        traffic[intersection][lane - 1].push_back(vehicleID);
        count++;
      } else {
        cout << "Warning: Invalid lane number "
             << lane << ". Record skipped.\n";
      }
    } catch (const invalid_argument &e) {
      cout << "Warning: Invalid number in traffic record. Skipping.\n";
    } catch (const out_of_range &e) {
      cout << "Warning: Number out of range in traffic record. Skipping.\n";
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
  cout << "\nStarting traffic simulation...\n";

  int nextVehicleID = 201;

  for (int minute = 1; minute <= minutes; minute++) {
    int greenLane = (minute - 1) % 3;

    cout << "\nMinute " << minute << endl;
    cout << "Lane " << greenLane + 1 << " has a green light.\n";

    for (auto &intersection : traffic) {
      // Add one arriving vehicle to each intersection
      int arrivalLane = minute % 3;

      intersection.second[arrivalLane].push_back(nextVehicleID);

      cout << "Vehicle " << nextVehicleID
           << " arrived at " << intersection.first
           << " in Lane " << arrivalLane + 1 << ".\n";

      nextVehicleID++;

      // Remove the first vehicle from the green lane
      list<int> &lane = intersection.second[greenLane];

      if (!lane.empty()) {
        int vehicleID = lane.front();
        lane.pop_front();

        cout << "Vehicle " << vehicleID
             << " left " << intersection.first
             << " from Lane " << greenLane + 1 << ".\n";
      } else {
        cout << "No vehicles waiting in Lane "
             << greenLane + 1 << " at "
             << intersection.first << ".\n";
      }
    }

    cout << "\nTraffic conditions after minute "
         << minute << ":\n";
    display_traffic(traffic);
  }
}

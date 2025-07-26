#include<iostream>
#include<vector>
#include<map>
#include<memory>

using namespace std;

enum class Size{COMPAT, REGULAR, HEAVY};

class Vehicle{
public:
    string id;
    Size size;

};

class Car: public Vehicle{
private:

public:
    Car(string id){
        this->id = id;
        size = Size::REGULAR;
    }
    
};

class Bike: public Vehicle{
private:

public:
    Bike(string id){
        this->id = id;
        size = Size::COMPAT;
    }
};

class Truck: public Vehicle{
private:

public:
    Truck(string id){
        this->id = id;
        size = Size::HEAVY;
    }
};


class Spot{
private:
    string spotId;
    Size size;
    bool isVacant;
    shared_ptr<Vehicle> parkedVehicle;

public:
    Spot(string spotId, Size size): spotId(spotId), size(size), isVacant(true) {};

    bool park(shared_ptr<Vehicle>vehicle){
        if(vehicle -> size == this -> size and isVacant) {
            isVacant = false;
            parkedVehicle = vehicle;
            return true;
        } 
        return false;
    }

    bool unpark(string vehicleId) {
        if (!isVacant && parkedVehicle->id == vehicleId) {
            isVacant = true;
            parkedVehicle.reset();
            return true;
        }
        return false;
    }

    bool matchesVehicle(string vehicleId){
        return (!isVacant && parkedVehicle && parkedVehicle->id == vehicleId);
    }
    
};

class Level{
    int levelId;

    // capacity
    int compatCap;
    int regularCap;
    int heavyCap;

    vector<Spot>spots;

public:
    Level(int levelId, int compatCap, int regularCap, int heavyCap)
        : levelId(levelId), compatCap(compatCap), regularCap(regularCap), heavyCap(heavyCap) {

        for (int i = 0; i < compatCap; i++) 
            spots.emplace_back(generateSpotId(levelId, Size::COMPAT, i), Size::COMPAT);
        for (int i = 0; i < regularCap; i++) 
            spots.emplace_back(generateSpotId(levelId, Size::REGULAR, i), Size::REGULAR);
        for (int i = 0; i < heavyCap; i++) 
            spots.emplace_back(generateSpotId(levelId, Size::HEAVY, i), Size::HEAVY);
    }

    string generateSpotId(int levelId, Size size, int index) {
        string prefix = (size == Size::COMPAT) ? "C" :
                        (size == Size::REGULAR) ? "R" : "H";
        return "L" + to_string(levelId) + "_" + prefix + "_" + to_string(index);
    }

    // Returns index of spot in the vector if parked, else -1
    int park(shared_ptr<Vehicle> vehicle) {
        for (int i = 0; i < spots.size(); i++) {
            if (spots[i].park(vehicle)) return i;
        }
        return -1;
    }


    bool unpark(shared_ptr<Vehicle>vehicle) {
        for (auto& spot : spots) {
            if (spot.matchesVehicle(vehicle -> id)) {
                spot.unpark(vehicle -> id);
                return true;
            }
        }
        return false;
    }
    
};

class ParkingLot{
private:
    vector<Level>levels;

    // Maps vehicle ID to {level index, spot index}
    unordered_map<string, pair<int, int>> vehicleLocation;

public:
    ParkingLot(int numLevels, int numCompat = 100, int numRegular = 100, int numHeavy = 100){
        for(int i = 0; i < numLevels; i++){
            levels.emplace_back(i, numCompat, numRegular, numHeavy);
        }
    }

    void park(shared_ptr<Vehicle>vehicle){
        if (vehicleLocation.find(vehicle->id) != vehicleLocation.end()) {
            cout << "Vehicle already parked\n";
            return;
        }

        for (int i = 0; i < levels.size(); i++) {
            int spotIdx = levels[i].park(vehicle);
            if (spotIdx != -1) {
                vehicleLocation[vehicle->id] = {i, spotIdx};
                cout << "Vehicle " << vehicle->id << " parked at Level " << i << ", Spot " << spotIdx << "\n";
                return;
            }
        }

        cout << "No spot available for vehicle " << vehicle->id << "\n";
    }

    void unpark(shared_ptr<Vehicle> vehicle) {
        auto it = vehicleLocation.find(vehicle->id);
        if (it == vehicleLocation.end()) {
            cout << "Vehicle " << vehicle->id << " not found in parking\n";
            return;
        }

        int levelIdx = it->second.first;
        if (levels[levelIdx].unpark(vehicle)) {
            vehicleLocation.erase(vehicle->id);
            cout << "Vehicle " << vehicle->id << " unparked from Level " << levelIdx << "\n";
        } else {
            cout << "Error in unparking vehicle " << vehicle->id << "\n";
        }
    }

};


int main(){

    ParkingLot pl(2, 2, 2, 1); // 2 levels, 2 compat, 2 regular, 1 heavy spots each

    auto bike1 = make_shared<Bike>("B101");
    auto car1 = make_shared<Car>("C101");
    auto truck1 = make_shared<Truck>("T101");

    pl.park(bike1);
    pl.park(car1);
    pl.park(truck1);

    pl.unpark(car1);
    pl.park(car1);  // Should park again

    auto car2 = make_shared<Car>("C102");
    auto car3 = make_shared<Car>("C103");

    pl.park(car2);
    pl.park(car3);  // Might fail if no space left

}
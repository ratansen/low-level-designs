#include<iostream>
#include<vector>
#include<map>
#include<memory>

using namespace std;

enum class Type{COMPAT, REGULAR, HEAVY};

class Vehicle{
public:
    string id;
    Type type;

};

class Car: public Vehicle{
private:

public:
    Car(string id){
        this->id = id;
        type = Type::REGULAR;
    }
    
};

class Bike: public Vehicle{
private:

public:
    Bike(string id){
        this->id = id;
        type = Type::COMPAT;
    }

};

class Car: public Vehicle{
private:

public:
    Car(string id){
        this->id = id;
    }
};



class Spot{
private:
    int id;
    Type type;
    bool isVacant;
    shared_ptr<Vehicle> parkedVehicle;

public:
    Spot(int id, Type type): id(id), type(type), isVacant(true) {};

    bool park(shared_ptr<Vehicle>vehicle){
        if(vehicle -> type == this->type and isVacant) {
            isVacant = false;
            parkedVehicle = vehicle;
            return true;
        } 
        return false;
    }

    void unpark(shared_ptr<Vehicle>vehicle){
        this->isVacant = true;
        parkedVehicle.reset();
    }
    
};

class Level{
    int id;

    // capacity
    int compatCap;
    int regularCap;
    int heavyCap;
    vector<Spot>spots;
public:
    Level(int id, int compatCap, int regularCap, int heavyCap)
        : id(id), compatCap(compatCap), regularCap(regularCap), heavyCap(heavyCap) {

        for(int i = 0; i < compatCap; i++) spots.emplace_back()
    }

    bool park(shared_ptr<Vehicle>vehicle){

    }
    

};

class ParkingLot{
private:
    vector<Level>levels;
public:
    ParkingLot(int numLevels, int numCompat, int numRegular, int numHeavy){
        for(int i = 0; i < numLevels; i++){
            levels.emplace_back(i, numCompat, numRegular, numHeavy);
        }
    }
    void park(shared_ptr<Vehicle>vehicle){
        for(auto e: levels){
            if(e.park(vehicle)){
                cout << "Vehicle parked\n";
                return;
            }
        }
        cout << "No spot available\n";
    }

};




int main(){

}
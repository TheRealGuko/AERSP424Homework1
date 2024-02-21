#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
using namespace std;


//Question 3
class Plane {
private:
    float pos;
    float vel;
    float distance;
    bool at_SCE;
    std::string origin;
    std::string destination;
    std::map<std::pair<std::string, std::string>, int> flightDistances;

public:
    Plane(const std::string from, const std::string to, std::map<std::pair<std::string, std::string>, int> flightDistances)
    {
        origin = from;
        destination = to;
        if (origin == "SCE" && destination == "PHL" || origin == "PHL" && destination == "SCE")
        {
            distance = flightDistances[{"SCE", "PHL"}];
            cout << "The total trip miles is " << distance << endl;
        }
        else if (origin == "SCE" && destination == "ORD" || origin == "ORD" && destination == "SCE")
        {
            distance = flightDistances[{"SCE", "ORD"}];
            cout << "The total trip miles is " << distance << endl;
        }
        else if (origin == "SCE" && destination == "EWR" || origin == "EWR" && destination == "SCE")
        {
            distance = flightDistances[{"SCE", "EWR"}];
            cout << "The total trip miles is " << distance << endl;
        }
        else
        {
            cout << "Not a valid input" << endl;
        }
        pos = 0;
        vel = 0;
        at_SCE = 0;
        cout << "Plane created at " <<this << endl;
    }

    ~Plane() {
        cout << "Plane Destroyed.";
    }

    void operate(float dt) {
        if (pos < distance)
        {
            pos += vel * dt;
            at_SCE = 0;
        }
        else
        {
            if (destination == "SCE")
            {
                at_SCE = 1;
            }
            else
            {
                std::string temp = origin;
                origin = destination;
                destination = temp;
                pos = 0.0;
            }   
        }
    }

    float getPos() {
        return pos;
    }
 
    std::string getOrigin() {
        return origin;
    }
 
    std::string getDestination() {
        return destination;
    }

    float getDistance()
    {  
        return distance;
    }

    bool isAtSCE() {
        return at_SCE;
    }

    float getVel() {
        return vel;
    }

    void setVel(float velocity) {
        vel = velocity;
    }
};

//Question 6
class Pilot {
private:
    std::string name;
    Plane* myPlane;
public:
    Pilot(const std::string& _name, Plane* _plane) : name(_name), myPlane(_plane) 
    {
        std::cout << name << " is at the gate, ready to board the plane." << std::endl;
        std::cout << "Memory address: " << this << std::endl;
    }

    ~Pilot()
    {
        std::cout << name << " is out of the plane." << std::endl;
    }
    std::string getName() const 
    {
        return name;
    }
};

int main() {

    /*The following is Question 1 for the homework*/
    float planeEmptyWeight, usableFuelPerGallon, baggageWeight; //Pounds
    int numFrontSeatOcc, numRearSeatOcc; //No Unit
    float planeWeightEmptyMoment; //Pounds-inches
    float frontSeatMomentArm, rearSeatMomentArm, fuelMomentArm, baggageMomentArm; //Inches
    float gallonUsableFuel; //Gallons

    float maxGrossWeight = 2950;  //Pounds
    float forwardCGLim = 82.1;  //Inches
    float aftCGLLim = 84.7; //inches

    cout << "Enter airplane empty weight (pounds): ";
    cin >> planeEmptyWeight;
    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> planeWeightEmptyMoment;
    cout << "Enter number of front seat occupants: ";
    cin >> numFrontSeatOcc;

    // Array to store weights of front seat occupants
    vector<float> frontSeatWeights(numFrontSeatOcc);
    float totalFrontWeight = 0;
    
    for (int i = 0; i < numFrontSeatOcc; ++i) {
        std::string iString = std::to_string(i+1);
        cout << "Enter weight of front seat occupant " + iString + " (pounds): ";
        cin >> frontSeatWeights[i];
        totalFrontWeight = totalFrontWeight + frontSeatWeights[i];
    }

    cout << "Enter front seat moment arm (inches): ";
    cin >> frontSeatMomentArm;
    cout << "Enter number of rear seat occupants: ";
    cin >> numRearSeatOcc;

    // Array to store weights of rear seat occupants
    vector<float> rearSeatWeights(numRearSeatOcc);
    float totalRearWeight = 0;
    for (int i = 0; i < numRearSeatOcc; ++i) {
        std::string iString = std::to_string(i+1);
        cout << "Enter weight of each rear seat occupant " + iString + " (pounds): ";
        cin >> rearSeatWeights[i];
        totalRearWeight = totalRearWeight + rearSeatWeights[i];
    }

    cout << "Enter rear seat moment arm (inches): ";
    cin >> rearSeatMomentArm;
    cout << "Enter number of gallons of usable fuel: ";
    cin >> gallonUsableFuel;
    cout << "Enter usable fuel weight per gallon (pounds): ";
    cin >> usableFuelPerGallon;
    cout << "Enter fuel tank moment arm (inches): ";
    cin >> fuelMomentArm;
    cout << "Enter baggage weight (pounds): ";
    cin >> baggageWeight;
    cout << "Enter baggage moment arm (inches): ";
    cin >> baggageMomentArm;

    float usableFuelWeight = gallonUsableFuel * usableFuelPerGallon;


    float totalWeight = planeEmptyWeight + totalFrontWeight + totalRearWeight + usableFuelWeight + baggageWeight;

    float totalMoment = planeWeightEmptyMoment + totalFrontWeight * frontSeatMomentArm + totalRearWeight * rearSeatMomentArm
        + usableFuelWeight * fuelMomentArm + baggageWeight * baggageMomentArm;
    
    cout << "\n";

    if (totalWeight > maxGrossWeight || totalMoment < forwardCGLim || totalMoment > aftCGLLim) {
        double fuelAdjustment = 0.0;

        cout << "The aircraft is out of design limits.\n";
        cout << "The old total weight was (pounds): " << fixed << setprecision(2) << totalWeight << endl;
        cout << "The old C.G. location  was (inches): " << fixed << setprecision(2) << totalMoment / totalWeight << endl;
        cout << "\n";
        if (totalWeight > maxGrossWeight) {
            fuelAdjustment = (totalWeight - maxGrossWeight) / usableFuelPerGallon;
        }
        double newGrossWeight = totalWeight - fuelAdjustment * usableFuelPerGallon;
        double newCGLocation = totalMoment / newGrossWeight;

        cout << "The aircraft new design limits are as follows.\n";
        cout << "Required fuel adjustment (gallons): " << fixed << setprecision(2) << fuelAdjustment << endl;
        cout << "New gross weight (punds): " << fixed << setprecision(2) << newGrossWeight << endl;
        cout << "New C.G. location (inches): " << fixed << setprecision(2) << newCGLocation << endl;
    }
    else {
        cout << "The aircraft is within design limits.\n";
        cout << "Gross weight (pounds): " << fixed << setprecision(2) << totalWeight << endl;
        cout << "C.G. location (inches): " << fixed << setprecision(2) << totalMoment / totalWeight << endl;
    }



    /*The following is Question 2 for the homework*/
    std::map<std::pair<std::string, std::string>, int> flightDistances;

    // Set the container with flight distances
    flightDistances[{"SCE", "PHL"}] = 160;
    flightDistances[{"SCE", "ORD"}] = 640;
    flightDistances[{"SCE", "EWR"}] = 220;



    /*Question 5*/
    float placeHolder = 0;
    std::string from;
    std::string to;
    cout << "Please enter a starting airport(SCE, EWR, PHL, or ORD):  ";
    cin >> from;
    cout << "Please enter a destination airport(SCE, EWR, PHL, or ORD): ";
    cin >> to;
    Plane plane(from, to, flightDistances);

    cout << "Please enter a flight speed: (mph) ";
    cin >> placeHolder;
    placeHolder = placeHolder / 3600;
    
    plane.setVel(placeHolder);

    float timestep = 10;
    float iterations = 1000;
    float position = 0.0;
    int time = 0;
    float distance = plane.getDistance();
    for (int i = 0; i < iterations; ++i) {
        if (distance-position>0)
        {
            plane.operate(timestep);
            position = plane.getPos();
            time += timestep;
            cout << "Time: " << time << " seconds, Position: " << position << " miles." << endl;
        }
        else
        {
            break;
        }
    }

}

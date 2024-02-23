#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;


//Question 3
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;
    //std::map<std::pair<std::string, std::string>, int> flightDistances;

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
        if (to == "SCE")
        {
            at_SCE = 0;
        }
        else
        {
            at_SCE = 1;
        }
        cout << "Plane created at " <<this << endl;
    }

    ~Plane() {
        cout << "Plane Destroyed.";
    }

    void operate(double dt) {
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

                swap(origin, destination);
                pos = 0.0;
            }
            else
            {
                swap(origin, destination);
                pos = 0.0;
            }   
        }
    }

    double getPos() {
        return pos;
    }
 
    std::string getOrigin() {
        return origin;
    }
 
    std::string getDestination() {
        return destination;
    }

    double getDistance()
    {  
        return distance;
    }

    bool isAtSCE() {
        return at_SCE;
    }

    double getVel() {
        return vel;
    }

    void setVel(double velocity) {
        vel = velocity;
    }
};



int main() {

    /*The following is Question 1 for the homework
    double planeEmptyWeight, usableFuelPerGallon, baggageWeight; //Pounds
    int numFrontSeatOcc, numRearSeatOcc; //No Unit
    double planeWeightEmptyMoment; //Pounds-inches
    double frontSeatMomentArm, rearSeatMomentArm, fuelMomentArm, baggageMomentArm; //Inches
    double gallonUsableFuel; //Gallons

    double maxGrossWeight = 2950;  //Pounds
    double forwardCGLim = 82.1;  //Inches
    double aftCGLLim = 84.7; //inches

    cout << "Enter airplane empty weight (pounds): ";
    cin >> planeEmptyWeight;
    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> planeWeightEmptyMoment;
    cout << "Enter number of front seat occupants: ";
    cin >> numFrontSeatOcc;

    // Array to store weights of front seat occupants
    vector<double> frontSeatWeights(numFrontSeatOcc);
    double totalFrontWeight = 0;
    
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
    vector<double> rearSeatWeights(numRearSeatOcc);
    double totalRearWeight = 0;
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

    double usableFuelWeight = gallonUsableFuel * usableFuelPerGallon;


    double totalWeight = planeEmptyWeight + totalFrontWeight + totalRearWeight + usableFuelWeight + baggageWeight;

    double totalMoment = planeWeightEmptyMoment + totalFrontWeight * frontSeatMomentArm + totalRearWeight * rearSeatMomentArm
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
    }*/



    /*The following is Question 2 for the homework*/
    std::map<std::pair<std::string, std::string>, int> flightDistances;

    // Set the container with flight distances
    flightDistances[{"SCE", "PHL"}] = 160;
    flightDistances[{"SCE", "ORD"}] = 640;
    flightDistances[{"SCE", "EWR"}] = 220;



    /*Question 5
    
    std::string from;
    std::string to;
    cout << "Please enter a starting airport(SCE, EWR, PHL, or ORD):  ";
    cin >> from;
    cout << "Please enter a destination airport(SCE, EWR, PHL, or ORD): ";
    cin >> to;
    Plane plane(from, to, flightDistances);

    double placeHolder = 0;
    cout << "Please enter a flight speed: (mph) ";
    cin >> placeHolder;
    placeHolder = placeHolder / 3600;
    
    plane.setVel(placeHolder);

    double timestep = 10;
    double iterations = 1000;
    double position = 0.0;
    int time = 0;
    double distance = plane.getDistance();
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
    }*/
/*--------------------------------------------------------------Question 6/7--------------------------------------------------------------------*/
class Plane;

class Pilot
{
Private:
	std::string name;
	Plane* myPlane; 

Public:
	Pilot(const std::string& pilotName, Plane* planePtr)
		name = pilotName;
        myPlane = planePtr;
// Prints out "Pilot ___ is at the gate, ready to board the plane. Memory Address: ____"
		{
			std::cout << "Pilot" << name << " is at the gate, ready to board the plane. Memory Address: " << myPlane << std::endl;
		}
// Prints out "Pilot ____ is out of the plane."
		~Pilot()
		{
			std::cout << "Pilot" << name << " is out of the plane." << std::endl;
		}
// getter for name of specific pilot
		std::string getName() const
		{
			return name;
		}
// function to control the plane
		void controlPlane(double timestep, int maxIterations);
};

class Plane
{
private:
	double pos;
	double vel;
	double distance;
	std::string origin;
	std::string destination;

public:
	Plane(const std::string& from, const std::string& to, double planeSpeed)
    {   
        pos = 0;
        vel = planeSpeed;
        distance = 0;
        origin = from;
        destination = to;
    }
// getter for position
	double getPos() const
	{
		return pos;
	}

	void operate(double dt)
	{
		pos += vel * dt;

		if (pos <= 0)
		{
			pos = 0
		}

		if (pos == 0)
		{
			std::cout << "Plane landed at SCE. Memory address: " << this << std::endl;
		}
	}
};

void Pilot::controlPlane(double timestep, int maxIterations)
{
	for (int i = 0, i < maxIterations; ++i)
	{
		std::cout << "Pilot " << name << " controlling the plane at memory address: " << myPlane << std::endl;
		myPlane->operate(timestep);

		if (myPlane->getPos() == 0)
		{
			break;
		}
	}
}

int main()
{
	Plane plane = ("SCE", "PHL", 450);

	std::shared_ptr<Pilot> pilot1 = std::make_shared<Pilot>("Pilot-in-Command", &plane);
	std::shared_ptr<Pilot> pilot2 = std::make_shared<Pilot>("Co-Pilot", &plane);

	double timestep = 50;
	int maxIterations = 10; // should be 1000 as in question 5, reduced for easier/smoother tests of code

	while (true) {
		pilot1->controlPlane(timestep, maxIterations);
		std::cout << "Plane is at SCE" << std::endl;

		pilot2->controlPlane(timestep, maxIterations);
		std::cout << "Plane is at SCE" << std::endl;

		plane = std::make_shared<Plane>("SCE", "PHL", 450);

		std::swap(pilot1, pilot2);

	}

	return 0;
}

/*-------------------------------------------------------------------Question 8-----------------------------------------------------------------*/
class Plane;

class Pilot
{
Private:
	std::string name;
	std::shared_ptr<Plane> myPlane; 

Public:
	Pilot(const std::string& pilotName, std::shared_ptr<Plane> planePtr)
		name = pilotName;
        myPlane = planePtr;
// Prints out "Pilot ___ is at the gate, ready to board the plane. Memory Address: ____"
		{
			std::cout << "Pilot" << name << " is at the gate, ready to board the plane. Memory Address: " << planePtr << std::endl;
		}
// Prints out "Pilot ____ is out of the plane."
		~Pilot()
		{
			std::cout << "Pilot" << name << " is out of the plane." << std::endl;
		}

		std::string getName() const
		{
			return name;
		}

		void controlPlane(double timestep, int maxIterations);
};

class Plane
{
private:
	double pos;
	double vel;
	double distance;
	std::string origin;
	std::string destination;

public:
	Plane(const std::string& from, const std::string& to, double planeSpeed)
    {   
        pos = 0;
        vel = planeSpeed;
        distance = 0;
        origin = from;
        destination = to;
    }

	~Plane()
	{}

	double getPos() const
	{
		return pos;
	}

	void operate(double dt)
	{
		pos += vel * dt;

		if (pos <= 0)
		{
			pos = 0
		}

		if (pos == 0)
		{
			std::cout << "Plane landed at SCE. Memory address: " << this << std::endl;
		}
	}
};

void Pilot::controlPlane(double timestep, int maxIterations)
{
	for (int i = 0, i < maxIterations; ++i)
	{
		std::cout << "Pilot " << name << " controlling the plane at memory address: " << myPlane.get() << std::endl;
		myPlane->operate(timestep);

		if (myPlane->getPos() == 0)
		{
			break;
		}
	}
}

int main()
{
	auto plane = std::make_shared<Plane>("SCE", "PHL", 450);

	auto pilot1 = std::make_shared<Pilot>("Pilot-in-Command", plane);
	auto pilot2 = std::make_shared<Pilot>("Co-Pilot", plane);

	double timestep = 50;
	int maxIterations = 10; // should be 1000 as in question 5, reduced for easier/smoother tests of code


	while (true) {
		pilot1->controlPlane(timestep, maxIterations);
		std::cout << "Plane is at SCE" << std::endl;

		pilot2->controlPlane(timestep, maxIterations);
		std::cout << "Plane is at SCE" << std::endl;

		plane = std::make_shared<Plane>("SCE", "PHL", 450);

		std::swap(pilot1m pilot2);

	}

	return 0;
}

    
/*    std::string from;
    std::string to;
    cout << "Please enter a starting airport(SCE, EWR, PHL, or ORD):  ";
    cin >> from;
    cout << "Please enter a destination airport(SCE, EWR, PHL, or ORD): ";
    cin >> to;
    Plane plane2(from, to, flightDistances);
    
    std::string name1, name2;
    cout << "What is the name of the captain: ";
    cin >> name1;

    cout << "What is the name of the co-captain: ";
    cin >> name2;

    Pilot pilot1(name1, &plane2);
    Pilot pilot2(name2, &plane2);

    int trips;
    cout << "Please enter the number of trips the plane will be making: ";
    cin >> trips;

    cout << "" << endl;

    int timestep = 10;
    plane2.setVel(400);
    
    std::string checkName = name2;
    for (int i = 0; i <= trips; ++i)
    {
        if (plane2.isAtSCE() == 1)
        {
            cout << "The plane " << &plane2 << " is at SCE." << endl;
        }
        else
        {
            if (to == "SCE")
            {
                cout << "The plane " << &plane2 << " is at " << from << "." << endl;
            }
            else
            {
                cout << "The plane " << &plane2 << " is at " << to << "." << endl;
            }
        }

        if (checkName == pilot1.getName())
        {
            cout << "Pilot " << name2 << " with certificate number " << &name2 << " has taken control of the plane " << &plane2  << "." << endl;
            cout << "" << endl;
            checkName = pilot2.getName();
        }
        else
        {
            cout << "Pilot " << name1 << " with certificate number " << &name1 << " has taken control of the plane " << &plane2 << "." << endl;
            cout << "" << endl;
            checkName = pilot1.getName();
        }

        while (plane2.getDistance() >= plane2.getPos())
        {
            plane2.operate(timestep);
        }
    }
}
*/

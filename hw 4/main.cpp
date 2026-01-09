#include <iostream>
#include "TimeTravelEngine.h"

using namespace std;

int main()
{
    TimeTravelEngine engine;

    engine.printAllBranches();
    cout << endl;

    engine.deleteTimeBranch(1);
    cout << endl;

    const int b1 = 1;
    const int b2 = 2;
    const int b3 = 3;

    engine.createTimeBranch(3, 2, "Home", b1);
    engine.createTimeBranch(2, 2, "Town", b2);
    engine.createTimeBranch(2, 3, "Village", b3);
    engine.createTimeBranch(5, 5, "Nowhere", b1);
    cout << endl;

    engine.printAllBranches();
    cout << endl;

    engine.travelTo(b1, "Forest");
    engine.travelTo(b1, "Castle");
    engine.travelTo(42, "Lab");
    engine.travelTo(b2, "Ruins");
    engine.travelTo(b2, "Gate");
    engine.travelTo(b2, "Tower");
    cout << endl;

    engine.placeTimeStone(b1);
    engine.activateTimeStone(b3);
    cout << endl;

    engine.travelTo(b3, "Field");
    engine.travelTo(b3, "Forest");
    engine.placeTimeStone(b3);
    engine.rewind(b3, 1);
    engine.placeTimeStone(b3);
    engine.activateTimeStone(b3);
    engine.activateTimeStone(b3);
    cout << endl;

    engine.rewind(b1, 1);
    engine.rewind(b1, 3);
    cout << endl;

    engine.printTimeBranch(b1);
    cout << endl;

    engine.fastForward(b1, 5);
    cout << endl;

    engine.printTimeBranch(b1);
    cout << endl;

    engine.mergeBranches(10, 11, 8);
    engine.mergeBranches(b1, b3, 8);

    const int m1 = 4;
    const int m2 = 5;
    const int mergedId = 8;

    engine.createTimeBranch(2, 2, "Home", m1);
    engine.createTimeBranch(2, 2, "Home", m2);

    engine.travelTo(m1, "Forest");
    engine.travelTo(m2, "Forest");

    engine.mergeBranches(m1, m2, b1);
    engine.mergeBranches(m1, m2, mergedId);
    cout << endl;

    engine.printAllBranches();
    cout << endl;

    engine.deleteTimeBranch(mergedId);
    engine.deleteTimeBranch(99);
    cout << endl;

    engine.travelTo(b2, "Portal");
    cout << endl;

    engine.rewind(b2, 1);
    engine.rewind(b2, 5);
    cout << endl;

    engine.printAllBranches();
    cout << endl;

    return 0;
}
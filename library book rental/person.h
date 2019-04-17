//begin person.h
#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include <string>
using namespace std;

class Person
{
private:
    string firstName;
    string lastName;
    int    cardID;
    bool active;

public:
    Person(string lName, string fName, int card, bool active);
    string getFirstName();
    string getLastName();
    int getID();
    bool getActive();
    string fullName();
    void setActive(bool activator);
};
#endif // end person.h

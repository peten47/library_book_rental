#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "person.cpp"
#include "book.cpp"
#include "person.h"
#include "book.h"

using namespace std;

int main() {

    vector<Book *> books;
    vector<Person *> cardholders;

    int nextCard = readData(cardholders, books);

    rentals(cardholders, books);


    int choice;
    do
    {
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                checkout(cardholders, books);

                break;

            case 2:
                bookReturn(cardholders, books);

                break;

            case 3:
                allBooks(books);

                break;

            case 4:
                allRentals(cardholders, books);

                break;

            case 5:
                idRentals(cardholders, books);

                break;

            case 6:
                newCard(nextCard, cardholders);
              
                break;

            case 7:
                closeCard(cardholders);
                // Close library card
                break;

            case 8:
                cout << "writing data..." << endl;
                writeData(cardholders, books);
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
    } while(choice != 8);
    return 0;

}

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

int readData (vector<Person*> & cardholders, vector<Book*> & books)
{
    string fname;
    string lname;
    int cardid;
    bool active;
    int temp = 0;

    int bookid;
    string booktitle;
    string authorname;
    string category;
    string line;
    int i = 0;

    ifstream input;

    input.open("persons.txt");


    if (input.is_open())
    {
        while (!input.eof())
        {
            input >> cardid >> active >> fname >> lname;

            Person * personPtr;
            personPtr = new Person(fname, lname, cardid, active);

            cardholders.push_back(personPtr);

            temp = cardid;

            personPtr = NULL;
            delete personPtr;
        }
    }



    cardholders.pop_back();

    input.close();

    input.open("books.txt");


    if (input.is_open())
    {
        while (getline(input, line))
        {

            if (i == 0)
            {
                bookid = stoi(line);
            }
            else if (i == 1)
            {
                booktitle = line;
            }
            else if (i == 2)
            {
                authorname = line;
            }
            else if (i == 3)
            {
                category = line;
                Book * bookPtr;
                bookPtr = new Book(bookid, booktitle, authorname, category);

                books.push_back(bookPtr);

                bookid = 0;
                booktitle = " ";
                authorname = " ";
                category = " ";

                bookPtr = NULL;
                delete bookPtr;


            }

            i++;

            if (i == 5)
            {
                i = 0;

            }

        }
    }

    input.close();

    return temp +1;
}

void rentals(vector<Person* > cardholders, vector <Book* > &books)
{
    ifstream input;

    input.open("rentals.txt");

    int bookid;
    int cardid;
    if (input.is_open())
    {
        while (!input.eof())
        {
            input >> bookid >> cardid;


            Person * PersonPtr;


            for (int j = 0; j < cardholders.size(); j++)
            {
                if (cardid == cardholders.at(j)->getID())
                {

                    PersonPtr = cardholders.at(j);

                    for (int k = 0; k < books.size(); k++)
                    {
                        if (bookid == books.at(k)->getID())
                        {
                            books.at(k) -> setPersonPtr(PersonPtr);


                        }
                    }
                }
            }

            PersonPtr = NULL;
            delete PersonPtr;


        }
    }

    input.close();

}



void output (vector<Person* > cardholders, vector <Book* > books)
{
    string fname;
    string lname;
    int cardid;
    bool active;

    for (int i = 0; i < cardholders.size(); i++)
    {
        cout << cardholders.at(i) -> fullName() << endl;
        cout << cardholders.at(i) -> getID() << endl;
        cout << cardholders.at(i) -> getActive() << endl;
    }

    for (int i = 0; i < books.size(); i++)
    {
        cout << books.at(i) -> getTitle() << endl;
        cout << books.at(i) -> getID() << endl;
        cout << books.at(i) -> getAuthor() << endl;
        cout << books.at(i) -> getCategory() << endl;
    }
}

void checkout(vector<Person*> & cardholders, vector<Book*> & books)
{
    int cardid;
    int bookid;
    bool personflag = false;
    bool bookflag = false;
    cout << "Please enter the card ID: ";
    cin >> cardid;

    for (int i = 0; i < cardholders.size(); i++)
    {
        if (cardid == cardholders.at(i) -> getID())
        {
            cout << "Cardholder: " << cardholders.at(i) -> fullName() << endl;
            personflag = true;
            cout << "Please enter the book ID: ";
            cin >> bookid;
            for (int j = 0; j < books.size(); j++)
            {
                if (bookid == books.at(j)->getID() && books.at(j)->getPersonPtr() == 0)
                {
                    cout << "Title: " << books.at(j)->getTitle() << endl;
                    books.at(j)->setPersonPtr(cardholders.at(i));
                    cout << "Rental Completed" << endl;
                    bookflag = true;
                    return;
                }
                else if (bookid == books.at(j)->getID() && books.at(j)->getPersonPtr() != 0)
                {
                    cout << "Book already checked out" << endl;
                    return;
                }
                else if (bookflag == false && (j+1) == books.size())
                {
                    cout << "Book ID not found" << endl;
                    return;
                }
            }
        }
        else if (personflag == false && (i+1) == cardholders.size())
        {
            cout << "Card ID not found" << endl;

            return;
        }
    }

    cout << "Please enter the book ID: ";
    cin >> bookid;

    for (int j = 0; j < books.size(); j++)
    {
        if (bookid == books.at(j) -> getID())
        {
            cout << "Title: " << books.at(j) -> getTitle() << endl;
            bookflag = true;
        }

        else if (bookflag == false && (j+1) == books.size())
        {
            cout << "Book ID not found" << endl;

            return;
        }
    }


}

void bookReturn(vector<Person*> cardholders, vector<Book*> & books)
{
    int bookid;
    bool bookflag = false;
    cout << "Please enter the book ID to return: ";
    cin >> bookid;

    for (int i = 0; i < books.size(); i++)
    {
        if (bookid == books.at(i) -> getID())
        {
            cout << "Title: " << books.at(i)->getTitle() << endl;
            books.at(i)->setPersonPtr(0);
            bookflag = true;
            cout << "Return Completed" << endl;
        }

        else if (bookflag == false && (i+1) == books.size())
        {
            cout << "Book ID not found" << endl;
        }
    }


}

void allBooks(vector <Book* > books)
{
    bool flag = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getPersonPtr() == 0)
        {
            cout << "Book ID: " << books.at(i) ->getID() << endl;
            cout << "Title " << books.at(i) -> getTitle() << endl;
            cout << "Author: " << books.at(i) -> getAuthor() << endl;
            cout << "Category: " << books.at(i) -> getCategory() << endl << endl;
            flag = true;
        }
        else if (flag == false && (i+1) == books.size())
        {
            cout << "No available books" << endl;
        }
    }

}

void allRentals(vector<Person* > cardholders, vector <Book* > books)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getPersonPtr() != 0)
        {
            for (int j = 0; j < cardholders.size(); j++)
            {
                if (cardholders.at(j) == books.at(i)-> getPersonPtr())
                {
                    cout << "Book ID: " << books.at(i) -> getID() << endl;
                    cout << "Title: " << books.at(i) -> getTitle() << endl;
                    cout << "Author: " << books.at(i) -> getAuthor() << endl;
                    cout << "Cardholder: " << cardholders.at(j) -> fullName() << endl;
                    cout << "Card ID: " << cardholders.at(j) -> getID() << endl << endl;
                 //   cout << "Book ID: " << books.at(i) -> getTitle() << " Person is " << cardholders.at(j)->fullName() << endl;
                }
            }
        }
    }

}

void idRentals(vector<Person* > cardholders, vector <Book* > books)
{
    int cardid;
    cout << "Please enter card ID: ";
    cin >> cardid;

    for (int i = 0; i < cardholders.size(); i++)
    {
        bool flag = false;
        if (cardholders.at(i) -> getID() == cardid)
        {
            cout << "Cardholder: " << cardholders.at(i) -> fullName() << endl << endl;

            for (int j = 0; j < books.size(); j++)
            {
                if (books.at(j)-> getPersonPtr() == cardholders.at(i))
                {
                    cout << "Book: ID: " << books.at(j)->getID() << endl;
                    cout << "Title: " << books.at(j)->getTitle() << endl;
                    cout << "Author: " << books.at(j)->getAuthor() << endl << endl;
                    flag = true;
                }

                else if (flag == false && (j+1) == books.size())
                {
                    cout << "No books currently checked out" << endl;
                }
            }


        }
    }
}

void writeData(vector<Person* > cardholders, vector <Book* > books)
{
    string fname;
    string lname;
    int cardid;
    bool active;

    ofstream output;

    output.open("persons.txt");

    if (output.is_open())
    {
        for (int j = 0; j < cardholders.size(); j++)
        {
            output << cardholders.at(j) -> getID() << " ";
            output << cardholders.at(j) -> getActive() << " ";
            output << cardholders.at(j) -> fullName() << endl;

        }
    }

    output.close();

    output.open("Rentals.txt");
    if (output.is_open())
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books.at(i)->getPersonPtr() != 0 )
            {
                output << books.at(i) -> getID() << " ";

                for (int k = 0; k < cardholders.size(); k++)
                {
                    if (cardholders.at(k) == books.at(i)->getPersonPtr())
                    {
                        output << cardholders.at(k)->getID() << endl;
                    }
                }
            }
        }
    }

    output.close();

}

void newCard(int nextCard, vector<Person*> & cardholders)
{
    string fname;
    string lname;
    bool flag = false;
    cout << "Please enter first name: ";
    cin >> fname;
    cout << "please enter last name: ";
    cin >> lname;

    Person * personPtr;

    for (int i = 0; i < cardholders.size(); i++)
    {
        if ((fname + ' ' + lname) == cardholders.at(i)->fullName())
        {
            cardholders.at(i) -> setActive(1);
            flag = true;
            cout << "Card ID " << cardholders.at(i)->getID() << " active" << endl;
            cout << "Cardholder: " << cardholders.at(i) -> fullName() << endl;
        }

        else if (flag == false && (i+1) == cardholders.size())
        {
            personPtr = new Person(fname, lname, nextCard, 1);
            cardholders.push_back(personPtr);

            cout << "Card ID " << nextCard << " active" << endl;

            cout << "Cardholder: " << cardholders.back() -> fullName() << endl;
        }
    }


}

void closeCard(vector<Person*> & cardholders)
{
    int cardid;
    string decision;
    bool flag = false;

    cout << "Please enter the card ID: ";
    cin >> cardid;

    for (int i = 0; i < cardholders.size(); i++)
    {
        if (cardid == cardholders.at(i)->getID())
        {
            flag = true;
            cout << "Cardholder: " << cardholders.at(i)->fullName() << endl;

            if (cardholders.at(i)->getActive() == true)
            {
                cout << "Are you sure you want to deactive card (y/n)? ";
                cin >> decision;

                if (decision == "y")
                {
                    cardholders.at(i)->setActive(false);


                }
                else if (decision == "n")
                {
                    cout << "Card ID not found" << endl;
                }
            }

            else if (cardholders.at(i)->getActive() == false)
            {
                cout << "Card ID is already inactive" << endl;
            }

        }
        else if (flag == false && (i+1) == cardholders.size())
        {
            cout << "Card ID not found" << endl;
        }
    }


}

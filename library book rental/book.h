//begin book.h
#ifndef BOOK_H
#define BOOK_H
#include "person.h"

#include <string>
using namespace std;

class Book
{
private:
    int ID;
    string title;
    string author;
    string category;
    Person * personPtr = nullptr;

public:
    Book(int bookID, string booktitle, string bookauthor, string bookcategory);
    int getID();
    string getTitle();
    string getAuthor();
    string getCategory();
    void setPersonPtr(Person * ptr);
    Person * getPersonPtr();
};
#endif // end book.h

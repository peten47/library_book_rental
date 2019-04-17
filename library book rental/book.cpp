#include "book.h"

Book::Book(int bookID, string booktitle, string bookauthor, string bookcategory)
{
    ID = bookID;
    title = booktitle;
    author = bookauthor;
    category = bookcategory;
}


int Book::getID()
{
    return ID;
}

string Book::getTitle()
{
    return title;
}

string Book::getAuthor()
{
    return author;
}

string Book::getCategory()
{
    return category;
}

void Book::setPersonPtr(Person *ptr)
{
    personPtr = ptr;
}

Person * Book::getPersonPtr()
{
    return personPtr;

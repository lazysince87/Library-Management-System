
/*

    Title: Library Management System Project

    Authors: Diego Munoz Bodden, Fabian Ho Chang, and Thuy Le

    Description:
        This project is meant to simulate the functions of a library via the use of a Library class. This Library class
        is then used to both store and operate on Textbook and Fiction Book objects (created by their respective classes, and
        also being derived from a general Book class). Using the Library, we can add a book, remove a book, search for a book
        by title or author, display all books, borrow a book, or return a book.

        The concepts this project shows are Vectors, Pointers, Classes & Objects, Class Inheritance, and Exception Handling.
    
    Features:
        1. Book Class
            Attributes: Title, Author, ISBN, Genre, Availability
            Methods: Constructor, Display book details, Display availability, Update availability,
                     Get title, Get author, Get ISBN, Get Availability
        
        2. Textbook Class (derived from Book Class)
            Attributes: Course, Edition 
            Methods: Constructor, Display textbook details 
        
        3. FictionBook Class (derived from Book Class)
            Attributes: Main character, Setting 
            Methods: Constructor, Display fiction book details 
        
        4. Library Class
            Attributes: Vector of textbook pointers, vector of fiction book pointers
            Methods: Add a book (overloaded for both textbook and fiction), Remove textbook, Remove fiction book,
                     Search for a book by title or author, Display all books, Borrow or return a book

        5. Main Function
            Description: Menu (switch statement) by which the methods of the Library Class are utilized
            Primary necessary variables:
                Library object
                Textbook pointer
                FictionBook pointer
                Integer variables choice, bookType, searchChoice, borrowOrReturnChoice, isbn
                String variables title, author, genre, course, edition, mainCharacter, setting
        
        6. Exception Handling
            Errors that are accounted for:
                Empty string (when adding book)
                Negative ISBN (when adding book)
                Duplicate ISBN for books that aren't the same (when adding book)
                Book not found (when removing, searching for, borrowing, or returning a book)
                Book not borrowable (when borrowing a book)
                Book not returnable (when returning a book)
            Addition errors that are accounted for but are not exceptions:
                Invalid input for [menu] choice
                Invalid input for bookType
                Invalid input for searchChoice
                Invalid input for borrowOrReturnChoice
            Note:
                Books that have the same title and author are assumed to have the same content

*/


// Including necessary libraries
#include <iostream>
#include <vector>
using namespace std;


// Book base class
class Book {
    
    // Private members
    private:
        string title, author, genre;
        int isbn;
        bool availability;
    
    // Public member functions
    public:
        
        // Constructor with arguments
        Book(string t, string a, int i, string g) {
            
            title = t;
            author = a;
            isbn = i;
            genre = g;
            availability = true;

        }

        // Function to display book details
        void displayBookDetails() {
            
            cout << "\t" << title << " is made by " << author << "; its genre is " << genre << "." << endl;
            cout << "\tIts ISBN is " << isbn << "." << endl;

        }

        // Function to display a book's availability
        void displayAvailability() {
            
            if (availability) {
                cout << "\t" << title << " is available." << endl;
            } else {
                cout << "\t" << title << " is not available." << endl;
            }

        }

        // Function to update a book's availability
        void updateAvailability(bool av) {

            availability = av;

        }

        // Function to return a book's title
        string getTitle() {

            return title;

        }

        // Function to return a book's author
        string getAuthor() {

            return author;
            
        }

        // Function to return a book's ISBN
        int getISBN() {

            return isbn;

        }

        // Function to get a book's availability
        bool getAvailability() {

            return availability;

        }

};


// Textbook class derived from Book base class
class Textbook : public Book {

    // Private members
    private:
        string course, edition;
    
    // Public member functions
    public:
        
        // Exception classes:
        //  Exception class to handle empty string
        class emptyStringError {};
        //  Exception class to handle negative ISBN
        class negativeISBNerror {};

        // Constructor with arguments; also calls base constructor with arguments
        Textbook(string t, string a, int i, string g, string c, string e) : Book(t, a, i, g) {
            
            // Throw exception if empty string
            if (t == "" || a == "" || g == "" || c == "" || e == "") {
                
                throw emptyStringError();
            
            // Throw exception if negative ISBN
            } else if (i < 0) {
                
                throw negativeISBNerror();

            } else {

                course = c;
                edition = e;

            }

        }

        // Function to display textbook details; also calls function to display book details from Book class
        void displayTextbookDetails() {

            displayBookDetails();
            cout << "\tThis is a Textbook. The Course it's for is " << course << " and the Edition is " << edition << "." << endl;

        }

};


// FictionBook class derived from Book base class
class FictionBook : public Book {

    // Private members
    private:
        string mainCharacter, setting;
    
    // Public member functions
    public:

        // Exception classes:
        //  Exception class to handle empty string
        class emptyStringError {};
        //  Exception class to handle negative ISBN
        class negativeISBNerror {};

        // Constructor with arguments; also calls base constructor with arguments
        FictionBook(string t, string a, int i, string g, string m, string s) : Book(t, a, i, g) {
            
            // Throw exception if empty string
            if (t == "" || a == "" || g == "" || m == "" || s == "") {
                
                throw emptyStringError();
            
            // Throw exception if negative ISBN
            } else if (i < 0) {
                
                throw negativeISBNerror();

            } else {

                mainCharacter = m;
                setting = s;

            }

        }

        // Function to display fiction book details; also calls function to display book details from Book class
        void displayFictionBookDetails() {

            displayBookDetails();
            cout << "\tThis is a Fiction Book. The Main Character is " << mainCharacter << " and the setting is " << setting << "." << endl;

        }
        
};

// Library class
class Library {
    
    // Private members
    private:

        // Creating two different vectors; one for Textbooks, and one for Fiction Books
        //  These will store pointers to either Textbook or Fiction Book objects
        vector<Textbook*> textbookSection;
        vector<FictionBook*> fictionBookSection;

    // Public member functions
    public:

        // Exception classes:
        //  Exception class to handle a book with a duplicate ISBN that isn't the same book
        class duplicateISBN {};
        //  Exception class to handle a book not being found
        class bookNotFoundError {};
        //  Exception class to handle a book not being able to be borrowed
        class bookNotBorrowableError {};
        //  Exception class to handle a book not being able to be returned
        class bookNotReturnableError {};

        // Overloaded functions to add either a Textbook or Fiction Book
        void addBook(Textbook* b) {
            
            // Declaring necessary variables (to check for duplicate ISBN error)
            string tempTitle, tempAuthor;
            int tempISBN;

            // Loop to go through Textbook vector
            for (int i = 0; i < textbookSection.size(); i++) {

                tempTitle = textbookSection[i]->getTitle();
                tempAuthor = textbookSection[i]->getAuthor();
                tempISBN = textbookSection[i]->getISBN();

                // If the ISBN of a given Textbook in the vector is the same as the one of the Textbook we are trying to add,
                // AND it is true that their titles or authors are not the same, then throw an error for duplicate ISBN
                if ( (b->getISBN() == tempISBN) && ( (b->getTitle() != tempTitle) || (b->getAuthor() != tempAuthor) ) ) {

                    throw duplicateISBN();

                }

            }

            // If no error occurs, we can add the Textbook
            textbookSection.push_back(b);

        }
        void addBook(FictionBook* b) {
            
            // Declaring necessary variables (to check for duplicate ISBN error)
            string tempTitle, tempAuthor;
            int tempISBN;

            // Loop to go through Fiction Book vector
            for (int i = 0; i < fictionBookSection.size(); i++) {

                tempTitle = fictionBookSection[i]->getTitle();
                tempAuthor = fictionBookSection[i]->getAuthor();
                tempISBN = fictionBookSection[i]->getISBN();

                // If the ISBN of a given Fiction Book in the vector is the same as the one of the Fiction Book we are trying to add,
                // AND it is true that their titles or authors are not the same, then throw an error for duplicate ISBN
                if ( (b->getISBN() == tempISBN) && ( (b->getTitle() != tempTitle) || (b->getAuthor() != tempAuthor) ) ) {

                    throw duplicateISBN();

                }

            }
            
            // If no error occurs, we can add the Fiction Book
            fictionBookSection.push_back(b);

        }

        // Function to remove Textbook
        Textbook* removeTextbook(string title, string author) {

            // Declaring necessary variables
            Textbook* txtPtr;
            string tempTitle, tempAuthor;

            // Loop to go through Textbook vector
            //  Search for matching title and author
            for (int i = 0; i < textbookSection.size(); i++) {

                tempTitle = textbookSection[i]->getTitle();
                tempAuthor = textbookSection[i]->getAuthor();

                // If match found, remove Textbook from vector and return the pointer so we can delete the object
                if ( (title == tempTitle) && (author == tempAuthor) ) {

                    txtPtr = textbookSection[i];
                    textbookSection.erase(textbookSection.begin() + i);
                    return txtPtr;

                }

            }

            throw bookNotFoundError();
        
        }
        // Function to remove Fiction Book
        FictionBook* removeFictionBook(string title, string author) {

            // Declaring necessary variables
            FictionBook* ficPtr;
            string tempTitle, tempAuthor;

            // Loop to go through Fiction Book vector
            //  Search for matching title and author
            for (int i = 0; i < fictionBookSection.size(); i++) {

                tempTitle = fictionBookSection[i]->getTitle();
                tempAuthor = fictionBookSection[i]->getAuthor();

                // If match found, remove Fiction Book from vector and return the pointer so we can delete the object
                if ( (title == tempTitle) && (author == tempAuthor) ) {

                    ficPtr = fictionBookSection[i];
                    fictionBookSection.erase(fictionBookSection.begin() + i);
                    return ficPtr;

                }

            }

            // If match not found, throw exception for book not being found
            throw bookNotFoundError();
        
        }

        // Function for searching for a book
        void bookSearch(string title, string author, int bookType, int searchChoice) {
            
            // Searching for Textbook
            if (bookType == 1) {

                // Vector to store textbooks with matching titles
                vector<Textbook*> matchingTextbooks;

                // Searching for Textbook by Title
                if (searchChoice == 1) {

                    // Declaring necessary variable
                    string tempTitle;

                    // Loop to go through Textbook vector
                    //  Search for matching title
                    for (int i = 0; i < textbookSection.size(); i++) {

                        tempTitle = textbookSection[i]->getTitle();

                    // If match found, add it to list of matches
                        if (title == tempTitle) {

                            matchingTextbooks.push_back(textbookSection[i]);

                        }

                    }
                
                // Searching for Textbook by Author
                } else if (searchChoice == 2) {

                    // Declaring necessary variable
                    string tempAuthor;

                    // Loop to go through Textbook vector
                    //  Search for matching author
                    for (int i = 0; i < textbookSection.size(); i++) {

                        tempAuthor = textbookSection[i]->getAuthor();

                    // If match found, add it to list of matches
                        if (author == tempAuthor) {

                            matchingTextbooks.push_back(textbookSection[i]);

                        }

                    }
                    
                }
                
                // Throw error if no matches
                if (matchingTextbooks.size() == 0) {

                    throw bookNotFoundError();
                
                // Otherwise, display details
                } else {

                    cout << "\nThere are " << matchingTextbooks.size() << " Textbook(s) with this title or author:\n" << endl;
                    // Loop to display details of all Textbooks of matching title or author
                    for (int i = 0; i < matchingTextbooks.size(); i++) {
                        
                        matchingTextbooks[i]->displayTextbookDetails();
                        matchingTextbooks[i]->displayAvailability();
                        cout << "" << endl;

                    }

                }
                
            // Searching for Fiction Book
            } else if (bookType == 2) {

                // Vector to store textbooks with matching authors
                vector<FictionBook*> matchingFictionBooks;
                
                // Searching for Fiction Book by Title
                if (searchChoice == 1) {

                    // Declaring necessary variable
                    string tempTitle;

                    // Loop to go through Fiction Book vector
                    //  Search for matching title
                    for (int i = 0; i < fictionBookSection.size(); i++) {

                        tempTitle = fictionBookSection[i]->getTitle();

                    // If match found, add it to list of matches
                        if (title == tempTitle) {

                            matchingFictionBooks.push_back(fictionBookSection[i]);

                        }

                    }
                
                // Searching for Fiction Book by Author
                } else if (searchChoice == 2) {

                    // Declaring necessary variable
                    string tempAuthor;

                    // Loop to go through Fiction Book vector
                    //  Search for matching author
                    for (int i = 0; i < fictionBookSection.size(); i++) {

                        tempAuthor = fictionBookSection[i]->getAuthor();

                    // If match found, add it to list of matches
                        if (author == tempAuthor) {

                            matchingFictionBooks.push_back(fictionBookSection[i]);

                        }

                    }
                    
                }

                // Throw error if no matches
                if (matchingFictionBooks.size() == 0) {

                    throw bookNotFoundError();
                
                // Otherwise, display details
                } else {
                    
                    cout << "\nThere are " << matchingFictionBooks.size() << " Fiction Book(s) with this title or author:\n" << endl;
                    // Loop to display details of all Fiction Books of matching title or author
                    for (int i = 0; i < matchingFictionBooks.size(); i++) {
                        
                        matchingFictionBooks[i]->displayFictionBookDetails();
                        matchingFictionBooks[i]->displayAvailability();
                        cout << "" << endl;

                    }

                }
                
            }

        }

        // Function to display all books
        void displayBooks() {

            // Displaying Textbooks:
            cout << "\nThere are " << textbookSection.size() << " Textbook(s):\n" << endl;
            // Loop to display details of all Textbooks
            for (int i = 0; i < textbookSection.size(); i++) {
                        
                textbookSection[i]->displayTextbookDetails();
                textbookSection[i]->displayAvailability();
                cout << "" << endl;

            }

             // Displaying Fiction Books:
            cout << "\nThere are " << fictionBookSection.size() << " Fiction Book(s):\n" << endl;
            // Loop to display details of all Fiction Books
            for (int i = 0; i < fictionBookSection.size(); i++) {
                        
                fictionBookSection[i]->displayFictionBookDetails();
                fictionBookSection[i]->displayAvailability();
                cout << "" << endl;

            }

        }

        // Function to borrow or return a book
        void borrowOrReturn(string title, string author, int bookType, int borrowOrReturnChoice) {
            
            // Declaring necessary variables
            string tempTitle, tempAuthor;
            int tempIndex;
            bool tempAvailability;
            //  Vector to store matching book indexes in case there are duplicates
            vector<int> matchingBookIndexes;

            // For Textbooks:
            if (bookType == 1) {

                // Loop to go through Textbook vector
                //  Search for matching title and author
                for (int i = 0; i < textbookSection.size(); i++) {

                    tempTitle = textbookSection[i]->getTitle();
                    tempAuthor = textbookSection[i]->getAuthor();

                    // If match found, add it to list of matches/duplicates
                    if ( (title == tempTitle) && (author == tempAuthor) ) {
                        
                        matchingBookIndexes.push_back(i);

                    }

                }

                // Throw error if no matches
                if (matchingBookIndexes.size() == 0) {

                    throw bookNotFoundError();

                // If we are borrowing a book...
                } else if (borrowOrReturnChoice == 1) {
                    
                    // Loop to look through book matches/duplicates for an available one to borrow
                    for (int i = 0; i < matchingBookIndexes.size(); i++) {
                        
                        // Checking if one of the matches/duplicates is available
                        tempIndex = matchingBookIndexes[i];
                        tempAvailability = textbookSection[tempIndex]->getAvailability();
                        
                        // If it is, stop loop early to borrow only that duplicate
                        if (tempAvailability) {

                            break;

                        }

                    }

                    // If book available, update availability and comfirm success
                    if (tempAvailability) {

                        textbookSection[tempIndex]->updateAvailability(false);
                        cout << "\nThe book has been borrowed successfully!\n" << endl;

                    // Otherwise, throw error
                    } else {

                        throw bookNotBorrowableError();

                    }

                // If we are returning a book...
                } else if (borrowOrReturnChoice == 2) {
                    
                    // Loop to look through book matches/duplicates for an available one to return
                    for (int i = 0; i < matchingBookIndexes.size(); i++) {
                        
                        // Checking if one of the matches/duplicates is not available
                        tempIndex = matchingBookIndexes[i];
                        tempAvailability = textbookSection[tempIndex]->getAvailability();
                        
                        // If it is not, stop loop early to return only that duplicate
                        if (!tempAvailability) {

                            break;

                        }

                    }

                    // If book is not available, update availability and comfirm success
                    if (!tempAvailability) {

                        textbookSection[tempIndex]->updateAvailability(true);
                        cout << "\nThe book has been returned successfully!\n" << endl;

                    // Otherwise, throw error
                    } else {

                        throw bookNotReturnableError();

                    }

                }

            // For Fiction Books...
            } else if (bookType == 2) {

                // Loop to go through Fiction Book vector
                //  Search for matching title and author
                for (int i = 0; i < fictionBookSection.size(); i++) {

                    tempTitle = fictionBookSection[i]->getTitle();
                    tempAuthor = fictionBookSection[i]->getAuthor();

                    // If match found, add it to list of matches/duplicates
                    if ( (title == tempTitle) && (author == tempAuthor) ) {
                        
                        matchingBookIndexes.push_back(i);

                    }

                }

                // Throw error if no matches
                if (matchingBookIndexes.size() == 0) {

                    throw bookNotFoundError();

                // If we are borrowing a book...
                } else if (borrowOrReturnChoice == 1) {
                    
                    // Loop to look through book matches/duplicates for an available one to borrow
                    for (int i = 0; i < matchingBookIndexes.size(); i++) {
                        
                        // Checking if one of the matches/duplicates is available
                        tempIndex = matchingBookIndexes[i];
                        tempAvailability = fictionBookSection[tempIndex]->getAvailability();
                        
                        // If it is, stop loop early to borrow only that duplicate
                        if (tempAvailability) {

                            break;

                        }

                    }

                    // If book available, update availability and comfirm success
                    if (tempAvailability) {

                        fictionBookSection[tempIndex]->updateAvailability(false);
                        cout << "\nThe book has been borrowed successfully!\n" << endl;

                    // Otherwise, throw error (cannot borrow book)
                    } else {

                        throw bookNotBorrowableError();

                    }

                // If we are returning a book...
                } else if (borrowOrReturnChoice == 2) {
                    
                    // Loop to look through book matches/duplicates for an available one to return
                    for (int i = 0; i < matchingBookIndexes.size(); i++) {
                        
                        // Checking if one of the matches/duplicates is not available
                        tempIndex = matchingBookIndexes[i];
                        tempAvailability = fictionBookSection[tempIndex]->getAvailability();
                        
                        // If it is not, stop loop early to return only that duplicate
                        if (!tempAvailability) {

                            break;

                        }

                    }

                    // If book is not available, update availability and comfirm success
                    if (!tempAvailability) {

                        fictionBookSection[tempIndex]->updateAvailability(true);
                        cout << "\nThe book has been returned successfully!\n" << endl;

                    // Otherwise, throw error (cannot return book)
                    } else {

                        throw bookNotReturnableError();

                    }

                }

            }

        }

};


// Main function
int main() {
    
    // Creating the library
    Library BC_Lib;
    // Declaring necessary variables for the user's choices
    int choice, bookType, searchChoice, borrowOrReturnChoice;
    string title, author, genre, course, edition, mainCharacter, setting;
    int isbn;
    // Declaring pointer variables to store pointers of created objects
    Textbook* txtPtr = nullptr;
    FictionBook* ficPtr = nullptr;

    cout << "Welcome to the Broward College Library! What would you like to do today?\n" << endl;
    // Loop for menu
    do {

        // Displaying menu
        cout << "Please pick a number." << endl;
        cout << "\t1. Add a Book" << endl;
        cout << "\t2. Remove a Book" << endl;
        cout << "\t3. Search for a Book" << endl;
        cout << "\t4. Display all Books" << endl;
        cout << "\t5. Borrow a Book" << endl;
        cout << "\t6. Return a Book" << endl;
        cout << "\t7. Leave" << endl;
        cout << "Selection: ";
        cin >> choice;
        
        // Switch statement for menu choices
        switch (choice) {
            
            // If user chooses to add a book...
            case 1: {
                
                // Loop to choose between adding a Textbook or Fiction Book
                do {
                    
                    cout << "\nWhat type of book would you like to add?" << endl;
                    cout << "\t1. Textbook" << endl;
                    cout << "\t2. Fiction Book" << endl;
                    cout << "Selection: ";
                    cin >> bookType;

                    // Try again if invalid input
                    if (bookType != 1 && bookType != 2) {
                        cout << "\nERROR: Invalid choice; please try again." << endl;
                    }

                } while (bookType != 1 && bookType != 2);

                // User picks book details
                cout << "\nTitle: ";
                cin.ignore();
                getline(cin, title);
                cout << "Author: ";
                getline(cin, author);
                cout << "ISBN (enter an integer): ";
                cin >> isbn;
                cout << "Genre: ";
                cin.ignore();
                getline(cin, genre);

                // User continues picking book details based on book type, and then the respective object is created
                // For Textbook:
                if (bookType == 1) {
                    
                    cout << "\nCourse: ";
                    getline(cin, course);
                    cout << "Edition: ";
                    getline(cin, edition);

                    // Creating new textbook object and adding it to the library
                    try {
                        
                        txtPtr = new Textbook(title, author, isbn, genre, course, edition);
                        BC_Lib.addBook(txtPtr);
                        txtPtr = nullptr;
                        cout << "\nThe book has been added successfully!\n" << endl;

                    }
                    // Catching empty string, negative ISBN, and duplicate ISBN exceptions
                    catch (Textbook::emptyStringError) {

                        cout << "\nERROR: Empty title, author, genre, course, or edition is invalid." << endl;
                        cout << "The book has not been added.\n" << endl;

                    }
                    catch (Textbook::negativeISBNerror) {

                        cout << "\nERROR: Negative ISBN is invalid." << endl;
                        cout << "The book has not been added.\n" << endl;

                    }
                    catch (Library::duplicateISBN) {
                        
                        delete txtPtr;
                        txtPtr = nullptr;
                        cout << "\nERROR: Books that aren't the same book cannot have the same ISBN.\n" << endl;

                    }

                // For Fiction Book:
                } else if (bookType == 2) {
                    
                    cout << "\nMain Character: ";
                    getline(cin, mainCharacter);
                    cout << "Setting: ";
                    getline(cin, setting);

                    // Creating new fiction book object and adding it to the library
                    try {

                        ficPtr = new FictionBook(title, author, isbn, genre, mainCharacter, setting);
                        BC_Lib.addBook(ficPtr);
                        ficPtr = nullptr;
                        cout << "\nThe book has been added successfully!\n" << endl;

                    }
                    // Catching empty string, negative ISBN, and duplicate ISBN exceptions
                    catch (FictionBook::emptyStringError) {

                        cout << "\nERROR: Empty title, author, genre, main character, or setting is invalid." << endl;
                        cout << "The book has not been added.\n" << endl;

                    }
                    catch (FictionBook::negativeISBNerror) {

                        cout << "\nERROR: Negative ISBN is invalid." << endl;
                        cout << "The book has not been added.\n" << endl;

                    }
                    catch (Library::duplicateISBN) {
                        
                        delete ficPtr;
                        ficPtr = nullptr;
                        cout << "\nERROR: Books that aren't the same book cannot have the same ISBN.\n" << endl;

                    }

                }

                break;
            }

            // If user chooses to remove a book...
            case 2: {
                
                // Loop to choose between removing a Textbook or Fiction Book
                do {
                    
                    cout << "\nWhat type of book would you like to remove?" << endl;
                    cout << "\t1. Textbook" << endl;
                    cout << "\t2. Fiction Book" << endl;
                    cout << "Selection: ";
                    cin >> bookType;

                    // Try again if invalid input
                    if (bookType != 1 && bookType != 2) {
                        cout << "\nERROR: Invalid choice; please try again." << endl;
                    }

                } while (bookType != 1 && bookType != 2);

                // Getting title and author of book to find it
                cout << "\nWhat is the title of the book?" << endl;
                cin.ignore();
                getline(cin, title);
                cout << "\nWhat is the author of the book?" << endl;
                getline(cin, author);

                // For Textbook:
                if (bookType == 1) {
                    
                    // Textbook is searched for and removed from the library; the object is also deleted
                    try {
                        
                        txtPtr = BC_Lib.removeTextbook(title, author);
                        delete txtPtr;
                        txtPtr = nullptr;
                        cout << "\nThe book was successfully removed!\n" << endl;

                    }
                    // Catching exception for book not being found
                    catch (Library::bookNotFoundError) {

                        cout << "\nERROR: Book was not found.\n" << endl;

                    }
                
                // For Fiction Book:
                } else if (bookType == 2) {

                    // Fiction Book is searched for and removed from the library; the object is also deleted
                    try {

                        ficPtr = BC_Lib.removeFictionBook(title, author);
                        delete ficPtr;
                        ficPtr = nullptr;
                        cout << "\nThe book was successfully removed!\n" << endl;

                    }
                    // Catching exception for book not being found
                    catch (Library::bookNotFoundError) {

                        cout << "\nERROR: Book was not found.\n" << endl;

                    }

                }
                
                break;
            }

            // If user chooses to search for a book...
            case 3: {
                
                // Loop to choose between searching for a Textbook or Fiction Book
                do {
                    
                    cout << "\nWhat type of book would you like to search for?" << endl;
                    cout << "\t1. Textbook" << endl;
                    cout << "\t2. Fiction Book" << endl;
                    cout << "Selection: ";
                    cin >> bookType;

                    // Try again if invalid input
                    if (bookType != 1 && bookType != 2) {
                        cout << "\nERROR: Invalid choice; please try again." << endl;
                    }

                } while (bookType != 1 && bookType != 2);

                // Loop to choose between searching by title or author
                do {
                    
                    cout << "\nWould you like to search by title or author?" << endl;
                    cout << "\t1. Title" << endl;
                    cout << "\t2. Author" << endl;
                    cout << "Selection: ";
                    cin >> searchChoice;

                    // Try again if invalid input
                    if (searchChoice != 1 && searchChoice != 2) {
                        cout << "\nERROR: Invalid choice; please try again." << endl;
                    }

                } while (searchChoice != 1 && searchChoice != 2);
                
                // Getting title or author from user depending on choice
                cin.ignore();
                if (searchChoice == 1) {

                    cout << "\nWhat is the title of the book?" << endl;
                    getline(cin, title);
                    author = "";

                } else if (searchChoice == 2) {

                    cout << "\nWhat is the author of the book?" << endl;
                    getline(cin, author);
                    title = "";

                }

                // Searching for book and displaying details
                try {

                    BC_Lib.bookSearch(title, author, bookType, searchChoice);

                }
                // Catching exception for book not being found
                catch (Library::bookNotFoundError) {

                    cout << "\nERROR: Book was not found.\n" << endl;

                }

                break;
            }

            // If user chooses to display all books...
            case 4: {
                
                // All books are displayed
                BC_Lib.displayBooks();
                
                break;
            }

            // If user chooses to borrow a book...
            case 5: {
                
                // User picked to borrow book, so we set variable accordingly
                borrowOrReturnChoice = 1;

                // Loop to choose between borrwing a Textbook or Fiction Book
                do {
                    
                    cout << "\nWhat type of book would you like to borrow?" << endl;
                    cout << "\t1. Textbook" << endl;
                    cout << "\t2. Fiction Book" << endl;
                    cout << "Selection: ";
                    cin >> bookType;

                    // Try again if invalid input
                    if (bookType != 1 && bookType != 2) {
                        cout << "\nERROR: Invalid choice; please try again." << endl;
                    }

                } while (bookType != 1 && bookType != 2);

                // Getting title and author of book to borrow it
                cout << "\nWhat is the title of the book?" << endl;
                cin.ignore();
                getline(cin, title);
                cout << "\nWhat is the author of the book?" << endl;
                getline(cin, author);

                // Borrowing book
                try {
                    
                    BC_Lib.borrowOrReturn(title, author, bookType, borrowOrReturnChoice);

                }
                // Catching book not found and book not available to be borrowed errors
                catch (Library::bookNotFoundError) {

                    cout << "\nERROR: Book was not found.\n" << endl;

                }
                catch (Library::bookNotBorrowableError) {

                    cout << "\nERROR: This book is not available at this time.\n" << endl;

                }
                
                break;
            }

            // If user chooses to return a book...
            case 6: {
                
                // User picked to return book, so we set variable accordingly
                borrowOrReturnChoice = 2;

                // Loop to choose between return a Textbook or Fiction Book
                do {
                    
                    cout << "\nWhat type of book would you like to return?" << endl;
                    cout << "\t1. Textbook" << endl;
                    cout << "\t2. Fiction Book" << endl;
                    cout << "Selection: ";
                    cin >> bookType;

                    // Try again if invalid input
                    if (bookType != 1 && bookType != 2) {
                        cout << "\nERROR: Invalid choice; please try again." << endl;
                    }

                } while (bookType != 1 && bookType != 2);

                // Getting title and author of book to return it
                cout << "\nWhat is the title of the book?" << endl;
                cin.ignore();
                getline(cin, title);
                cout << "\nWhat is the author of the book?" << endl;
                getline(cin, author);

                // Returning book
                try {
                    
                    BC_Lib.borrowOrReturn(title, author, bookType, borrowOrReturnChoice);

                }
                // Catching book not found and book not able to be returned errors
                catch (Library::bookNotFoundError) {

                    cout << "\nERROR: Book was not found.\n" << endl;

                }
                catch (Library::bookNotReturnableError) {

                    cout << "\nERROR: This book cannot be returned, as all matches are already present." << endl;
                    cout << "It is likely that this book does not belong to this library.\n" << endl;

                }
                
                break;
            }

            // If user chooses to leave, then end loop and quit program
            case 7: {
                
                cout << "\nGoodbye!" << endl;
                
                break;
            }

            // If user choice is invalid, display error and try again
            default: {
                
                cout << "\nERROR: Invalid choice; please try again.\n" << endl;
                
                break;
            }

        }

    // End loop if user choice is to leave
    } while (choice != 7);

}
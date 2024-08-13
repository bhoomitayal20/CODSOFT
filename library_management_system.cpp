#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
};

struct Borrower {
    string name;
    string borrowedISBN;
    time_t dueDate;
    bool hasOverdueFine;

    Borrower(string n) : name(n), borrowedISBN(""), dueDate(0), hasOverdueFine(false) {}
};

// Function to search for a book by title, author, or ISBN
void searchBook(const vector<Book>& books) {
    string query;
    cout << "Enter book title, author, or ISBN to search: ";
    cin.ignore();
    getline(cin, query);

    for (const auto& book : books) {
        if (book.title == query || book.author == query || book.isbn == query) {
            cout << "\nBook found:\n";
            cout << "Title: " << book.title << "\nAuthor: " << book.author << "\nISBN: " << book.isbn << "\n";
            cout << "Status: " << (book.isAvailable ? "Available" : "Checked out") << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

// Function to check out a book
void checkoutBook(vector<Book>& books, Borrower& borrower) {
    if (!borrower.borrowedISBN.empty()) {
        cout << "Borrower has already checked out a book. Return it first.\n";
        return;
    }

    string isbn;
    cout << "Enter ISBN of the book to check out: ";
    cin >> isbn;

    for (auto& book : books) {
        if (book.isbn == isbn) {
            if (book.isAvailable) {
                book.isAvailable = false;
                borrower.borrowedISBN = isbn;

                time_t now = time(0);
                borrower.dueDate = now + (7 * 24 * 60 * 60); // 1 week due date
                cout << "Book checked out successfully. Due date is in 7 days.\n";
                return;
            } else {
                cout << "Book is currently unavailable.\n";
                return;
            }
        }
    }
    cout << "Book not found.\n";
}

// Function to return a book
void returnBook(vector<Book>& books, Borrower& borrower) {
    if (borrower.borrowedISBN.empty()) {
        cout << "Borrower has no book to return.\n";
        return;
    }

    for (auto& book : books) {
        if (book.isbn == borrower.borrowedISBN) {
            book.isAvailable = true;

            time_t now = time(0);
            if (now > borrower.dueDate) {
                borrower.hasOverdueFine = true;
                cout << "Book is overdue. A fine will be calculated.\n";
            } else {
                borrower.hasOverdueFine = false;
                cout << "Book returned on time.\n";
            }
            borrower.borrowedISBN = "";
            return;
        }
    }
}

// Function to calculate fine for overdue books
void calculateFine(Borrower& borrower) {
    if (borrower.hasOverdueFine) {
        cout << "Fine is $5 for overdue book.\n";
        borrower.hasOverdueFine = false;
    } else {
        cout << "No fine to be paid.\n";
    }
}

// Function to display the main menu
void showMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Search Book\n";
    cout << "2. Check Out Book\n";
    cout << "3. Return Book\n";
    cout << "4. Calculate Fine\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Book> books = {
        Book("The Great Gatsby", "F. Scott Fitzgerald", "123456789"),
        Book("1984", "George Orwell", "987654321"),
        Book("To Kill a Mockingbird", "Harper Lee", "192837465")
    };

    Borrower borrower("John Doe");

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                searchBook(books);
                break;
            case 2:
                checkoutBook(books, borrower);
                break;
            case 3:
                returnBook(books, borrower);
                break;
            case 4:
                calculateFine(borrower);
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}


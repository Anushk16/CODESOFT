#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Structure to represent a book
struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(const string& t, const string& a, const string& isbn)
        : title(t), author(a), ISBN(isbn), isAvailable(true) {}
};

// Structure to represent a borrower
struct Borrower {
    string name;
    int borrowedBooks;

    Borrower(const string& n) : name(n), borrowedBooks(0) {}
};

// Structure to represent a transaction
struct Transaction {
    string ISBN;
    string borrowerName;
    time_t checkoutDate;
    time_t returnDate;
    bool returned;
};

// Function to search for books
void searchBooks(const vector<Book>& books, const string& keyword) {
    cout << "Search Results:" << endl;
    for (const Book& book : books) {
        if (book.title.find(keyword) != string::npos ||
            book.author.find(keyword) != string::npos ||
            book.ISBN.find(keyword) != string::npos) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.ISBN << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
        }
    }
}

// Function to check out a book
void checkoutBook(vector<Book>& books, vector<Transaction>& transactions, const string& ISBN, const string& borrowerName) {
    for (Book& book : books) {
        if (book.ISBN == ISBN && book.isAvailable) {
            book.isAvailable = false;
            time_t currentTime = time(nullptr);
            time_t returnDate = currentTime + 14 * 24 * 60 * 60; // 2 weeks from now
            transactions.push_back({ISBN, borrowerName, currentTime, returnDate, false});
            cout << "Book checked out successfully. Return by: " << ctime(&returnDate);
            return;
        }
    }
    cout << "Book not found or unavailable." << endl;
}

// Function to return a book
void returnBook(vector<Book>& books, vector<Transaction>& transactions, const string& ISBN, const string& borrowerName) {
    for (Transaction& transaction : transactions) {
        if (transaction.ISBN == ISBN && transaction.borrowerName == borrowerName && !transaction.returned) {
            for (Book& book : books) {
                if (book.ISBN == ISBN) {
                    book.isAvailable = true;
                    transaction.returned = true;
                    cout << "Book returned successfully." << endl;
                    return;
                }
            }
        }
    }
    cout << "Book not found or not borrowed by this borrower." << endl;
}

int main() {
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

    while (true) {
        cout << "Library Management System" << endl;
        cout << "1. Search Books" << endl;
        cout << "2. Check Out Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter search keyword (Title, Author, or ISBN): ";
                string keyword;
                cin.ignore();
                getline(cin, keyword);
                searchBooks(books, keyword);
                break;
            case 2:
                cout << "Enter ISBN of the book to check out: ";
                string checkoutISBN;
                cin >> checkoutISBN;
                cout << "Enter borrower name: ";
                string borrowerName;
                cin.ignore();
                getline(cin, borrowerName);
                checkoutBook(books, transactions, checkoutISBN, borrowerName);
                break;
            case 3:
                cout << "Enter ISBN of the book to return: ";
                string returnISBN;
                cin >> returnISBN;
                cout << "Enter borrower name: ";
                string returnBorrower;
                cin.ignore();
                getline(cin, returnBorrower);
                returnBook(books, transactions, returnISBN, returnBorrower);
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

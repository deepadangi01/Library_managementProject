#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Node structure for Book in BST
struct BookNode {
    int id;
    string title, author;
    BookNode *left, *right;

    BookNode(int bookID, string bookTitle, string bookAuthor)
        : id(bookID), title(bookTitle), author(bookAuthor), left(nullptr), right(nullptr) {}
};

// Class to manage book storage using BST
class Library {
private:
    BookNode* root;
    
    BookNode* insert(BookNode* node, int id, string title, string author) {
        if (!node) return new BookNode(id, title, author);
        if (id < node->id)
            node->left = insert(node->left, id, title, author);
        else
            node->right = insert(node->right, id, title, author);
        return node;
    }
    
    void inorder(BookNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << "ID: " << node->id << ", Title: " << node->title << ", Author: " << node->author << endl;
        inorder(node->right);
    }
    
    BookNode* search(BookNode* node, int id) {
        if (!node || node->id == id) return node;
        if (id < node->id) return search(node->left, id);
        return search(node->right, id);
    }

public:
    Library() : root(nullptr) {}
    
    void addBook(int id, string title, string author) {
        root = insert(root, id, title, author);
        cout << "Book inserted successfully: ID " << id << ", Title: " << title << ", Author: " << author << endl;
    }
    
    void displayBooks() {
        inorder(root);
    }
    
    void findBook(int id) {
        BookNode* book = search(root, id);
        if (book)
            cout << "Found - ID: " << book->id << ", Title: " << book->title << ", Author: " << book->author << endl;
        else
            cout << "Book not found!" << endl;
    }
};

// Queue structure for managing book borrowing
class BorrowQueue {
private:
    queue<int> borrowQueue;
public:
    void borrowBook(int bookID) {
        borrowQueue.push(bookID);
        cout << "Book with ID " << bookID << " added to borrow queue." << endl;
    }
    
    void processBorrow() {
        if (borrowQueue.empty()) {
            cout << "No books in borrow queue!" << endl;
            return;
        }
        cout << "Processing borrow request for book ID: " << borrowQueue.front() << endl;
        borrowQueue.pop();
    }
};

int main() {
    Library lib;
    BorrowQueue borrowQ;
    
    lib.addBook(101, "C++ Primer", "Stanley B. Lippman");
   
    
    cout << "Library Books:\n";
    lib.displayBooks();
    
    cout << "\nSearching for book with ID 202:\n";
    lib.findBook(202);
    
    borrowQ.borrowBook(202);
    borrowQ.processBorrow();
    
    return 0;
}

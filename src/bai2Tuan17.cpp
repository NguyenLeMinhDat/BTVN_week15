#include <iostream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

class Book {
private:
    class Node {
    public:
        string index;
        string title;
        Node* left;
        Node* right;
    
    public:
        Node(string idx, string t, Node* l = 0, Node* r = 0) : index(idx), title(t), left(l), right(r) {}

        void Remove() {
            if (left) left->Remove();
            if (right) right->Remove();
            delete this;
        }
    };
protected:
    Node* root;

public:
    Book() : root(NULL) {}

    Book(string idx, string t) {
        root = new Node(idx, t);
    }

    ~Book() {
        RemoveAll();
    }

    Node* Root() const { return root; }

    void RemoveAll() {
        if (root) {
            root->Remove();
            root = 0;
        }
    }

    void Insert(string idx, string t) {
        root = insert(root, idx, t);
    }

    static void printBook(Node* r, int i) {
        if (!r) return;

        for (int k = 0; k < i; k++) cout << "  ";
        cout << "- " << r->index << ": " << r->title << endl;

        printBook(r->left, i + 1);
        printBook(r->right, i + 1);
    }

    static bool isCopy(Node* r1, Node* r2) {
        if (!r1 && !r2) return true;
        if (!r1 || !r2) return false;
        if (r1->index != r2->index || r1->title != r2->title) return false;

        return isCopy(r1->left, r2->left) && isCopy(r1->right, r2->right);
    }

private:
    Node* insert(Node* n, string idx, string t) {
        if (!n) return new Node(idx, t);

        if (height(n->left) <= height(n->right))
            n->left = insert(n->left, idx, t);
        else 
            n->right = insert(n->right, idx, t);
        
        return n;
    }

    int height(Node* n) {
        if (!n) return 0;
        return 1 + max(height(n->left), height(n->right));
    }
};

int main() {
    Book b1, b2, b3;
    b1.Insert("1", "Chuyen dong cua hat tich dien trong chan khong");
    b1.Insert("1.1", "Phuong trinh chuyen dong trong dien truong va tu truong");
    b1.Insert("1.2", "Chuyen dong hat tich dien trong tu truong deu");

    b2.Insert("1", "Chuyen dong cua hat tich dien trong chan khong");
    b2.Insert("1.1", "Phuong trinh chuyen dong trong dien truong va tu truong");
    b2.Insert("1.2", "Luong tinh song hat cua cac he vi mo");

    b3.Insert("1", "Chuyen dong cua hat tich dien trong chan khong");
    b3.Insert("1.1", "Phuong trinh chuyen dong trong dien truong va tu truong");
    b3.Insert("1.2", "Chuyen dong hat tich dien trong tu truong deu");

    cout << "Sach 1 gom: " << endl;
    Book::printBook(b1.Root(), 0);

    cout << "Sach 2 gom: " << endl;
    Book::printBook(b2.Root(), 0);

    cout << "So sanh sach 1 va sach 2:" << endl;
    if (Book::isCopy(b1.Root(), b2.Root()))
        cout << "\tHai cuon sach la ban copy cua nhau." << endl;
    else
        cout << "\tHai cuon sach khac nhau" << endl;

    cout << "So sanh sach 1 va sach 3:" << endl;
    if (Book::isCopy(b1.Root(), b3.Root()))
        cout << "\tHai cuon sach la ban copy cua nhau." << endl;
    else
        cout << "\tHai cuon sach khac nhau" << endl;
    
    return 0;
}
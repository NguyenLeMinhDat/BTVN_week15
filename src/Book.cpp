#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    class Node {
    public:
        string title;
        int pages;
        Node* first;
        Node* next;

        Node(string t, int p) : title(t), pages(p), first(NULL), next(NULL) {}

        ~Node() {
            Node* n = first;
            while (n) {
                Node* temp = n;
                n = n->next;
                delete temp;
            }
        }

        int totalPages() {
            int sum = pages;
            Node* r = first;
            while(r) {
                sum += r->totalPages();
                r = r->next;
            }
            return sum;
        }
    };
protected:
    Node* root;
public:
    Book() { root = NULL; }

    Book(string t) {
        root = new Node(t, 0);
    }

    ~Book() {
        removeAll();
    }

    void removeAll() {
        if (root) {
            delete root;
            root = NULL;
        }
    }

    int totalChapters() {
        if (!root) return 0;

        int count = 0;
        Node* r = root->first;
        while (r) {
            count++;
            r = r->next;
        }
        return count;
    }

    void findLongestChapter() {
        if (!root || !root->first) {
            cout << "Sach rong hoac chua co chuong nao!" << endl;
            return;
        }

        Node* r = NULL;
        int maxP = 0;

        Node* chap = root->first;
        while (chap) {
            int curP = chap->totalPages();
            if (maxP < curP) {
                maxP = curP;
                r = chap;
            }
            chap = chap->next;
        }
        cout << "Chuong dai nhat trong cuon sach la chuong: " << r->title << " voi " << r->pages << " trang" << endl; 
    }

    bool delSection(string t) {
        if (!root) return false;
        return delSection(root, NULL, t);
    }

    void findChapter(string t) {
        if (!root) {
            cout << "Sach rong!" << endl;
            return;
        }

        Node* chap = root->first;
        while (chap) {
            if (chap->title == t) {
                cout << "Tim thay chuong voi tieu de: " << t << "!" << endl;
                printChapter(chap);
                return;
            }
            chap = chap->next;
        }
        cout << "Khong tim thay chuong voi tieu de: " << t << "!" << endl;
    }

    void addNode(string a, string b, int p = 0) {
        Node* r = findNode(root, a);
        if (r) {
            Node* newNode = new Node(b, p);

            if (!r->first)
                r->first = newNode;
            else {
                Node* temp = r->first;
                while (temp->next)
                    temp = temp->next;
                temp->next = newNode;
            }

            updateChapter(root, a, p);
        }
        else {
            cout << "Khong tim thay tieu de!" << endl;
        }
    }
private:
    bool delSection(Node* parent, Node* prevSibling, string t) {
        if(!parent) return false;
        
        Node* child = parent->first;
        Node* prev = NULL;
        
        while(child) {
            if(child->title == t) {
                int deletedPages = child->totalPages();
                
                if(prev) {
                    prev->next = child->next;
                } else {
                    parent->first = child->next;
                }
                
                child->next = NULL;
                delete child;
                
                updateChapter(root, parent->title, -deletedPages);
                return true;
            }
            
            if(delSection(child, prev, t)) {
                return true;
            }
            
            prev = child;
            child = child->next;
        }
        return false;
    }

    Node* findNode(Node* r, string t) {
        if (!r) return NULL;

        if (r->title == t) 
            return r;
        
        Node* temp = r->first;
        while (temp) {
            Node* f = findNode(temp, t);
            if (f) return f;
            temp = temp->next;
        }

        return NULL;
    }

    void updateChapter(Node* r, string t, int p) {
        if (!r) return;

        if (r->title == t) {
            r->pages += p;
            return;
        }
        
        Node* temp = r->first;
        while (temp) {
            if (findNode(temp, t)) {
                r->pages += p;
                updateChapter(temp, t, p);
                return;
            }

            temp = temp->next;
        }
    }

    void printChapter(Node* chap) {
        if (!chap) return;
        
        // cout << "De muc cua chuong " << chap->title << " :" << endl;
        
    }
};

int main() {
    Book book("Vat ly dien tu");

    book.addNode("Vat ly dien tu", "Chuong 1: Chuyen dong cua hat tich dien trong chan khong");
    book.addNode("Vat ly dien tu", "Chuong 2: Mot so van de vat ly luong tu");
    book.addNode("Vat ly dien tu", "Chuong 3: Pho nang luong cua cac he hat luong tu");

    book.addNode("Chuong 1: Chuyen dong cua hat tich dien trong chan khong", "1.1 Phuong trinh chuyen dong trong dien truong va tu truong", 3);
    book.addNode("Chuong 1: Chuyen dong cua hat tich dien trong chan khong", "1.2 Chuyen dong hat tich dien trong tu truong deu", 4);
    book.addNode("Chuong 2: Mot so van de vat ly luong tu", "2.1 Luong tinh song hat cua cac he vi mo", 7);
    book.addNode("Chuong 2: Mot so van de vat ly luong tu", "2.2 Cac tinh chat cua song De Broglie", 6);
    

    book.addNode("1.2 Chuyen dong hat tich dien trong tu truong deu", "1.2.1 Truong hop van toc ban dau vuong goc voi tu truong", 2);
    book.addNode("1.2 Chuyen dong hat tich dien trong tu truong deu", "1.2.2 Truong hop tong quat", 2);
    book.addNode("2.1 Luong tinh song hat cua cac he vi mo", "2.1.1 Luong tinh song hat cua he buc xa tu", 4);
    book.addNode("2.1 Luong tinh song hat cua cac he vi mo", "2.1.2 Luong tinh song hat cua vat chat", 3);
    book.addNode("2.2 Cac tinh chat cua song De Broglie", "2.2.1 Ham song phang De Broglie", 2);
    book.addNode("2.2 Cac tinh chat cua song De Broglie", "2.2.2 Y nghia xac suat cua song De Broglie", 4);
    
    
    cout << "1. So chuong: " << book.totalChapters() << endl;

    cout << "\n2. Tim chuong dai nhat trong cuon sach:" << endl << "\t";
    book.findLongestChapter();

    cout << "\n3. Tim chuong 2:" << endl;
    book.findChapter("Chuong 2: Mot so van de vat ly luong tu");


    cout << "\n3. Xoa muc 2.2:" << endl;
    if (book.delSection("2.2 Cac tinh chat cua song De Broglie"))
        cout << "Da xoa thanh cong!" << endl;

    cout <<"\n3. Chuong 2 sau khi xoa muc 2.2:" << endl;
    book.findChapter("Chuong 2: Mot so van de vat ly luong tu");

    return 0;
}
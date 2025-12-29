#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    class Node {
    public:
        string title;
        int pages;
        int totalP;
        Node* first;
        Node* next;
        Node* father;

        Node(string t, int p, Node* pr = NULL) : title(t), pages(p), totalP(p), first(NULL), next(NULL), father(pr) {}

        ~Node() {
            Node* n = first;
            while (n) {
                Node* temp = n;
                n = n->next;
                delete temp;
            }
        }

        // int totalPages() {
        //     int sum = pages;
        //     Node* r = first;
        //     while(r) {
        //         sum += r->totalPages();
        //         r = r->next;
        //     }
        //     return sum;
        // }
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
            int curP = chap->totalP;
            if (maxP < curP) {
                maxP = curP;
                r = chap;
            }
            chap = chap->next;
        }
        if (r)
            cout << r->title << " voi tong cong " << r->totalP << " trang" << endl; 
    }

    bool delSection(string t) {
        Node* n = findNode(root, t);
        if (!n || n == root) return false;

        Node* r = n->father;
        int d = -n->totalP;

        if (r->first == n)
            r->first = n->next;
        else {
            Node* temp = r->first;
            while (temp->next != n) temp = temp->next;
            temp->next = n->next;
        }

        updateChapter(r, d);
        n->next = NULL;
        delete n;
        return true;
    }

    void findChapter(string t) {
        Node* chap = findNode(root, t);
        if (chap) {
            cout << "Muc luc chuong [" << t << "] (Tong: " << chap->totalP << " trang):" << endl;
            printChapter(chap, 1); 
        } else {
            cout << "Khong tim thay chuong!" << endl;
        }
    }

    void addNode(string a, string b, int p = 0) {
        Node* r = findNode(root, a);
        if (r) {
            Node* newNode = new Node(b, p, r);

            if (!r->first)
                r->first = newNode;
            else {
                Node* temp = r->first;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }

            updateChapter(r, p);
        }
        else {
            cout << "Khong tim thay tieu de!" << endl;
        }
    }
private:
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

    void updateChapter(Node* r, int p) {
        Node* temp = r;
        while (temp) {
            temp->totalP += p;
            temp = temp->father;
        }
    }

    void printChapter(Node* n, int i) {
        if (!n) return;
        
        for (int k = 0; k < i; k++) cout << "  ";
        cout << "- " << n->title << " (" << n->totalP << " trang)" << endl;

        Node* temp = n->first;
        while (temp) {
            printChapter(temp, i + 1);
            temp = temp->next;
        }
    }
};

int main() {
    Book book("Vat ly dien tu");

    book.addNode("Vat ly dien tu", "Chuong 1: Chuyen dong cua hat tich dien trong chan khong");
    book.addNode("Vat ly dien tu", "Chuong 2: Mot so van de vat ly luong tu");
    book.addNode("Vat ly dien tu", "Chuong 3: Pho nang luong cua cac he hat luong tu");

    book.addNode("Chuong 1: Chuyen dong cua hat tich dien trong chan khong", "1.1 Phuong trinh chuyen dong trong dien truong va tu truong", 3);
    book.addNode("Chuong 1: Chuyen dong cua hat tich dien trong chan khong", "1.2 Chuyen dong hat tich dien trong tu truong deu", 2);
    book.addNode("Chuong 2: Mot so van de vat ly luong tu", "2.1 Luong tinh song hat cua cac he vi mo", 1);
    book.addNode("Chuong 2: Mot so van de vat ly luong tu", "2.2 Cac tinh chat cua song De Broglie", 2);
    

    book.addNode("1.2 Chuyen dong hat tich dien trong tu truong deu", "1.2.1 Truong hop van toc ban dau vuong goc voi tu truong", 5);
    book.addNode("1.2 Chuyen dong hat tich dien trong tu truong deu", "1.2.2 Truong hop tong quat", 4);
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
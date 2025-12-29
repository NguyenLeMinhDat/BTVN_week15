#include <iostream>
#include <chrono>
using namespace std;

enum TraversalOrderMode {
    preOder = -1,   // truoc
    inOrder,        // giua
    postOrder       // sau
};

template <class T>
class BinaryTree {
private:
    class Node {
    public:
        T Value;
        Node* Left;
        Node* Right;

    public:
        Node(const T& value = T{}, Node* left = 0, Node* right = 0): Value(value), Left(left), Right(right) { }

        void Remove() {
            if (Left) Left->Remove();
            if (Right) Right->Remove();

            // cout <<  Value << ", ";
            delete this;
        }
        int Height() const {
            int hl = Left ? Left->Height() : 0;
            int hr = Right ? Right->Height() : 0;
            return (hl > hr ? hl : hr) + 1;
        }
    };
protected:
    Node* root{0};

public:
    BinaryTree() { }
    BinaryTree(T* a, int n) {
        root = CreateNode(a, n, 0);
    }
    ~BinaryTree() {
        RemoveAll();
    }

    Node* Root() const { return root; }
    Node* Root(const T& value) {
        return root = new Node(value);
    }

    void Traversal(int mode, void (*callback)(const T&)) {
        trav(mode, root, callback);
    }

    void RemoveAll() {
        // cout << "Remove ";
        if (root) {
            root->Remove();
            root = 0;
        }
        // cout << endl;
    }

    Node* CreateNode(T* a, int n, int i) {
        if (i >= n) return 0;

        int k = 2 * i;
        return new Node(a[i], CreateNode(a, n, k + 1), CreateNode(a, n, k + 2));
    }

public:
    void Heapify(T* a, int n, int i) {
        int max = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && a[l] > a[max]) max = l;
        if (r < n && a[r] > a[max]) max = r;

        if (max != i) {
            swap(a[i], a[max]);
            Heapify(a, n, max);
        }
    }

    void buildHeap(T* a, int n) {
        int i;
        for (i = n / 2 - 1; i >= 0; i--)
            Heapify(a, n, i);
    }

    void heapSort(T* a, int n) {
        int i;
        for (i = n / 2 - 1; i >= 0; i--) 
            Heapify(a, n, i);
        
        for (i = n - 1; i > 0; i--) {
            swap(a[0], a[i]);
            Heapify(a, i, 0);
        }
    }

private:
    void trav(int mode, Node* node, void (*callback)(const T&)) {
        if (!node) return;

        if (mode < 0) callback(node->Value);
        trav(mode, node->Left, callback);
        if (mode == 0) callback(node->Value);
        trav(mode, node->Right, callback);
        if (mode > 0) callback(node->Value);
    }

public:
    static bool identicalTrees(Node* t1, Node* t2) {
        if (!t1 && !t2) return true;

        if (!t1 || !t2) return false;
        if (t1->Value != t2->Value) return false;

        return identicalTrees(t1->Left, t2->Left) && identicalTrees(t1->Right, t2->Right);
    }
};

void visit(const int& x) {
    cout << x << ' ';
}

int main() {

    // ----------- Bai 1 ------------
    cout << "----------- Bai 1 ------------" << endl;
    int A[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    int n = sizeof(A) / sizeof(int);
    BinaryTree<int> bt(A, n);
    cout << "Thu tu duyet truoc: " << endl;
    bt.Traversal(-1, visit);
    cout << endl;
    cout << "Thu tu duyet giua: " << endl;
    bt.Traversal(0, visit);
    cout << endl;
    cout << "Thu tu duyet sau: " << endl;
    bt.Traversal(1, visit);
    cout << endl;

    bt.buildHeap(A, n);
    BinaryTree<int> btHeap(A, n);
    cout << "Sau khi vun dong, thu tu duyet truoc:" << endl;
    btHeap.Traversal(-1, visit);
    cout << endl;

    // ----------- Bai 2 ------------
    cout << "----------- Bai 2 ------------" << endl;
    cout << "Cay 1 theo thu tu duyet truoc: " << endl;
    bt.Traversal(-1, visit);
    cout << endl;
    cout << "Cay 2 theo thu tu duyet truoc: " << endl;
    btHeap.Traversal(-1, visit);
    cout << endl;

    bool res1 = BinaryTree<int>::identicalTrees(bt.Root(), btHeap.Root());
    cout << "So sanh cay 1 voi cay 2: " << (res1 ? "Giong nhau" : "Khac nhau") << endl;

    bool res2 = BinaryTree<int>::identicalTrees(bt.Root(), bt.Root());
    cout << "So sanh cay 1 voi chinh no: " << (res2 ? "Giong nhau" : "Khac nhau") << endl;

    const int N = 10001;
    int* data = new int[N];
    for (int i = 0; i < N; i++) data[i] = i;

    BinaryTree<int> t1(data, N);
    BinaryTree<int> t2(data, N);

    auto start = chrono::high_resolution_clock::now();
    bool res = BinaryTree<int>::identicalTrees(t1.Root(), t2.Root());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Thoi gian thuc thi khi so nut > 10000: " << duration.count() << "ms" << endl;

    delete[] data;
    return 0;
}   
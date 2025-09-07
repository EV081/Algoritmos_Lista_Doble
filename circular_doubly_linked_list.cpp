#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T d) {
        data = d;
        next = nullptr;
        prev = nullptr;
    }
    ~Node() = default;
};

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    Node<T>* getHead() {
        return head;
    }

    T front() {
        return head->data;
    }

    T back() {
        return tail->data;
    }

    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->prev = nullptr;
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
    }

    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = nullptr;
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
    }

    void popFront() {
        if(!head) return;
        if(head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }

    void popBack() {
        if(!tail) return;
        if(head == tail) {
            delete tail;
            tail = nullptr;
            head = nullptr;
            return;
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }

    void insert(int pos, T num) {
        if (!head) {
            head = new Node<T>(num);
            tail = head;
            return;
        }
        Node<T>* nodo = new Node<T>(num);
        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos - 1) {
            temp = temp->next;
        }

        if (pos == 0) {
            nodo->next = head;
            head->prev = nodo;
            head = nodo;
            return;
        }

        if (temp->next == nullptr) {
            temp->next = nodo;
            nodo->prev = temp;
            tail = nodo;
            return;
        }

        nodo->next = temp->next;
        nodo->prev = temp;
        temp->next->prev = nodo;
        temp->next = nodo;
    }

    void remove(int pos) {

        if (head == nullptr) {
            return;
        }

        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos - 1) {
            temp = temp->next;
        }

        if (temp == head) {
            head = temp->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }

        else if (temp->next == nullptr) {
            temp->prev->next = nullptr;
        }

        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
    }

    T operator[](int pos) {
        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        Node<T>* temp = head;
        int i = 0;
        while(temp != nullptr) {
            i++;
            temp = temp->next;
        }
        return i;
    }

    void clear() {
        while(head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr) {
            head = temp->prev;
        }

        tail = head;
        while (tail != nullptr and tail->next != nullptr) {
            tail = tail->next;
        }
    }
    template<typename T_>
    friend ostream& operator<<(ostream& os, const List<T_> &l);

    ~List() {
        clear();
    }

};

template<typename T>
ostream& operator<<(ostream &os, const List<T> &l) {
    Node<T>* temp = l.head;
    while (temp != nullptr) {
        os << temp->data << " ";
        temp = temp->next;
    }
    return os;
}

int main () {
    List<int> l1;
    l1.pushFront(30);
    l1.pushBack(50);
    l1.pushFront(20);
    l1.pushFront(10);
    l1.pushBack(40);

    cout << "-------------" << endl;

    cout << l1 << "\n";

    cout << "Tamaño de lista: " << l1.size() << endl;

    cout << "Agregar el 5 en la posicion 4: " <<endl;
    l1.insert(4,5);

    cout << "El valor en la posicion 4:" << endl;
    cout << l1[4] << endl;

    l1.reverse();
    cout << "Reverse: ---" << endl;
    cout << l1 << "\n";

    return 0;
}

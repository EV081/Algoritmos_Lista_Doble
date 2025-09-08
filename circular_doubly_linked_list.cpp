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
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
    }

    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            tail = newNode;
        }
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
        head->prev = tail;
        tail->next = head;
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
        tail->next = head;
        head->prev = tail;
        delete temp;
    }

    void insert(int pos, T num) {
        Node<T>* temp = head;

        if (head == nullptr) {
            Node<T>* nodo = new Node<T>(num);
            head = tail = nodo;
            nodo->prev = nodo;
            nodo->next = nodo;
            return;
        }

        if (pos == 0) {
            pushFront(num);
            return;
        }

        int i = 0;
        while(i < pos - 1 and temp != tail) {
            temp = temp->next;
            i++;
        }

        Node<T>* nodo = new Node<T>(num);
        nodo->next = temp->next;
        nodo->prev = temp;
        temp->next->prev = nodo;
        temp->next = nodo;

        if (temp == tail) {
            tail = nodo;
        }
    }

    void remnove(int pos) {
        if (head == nullptr) {
            return;
        }

        if (pos == 0) {
            popFront();
            return;
        }

        Node<T>* temp = head;
        int i = 0;
        while (i++ < pos - 1 && temp != tail) {
            temp = temp->next;
        }

        if (temp == tail) {
            return; //si la posición esta fuera del tamaño de lista que no haga nada
        }

        Node<T>* temp2 = temp->next;
        if (temp2 == tail) {
            popBack();
            return;
        }

        temp->next = temp2->next;
        temp2->next->prev = temp;
        delete temp2;
    }

    T operator[](int pos) {
        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos and temp != tail) {
            temp = temp->next;
        }
        if (temp == tail) { //si la posición esta fuera del tamaño de lista que devuelva el valor de la cola xd
            return temp->data;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        Node<T>* temp = head;
        int i = 0;
        while(temp != tail) {
            i++;
            temp = temp->next;
        }
        return i;
    }

    void clear() {
        tail->next = nullptr;
        while(head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse() {
        if (!head || head == tail) return;

        Node<T>* oldHead = head;
        Node<T>* oldTail = head->prev;

        Node<T>* current = head;
        do {
            Node<T>* nxt = current->next;
            current->next = current->prev;
            current->prev = nxt;
            current = nxt;
        } while (current != head);

        head = oldTail;
        tail = oldHead;
    }

    template<typename T_>
    friend ostream& operator<<(ostream& os, const List<T_> &l);

    ~List() {
        clear();
    }
};

template<typename T>
ostream& operator<<(ostream &os, const List<T> &l) {
    if (!l.head) return os;
    const Node<T>* cur = l.head;
    do {
        os << cur->data << " ";
        cur = cur->next;
    } while (cur != l.head);
    return os;
}

int main () {
    List<int> l1;
    l1.pushFront(30);
    l1.pushFront(20);
    l1.pushFront(10);
    l1.pushBack(40);

    cout << "-------------" << endl;
    cout << l1 << "\n";
    l1.insert(4, 50);

    cout << l1 << "\n";
    cout << "Tamaño de lista: " << l1.size() << endl;

    cout << "Agregar el 5 en la posicion 3: " <<endl;
    l1.insert(3,5);
    cout << l1 << "\n";

    cout << "El valor en la posicion 4:" << endl;
    cout << l1[4] << endl;

    l1.reverse();
    cout << "Reverse: " << endl;
    cout << l1 << "\n";

    l1.clear();
    cout << "Clear: " << endl;
    cout << l1 << "\n";

    return 0;
}
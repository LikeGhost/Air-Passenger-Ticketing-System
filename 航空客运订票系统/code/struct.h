#include<string>
using namespace std;
template<typename T>
class queue {
public:
    void push(T data) {
        qnode* New = new qnode;
        New->data = data;
        New->next = NULL;
        tail->next = New;
        tail = New;
        len++;
    }
    T front() {
        qnode* del = Q->next;
        T ret;
        if (del == tail)tail = Q;
        Q->next = del->next;
        ret = del->data;
        len--;
        return ret;
    }
    bool isempty() {
        return len == 0 ? 1 : 0;
    }
    int l() {
        return len;
    }
    queue() {
        Q = new qnode;
        tail = Q;
    }
private:
    struct qnode {
        T data;
        qnode* next;
    };
    qnode* Q = new qnode, * tail;
    int len = 0;
};
struct Passenger_Node {
    string name;
    int seat=-1;
};
struct Tickets_Node {
    Passenger_Node* Buyer[500] = {0};
    queue<int> Refund;
    queue<Passenger_Node*> Waiter;
};

struct Plane_Node {
    string start, end;
    string FlightNum;
    string PlaneNum;
    string date;
    string cap, lecap;
    Plane_Node* saplnext = NULL, * safnnext = NULL,*satmnext=NULL;
    Plane_Node* saplpre = NULL, * safnpre = NULL,*satmpre=NULL;
    Tickets_Node* ticket;
    Plane_Node() {
        ticket = new Tickets_Node;
    }
};

struct Flight_Num {
    Plane_Node* data = NULL;
    Flight_Num* left = NULL, * right = NULL;
    int height;
};
struct Flight_End {
    string End;
    Plane_Node* data = NULL;
    Flight_End* left = NULL, * right = NULL;
    int height;
};
struct Flight_Start {
    string start;
    Flight_End* FENode = NULL;
    Flight_Start* left = NULL, * right = NULL;
    int height;
};
struct Flight_Time {
    string date;
    int count=0;
    Plane_Node* data = NULL;
    Flight_Time* next=NULL;
};
Plane_Node* Search_r = NULL;
bool Search_End_Sign = false;
int FlightCount = 0;

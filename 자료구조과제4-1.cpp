#include <iostream>
using namespace std;

class Node {
private:
	int data;
	Node* link;
public:
	Node(int val = 0) : data(val), link(nullptr) {};
	Node* getLink() { return this->link; };
	void setLink(Node* next) { this->link = next; }//다음노드의 주소를 가지게한다
	bool hasData(int val) { return this->data == val; }//노드가 값을 가지고있는지?
	void setData(int data) { this->data = data; }
	int getData() { return this->data; }
};

class LinkedList {
private:
	Node head; //헤드노드
	int cnt; //리스트 원소의 갯수 
	Node* getHead() { return head.getLink(); }
	Node* getNode(int pos) {
		Node* p = &head; //시작 헤드노드 주소 p에 저장
		for (int i = -1; i < pos; i++) {
			if (p == nullptr) break;
			p = p->getLink();
		}
		return p;
	}

public:
	LinkedList() {this->cnt = 0;}
	bool empty() {return this->getHead() == nullptr;}
	int size() { return this->cnt;}
	void display() {
		for (Node* p = getHead(); p != nullptr; p = p->getLink())
			cout << p->getData() << " ";
	}
	void insert(int pos, int data) { //pos번째 데이터 삽입
		if (!(pos >= 0 && pos <= size()))
			throw "Error:Out of range1";
		Node* prev = this->getNode(pos - 1);
		if (prev != nullptr) {
			Node* p = new Node(data);
			p->setLink(prev->getLink());
			prev->setLink(p);
			this->cnt++;
		}
	}

	void remove(int pos) { //pos번째 데이터 삭제
		if (this->empty() || !(pos >= 0 && pos < size()))
			throw "Error: List is empty or out of range";
		Node* prev = this->getNode(pos - 1);
		if (prev != NULL) {
			Node* removed = prev->getLink();
			prev->setLink(removed->getLink());
			delete removed;
			this->cnt--;
		}
	}
	int find(int query) {
		int idx = 0;
		for (Node* p = getHead(); p != nullptr; p = p->getLink()) {
			if (p->hasData(query)) return idx;
			idx++;
		}
	}

	void replace(int pos, int data) {
		if (this->empty() || !(pos >= 0 && pos < size()))
			throw "Error: List is empty or out of range";

		Node* node = getNode(pos);
		node->setData(data);
	}

	int get(int pos) {
		if (this->empty() || !(pos >= 0 && pos < size()))
			throw "Error: List is empty or out of range";

		Node* node = getNode(pos);
		return node->getData();
	}

	~LinkedList() {
		while (!this->empty())
			this->remove(0);
	}

	void sorted_insert(int input) {
		if (this->empty()) {
			insert(0, input);
			cout << this->get(0) << endl;
		}
		else {
			insert(0, input);
			for (int i = 0; i < cnt-1; i++) {
				if (this->get(i) < this->get(i + 1)) {
					int Bigdata = get(i + 1);
					int Smalldata = get(i);
					replace(i, Bigdata);
					replace(i + 1, Smalldata);
				}
				else break;
			}

			for (int i = 0; i < cnt; i++) {
				cout << this->get(i) << " ";
			}
			cout << endl;
		}
	}
};


int main() {
	LinkedList linklist;
	int n;
	int input[20];

	cin >> n;
	try {
		for (int i = 0; i < n; i++) {
			cin >> input[i];
			linklist.sorted_insert(input[i]);
		}

		return 0;
	}
	catch (string exption) {
		cout << exption << endl;
		return 1;
	}
}
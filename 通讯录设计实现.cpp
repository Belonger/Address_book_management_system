#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>//��д�ļ���ͷ�ļ�
using namespace std;

struct ElementType;
struct Node;
struct Queue;
typedef struct Queue* MyQueue;

struct ElementType {
	int id;
	string name;
	int num;
};

struct Node {
	ElementType data;
	Node* next;
};

struct Queue {
	Node* front;
	Node* rear;
};

MyQueue Init(MyQueue& q);//Initialize queue
bool IsEmpty(MyQueue q);//Determine if the queue is empty
bool Insert(ElementType x, MyQueue q);//Insert the data to the end of the queue
bool Delete(const int message, MyQueue q);//Find some data in the queue, and then delete the corresponding node
void Print(const Node* q);//Prints all the information in a node
void PrintAll(const MyQueue q);//Prints information from all nodes
bool FindByName(const string massage, const MyQueue q);//Prints information from all nodes
void Input(MyQueue q);//When the address book is empty, re-enter the information into the address book 
void Write(MyQueue q);//Write the information from the queue to the document 
MyQueue Read();//Write the information from the queue to the document
MyQueue ReadOrClear(MyQueue& q);//Whether to empty all the information 
void Swap(ElementType& x, ElementType& y);//Swap functions in sort
MyQueue BubbleSort(MyQueue q);//Sort by student ID using bubble sort 
void Menu(MyQueue q);//main menu

//��ʼ������ 
MyQueue Init(MyQueue& q) {
	q = new Queue();
	if (q == NULL) return NULL;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

//�鿴�����Ƿ�Ϊ�� 
bool IsEmpty(MyQueue q) {
	return q->front == NULL;
}

//�����Ϣ 
bool Insert(ElementType x, MyQueue q) {
	Node* temp = new Node();
	if (temp == NULL) return false;
	temp->data = x;//������Ҫ�ĳ���Ҫ�����ݣ����(����)�ĳ�һ����������ʽ����ֵ��ʱ����ú�������ӡ��ʱ��Ҳ���ú���
	temp->next = NULL;
	if (IsEmpty(q)) {
		q->front = temp;
		q->rear = temp;
		return true;
	}
	else {
		q->rear->next = temp;
		q->rear = temp;
		return true;
	}
}

//ɾ������ 
bool Delete(const int message, MyQueue q) {
	Node* temp = new Node();
	if (temp == NULL) return false;//���봢��ռ�ʧ��
	bool pd = 0;
	//�����ҵ����id�ٽ���ɾ��
	//���ж��ǲ���ͷ�ڵ㣬�������ٰ�ͷ�ڵ㵱�׽ڵ����ʹ��
	if (q->front->data.id == message) {//���ɾ��ͷ�ڵ�
		temp = q->front;
		q->front = q->front->next;
		delete temp;
		temp = NULL;
		pd = 1;
	}
	else if (q->rear->data.id == message) {//���ɾ��β�ڵ�
		//���ҵ�β�ڵ��ǰһ�����
		temp = q->front;
		while (temp->next->data.id != message) temp = temp->next;
		q->rear = temp;
		q->rear->next = NULL;
		pd = 1;
	}
	else {//���ɾ���м�ڵ�
		temp = q->front;
		while (temp->next != NULL && temp->next->data.id != message) temp = temp->next;
		if (temp->next == NULL) return false;//�ж��ǲ���û���ҵ���û���ҵ�����false
		Node* mp = new Node();
		mp = temp->next;
		temp->next = temp->next->next;
		delete mp;
		mp = NULL;
		pd = 1;
	}
	if (pd == 1) {
		Write(q);
		cout << "�ѳɹ�ɾ����ѧ����Ϣ��" << endl;
		return true;
	}
}

//ͨ���������в��� 
bool FindByName(const string massage, const MyQueue q) {//�˺���ֻ�в��ҹ��ܣ�û�д�ӡ���ܣ���ӡ��������һ������
	Node* temp = new Node();
	bool pd = 0;
	if (q->front->data.name == massage) {
		temp = q->front;
		Print(temp);
		return true;
	}
	else {
		temp = q->front;
		while (temp->next != NULL && temp->next->data.name != massage) temp = temp->next;
		if (temp->next == NULL) return false;//û���ҵ�����˵�����������false
		Print(temp->next);
		return true;
	}
}

//�������д�ӡ 
void Print(const Node* q) {
	cout << "��ѧ������ϢΪ��" << endl;
	cout << "ѧ�ţ� " << q->data.id << " ������" << q->data.name << " �绰���룺" << q->data.num << endl;
}

//��ӡȫ����ѧ����Ϣ 
void PrintAll(const MyQueue q) {
	cout << "ѧ��";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "����";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "�绰����" << endl;

	Node* temp;
	temp = q->front;
	while (temp != NULL) {
		cout << " " <<temp->data.id << "	      " << temp->data.name << "           " << temp->data.num << endl;
		temp = temp->next;
	}
	//cout << endl;
}

//ʵ������Ĺ��ܺ��� 
void Swap(ElementType& x, ElementType& y) {
	ElementType temp;
	temp = x;
	x = y;
	y = temp;
}

MyQueue BubbleSort(MyQueue q) {
	if (q->front == NULL || q->front->next == NULL) return NULL;
	for (Node* i = q->front; i->next != NULL; i = i->next) {
		for (Node* j = q->front; j->next != NULL; j = j->next) {
			if (j->data.id > j->next->data.id) {
				Swap(j->data, j->next->data);
			}
		}
	}
	return q;
}

//��ȫ����Ϣ���뵽�ĵ���
void Write(MyQueue q) {
	//�ȸ���ѧ�Ž��������ٽ��д洢
	q=BubbleSort(q);
	ofstream writeIt;
	writeIt.open("data.txt");
	if (writeIt.fail()) {
		cout << "���ļ�û���ҵ���" << endl;
		cout << "�������˳���" << endl;
		exit(1);
	}

	Node* temp = new Node();
	if (q!= NULL) {
		temp= q->front;
		while (temp != NULL) {
			writeIt << temp->data.id << " " << temp->data.name << " " << temp->data.num << endl;;
			temp = temp->next;
		}
	}
	writeIt.close();
}

//���ĵ��ж������е���Ϣ
MyQueue Read() {
	ifstream readIt("data.txt");
	if (readIt.fail()) {
		cout << "���ļ�û���ҵ���" << endl;
		cout << "�������˳���" << endl;
		exit(1);
	}
	int id1;
	string name1;
	int num1;
	MyQueue q=new Queue();
	ElementType x;
	while (!readIt.eof()) {
		readIt >> id1 >> name1 >> num1;
		if (readIt.eof()) break;
		x.id = id1;
		x.name = name1;
		x.num = num1;
		Insert(x, q);
	}
	readIt.close();
	return q;
}

//�����ĵ��е���Ϣ
MyQueue ReadOrClear(MyQueue& q) {
	q=Read();
	return q;
}

//ʹ���������ÿ�
void MakeEmpty(MyQueue& q) {
	while (q->front != NULL) {
		Node* temp = new Node();
		temp = q->front;
		q->front = q->front->next;
		delete temp;
	}
}

//���˵�
void Menu(MyQueue q) {
	q=ReadOrClear(q);
	while (1) {
		cout << endl;
		cout << "|--------------------ѧ��ͨѶ¼ϵͳ---------------------|" << endl;
		cout << "|--------------------1 ���ѧ����Ϣ---------------------|" << endl;
		cout << "|--------------------2 ɾ��ѧ����Ϣ---------------------|" << endl;
		cout << "|--------------------3 ��ʾѧ����Ϣ---------------------|" << endl;
		cout << "|--------------------4 ��ѯѧ����Ϣ---------------------|" << endl;
		cout << "|--------------------5 ѧ����Ϣ����---------------------|" << endl;
		cout << "|--------------------6 �����Ļ��Ϣ---------------------|" << endl;
		cout << "|--------------------7 ����ĵ���Ϣ---------------------|" << endl;
		cout << "|--------------------8 �˳�����ϵͳ---------------------|" << endl;
		cout << "|-------------------------------------------------------|" << endl;
		int n;
		cout << "��������ѡ��" << endl;
		cin >> n;
		switch (n) {
			case 1: {
				ElementType x;
				cout << "�������ѧ������Ϣ��ѧ�� ���� �绰����" << endl;
				cin >> x.id >> x.name >> x.num;
				Insert(x, q);
				Write(q);
				cout << "�ѳɹ���Ӹ�ѧ����Ϣ!" << endl;
				break;
			}
			case 2: {
				cout << "�������ѧ����ѧ�ţ�" << endl;
				int num1;
				cin >> num1;
				if (!Delete(num1, q)) {
					cout << "��ϵͳ�в����ڸ�ѧ����" << endl;
				};
				break;
			}
			case 3: {
				cout << "���ڴ�ӡȫ��ѧ����Ϣ��.......���Ե�!" << endl;
				cout << "ȫ��ѧ������ϢΪ��" << endl;
				PrintAll(q);
				break;
			}
			case 4: {
				cout << "�������ѧ����������" << endl;
				string name1;
				cin >> name1;
				if (!FindByName(name1, q)) {
					cout << "��ϵͳ�в����ڸ�ѧ����" << endl;
				}
				break;
			}
			case 5: {
				cout << "���ڸ���ѧ����ѧ�Ŷ�ѧ����������....." << endl;
				cout << "������󣬽��Ϊ��" << endl;
				BubbleSort(q);
				PrintAll(q);
				break;
			}
			case 6: {
				system("cls");
				break;
			}
			case 7: {
				cout << "��������ȷ���Ƿ�Ҫ����ĵ��е�ȫ��ѧ����Ϣ����������롰yes��,����������롰no����" << endl;
				string s;
				cin >> s;
				if (s == "yes") { 
					//�ȰѶ����е�ȫ���ڵ㶼delete�����ٽ���д���ĵ���
					MakeEmpty(q);
					q = Init(q);
					Write(q);
					cout << "�Ѿ��ɹ�����ĵ��е�ȫ��ѧ����Ϣ��" << endl;
				}
				break;
			}
			case 8: {
				cout << "�˳��ɹ���" << endl;
				exit(0);
			}
			default:
				cout << "�����ѡ�������������������!" << endl;
		}
	}
}

int main() {
	MyQueue q;
	q = Init(q);
	Menu(q);
	return 0;
}

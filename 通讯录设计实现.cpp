#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>//读写文件的头文件
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

//初始化队列 
MyQueue Init(MyQueue& q) {
	q = new Queue();
	if (q == NULL) return NULL;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

//查看队列是否为空 
bool IsEmpty(MyQueue q) {
	return q->front == NULL;
}

//添加信息 
bool Insert(ElementType x, MyQueue q) {
	Node* temp = new Node();
	if (temp == NULL) return false;
	temp->data = x;//这里需要改成需要的内容，最好(必须)改成一个函数的形式，赋值的时候调用函数，打印的时候也调用函数
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

//删除功能 
bool Delete(const int message, MyQueue q) {
	Node* temp = new Node();
	if (temp == NULL) return false;//申请储存空间失败
	bool pd = 0;
	//先是找到这个id再进行删除
	//先判断是不是头节点，若不是再把头节点当首节点进行使用
	if (q->front->data.id == message) {//如果删除头节点
		temp = q->front;
		q->front = q->front->next;
		delete temp;
		temp = NULL;
		pd = 1;
	}
	else if (q->rear->data.id == message) {//如果删除尾节点
		//先找到尾节点的前一个结点
		temp = q->front;
		while (temp->next->data.id != message) temp = temp->next;
		q->rear = temp;
		q->rear->next = NULL;
		pd = 1;
	}
	else {//如果删除中间节点
		temp = q->front;
		while (temp->next != NULL && temp->next->data.id != message) temp = temp->next;
		if (temp->next == NULL) return false;//判断是不是没有找到，没有找到返回false
		Node* mp = new Node();
		mp = temp->next;
		temp->next = temp->next->next;
		delete mp;
		mp = NULL;
		pd = 1;
	}
	if (pd == 1) {
		Write(q);
		cout << "已成功删除该学生信息！" << endl;
		return true;
	}
}

//通过姓名进行查找 
bool FindByName(const string massage, const MyQueue q) {//此函数只有查找功能，没有打印功能，打印功能在另一个函数
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
		if (temp->next == NULL) return false;//没有找到这个人的姓名，返回false
		Print(temp->next);
		return true;
	}
}

//单个进行打印 
void Print(const Node* q) {
	cout << "该学生的信息为：" << endl;
	cout << "学号： " << q->data.id << " 姓名：" << q->data.name << " 电话号码：" << q->data.num << endl;
}

//打印全部的学生信息 
void PrintAll(const MyQueue q) {
	cout << "学号";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "姓名";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "电话号码" << endl;

	Node* temp;
	temp = q->front;
	while (temp != NULL) {
		cout << " " <<temp->data.id << "	      " << temp->data.name << "           " << temp->data.num << endl;
		temp = temp->next;
	}
	//cout << endl;
}

//实现排序的功能函数 
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

//把全部信息存入到文档中
void Write(MyQueue q) {
	//先根据学号进行排序，再进行存储
	q=BubbleSort(q);
	ofstream writeIt;
	writeIt.open("data.txt");
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已退出！" << endl;
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

//从文档中读出所有的信息
MyQueue Read() {
	ifstream readIt("data.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已退出！" << endl;
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

//读入文档中的信息
MyQueue ReadOrClear(MyQueue& q) {
	q=Read();
	return q;
}

//使整个队列置空
void MakeEmpty(MyQueue& q) {
	while (q->front != NULL) {
		Node* temp = new Node();
		temp = q->front;
		q->front = q->front->next;
		delete temp;
	}
}

//主菜单
void Menu(MyQueue q) {
	q=ReadOrClear(q);
	while (1) {
		cout << endl;
		cout << "|--------------------学生通讯录系统---------------------|" << endl;
		cout << "|--------------------1 添加学生信息---------------------|" << endl;
		cout << "|--------------------2 删除学生信息---------------------|" << endl;
		cout << "|--------------------3 显示学生信息---------------------|" << endl;
		cout << "|--------------------4 查询学生信息---------------------|" << endl;
		cout << "|--------------------5 学生信息排序---------------------|" << endl;
		cout << "|--------------------6 清空屏幕信息---------------------|" << endl;
		cout << "|--------------------7 清空文档信息---------------------|" << endl;
		cout << "|--------------------8 退出管理系统---------------------|" << endl;
		cout << "|-------------------------------------------------------|" << endl;
		int n;
		cout << "输入您的选择：" << endl;
		cin >> n;
		switch (n) {
			case 1: {
				ElementType x;
				cout << "请输入该学生的信息：学号 姓名 电话号码" << endl;
				cin >> x.id >> x.name >> x.num;
				Insert(x, q);
				Write(q);
				cout << "已成功添加该学生信息!" << endl;
				break;
			}
			case 2: {
				cout << "请输入该学生的学号：" << endl;
				int num1;
				cin >> num1;
				if (!Delete(num1, q)) {
					cout << "该系统中不存在该学生！" << endl;
				};
				break;
			}
			case 3: {
				cout << "正在打印全部学生信息中.......请稍等!" << endl;
				cout << "全部学生的信息为：" << endl;
				PrintAll(q);
				break;
			}
			case 4: {
				cout << "请输入该学生的姓名：" << endl;
				string name1;
				cin >> name1;
				if (!FindByName(name1, q)) {
					cout << "该系统中不存在该学生！" << endl;
				}
				break;
			}
			case 5: {
				cout << "正在根据学生的学号对学生进行排序....." << endl;
				cout << "排完序后，结果为：" << endl;
				BubbleSort(q);
				PrintAll(q);
				break;
			}
			case 6: {
				system("cls");
				break;
			}
			case 7: {
				cout << "请您在三确认是否要清空文档中的全部学生信息！清空请输入“yes”,不清空请输入“no”。" << endl;
				string s;
				cin >> s;
				if (s == "yes") { 
					//先把队列中的全部节点都delete掉，再进行写入文档中
					MakeEmpty(q);
					q = Init(q);
					Write(q);
					cout << "已经成功清空文档中的全部学生信息！" << endl;
				}
				break;
			}
			case 8: {
				cout << "退出成功！" << endl;
				exit(0);
			}
			default:
				cout << "输入的选项序号有误，请重新输入!" << endl;
		}
	}
}

int main() {
	MyQueue q;
	q = Init(q);
	Menu(q);
	return 0;
}

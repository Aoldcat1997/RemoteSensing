///*Define a friend class to facilitate direct manipulation of data*/
//#include<iostream>
//using namespace std;
//template<class T>
//class LinkList;
//template <class T>
//// 节点类
//class LinkNode
//{
//	// 链表友元类
//	// 在一个类中指明其他的类（或者）函数能够直接访问该类中的private和protected成员
//	friend class LinkList<T>;
//private:
//	T _data;
//	LinkNode<T>* _next;
//
//public:
//	LinkNode(T x)
//	{
//		_data = x;
//		_next = NULL;
//	}
//};
//
//template <class T>
//// 链表类，私有属性为LinkNode
//class LinkList
//{
//
//private:
//	// 头节点为私有属性
//	LinkNode<T>* _head;
//public:
//	LinkList()
//	{
//		_head = NULL;
//	}
//	LinkNode<T>* _CreateNode(const T& x);//Create a new node
//	void clear(LinkNode<T>*& cur);//Delete a new node
//	void PushBack(const T& x);//tail insertion to create a linked list
//	void PushFront(const T& x);//Head insertion to create a linked list
//	void PopBack();	//Remove an element from the tail
//	void PopFront();//Remove an element from the head
//	int Length();//Find the length of the linear table
//	LinkNode<T>* Find(T x);//Find a number
//	void Insert_right(int pos, const T& x);//Insert after the nth
//	void Insert_cur(int pos, const T& x);//Insert at the specified location
//	void Insert_left(int pos, const T& x);//Insert in front of the nth
//	void Delete_pos(int pos);//Delete the nth element
//	void Delete_val(const T& x);//Delete specified element
//	void reset(const T& x, const T& y);//Update an element
//	int located(const T& x);//Locate the serial number of the specified element
//	void Print();// Print linear table
//	bool writeToFile();//Write file
//	T* readFromFile();//Read in data file
//	int readlen();
//};
//
//template<class T>
//void LinkList<T>::Print()
//{
//	LinkNode<T>* tmp = _head;
//	while (tmp != NULL)
//	{
//		cout << tmp->_data << "-->";
//		//将指针移动到下一节点
//		tmp = tmp->_next;
//	}
//	cout << "NULL" << endl;
//}
//
//template <class T>
//LinkNode<T>* LinkList<T>::_CreateNode(const T& x)
//{
//	// 利用节点类，创建节点
//	LinkNode<T>* tmp = new LinkNode<T>(x);
//	return tmp;
//}
//
//template<class T>
//void LinkList<T>::clear(LinkNode<T>*& cur)
//{
//	// 当前指针指向一个空地址
//	cur->_next = NULL;
//	delete  cur;
//	cur = NULL;
//}
//
//template<class T>
//int LinkList<T> ::Length()
//{
//
//	int len = readlen();/*调用一个读文件的函数，来判别链表状态，Call a function that reads the file to determine the state of the linked list*/
//	if (len > 0) {
//		return len;
//	}
//	else {
//		len = 0;
//		if (_head == NULL)
//		{
//			return 0;
//		}
//		else
//		{
//			LinkNode<T>* begin = _head;
//			while (begin != NULL)
//			{
//				begin = begin->_next;
//				len++;
//			}
//		}
//	}
//	return len;
//}
//template<class T>
//int LinkList<T> ::Length()
//{
//
//	int len = readlen();/*调用一个读文件的函数，来判别链表状态，Call a function that reads the file to determine the state of the linked list*/
//	if (len > 0) {
//		return len;
//	}
//	else {
//		len = 0;
//		if (_head == NULL)
//		{
//			return 0;
//		}
//		else
//		{
//			LinkNode<T>* begin = _head;
//			while (begin != NULL)
//			{
//				begin = begin->_next;
//				len++;
//			}
//		}
//	}
//	return len;
//}
//
//template <class T>
//void LinkList<T> ::Delete_pos(int pos)
//{
//	int len = Length();
//	if (pos <= len)
//	{
//		if (_head == NULL)
//		{
//			cout << "List is empty!!!" << endl;
//		}
//		else if (_head->_next == NULL)
//		{
//			clear(_head);
//		}
//		else
//		{
//			LinkNode<T>* begin = _head->_next;
//			LinkNode<T>* temp = _head;
//			pos = pos - 1;
//			while (--pos)
//			{
//				if (begin->_next != NULL)
//				{
//					begin = begin->_next;
//					temp = temp->_next;
//				}
//			}
//			temp->_next = begin->_next;
//			begin->_next = temp;
//		}
//	}
//	else
//	{
//		cout << "Input Error!!!" << endl;
//	}
//}
//
//
//template <class T>
//void LinkList<T> ::PushFront(const T& x)
//{
//	if (_head == NULL)
//	{
//		_head = _CreateNode(x);
//	}
//	else
//	{
//		LinkNode<T>* prev = _CreateNode(x);
//		prev->_next = _head;
//		_head = prev;
//	}
//}
//
//
//template <class T>
//void LinkList<T> ::PushBack(const T& x)
//{
//	if (_head == NULL)
//	{
//		_head = _CreateNode(x);
//	}
//	else
//	{
//		LinkNode<T>* end = _head;
//		while (end->_next != NULL)
//		{
//			end = end->_next;
//		}
//		end->_next = _CreateNode(x);
//	}
//}
//
//template <class T>
//void LinkList<T> ::PopBack()
//{
//	if (_head == NULL)
//	{
//		cout << "The List is empty!!!" << endl;
//		return;
//	}
//	else if (_head->_next == NULL)
//	{
//		clear(_head);
//	}
//	else
//	{
//		LinkNode<T>* temp = _head;
//		LinkNode<T>* end = _head;
//		while (end->_next != NULL)
//		{
//			temp = end;
//			end = end->_next;
//		}
//		temp->_next = NULL;
//		clear(end);
//	}
//}
//template <class T>
//void LinkList<T> ::PopFront()
//{
//	if (_head == NULL)
//	{
//		cout << "List is empty!!!" << endl;
//		return;
//	}
//	else if (_head->_next == NULL)
//	{
//		clear(_head);
//	}
//	else
//	{
//		LinkNode<T>* tmp = _head;
//		_head = _head->_next;
//		clear(tmp);
//		tmp = NULL;
//	}
//}
//template <class T>
//LinkNode<T>* LinkList<T> ::Find(T x)
//{
//	if (_head == NULL)
//	{
//		cout << "List is empty,not found!!!" << endl;
//		return NULL;
//	}
//	else if (_head->_data == x)
//	{
//		return _head;
//	}
//	else
//	{
//		LinkNode<T>* n = _head;
//		while (n->_next != NULL && n->_data != x)
//		{
//			n = n->_next;
//			if (n->_data == x)
//			{
//				return n;
//			}
//		}
//	}
//	return NULL;
//}
//template <class T>
//void LinkList<T> ::Insert_right(int pos, const T& x)
//{
//	int len = Length();
//	if (pos <= len)
//	{
//		if (_head == NULL)
//		{
//			cout << "List is empty!!!" << endl;
//			return;
//		}
//		else
//		{
//			LinkNode<T>* begin = _head;
//			LinkNode<T>* tmp = _CreateNode(x);
//			while (--pos)
//			{
//				if (begin->_next != NULL)
//				{
//					begin = begin->_next;
//				}
//			}
//			tmp->_next = begin->_next;
//			begin->_next = tmp;
//		}
//	}
//	else
//	{
//		cout << "Input Error!!!" << endl;
//	}
//}
//
//template <class T>
//void LinkList<T> ::Insert_cur(int pos, const T& x)
//{
//	int len = Length();
//	if (pos <= len)
//	{
//		if (_head == NULL)
//		{
//			cout << "List is empty!!!" << endl;
//			return;
//		}
//		else
//		{
//			Insert_right(pos - 1, x);
//		}
//	}
//	else
//	{
//		cout << "Input Error!!!" << endl;
//	}
//}
//
//template <class T>
//void LinkList<T> ::Insert_left(int pos, const T& x)
//{
//	int len = Length();
//	int temp = pos - 1;
//	if (pos <= len)
//	{
//		if (_head == NULL)
//		{
//			cout << "List is empty!!!" << endl;
//			return;
//		}
//		else
//		{
//			LinkNode<T>* begin = _head;
//			LinkNode<T>* tmp = _CreateNode(x);
//			while (--temp)
//			{
//				if (begin->_next != NULL)
//				{
//					begin = begin->_next;
//				}
//			}
//			tmp->_next = begin->_next;
//			begin->_next = tmp;
//		}
//	}
//	else
//	{
//		cout << "Input Error!!!" << endl;
//	}
//}
//
//template <class T>
//int LinkList<T> ::located(const T& x)
//{
//	if (_head == NULL)
//	{
//		cout << "List is empty,not found!!!" << endl;
//		return -1;
//	}
//	else if (_head->_data == x)
//	{
//		return 1;
//	}
//	else
//	{
//		LinkNode<T>* n = _head;
//		int temp = 0;
//		while (n->_next != NULL && n->_data != x)
//		{
//			n = n->_next;
//			temp++;
//			if (n->_data == x)
//			{
//				return temp + 1;
//			}
//		}
//	}
//	return -1;
//}
//
//
//template <class T>
//void LinkList<T> ::Delete_val(const T& x)
//{
//	if (_head == NULL)
//	{
//		cout << "List is empty!!!" << endl;
//		return;
//	}
//	else if (_head->_next == NULL && _head->_data == x)
//	{
//		clear(_head);
//		return;
//	}
//	else
//	{
//		if (_head->_data == x) {
//			while (1) {
//				if (_head->_data != x)break;
//				PopFront();
//			}
//		}
//		else
//		{
//			while (1)
//			{
//				LinkNode<T>* n = Find(x);
//				if (n == NULL)break;
//				else {
//					LinkNode<T>* begin = _head;
//					while (begin->_next != n && begin->_next != NULL)
//					{
//						begin = begin->_next;
//					}
//					begin->_next = n->_next;
//					clear(n);
//				}
//
//			}
//			return;
//		}
//	}
//	return;
//}
//
//template <class T>
//inline void LinkList<T>::reset(const T& x, const T& y)
//{
//	if (_head == NULL)
//	{
//		cout << "List is empty!!!" << endl;
//		return;
//	}
//	else
//	{
//		while (1)
//		{
//			LinkNode<T>* n = Find(x);
//			if (n == NULL)break;
//			else {
//				n->_data = y;
//			}
//		}
//	}
//}
//
//
//template <class T>
//inline bool LinkList<T>::writeToFile()
//{
//	ofstream writefile("data.txt");
//	int len;
//	len = Length();
//	writefile << len << endl;
//	LinkNode<T>* begin = _head;
//	while (begin != NULL)
//	{
//		writefile << begin->_data << endl;
//		begin = begin->_next;
//	}
//	return true;
//}
//
//template <class T>
//inline T* LinkList<T>::readFromFile()
//{
//	ifstream readfile("data.txt");
//	int length;
//	readfile >> length;
//	T* temp = new T[length];
//	for (int i = 0; i < length; i++)
//	{
//		readfile >> temp[i];
//	}
//	return temp;
//}
//
//
//template <class T>
//inline int LinkList<T>::readlen()
//{
//	// 文件读取函数
//	ifstream readfile("data.txt");
//	int length;
//	readfile >> length;
//	return length;
//}
//
//class Point
//{
//private:
//	double x;
//	double y;
//public:
//	Point(double x = 0.0, double y = 0.0)
//	{
//		this->x = x, this->y = y;
//	}
//	void setdata(double a, double b)
//	{
//		this->x = a; this->y = b;
//	}
//	Point operator=(Point a);//重载运算符“=”
//	int operator==(Point a);//重载运算符“==”
//	int operator!=(Point a);
//	double getx()
//	{
//		return x;
//	}
//	double gety()
//	{
//		return y;
//	}
//	//重载输入流
//	friend istream& operator>>(istream& is, Point& p)
//	{
//		is >> p.x;
//		is >> p.y;
//		return is;
//	}//重载输出流
//	friend ostream& operator<<(ostream& os, Point p)
//	{
//		os << "(" << p.x << "," << p.y << ")";
//		return os;
//	}
//};
//
//inline Point Point::operator=(Point a)
//{
//	this->x = a.x;
//	this->y = a.y;
//	return *this;
//}
//inline int Point::operator==(Point a)
//{
//	if (this->x == a.getx() && this->y == a.gety())
//	{
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//inline int Point::operator!=(Point a)
//{
//	if (this->x != a.getx() && this->y != a.gety())
//	{
//		return 1;
//	}
//	else if (this->x != a.getx() || this->y != a.gety()) {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//

///*
//Perform some basic operations on the linear table of the chained storage structure. mainly includes:
//(1) Insert: The operation mode is to insert before the specified element, insert after the specified element, and insert at the specified position.
//(2) Delete: The operation mode can be divided into deleting the specified element, deleting the element of the specified position, and the like, and attempting to implement the logical deletion operation.
//(3) Display data
//(4) Find: Query the specified element (can complete the query operation according to a certain data member)
//(5) Positioning operation: locating the serial number of the specified element
//(6) Update: modify the data of the specified element
//(7) Read and write operations of data files, etc.
//Other operations can be supplemented according to specific needs.
//The linear table is required to use the definition of the class, the type of the data object is defined by itself, and the experimental single linked list and the doubly linked list are selected by themselves.
//*/
//#include<iostream>
//#include <fstream>
//using namespace std;
//template<class T>
//class LinkList;
//template <class T>
///*Define a friend class to facilitate direct manipulation of data*/
//class LinkNode
//{
//	friend class LinkList<T>;
//private:
//	T _data;
//	LinkNode<T>* _next;
//public:
//	LinkNode(T x)
//	{
//		_data = x;
//		_next = NULL;
//	}
//};
//template <class T>
//class LinkList
//{
//
//private:
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
//template<class T>
//void LinkList<T>::Print()
//{
//	LinkNode<T>* tmp = _head;
//	while (tmp != NULL)
//	{
//		cout << tmp->_data << "-->";
//		tmp = tmp->_next;
//	}
//	cout << "NULL" << endl;
//}
////����һ���µĽ�㣬��Ϊ�����ռ�
////Create a new node and allocate space for it
//template <class T>
//LinkNode<T>* LinkList<T>::_CreateNode(const T& x)
//{
//	LinkNode<T>* tmp = new LinkNode<T>(x);
//	return tmp;
//}
////���ĳһ���ڵ㣬�ͷſռ�
////Clear a node and free up space
//template<class T>
//void LinkList<T>::clear(LinkNode<T>*& cur)
//{
//	cur->_next = NULL;
//	delete  cur;
//	cur = NULL;
//}
////�������ĳ���
////Get the length of the linked list
//template<class T>
//int LinkList<T> ::Length()
//{
//
//	int len = readlen();/*����һ�����ļ��ĺ��������б�����״̬��Call a function that reads the file to determine the state of the linked list*/
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
///*ǰ�巨��������
//��һ���ձ�ʼ���ظ��������ݣ�ִ����������
//��1�������µĽ�㣬���������ݴ�����½ڵ�ĵ�_data����
//��2�����ýڵ���뵽�����ǰ�ˣ�ֱ�����뵽������Ϊֹ��
//Start with an empty table, read the data repeatedly, and perform the following two steps.
//(1) Generate a new node and store the read data in the _data field of the new node.
//(2) Insert the node into the front end of the linked list until the end character is read.
//*/
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
///*�ú�巨����������Ҫ����һ��β��ָ��end,����ָ������������һ���ڵ㣬�½ڵ����ӵ�����ָ��β�ڵ�ĺ��档end���Ҫ���ڸ���ͷ�ڵ�λ��
//To build a linked list with post-insertion, you need to set a tail pointer end, always pointing to the last node of the new linked list, and the new node is linked to the end of the chain end node it refers to. End is initially placed at the location of the additional head node
//*/
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
///*��β��ɾ��һ�����ݣ�����ֻ��һ���ڵ������������������
//�����㣬�����ҵ�β��Ԫ�أ�Ȼ�����clear()�����������β����һ��Ԫ��
//Remove a data from the tail, considering the case of only one node, multiple nodes.
//Multiple nodes, first find the tail element, then call the clear() function to clean up the first element of the tail*/
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
///*��ͷ��ɾ��һ��Ԫ�أ�ʵ�ַ����ʹ�β��ɾ��һ��Ԫ�ػ������ƣ�������Խ���
//Deleting an element from the head, the implementation method is basically similar to deleting an element from the tail, not much explanation*/
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
///*����ĳһ��Ԫ�أ�����������������������_data��x���бȶԣ�������������;���Ҫ���������==
//Find an element, traverse the entire list, and compare its data _data with x. If it is another type, you need to overload the operator ==*/
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
///*�ڵ�pos��Ԫ�غ����һ����Ԫ�أ�����һ���µĽ�㣬ͨ���ƶ�beginָ�룬pos����ָ������λ�ã�����Ԫ�ز��뵽֮��
//Insert a new element after the pos element, create a new node, by moving the begin pointer, pos controls the final position of the pointer, inserting the new element after*/
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
///*�ڵ�pos��Ԫ�ز���һ����Ԫ�أ���Ϊд��һ���ں������ĺ�����Ϊ��͵������ֱ�ӵ�����Insert_right()�������
//Insert a new element in the pos element, because a function inserted later is written. In order to be lazy, the function Insert_right() is called directly.
//*/
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
///*�ڵ�pos��Ԫ��ǰ����һ����Ԫ�أ�����һ���µĽ�㣬ͨ���ƶ�beginָ�룬pos����ָ������λ�ã�����Ԫ�ز��뵽֮ǰ�������֮��ʵ�ַ����������ƣ�ֻ����Ҫע��pos�Ŀ���
//Insert a new element in front of the pos element, create a new node, by moving the begin pointer, pos controls the final position of the pointer, inserting the new element before, and the implementation method is basically similar to the method after inserting, just need to pay attention to the control of pos
//*/
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
///*ɾ����pos��Ԫ�أ���������pos����ָ��λ�ã�Ȼ��ɾ����ok
//Delete the pos element, still use pos to control the pointer position, then delete it ok
//*/
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
///*����ĳһ��Ԫ��λ�ã���������λ�ã���һ��temp���м�����������������һһ���бȶ��䡪��data���ݣ������������;���Ҫ�����������=��������ĺ����ᵽ�ȶԵĶ���Ҫʵ�֣����ܽ��бȶԣ��ȶԳɹ��ͷ��أ��������ʵ����Ȼ��Ҫ����
//Find a certain element position, and return its position, use a temp to count, traverse the entire linked list, one by one than it - data data (if other types need to overload the operator "=", the latter function mentioned The comparison needs to be implemented in order to compare. If the comparison is successful, it will return. The implementation of other classes still needs to be overloaded.
//*/
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
///*ɾ��ָ����Ԫ�أ���������һһ�ȶԣ��ҵ��͵���chear()����ɾ��������ռ�
//Delete the specified element, traverse the linked list, compare one by one, find the call to the chear () function to delete and clean up the space*/
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
///*����ָ��Ԫ�ص�ֵ����������һһ�ȶԣ�ǰ���ᵽ�����صģ����ҵ�Ҫ���µ�Ԫ�غ�ͽ��µ�ֵ��ֵ����
//Update the value of the specified element, traverse the linked list, one-to-one comparison (above mentioned overloaded), find the element to be updated and assign the new value to it
//*/
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
///*�����������д���ļ�����ʵ���������ݵĴ��棬��������������࣬д��û�����⣬������ͬһ���ļ��ж���֮ǰд�����ݣ�����һЩ����û��ʵ�֣����ǻ�������������ok��,���Ժ����ͱ��ֳ����˵ģ�������Ķ�����Ҫ�������������������
//Write the data of the linked list to the file, which can store all the data, but if it is other classes, there is no problem in writing. If you want to read the previously written data from the same file, some difficulties are not realized, but the basic data. The type is ok, the test function is shown��(Reading of other classes requires overloading the input stream, output stream)
//*/
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
///*���ļ�������ǰд������ݣ��������ᵽֻ�����������������
//Read the previously written data from the file, mentioned above only can meet the basic data type
//*/
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
///*Ϊ�˸��õĲ�����������غ����Ĺ��ܣ�д������һ�����������ļ��õ������ȵĺ���
//For better operation, test the function of the related function, write a function that gets the length of the linked list from the file.
//*/
//template <class T>
//inline int LinkList<T>::readlen()
//{
//	ifstream readfile("data.txt");
//	int length;
//	readfile >> length;
//	return length;
//}
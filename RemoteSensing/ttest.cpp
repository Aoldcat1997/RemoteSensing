//#include "LinkList.h"
//#include "Point.h"
////����pointʱ����
//void point_();
////����intʱ����
//void int_();
//void Menu()
//{
//	cout << "	* * * * * * * welcome to use SeqList* * * * * * * * *" << endl;
//	cout << "	*	1. ��彨������		2. ǰ�彨������       *" << endl;
//	cout << "	*	3. ɾ����ʼ����		4. ɾ���������       *" << endl;
//	cout << "	*	5. ����Ԫ��֮ǰ		6. ����Ԫ��֮��       *" << endl;
//	cout << "	*	7. ��ǰλ�ò���	        8.ɾ��ָ��λ��Ԫ��     *" << endl;
//	cout << "	*	9. ɾ��ָ��Ԫ��	        10.�� ��             *" << endl;
//	cout << "	*	11. �������	        12.��ʾ����           *" << endl;
//	cout << "	*	13. ��λָ��Ԫ��λ��	14.��������           *" << endl;
//	cout << "	*	15. ����ָ��Ԫ������    0.�˳�                  *" << endl;
//	cout << "	*        		    			     *" << endl;
//	cout << "	* * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
//
//	/*
//	cout << "	* * * * * * * * * * * * * * * *welcome to use SeqList* * * * * * * * * * * * * * * * * * * * *" << endl;
//	cout << "	*	1. Post-insertion		             2. Pre-plugging                         *" << endl;
//	cout << "	*	3. Delete start data		             4. Delete last data                     *" << endl;
//	cout << "	*	5. Before inserting an element		     6. After inserting the element          *" << endl;
//	cout << "	*	7.Current position insertion	             8.Delete specified location element     *" << endl;
//	cout << "	*	9.Delete specified element	             10.Search                               *" << endl;
//	cout << "	*	11. Output length	                     12.Display Data                         *" << endl;
//	cout << "	*	13. Locate the specified element location    14.Save data                            *" << endl;
//	cout << "	*	15. Update specified element data            0.Drop out                              *" << endl;
//	cout << "	*        		    			                                              *" << endl;
//	cout << "	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
//	*/
//}
//int main()
//{
//	//point_();
//	int_();
//	return 0;
//}
//void point_() {
//	Point temp;
//	temp.setdata(0, 0);
//	Point Item;
//	LinkList<Point> mylist;
//	int select = 1;
//	int pos;
//	Menu();
//	while (select)
//	{
//		cout << "Please select:			          " << endl;
//		cin >> select;
//		switch (select)
//		{
//		case 1:
//			if (mylist.readlen() != 0)
//			{
//				ifstream readfile("point.txt");
//				int length, x, y;
//				readfile >> length;
//				Point temp[length];
//				for (int i = 0; i < length; i++)
//				{
//					readfile >> x;
//					readfile >> y;
//					temp[i].setdata(x, y);
//				}
//				for (int i = 0; i < length; i++)
//				{
//					mylist.PushBack(temp[i]);
//				}
//			}
//			break;
//		case 2:
//			if (mylist.readlen() != 0)
//			{
//				ifstream readfile("point.txt");
//				int length, x, y;
//				readfile >> length;
//				Point  temp[length];
//				for (int i = 0; i < length; i++)
//				{
//					readfile >> x;
//					readfile >> y;
//					temp[i].setdata(x, y);
//				}
//				for (int i = 0; i < length; i++)
//				{
//					mylist.PushFront(temp[i]);
//				}
//			}
//			break;
//		case 3:
//			mylist.PopFront();
//			break;
//		case 4:
//			mylist.PopBack();
//			break;
//		case 5:
//			cout << "������Ҫ�����λ��:" << endl;
//			cin >> pos;
//			cout << "������Ҫ�����ֵ:" << endl;
//			cin >> Item;
//			mylist.Insert_left(pos, Item);
//			break;
//		case 6:
//			cout << "������Ҫ�����λ��:" << endl;
//			cin >> pos;
//			cout << "������Ҫ�����ֵ:" << endl;
//			cin >> Item;
//			mylist.Insert_right(pos, Item);
//			break;
//		case 7:
//			cout << "������Ҫ�����λ��:" << endl;
//			cin >> pos;
//			cout << "������Ҫ�����ֵ:" << endl;
//			cin >> Item;
//			mylist.Insert_cur(pos, Item);
//			break;
//		case 8:
//			cout << "������Ҫɾ����λ��:" << endl;
//			cin >> pos;
//			mylist.Delete_pos(pos);
//			break;
//		case 9:
//			cout << "������Ҫɾ����ֵ:" << endl;
//			cin >> Item;
//			mylist.Delete_val(Item);
//			break;
//		case 10:
//			cout << "������Ҫ���ҵ�ֵ:" << endl;
//			cin >> Item;
//			mylist.Find(Item);
//			break;
//		case 11:
//			cout << "�����Ա�ĳ���Ϊ��" << mylist.Length() << endl;
//			break;
//		case 12:
//			mylist.Print();
//			break;
//		case 13:
//			cout << "������Ҫ���ҵ�ֵ:" << endl;
//			cin >> Item;
//			int che;
//			che = mylist.located(Item);
//			if (che >= 0) {
//				cout << "��Ԫ�ص����Ϊ��" << mylist.located(Item) << endl;
//			}
//			else {
//				cout << "��Ԫ�ز�����!" << endl;
//			}
//			break;
//		case 14:
//			mylist.writeToFile();
//			break;
//		case 15:
//			cout << "������Ҫ���µ�ֵ:" << endl;
//			cin >> Item;
//			cout << "������Ҫ����Ϊ:" << endl;
//			cin >> temp;
//			mylist.reset(Item, temp);
//			break;
//		case 0:
//			exit(0);
//		default:
//			break;
//		}
//		cout << endl;
//		Menu();
//	}
//
//}
//void int_()
//{
//	int temp = -1;
//	int Item;
//	LinkList<int> mylist;
//	int select = 1;
//	int pos;
//	Menu();
//	while (select)
//	{
//		cout << "Please select:			          " << endl;
//		cin >> select;
//		switch (select)
//		{
//		case 1:
//			if (mylist.readlen() != 0)
//			{
//
//				int* sum = mylist.readFromFile();
//				for (int i = 0; i < mylist.Length(); i++)
//				{
//					mylist.PushBack(sum[i]);
//				}
//				delete[]sum;
//			}
//			else {
//				cout << "������Ҫ����ֵ(-1����):" << endl;;
//				while (cin >> Item)
//				{
//					if (Item == temp)break;
//					mylist.PushBack(Item);
//				}
//			}
//			break;
//		case 2:
//			if (mylist.readlen() != 0)
//			{
//
//				int* sum = mylist.readFromFile();
//				for (int i = 0; i < mylist.Length(); i++)
//				{
//					mylist.PushFront(sum[i]);
//				}
//				delete[]sum;
//			}
//			else {
//				cout << "������Ҫͷ���ֵ(-1����):" << endl;;
//				while (cin >> Item)
//				{
//					if (Item == temp)break;
//					mylist.PushFront(Item);
//				}
//			}
//			break;
//		case 3:
//			mylist.PopFront();
//			break;
//		case 4:
//			mylist.PopBack();
//			break;
//		case 5:
//			cout << "������Ҫ�����λ��:" << endl;
//			cin >> pos;
//			cout << "������Ҫ�����ֵ:" << endl;
//			cin >> Item;
//			mylist.Insert_left(pos, Item);
//			break;
//		case 6:
//			cout << "������Ҫ�����λ��:" << endl;
//			cin >> pos;
//			cout << "������Ҫ�����ֵ:" << endl;
//			cin >> Item;
//			mylist.Insert_right(pos, Item);
//			break;
//		case 7:
//			cout << "������Ҫ�����λ��:" << endl;
//			cin >> pos;
//			cout << "������Ҫ�����ֵ:" << endl;
//			cin >> Item;
//			mylist.Insert_cur(pos, Item);
//			break;
//		case 8:
//			cout << "������Ҫɾ����λ��:" << endl;
//			cin >> pos;
//			mylist.Delete_pos(pos);
//			break;
//		case 9:
//			cout << "������Ҫɾ����ֵ:" << endl;
//			cin >> Item;
//			mylist.Delete_val(Item);
//			break;
//		case 10:
//			cout << "������Ҫ���ҵ�ֵ:" << endl;
//			cin >> Item;
//			mylist.Find(Item);
//			break;
//		case 11:
//			cout << "�����Ա�ĳ���Ϊ��" << mylist.Length() << endl;
//			break;
//		case 12:
//			mylist.Print();
//			break;
//		case 13:
//			cout << "������Ҫ���ҵ�ֵ:" << endl;
//			cin >> Item;
//			int che;
//			che = mylist.located(Item);
//			if (che >= 0) {
//				cout << "��Ԫ�ص����Ϊ��" << mylist.located(Item) << endl;
//			}
//			else {
//				cout << "��Ԫ�ز�����!" << endl;
//			}
//			break;
//		case 14:
//			mylist.writeToFile();
//			break;
//		case 15:
//			cout << "������Ҫ���µ�ֵ:" << endl;
//			cin >> Item;
//			cout << "������Ҫ����Ϊ:" << endl;
//			cin >> temp;
//			mylist.reset(Item, temp);
//			break;
//		case 0:
//			exit(0);
//		default:
//			break;
//		}
//		cout << endl;
//		Menu();
//	}
//}
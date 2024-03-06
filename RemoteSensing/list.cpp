//#include<iostream>
//using namespace std;
//
//const int MaxSize = 100;
//// ģ����
//template <class DataType>
//class SeqList
//{
//public:
//    // Ĭ�Ϲ��캯��,��ʼ��
//    SeqList() { length = 0; }
//    // ��ֵ���캯��
//    SeqList(DataType a[], int n);
//    // ��������
//    ~SeqList() {}
//    // ����
//    int Length() { return length; }
//    // 
//    // ��ȡԪ��
//    DataType Get(int i);
//    // ȷ��Ԫ��λ��
//    int Locate(DataType x);
//    // ����Ԫ��
//    void Insert(int i, DataType x);
//    // ɾ��ĳ��λ��Ԫ��
//    DataType Delete(int i);
//    void PrintList();
//private:
//    // �����������
//    DataType data[MaxSize];
//    // ���ݳ���
//    int length;
//};
//// ��ֵ��ʼ��
//template <class DataType>
//// ��ĳ�Ա����
//SeqList<DataType>::SeqList(DataType a[], int n)
//{
//    if (n > MaxSize) throw "wrong parameter";
//    // ������ֵ
//    for (int i = 0; i < n; i++)
//        data[i] = a[i];
//
//    length = n;
//}
//
//template <class DataType>
//DataType SeqList<DataType>::Get(int i)
//{
//    // ��֤����
//    if (i<1 && i>length) throw "wrong Location";
//    // ֱ�ӷ�������
//    // ���ظ�����
//    else return data[i - 1];
//}
//
//template <class DataType>
//// ��Ա����
//int SeqList<DataType>::Locate(DataType x)
//{
//    for (int i = 0; i < length; i++)
//        if (data[i] == x) return i + 1;
//    return 0;
//}
//
//template <class DataType>
//// ��������ͨ�����ݺ���ʵ��
//void SeqList<DataType>::Insert(int i, DataType x)
//{
//    if (length >= MaxSize) throw "Overflow";
//    if (i<1 || i>length + 1) throw "Location";
//    for (int j = length; j >= i; j--)
//        data[j] = data[j - 1];
//    data[i - 1] = x;
//    length++;
//}
//
//template <class DataType>
//DataType SeqList<DataType>::Delete(int i)
//{
//    int x;
//    if (length == 0) throw "Underflow";
//    if (i<1 || i>length) throw "Location";
//    x = data[i - 1];
//    // ɾ��ͨ������ǰ��ʵ��
//    for (int j = i; j < length; j++)
//        data[j - 1] = data[j];
//    length--;
//    return x;
//}
//
//template <class DataType>
//void SeqList<DataType>::PrintList()
//{
//    for (int i = 0; i < length; i++)
//        cout << data[i] << endl;
//}
//
//int main()
//{
//    // ʵ����
//    SeqList<int> p;
//    // ���ò�������
//    p.Insert(1, 5);
//    p.Insert(2, 9);
//    // ��ӡ�б�
//    p.PrintList();
//    p.Insert(2, 3);
//    cout << p.Length() << endl;
//    p.PrintList();
//    cout << p.Get(3) << endl;
//    p.Delete(2);
//    p.PrintList();
//    return 0;
//}
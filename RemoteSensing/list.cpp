//#include<iostream>
//using namespace std;
//
//const int MaxSize = 100;
//// 模板类
//template <class DataType>
//class SeqList
//{
//public:
//    // 默认构造函数,初始化
//    SeqList() { length = 0; }
//    // 赋值构造函数
//    SeqList(DataType a[], int n);
//    // 析构函数
//    ~SeqList() {}
//    // 长度
//    int Length() { return length; }
//    // 
//    // 获取元素
//    DataType Get(int i);
//    // 确定元素位置
//    int Locate(DataType x);
//    // 插入元素
//    void Insert(int i, DataType x);
//    // 删除某个位置元素
//    DataType Delete(int i);
//    void PrintList();
//private:
//    // 数据最大容量
//    DataType data[MaxSize];
//    // 数据长度
//    int length;
//};
//// 赋值初始化
//template <class DataType>
//// 类的成员函数
//SeqList<DataType>::SeqList(DataType a[], int n)
//{
//    if (n > MaxSize) throw "wrong parameter";
//    // 遍历赋值
//    for (int i = 0; i < n; i++)
//        data[i] = a[i];
//
//    length = n;
//}
//
//template <class DataType>
//DataType SeqList<DataType>::Get(int i)
//{
//    // 验证输入
//    if (i<1 && i>length) throw "wrong Location";
//    // 直接访问数组
//    // 返回该数据
//    else return data[i - 1];
//}
//
//template <class DataType>
//// 成员函数
//int SeqList<DataType>::Locate(DataType x)
//{
//    for (int i = 0; i < length; i++)
//        if (data[i] == x) return i + 1;
//    return 0;
//}
//
//template <class DataType>
//// 插入数据通过数据后移实现
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
//    // 删除通过数据前移实现
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
//    // 实例化
//    SeqList<int> p;
//    // 调用插入数据
//    p.Insert(1, 5);
//    p.Insert(2, 9);
//    // 打印列表
//    p.PrintList();
//    p.Insert(2, 3);
//    cout << p.Length() << endl;
//    p.PrintList();
//    cout << p.Get(3) << endl;
//    p.Delete(2);
//    p.PrintList();
//    return 0;
//}
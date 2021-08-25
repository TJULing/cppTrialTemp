
/*
#include<iostream>
//#include<string.h>
using namespace std;


int main() {

	int aInt = 1;
	int* pInt = &aInt;
	//delete pInt; //释放局部变量会崩溃
	pInt = new int;
	delete pInt;
	pInt = nullptr;
	//delete pInt; //若不置空或赋给新的地址，而重复释放堆中内存也会崩溃
	
	std::cout <<"====================="<<'\n';
	std::cout << "字符串本质是以空字符结尾的字符数组"<<'\n';
	
	char charBuff1[] = {'s','t','u','p','i','d','!','\0'}; //字符数组 创建并初始化1，无需指定数组大小，需要手动加“\0”；
	std::cout << charBuff1 <<"\t大小：(含末尾)\t"<<sizeof(charBuff1) <<endl;

	char charBuff2[] = "hello world!"; //字符数组 创建并初始化2;
	std::cout << charBuff2 << "\t大小：(含末尾)\t" << sizeof(charBuff2) << endl;
	
	char charBuff3[51]; //创建字符数组缓冲区，须提前声明大小，后续使用注意越界和空格问题（cin不能自动检查,cin.geline()可以）；
	std::cout << "请输入50个以内字符：（cin默认输入方式：1.不能检查越界问题（发生越界会运行时报错）；2.遇空格会忽略后续内容）" << endl;
	//std::cin >> charBuff3;//注意问题：1.不自动检查越界问题；2.遇空格自动停止；
	std::cin.getline(charBuff3, 50);
	std::cout << charBuff3 << endl;
		
	char charBuff4[51];
	std::cin.getline(charBuff4,50);//cin.getline(char *_Str,streamSize)，第二参数指定了最长输入字符数，超出部分会忽略；默认换行符\n作为分隔符，可在第三参数指定其他；
	std::cout <<"通过cin.getling()函数控制输入字符数50，并指定终止的分隔符"<<'\n';
	std::cout <<charBuff4<< '\n';
	
	const char* charPtr = "a const char pointer can also 用于存储字符串";
	std::cout << charPtr << endl;
}
*/


//各种重载运算符的问题与例子
//参考：https://www.runoob.com/cplusplus/cpp-overloading.html；
//		https://www.cnblogs.com/codingmengmeng/p/5871254.html


/*
// 各种重载运算符，可以：
//（1）返回void：不能适用与连续赋值情形，如：a=b=c; display(a=b);等
//（2）按值返回：不能适用于某些连续赋值情形，如：(a=b)=c;
//（3）按引用返回：推荐：适用最广，且高效（省去调用复制构造函数和析构函数）

#include <iostream>
using namespace std;

class Time
{
private:
	int hours;             // 0 到 23
	int minutes;           // 0 到 59
public:
	// 所需的构造函数
	Time() {
		hours = 0;
		minutes = 0;
	}
	Time(int h, int m) {
		hours = h;
		minutes = m;
	}
	// 显示时间的方法
	void displayTime() { cout << "H: " << hours << " M:" << minutes << endl; }//只能由非const的Time对象调用，而不能被const的Time对象调用
	void displayTime() const { cout << "H: " << hours << " M:" << minutes << endl; }//能被 非const和const的Time对象 调用

	// 重载前缀递增运算符（ ++ ）
	Time operator++ () //按引用返回对象自身：存在问题——对于形如（a = b） = c）的连续赋值情况，将不会得到预期结果
	//Time & operator() //按引用返回对象自身
	{
		++minutes;          // 对象加 1
		if (minutes >= 60)
		{
			++hours;
			minutes -= 60;
		}
		return Time(hours, minutes);//新建副本，并按值返回
		//return *this；//按引用返回对象自身
	}
	// 重载后缀递增运算符（ ++ ）：增加 int 参数（不使用）；函数内创建原始值临时副本；对象自身++；但仅返回临时副本。
	Time operator++(int)
	{
		// 新建临时对象（局部变量） 用于保存原始值
		Time T(hours, minutes);//调用构造函数

		// 对象自身递增
		++minutes;
		if (minutes >= 60)
		{
			++hours;
			minutes -= 60;
		}
		// 返回旧的原始值 （局部变量 必须按值返回）
		return T;
	}
};
int main()
{
	const Time TT;
	//const对象只能调用const成员函数,必须要提供一个const版本的成员函数
	TT.displayTime();//TT为const Time，即常量对象，调用dispalyTime()时，隐式地传递了const Time * const this指针
					 //但displayTime()只有非const版本，接受参数时不能将 const Time类型this 转为 Time类型this
					 //故出现error：“void Time::displayTime(void)”: 不能将“this”指针从“const Time”转换为“Time &”
					 //注：c++对类的this指针做了隐藏，本质上，const指针修饰的是被隐藏的this指针：const 类名 * const this
					 //解决办法：提供const版本成员函数
					 //tips：尽量对不修改成员数据的函数都设为const，也可重载成 非const版本和const版本

	Time T1(11, 59), T2(10, 40);

	++T1;                    // T1 加 1
	T1.displayTime();        // 显示 T1
	++T1;                    // T1 再加 1
	T1.displayTime();        // 显示 T1

	T2++;                    // T2 加 1
	T2.displayTime();        // 显示 T2
	T2++;                    // T2 再加 1
	T2.displayTime();        // 显示 T2
	return 0;
}
*/

/*总结：

1）const成员函数可以访问非const对象的非const数据成员、const数据成员，也可以访问const对象内的所有数据成员；

2）非const成员函数可以访问非const对象的非const数据成员、const数据成员，但不可以访问const对象的任意数据成员；

3）作为一种良好的编程风格，在声明一个成员函数时，若该成员函数并不对数据成员进行修改操作，应尽可能将该成员函数声明为const 成员函数。

4）如果只有const成员函数，非const对象是可以调用const成员函数的。当const版本和非const版本的成员函数同时出现时，非const对象调用非const成员函数
*/





#include<iostream>
using namespace std;
class Line
{
public:
	Line() { ptr = new int; *ptr = 0; cout << "调用无参数构造函数" << endl; };
	//Line(int len);             // 简单的构造函数（ps：构造函数不能有返回值）；默认为implicit，可以产生隐式自动转换：形如Line myLine = 10 时，将调用该构造函数，构造的同时实现类型转换运算;
	explicit Line(int len);//注意：使用explicit关键字，防止类构造函数的隐式自动转换，只对有一个参数的类构造函数有效
	~Line();                     // 析构函数
	Line(const Line &);      // 拷贝构造函数：属于特殊（形参类型为同类对象）构造函数，也不能有返回值
	Line& operator=(const Line &);//赋值运算符 （也可按值返回，但是分别多调用一次复制构造函数和析构函数）
	Line& operator=(const int rhs) { *ptr = rhs; cout<<"类型转换（赋值）运算符"<<endl; return *this; };//类型转换（赋值）运算符 （也可按值返回）
	//void operator=(const Line &rhs) {if (this == &rhs)return;if (this != NULL) { delete ptr; ptr = NULL; };ptr = new int;*ptr = rhs.getLength();}//无return自己的赋值运算符重载
	operator int() { cout << "调用Line到int的转换运算符函数" << endl; return (*ptr);};
	
	//Line operator+(const Line & rhs) { cout << "调用+运算符函数：" << endl; Line result(*ptr + rhs.getLength()); return result; }
		//（内部“构拷删”：a.先调用int参数的构造函数 创建局部变量result，b.再按值返回，调用复制构造函数将局部变量result拷贝给返回值；c.析构局部变量result）
	Line operator+(const Line & rhs) { cout << "调用+运算符函数：" << endl; return Line(*ptr + rhs.getLength()); }
		//（内部直接在return处“构”，无“拷删”）
	Line operator+(int aInt) { cout << "调用+运算符函数：（重载为 Line+int）" << endl; return Line(*ptr + aInt); }
	friend Line operator+(int, const Line&);
	
	int getLength() const;
	void setLength(int aInt) {*ptr = aInt;}
	void show() const;

private:
	int *ptr;
};

//友元函数以friend在类内声明，在外部定义，无Line::
Line operator+(int aInt, const Line &aLine) { cout << "调用+运算符函数：（重载为 int + Line）" << endl;  return Line(aInt + aLine.getLength()); };

// 成员函数定义，包括构造函数
explicit Line::Line(int len)
{
	cout << "调用有参数构造函数" << endl;
	// 为指针分配内存
	ptr = new int;
	*ptr = len;
}

Line::Line(const Line &obj)
{
	cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;
	ptr = new int;
	*ptr = *obj.ptr; // 拷贝值
}

Line& Line::operator=(const Line &rhsLine)
{
	cout << "调用 重载的赋值运算符=，且有返回值：" << endl;
	if (this != &rhsLine) {//三步走
		if (ptr != NULL) {
			delete ptr;
			ptr = NULL;
		}

		ptr = new int;
		*ptr = rhsLine.getLength();
	}
	return *this;
}

Line::~Line(void)
{
	cout << "释放内存" << endl;
	delete ptr;
}
int Line::getLength() const
{
	return *ptr;
}
void Line::show() const //成员函数：隐含this指针作为参数
{
	cout << "大小 : " << *ptr << endl; //成员函数可直接访问成员变量
}

void display(Line obj) //非成员函数：不包含this指针，故需要传入对象（按值/引用传递）
{
	cout << "大小 : " << obj.getLength() << endl; //无this指针，只能调用对象的公共成员函数
}

// 程序的主函数
int main()
{
	Line line; //调用无参数的构造函数；
	Line line1(10); //调用int参数的构造函数；
	//Line line11 = 10; //注意：若构造函数Line(int)是默认的implicit情况（注：只有一个参数），将被调用实现“隐式自动类型转换”：创建并用int 10初始化Line line11
						//若采用explicit关键字作显式声明：作用是防止类构造函数的隐式自动转换.（只对有一个参数的类构造函数有效）,将不能采用上述方式调用构造函数创建并初始化，而采用以下先创建，后类型转换赋值： 
	Line line11; 
	line11 = 10; //类型转换：优先调用 “重载的赋值=运算符”函数实现类型转换，若未定义，则先自动调用“接受int参数的构造函数”构造一个临时的Line类对象，再自动调用“复制运算符=”函数赋值给line，最后自动析构临时对象。
	int intLine;
	intLine = line11; //类型转换：调用Line类内operator int(){return (*ptr)}的转换运算符，实现从Line到int的转换；
	cout << "Line转到int，大小 : " << intLine << endl;
	cout << "====================" << endl;

	Line line2(line1); //调用复制构造函数；
	Line line22 = line11; //注意：用line11来初始化line22，调用的也是复制构造函数；
	//另外：按值传递对象进入/返回函数时，也将分别调用复制构造函数；
	cout << "====================" << endl;

	cout << "尝试 +运算符：1" << endl;
	Line line33;
	line33 = line11 + line22;//（1）先计算右侧：调用+运算符函数（内部“构拷删” 或 直接在return时“构”而无“拷删”）；（2）再“赋删”：调用赋值运算符函数=给左侧赋值，并析构（1）中的返回值对象；
	cout << "尝试 +运算符：2" << endl; 
	Line line44(line11 + line22);//注意：仅调用+运算符函数（内部“构拷删” 或 直接在return时“构”而无“拷删”），返回的值对象直接给了line44，没有调用复制构造函数！
	cout << "尝试 +运算符：3" << endl;
	Line line55 = line11 + line22;//注意：仅调用+运算符函数（内部“构拷删” 或 直接在return时“构”而无“拷删”），返回的值对象直接给了line55，没有调用复制构造函数！
	cout << "====================" << endl;

	cout << "尝试 +运算符函数：（重载为 Line+int）" << endl;
	Line line66(line11 + 5);
	cout << "尝试 +运算符函数：（重载为 int+Line）" << endl;
	Line line77 = 5 + line11;//调用友元函数：	friend Line operator+(int, const Line&)
	cout << "====================" << endl;

	Line line4;
	line4 = line;//注意：line4定义后已经存在，所以调用的是重载的赋值运算符=，可以无返回值；
	(line4 = line).show();//调用的是重载的赋值运算符=，由于连续调用，前者须有返回值；
	display(line4);//注意：display定义为按值传递，故：调用 复制构造函数、析构函数；
	display(line4 = line);//1 先赋值：调用的赋值运算符=，且须有返回值（可以按值也可以按引用返回）；2 再按值传递：复制line4到函数形参，调用复制构造函数；3 再析构形参对象

	return 0;
}





/* 函数调用运算符 () 可以被重载用于类的对象。当重载 () 时，您不是创造了一种新的调用函数的方式，相反地，这是创建一个可以传递任意数目参数的运算符函数。

#include <iostream>
using namespace std;

class Distance
{
private:
	int feet;             // 0 到无穷
	int inches;           // 0 到 12
public:
	// 所需的构造函数
	Distance() {
		feet = 0;
		inches = 0;
	}
	Distance(int f, int i) {
		feet = f;
		inches = i;
	}
	// 重载函数调用运算符
	Distance operator()(int a, int b, int c)
	{
		Distance D;
		// 进行随机计算
		D.feet = a + c + 10;
		D.inches = b + c + 100;
		return D;
	}
	// 显示距离的方法
	void displayDistance()
	{
		cout << "F: " << feet << " I:" << inches << endl;
	}

};
int main()
{
	Distance D1(11, 10), D2;

	cout << "First Distance : ";
	D1.displayDistance();

	D2 = D1(10, 10, 10); // invoke operator()
	cout << "Second Distance :";
	D1.displayDistance();//D1的值仍是11，10
	D2.displayDistance();

	return 0;
}

*/





#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
struct Elem {
  Elem* next;
  void insert_after(Elem* new_element) {
    new_element->next = this->next;
    this->next = new_element; //当前对象
  }
  char prefix[2];
  short operator_num;
};

struct AAA {
  bool set_year(int year) {
    this->year = year; //当前的对象的属性
    return true;
  }
  int get_year() const { //const ：在当前方法中不可以修改year
    return this->year;
  }

  private:
  int year;
};
//const int* ptr1; // 指向 const int 的指针，不能通过 ptr1 修改指向的值
//int const* ptr2; // 同上，与 ptr1 等效
//int* const ptr3; // const 指针，指向 int，不能修改 ptr3 本身的值
//const int* const ptr4; // 指向 const int 的 const 指针，不能修改 ptr4 也不能通过 ptr4 修改值

void xxx(const char* sxx) {
  printf("%s\n", sxx);
  //  sxx[0] = '\0'; //变异不通过
}
//const对象调用成员函数：const对象只能调用const成员函数，不能调用非const成员函数
class MyClass {
  public:
  void func02() {
    // 非const成员函数
  }
  void func() const {
    // const成员函数
  }
};
int main() {
  const MyClass obj;
  obj.func(); // 可以调用const成员函数
  //  obj.func02(); // 不能调用非const成员函数，会编译错误 这个怎么
  MyClass obj2;
  obj2.func02();
}

const int SIZE = 10;
int arr[SIZE]; // 正确，SIZE是常量表达式
int n = 5;
// int arr[n];  // 错误，n不是常量表达式
/**
 *使用指针的场景
 */
//01 分配内存
void test01() {
  // 动态分配内存
  int* p = new int;
  *p = 10;
  delete p;
}

void increment(int* num) {
  (*num)++;
}
//02 函数参数传递，修改传入的参数的值
void test02() {
  int num = 10;
  increment(&num);
  printf("%d\n", num);
}
//03 返回多个值
void getMinMax(int* arr, int size, int* min, int* max) {
  // 计算最小值和最大值
}
void test03() {
  int arr[] = { 1, 2, 3, 4, 5 };
  int minVal, maxVal;
  getMinMax(arr, 5, &minVal, &maxVal);
}
/**
 *使用引用的场景
 */
// 函数参数传递，避免对象的拷贝
//const 修饰的引用， 避免修改arr+
void printArray(const std::vector<int>& arr) {
  //auto 可以让编译器自动推断变量的类型 const int&
  for(const auto& num : arr) { // &num 是对arr元素的引用，避免不必要的复制
    std::cout << num << " ";
  }
}

void test04() {
  std::vector<int> nums = { 1, 2, 3, 4, 5 };
  printArray(nums);
}
// 函数返回值，避免对象的拷贝
//由于 fullName 是静态存储的，函数不是可重入的。每次调用函数时，fullName 都会被覆盖，这意味着之前返回的引用将指向新的值。
//在实际应用中，如果你需要返回由多个参数组合而成的字符串，并且涉及到多线程或者需要多个独立的全名实例，通常更好的做法是返回一个字符串值而不是引用。
// 这样可以避免上述问题，但代价是可能会有额外的字符串复制开销（尽管现代编译器通常会通过返回值优化（RVO）来减少这种开销）。
const std::string& getFullName(const std::string& firstName, const std::string& lastName) {
  static std::string fullName; //扩大变量的作用域，避免悬空引用
  fullName = firstName + " " + lastName;
  return fullName;
}

void test05() {
  std::string firstName = "John";
  std::string lastName = "Doe";
  std::string fullName = getFullName(firstName, lastName);
  std::cout << fullName << std::endl;
}
void test06() {
  // 容器的元素类型
  std::vector<int> nums = { 1, 2, 3, 4, 5 };
  std::vector<int>& numsRef = nums;
  numsRef.push_back(6);
}
/**
 * nullptr 使用场景呢
 */
int* ptr = nullptr; // 1初始化一个指向整数的空指针
//2. 与函数重载一起使用：
void foo(int* ptr) {
  // 处理整数指针的情况
}

void foo(std::nullptr_t ptr) {
  // 处理空指针的情况
}
//3 安全地进行指针比较：
int* ptr02 = nullptr;
void test07() {
  if(ptr02 == nullptr) {
    // 指针为空
  }
}
//4与模板一起使用：在模板编程中，nullptr可以用于推导模板参数类型，以避免与整数类型的参数混淆。
template <typename T>
void print(T* ptr) {
  // 打印指针指向的值
  std::cout << *ptr << std::endl;
}
void test08() {
  print<int>(nullptr); // 推导模板参数类型为int*
}
/**
* std::byte 指针
*/
//声明和初始化std::byte指针
std::byte* ptr01 = nullptr;
//分配10个std::byte大小的内存
std::byte* ptr04 = new std::byte[10];
//ptr04[0] = std::byte(0x01); // 使用std::byte指针访问和修改内存中的数据
/**
* void 指针
*/
//2. 将void*指针转换为其他指针类型：
int num = 42;
void* voidPtr = &num; // 将int指针转换为void*指针
int* intPtr = static_cast<int*>(voidPtr); // 将void*指针转换为int指针
//std::cout << *intPtr << std::endl; // 输出指针指向的int数据
//3. 使用void*指针进行通用的指针操作：
//void* ptr = nullptr;
//int num = 42;
//ptr = &num; // 将int指针赋值给void*指针
//// 进行通用的指针操作，例如比较、递增等
//if (ptr != nullptr) {
//  int* intPtr = static_cast<int*>(ptr);
//  (*intPtr)++;
//  std::cout << *intPtr << std::endl;
//}


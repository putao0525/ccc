#include <cstdio>
#include <stdexcept>

struct CyberdyneSeries800 {
  CyberdyneSeries800() {
    printf("I'm a friend of Sarah Connor.");
  }
  ~CyberdyneSeries800() {
    throw std::runtime_error{ "I'll be back." };
  }
};

int main() {
  try {
    //这是因为 C++ 标准规定，如果在处理一个异常的过程中抛出了另一个异常而没有捕获它，程序必须终止。
    CyberdyneSeries800 t800;
    throw std::runtime_error{ "Come with me if you want to live." };
  } catch(const std::exception& e) {
    //局部对象 t800 的生命周期结束，因此它的析构函数被调用。
    // 但是，由于析构函数中抛出了一个异常，而且当前已经有一个异常正在被处理（"Come with me if you want to live."），
    // 这就违反了 C++ 的异常处理规则，导致程序调用 std::terminate()。
    printf("Caught exception: %s\n", e.what());
  }
}

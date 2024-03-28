﻿#include <cstdio>

struct Tracer {
  Tracer(const char* name)
      : name{ name } {
    printf("%s constructed.\n", name);
  }
  ~Tracer() {
    printf("%s destructed.\n", name);
  }

  private:
  const char* const name;
};

static Tracer t1{ "Static variable" };
thread_local Tracer t2{ "Thread-local variable" };

int main() {
  //静态先执行
  printf("A\n");
  //非静态的
  Tracer t3{ "Automatic variable" };
  printf("B\n");
  const auto* t4 = new Tracer{ "Dynamic variable" }; //自动变量， main返回之后会被释放掉
  printf("C\n");
  return 0;
}
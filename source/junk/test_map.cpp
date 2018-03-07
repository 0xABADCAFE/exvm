#include <string>
#include <unordered_map>
#include <cstdio>

class UnorderedMapEnumerator {

  private:
    std::unordered_map<std::string, int> map;
    int nextID;
  public:
    int enumerate(const char* symbol);

    UnorderedMapEnumerator() : nextID(0) {}
};

int UnorderedMapEnumerator::enumerate(const char* symbol) {
  std::string key = symbol;
  int val = map[key];
  if (val == 0) {
    val = ++nextID;
    map[key] = val;
  }
  return val;
}

int main() {

  UnorderedMapEnumerator enumerator;

  char buffer[100];

  int sum1 = 0, sum2 = 0;

  for (int i = 0; i < 1000000; i++) {
    sum1 += i;
    std::sprintf(buffer, "TestKey_%d", i);
    sum2 += enumerator.enumerate(buffer);
  }

  std::printf("Sum1:%d, Sum2:%d, test:%d\n", sum1, sum2, enumerator.enumerate("TestKey_0"));
  return 0;
}

// 여러 인덱스 지우기: 내림차순 정렬(rbegin, rend) 후 뒤에서부터 erase
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& v) {
  for (int x : v) cout << x << ' ';
  cout << '\n';
}

int main() {
  // 1. string::erase 기본
  string s1 = "abcde";
  s1.erase(1, 1);  // 1번 위치에서 1글자 삭제
  cout << s1 << '\n';  // acde

  string s2 = "abcde";
  s2.erase(1, 3);  // 1번 위치에서 3글자 삭제
  cout << s2 << '\n';  // ae

  string s3 = "abcde";
  s3.erase(2);  // 2번 위치부터 끝까지 삭제
  cout << s3 << '\n';  // ab

  // 2. sort(rbegin, rend)로 내림차순 정렬
  vector<int> indices = {1, 16, 6, 15, 0, 10, 11, 3};
  sort(indices.begin(), indices.end());
  PrintVector(indices);  // 0 1 3 6 10 11 15 16
  sort(indices.rbegin(), indices.rend());
  PrintVector(indices);  // 16 15 11 10 6 3 1 0

  // 3. 큰 인덱스부터 erase (올바른 방법)
  string my_string = "apporoograpemmemprs";
  for (int index : indices) {
    my_string.erase(index, 1);
  }
  cout << my_string << '\n';  // programmers

  // 4. 정렬 없이 주어진 순서대로 erase (틀린 방법)
  string wrong = "apporoograpemmemprs";
  vector<int> unsorted = {1, 16, 6, 15, 0, 10, 11, 3};
  for (int index : unsorted) {
    wrong.erase(index, 1);
  }
  cout << wrong << '\n';  // pororapemep  (틀림)

  // 오름차순 {0, 1, 3, 6, 10, 11, 15, 16}으로 지우면 더 나쁘다.
  // 6번 지운 뒤 문자열 길이가 13인데 erase(15, 1)을 호출해서
  // out_of_range 에러로 프로그램이 종료된다.

  // 5. 처음 2번 지울 때 인덱스가 밀리는 과정
  string step = "abcdef";
  step.erase(0, 1);
  cout << step << '\n';  // bcdef  ('b'가 0번으로 당겨짐)
  step.erase(1, 1);
  cout << step << '\n';  // bdef   (원래 1번 'b'가 아니라 원래 2번 'c'가 지워짐)

  // 6. vector에도 같은 패턴
  vector<int> nums = {10, 20, 30, 40, 50};
  vector<int> remove_at = {0, 3, 1};
  sort(remove_at.rbegin(), remove_at.rend());  // 3 1 0
  for (int index : remove_at) {
    nums.erase(nums.begin() + index);
  }
  PrintVector(nums);  // 30 50
  return 0;
}

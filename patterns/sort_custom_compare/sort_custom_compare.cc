// sort()의 사용자 정의 비교 함수 예제 모음
// 설명: sort_custom_compare.md
// 컴파일: g++ -std=c++17 -o sort_custom_compare sort_custom_compare.cc

#include <algorithm>   // sort, stable_sort
#include <functional>  // greater
#include <iostream>
#include <string>
#include <utility>     // pair
#include <vector>

using namespace std;

// 2-1. 오름차순
bool Ascending(int a, int b) {
  return a < b;
}

// 2-2. 내림차순
bool Descending(int a, int b) {
  return a > b;
}

// 2-3. 이어 붙였을 때 더 큰 쪽이 앞
bool ConcatGreater(const string& a, const string& b) {
  return a + b > b + a;
}

// 2-4. 점수 내림차순, 같으면 번호 오름차순
bool ScoreDescIdAsc(const pair<int, int>& a, const pair<int, int>& b) {
  if (a.first != b.first) {
    return a.first > b.first;
  }
  return a.second < b.second;
}

void Print(const vector<int>& v) {
  for (int n : v) cout << n << ' ';
  cout << '\n';
}

int main() {
  // 2-1. 오름차순
  vector<int> v = {4, 1, 5, 2, 3};
  sort(v.begin(), v.end(), Ascending);
  Print(v);  // 출력: 1 2 3 4 5

  // 2-2. 내림차순
  v = {4, 1, 5, 2, 3};
  sort(v.begin(), v.end(), Descending);
  Print(v);  // 출력: 5 4 3 2 1

  // 2-3. 「가장 큰 수」
  vector<string> words = {"3", "30", "34", "5", "9"};
  sort(words.begin(), words.end(), ConcatGreater);
  for (const string& s : words) cout << s << ' ';
  cout << '\n';  // 출력: 9 5 34 3 30

  // 2-4. 다중 조건 정렬 ({점수, 번호})
  vector<pair<int, int>> scores = {{90, 2}, {80, 3}, {90, 1}};
  sort(scores.begin(), scores.end(), ScoreDescIdAsc);
  for (const auto& p : scores) cout << p.first << ' ' << p.second << '\n';
  // 출력:
  // 90 1
  // 90 2
  // 80 3

  // 3-1. 람다로 내림차순
  v = {4, 1, 5, 2, 3};
  sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
  Print(v);  // 출력: 5 4 3 2 1

  // 3-2. greater<int>()로 내림차순
  v = {4, 1, 5, 2, 3};
  sort(v.begin(), v.end(), greater<int>());
  Print(v);  // 출력: 5 4 3 2 1

  // 3-3. stable_sort: 점수가 같으면 입력 순서 유지
  vector<pair<int, char>> students = {{90, 'A'}, {80, 'B'}, {90, 'C'}};
  stable_sort(students.begin(), students.end(),
              [](const pair<int, char>& a, const pair<int, char>& b) {
                return a.first > b.first;
              });
  for (const auto& p : students) cout << p.first << ' ' << p.second << '\n';
  // 출력:
  // 90 A
  // 90 C
  // 80 B
  return 0;
}

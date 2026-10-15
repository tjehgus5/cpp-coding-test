// 숫자 문자 → 정수 변환 (c - '0') 예제 모음
// 설명: char_to_int.md
// 컴파일: g++ -std=c++17 -o char_to_int char_to_int.cc

#include <algorithm>  // reverse
#include <cctype>     // isdigit
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 큰 수 덧셈: 자리수마다 c - '0'으로 꺼내고 + '0'으로 되돌린다.
string AddBig(string a, string b) {
  string result;
  int i = a.size() - 1;
  int j = b.size() - 1;
  int carry = 0;
  while (i >= 0 || j >= 0 || carry) {
    int sum = carry;
    if (i >= 0) sum += a[i--] - '0';
    if (j >= 0) sum += b[j--] - '0';
    result.push_back(sum % 10 + '0');
    carry = sum / 10;
  }
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  // 3-1. 한 글자씩 정수로 꺼내기
  string s = "123";
  for (char c : s) cout << c - '0' << ' ';
  cout << '\n';  // 출력: 1 2 3

  // 3-2. 각 자리수의 합
  string digits = "98765";
  int sum = 0;
  for (char c : digits) sum += c - '0';
  cout << sum << '\n';  // 출력: 35

  // 3-3. 문자열 → 정수 직접 만들기
  string number_str = "1234567890123";
  long long num = 0;
  for (char c : number_str) num = num * 10 + (c - '0');
  cout << num << '\n';  // 출력: 1234567890123

  // 3-4. 숫자만 골라서 계산
  string mixed = "a1b2c3";
  int total = 0;
  for (char c : mixed) {
    if (isdigit(c)) total += c - '0';
  }
  cout << total << '\n';  // 출력: 6

  // 3-5. 격자 입력을 2차원 배열로
  vector<string> rows = {"0110", "1011", "0001"};
  int board[3][4];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) board[i][j] = rows[i][j] - '0';
  }
  cout << board[1][2] << '\n';  // 출력: 1

  // 3-6. 큰 수 덧셈
  cout << AddBig("99999999999999999999", "1") << '\n';
  // 출력: 100000000000000000000

  // 3-7. 알파벳 → 0~25
  string word = "abz";
  for (char c : word) cout << c - 'a' << ' ';
  cout << '\n';  // 출력: 0 1 25

  // 정수 → 숫자 문자
  char seven = 7 + '0';
  cout << seven << '\n';  // 출력: 7
  return 0;
}

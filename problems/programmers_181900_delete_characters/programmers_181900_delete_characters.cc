// 프로그래머스 181900 글자 지우기
// https://school.programmers.co.kr/learn/courses/30/lessons/181900
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 풀이 1 (제출): 인덱스를 내림차순 정렬한 뒤 뒤에서부터 erase
// 프로그래머스가 함수 이름을 solution으로 정해 두었으므로 그대로 쓴다.
string solution(string my_string, vector<int> indices) {
  sort(indices.rbegin(), indices.rend());
  for (int index : indices) {
    my_string.erase(index, 1);
  }
  return my_string;
}

// 풀이 2: 지울 위치를 표시해 두고 남은 글자만 모은다.
string SolveByCheckArray(string my_string, vector<int> indices) {
  vector<bool> is_deleted(my_string.size(), false);
  for (int index : indices) {
    is_deleted[index] = true;
  }

  string answer = "";
  for (int i = 0; i < (int)my_string.size(); i++) {
    if (!is_deleted[i]) {
      answer += my_string[i];
    }
  }
  return answer;
}

int main() {
  string my_string = "apporoograpemmemprs";
  vector<int> indices = {1, 16, 6, 15, 0, 10, 11, 3};

  cout << solution(my_string, indices) << '\n';           // programmers
  cout << SolveByCheckArray(my_string, indices) << '\n';  // programmers
  return 0;
}

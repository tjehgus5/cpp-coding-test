// 프로그래머스 42579 베스트앨범
// https://school.programmers.co.kr/learn/courses/30/lessons/42579
// 설명: programmers_42579_best_album.md
// 컴파일: g++ -std=c++17 -o best_album programmers_42579_best_album.cc

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// 프로그래머스가 함수 이름을 solution으로 정해 두었으므로 그대로 쓴다.
vector<int> solution(vector<string> genres, vector<int> plays) {
  vector<int> answer;
  unordered_map<string, int> gen_total;
  unordered_map<string, vector<pair<int, int>>> songs;  // 장르 → {id, plays} 목록

  // 1. 같은 장르 Key로 총합과 노래 목록을 각각 저장
  for (int i = 0; i < (int)plays.size(); i++) {
    gen_total[genres[i]] += plays[i];
    songs[genres[i]].push_back({i, plays[i]});
  }

  // 2. 장르 총 재생 횟수 내림차순
  vector<pair<string, int>> vec_total(gen_total.begin(), gen_total.end());
  sort(vec_total.begin(), vec_total.end(),
       [](const auto& a, const auto& b) { return a.second > b.second; });

  // 3. 정렬된 장르 순서대로, 각 장르의 상위 2곡 선택
  for (const auto& p : vec_total) {
    const string& genre = p.first;
    auto& song_list = songs[genre];

    sort(song_list.begin(), song_list.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
           if (a.second != b.second) {
             return a.second > b.second;  // 재생 횟수 내림차순
           }
           return a.first < b.first;  // 고유 번호 오름차순
         });

    int cnt = min(2, (int)song_list.size());
    for (int i = 0; i < cnt; i++) {
      answer.push_back(song_list[i].first);
    }
  }

  return answer;
}

void Print(const vector<int>& v) {
  for (int n : v) cout << n << ' ';
  cout << '\n';
}

int main() {
  // 기본: classic 3곡 / pop 2곡
  Print(solution({"classic", "pop", "classic", "classic", "pop"},
                 {500, 600, 150, 800, 2500}));
  // 출력: 4 1 3 0

  // 같은 재생 횟수: 0번을 먼저 선택
  Print(solution({"pop", "pop", "pop"}, {100, 100, 50}));
  // 출력: 0 1

  // 노래 1곡인 장르: 그 장르에서 1개만 추가
  Print(solution({"jazz", "pop", "pop"}, {5000, 100, 200}));
  // 출력: 0 2 1
  return 0;
}

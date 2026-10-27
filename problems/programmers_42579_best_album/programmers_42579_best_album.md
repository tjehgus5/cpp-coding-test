# 프로그래머스 42579 베스트앨범 — 오답노트 (정렬·해시·중첩 자료구조)

| 항목 | 내용 |
|---|---|
| 문제 | [베스트앨범](https://school.programmers.co.kr/learn/courses/30/lessons/42579) |
| 사이트 | 프로그래머스 > 코딩테스트 고득점 Kit > 해시 |
| 분류 | 자료구조 > 해시(`unordered_map`) + 함수 > 정렬 |
| 사용한 패턴 | [sort()의 사용자 정의 비교 함수](../../patterns/sort_custom_compare/sort_custom_compare.md) |
| 함께 복습한 문제 | [H-Index](https://school.programmers.co.kr/learn/courses/30/lessons/42747), [가장 큰 수](https://school.programmers.co.kr/learn/courses/30/lessons/42746) |
| 시간 복잡도 | O(N log N) |
| 작성일 | 2026-10-28 |
| 제출 코드 | [programmers_42579_best_album.cc](programmers_42579_best_album.cc) |

> **목표:** 코드를 외우는 것이 아니라, 자료형 → 정렬 기준 → 반복문 위치 → 반환값을 스스로 설계한다.

## 목차
0. [나의 반복 실수 요약 (가장 먼저 읽기)](#0-나의-반복-실수-요약-가장-먼저-읽기)
1. [sort()와 compare() — 무조건 기억하기](#1-sort와-compare--무조건-기억하기)
2. [중첩 자료구조를 읽는 방법](#2-중첩-자료구조를-읽는-방법)
3. [unordered_map → vector가 필요한 이유와 주의점](#3-unordered_map--vector가-필요한-이유와-주의점)
4. [반복문과 결과 저장의 위치](#4-반복문과-결과-저장의-위치)
5. [베스트앨범 정답 코드](#5-베스트앨범-정답-코드)
6. [이전 정렬 문제와 연결해서 기억하기](#6-이전-정렬-문제와-연결해서-기억하기)
7. [다음 문제를 풀기 전 6단계 체크리스트](#7-다음-문제를-풀기-전-6단계-체크리스트)
8. [5분 셀프 테스트](#8-5분-셀프-테스트)

---

## 0. 나의 반복 실수 요약 (가장 먼저 읽기)

| 우선순위 | 실제로 했던 실수·질문 | 원인 | 앞으로의 점검 질문 |
|---|---|---|---|
| 1 | `a.second < b.second`로 정렬해 장르/재생 횟수가 오름차순이 됨 | 비교 기준의 방향 혼동 | "a가 b보다 앞에 와야 하는 조건인가?" |
| 2 | `vector<int,int>`를 `sort()`의 람다 인수로 사용 | 컨테이너 타입과 원소 타입 혼동 | "지금 정렬하는 vector 안의 원소 하나는 무슨 타입인가?" |
| 3 | `push_back(i, plays[i])` 사용 | `vector<pair<...>>`에 pair 하나를 넣는다는 점 놓침 | "추가하는 원소 하나의 형식이 `{id, plays}`인가?" |
| 4 | `temp_int`, `temp_vec`를 노래 반복문 내부에 선언하고 매번 `result.push_back()` | 노래별 처리와 장르별 결과 저장을 구분하지 못함 | "지금 저장할 값은 노래 하나의 결과인가, 장르 하나의 결과인가?" |
| 5 | `unordered_map`과 `map`만으로 Value 기준 정렬이 될지 혼란 | Key 검색과 Value 정렬은 다른 요구사항 | "정렬의 기준이 Key인가, Value인가?" |
| 6 | H-Index에서 `<=`, `==`, 즉시 `return` 사용 | 문제의 이상(≥), 최댓값, 인덱스+1 관계 혼동 | "문제 조건이 `==`인가 `>=`인가? 후보를 즉시 반환해도 되는가?" |

> **한 줄 요약:** 자료구조가 틀린 경우보다, 저장한 데이터의 의미와 비교 방향이 일치하지 않은 경우가 많았다.

## 1. sort()와 compare() — 무조건 기억하기

### 1-1. compare(a, b)의 의미

```cpp
bool Compare(int a, int b) {
  return a > b;
}
```

- `true`: `a`가 `b`보다 앞에 와야 함
- `false`: `a`가 `b`보다 앞에 와야 한다는 조건이 성립하지 않음. 동등한 순위일 수도 있으므로 반드시 역순이라는 뜻은 아님.
- `sort()`는 비교할 두 원소를 여러 번 전달하며, 실제 선택 순서와 이동 방법은 라이브러리 구현에 따라 달라질 수 있음.
- `Compare()`는 두 원소를 직접 교환하는 함수가 아님.

| 목적 | 비교 조건 | 결과 예시 |
|---|---|---|
| 숫자 오름차순 | `return a < b;` | 1, 2, 3 |
| 숫자 내림차순 | `return a > b;` | 3, 2, 1 |
| 재생 횟수 내림차순 | `return a.second > b.second;` | 2500, 800, 600 |
| 동률이면 고유번호 오름차순 | `return a.first < b.first;` | id 0, id 3 |

> **주의:** `<=` 또는 `>=`를 정렬 비교 함수의 기준으로 사용하지 말 것. 자기 자신을 비교하면 `false`여야 하며, 비교 관계는 일관된 엄격 약순서(strict weak ordering)를 따라야 함.

### 1-2. 비교 함수 인수는 vector 전체가 아니라 원소 하나의 타입

```cpp
vector<pair<int, int>> song_list;
```

위 컨테이너의 원소 하나는 `pair<int, int>`이므로:

```cpp
sort(song_list.begin(), song_list.end(),
     [](const pair<int, int>& a, const pair<int, int>& b) {
       if (a.second != b.second) {
         return a.second > b.second;  // 재생 횟수: 내림차순
       }
       return a.first < b.first;  // 고유 번호: 오름차순
     });
```

잘못된 형태: `[](const vector<int,int>& a, const vector<int,int>& b)`

### 1-3. 다중 조건 비교의 템플릿

1. 첫 번째 우선순위가 다르면 첫 번째 기준으로 비교한다.
2. 첫 번째 우선순위가 같으면 두 번째 기준으로 비교한다.

```cpp
if (a.first != b.first) {
  return a.first > b.first;  // 첫 기준: 내림차순
}
return a.second < b.second;  // 동률: 두 번째 기준 오름차순
```

## 2. 중첩 자료구조를 읽는 방법

### 2-1. 선언을 안쪽부터 읽는다

```cpp
unordered_map<string, vector<pair<int, int>>> songs;
```

| 부분 | 의미 |
|---|---|
| `string` | Key: 장르 이름 (`"pop"`) |
| `pair<int, int>` | 노래 한 곡: `{고유 번호, 재생 횟수}` |
| `vector<pair<int, int>>` | 한 장르에 속한 노래 목록 |
| `unordered_map<...>` | 장르 이름을 이용해 노래 목록에 접근 |

입력:

```cpp
genres = {"classic", "pop", "classic", "classic", "pop"};
plays  = {500, 600, 150, 800, 2500};
```

저장 코드:

```cpp
for (int i = 0; i < plays.size(); i++) {
  songs[genres[i]].push_back({i, plays[i]});
}
```

저장 결과:

```cpp
songs["classic"] = {{0, 500}, {2, 150}, {3, 800}};
songs["pop"]     = {{1, 600}, {4, 2500}};
```

### 2-2. push_back()과 emplace_back() 구분

```cpp
songs[genres[i]].push_back({i, plays[i]});   // pair 한 개 전달
songs[genres[i]].emplace_back(i, plays[i]);  // pair의 생성 인수 전달
songs[genres[i]].push_back(i, plays[i]);     // 오류: push_back에 인수 2개
```

### 2-3. auto&와 p.first, p.second

```cpp
for (auto& p : songs) {
  // p.first  : 장르 이름 (string)
  // p.second : 노래 목록 (vector<pair<int, int>>)
  auto& song_list = p.second;
}
```

- `auto p`는 원소를 복사함.
- `auto& p`는 원소를 참조하므로 `p.second`를 정렬하면 원본 맵 안의 목록도 정렬됨.
- `auto& song_list = songs[genre];`는 새 목록을 복사하는 게 아니라, 해당 Key의 목록을 참조함.

## 3. unordered_map → vector가 필요한 이유와 주의점

### 3-1. 목적이 다르다

| 자료구조 | 잘하는 일 | 정렬 관련 사실 |
|---|---|---|
| `unordered_map` | Key별 집계·검색 (평균 빠름) | 원소 순서를 보장하지 않음 |
| `map` | Key별 검색 + Key 기준 순서 유지 | `map<string, ...>`은 장르 이름순이지 총 재생 횟수순이 아님 |
| `vector` | 순서대로 저장하고 `sort()` 적용 | 총 재생 횟수라는 Value 기준으로 정렬하기 좋음 |

장르 합계:

```cpp
unordered_map<string, int> gen_total;
gen_total["classic"] = 1450;
gen_total["pop"] = 3100;
```

정렬 가능한 별도 벡터:

```cpp
vector<pair<string, int>> vec_total(gen_total.begin(), gen_total.end());

sort(vec_total.begin(), vec_total.end(),
     [](const auto& a, const auto& b) { return a.second > b.second; });
// {{"pop", 3100}, {"classic", 1450}}
```

> **핵심:** vector로 복사하는 추가 비용은 있지만, 장르가 100개 미만인 이 문제에서는 작다. 복사를 무조건 피하는 것보다 의도한 순서를 제대로 만드는 것이 먼저다.

### 3-2. vector로 옮기면 Key를 잃는가?

```cpp
vector<pair<string, int>> a(gen_total.begin(), gen_total.end());
// Key와 Value를 둘 다 저장함: a[i].first는 장르, a[i].second는 총 재생 횟수
```

반면 아래처럼 Value만 넣으면 해당 벡터에서는 장르 Key를 직접 알 수 없음:

```cpp
for (const auto& p : some_map) {
  result.push_back(p.second);
}
```

다만 원래 맵의 Key가 사라지지는 않음. `result`에 무엇을 저장할지는 이후에 필요한 정보에 따라 결정한다.

### 3-3. 공통 Key를 이용해 두 맵 연결하기

```cpp
unordered_map<string, int> gen_total;
unordered_map<string, vector<pair<int, int>>> songs;

for (int i = 0; i < plays.size(); i++) {
  gen_total[genres[i]] += plays[i];
  songs[genres[i]].push_back({i, plays[i]});
}

for (const auto& p : vec_total) {
  const string& genre = p.first;
  auto& song_list = songs[genre];  // 같은 장르 이름으로 연결
}
```

두 맵 자체를 이어 붙이는 게 아니다. `"pop"` 같은 같은 Key로 각각 조회하는 것이다.

## 4. 반복문과 결과 저장의 위치

베스트앨범은 노래 단위 처리와 장르 단위 처리가 중첩된다.

```cpp
for (auto& genre_entry : songs) {  // 장르 1개
  int total = 0;                   // 장르마다 새로 초기화
  vector<int> selected;

  for (const auto& song : genre_entry.second) {  // 노래 1개씩
    total += song.second;
    // 선택 조건 처리
  }

  // 장르 하나의 계산을 완료한 뒤 장르 결과 1개 저장
  result.push_back({total, selected});
}
```

> **오답 패턴:** `total`, `selected`를 노래 반복문 안에서 선언하거나, 노래마다 `result.push_back()`하면 장르별 합계/상위 2곡으로 묶이지 않음.

**확인 질문:** `result`의 원소 개수는 전체 노래 수 N인가, 전체 장르 수 G인가? → 장르 단위 결과라면 G.

## 5. 베스트앨범 정답 코드

지금 학습한 두 `unordered_map` 방식. 실행 가능한 전체 코드는 [programmers_42579_best_album.cc](programmers_42579_best_album.cc).

```cpp
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
  vector<int> answer;
  unordered_map<string, int> gen_total;
  unordered_map<string, vector<pair<int, int>>> songs;

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
```

단계별 저장 결과:

```
gen_total : {classic: 1450, pop: 3100}
songs     : classic {{0,500},{2,150},{3,800}} / pop {{1,600},{4,2500}}
vec_total : {{pop,3100},{classic,1450}}
pop 정렬  : {{4,2500},{1,600}}         -> answer {4,1}
classic   : {{3,800},{0,500},{2,150}} -> answer {4,1,3,0}
```

- **시간 복잡도**(평균적인 해시 조회 가정): O(N + G log G + Σ m_g log m_g)로, 최악의 장르 분포를 고려하면 정렬 부분은 O(N log N)에 포함됨. m_g는 장르 g의 노래 수.
- **공간 복잡도:** O(N + G) (노래 목록 + 장르 합계/정렬 목록).

### 반드시 확인할 테스트

| 상황 | 입력의 핵심 | 확인할 결과 |
|---|---|---|
| 기본 | classic 3곡 / pop 2곡 | `{4, 1, 3, 0}` |
| 같은 재생 횟수 | 한 장르에 `{id0: 100, id1: 100}` | 0번을 먼저 선택 |
| 노래 1곡인 장르 | 장르에 노래 1개뿐 | 그 장르에서 1개만 추가 |
| 장르 정렬 | 합계 3100과 1450 | 3100 장르부터 처리 |

## 6. 이전 정렬 문제와 연결해서 기억하기

### 6-1. H-Index — i+1은 후보 논문 수

```cpp
sort(citations.rbegin(), citations.rend());
int answer = 0;
for (int i = 0; i < citations.size(); i++) {
  if (citations[i] >= i + 1) {
    answer = i + 1;
  } else {
    break;
  }
}
return answer;
```

- `citations[i]`: i+1번째로 많이 인용된 논문의 인용 횟수
- `i + 1`: H-Index 후보 h
- `citations[i] >= i + 1`이면 적어도 h편이 h회 이상 인용됨
- `return citations[i]`는 잘못된 반환 대상. h 후보의 최댓값을 반환해야 함.
- `if (count == h)`는 부정확하고 `count >= h`가 맞음.
- 반복문 뒤의 `return`을 누락하면 조건을 못 만족했을 때 정의되지 않은 동작 발생.

검증: `{10,10,10}` → 3, `{10,8,5,2,1}` → 3, `{0,0,0}` → 0.

### 6-2. 가장 큰 수 — 숫자 자체가 아니라 이어 붙인 결과를 비교

```cpp
bool Compare(const string& a, const string& b) {
  return a + b > b + a;
}
```

- `"3"`과 `"30"`은 `"330"`과 `"303"`을 비교: `"3"`이 먼저.
- 문자열 두 개를 잇는 순서를 바꿔 비교하면 길이가 같아 사전식 비교가 숫자 크기 비교와 일치.
- 모두 0이면 `"000"` 대신 `"0"` 반환하도록 예외 처리.
- `sort(v.rbegin(), v.rend(), Compare)`도 가능하나 비교 방향과 역방향 반복자를 동시에 사용하면 헷갈리기 쉬우므로, 처음에는 `sort(v.begin(), v.end(), Compare)`가 명확함.

## 7. 다음 문제를 풀기 전 6단계 체크리스트

- [ ] **원소의 뜻:** `pair.first`와 `pair.second`는 각각 무엇인가?
- [ ] **Key/Value:** `unordered_map`의 Key는 무엇이며, Value에는 무엇을 저장하는가?
- [ ] **원소 자료형:** `sort()`의 람다 인수는 벡터 안의 원소 타입인가?
- [ ] **정렬 방향:** `Compare(a, b)`가 `true`이면 정말 `a`가 앞에 와야 하는가?
- [ ] **반복문 범위:** 누적변수 초기화와 `push_back()`은 노래별/장르별 중 올바른 위치인가?
- [ ] **반례/반환:** 동률·원소 하나·모두 0·조건 불만족 시에도 유효한 값을 반환하는가?

## 8. 5분 셀프 테스트

코드를 보기 전에 답하기.

1. `vector<pair<int,int>> v`를 정렬할 때 비교 함수의 두 인수 타입은?
2. `songs["pop"].push_back({4, 2500});`에서 Key, 원소 타입, 각 숫자의 의미는?
3. `map<string,int>`에 pop:3100, classic:1450을 넣으면 pop이 먼저 순회되는가?
4. 노래를 `{id, play}`로 저장했다면 play 내림차순 + 동률 id 오름차순 비교식은?
5. `citations = {10,10,10}`의 H-Index는? 가장 큰 수에서 `{0,0,0}`은 무엇을 반환해야 하는가?

<details>
<summary>정답 확인</summary>

1. `const pair<int,int>& a, const pair<int,int>& b`
2. Key는 `"pop"`, 원소는 `pair<int,int>`이며 `{id=4, plays=2500}`
3. 아니오. `map`의 기본 Key 정렬은 문자열 오름차순이므로 classic이 먼저
4. `if (a.second != b.second) return a.second > b.second; return a.first < b.first;`
5. H-Index는 3, 가장 큰 수 문제의 문자열 정답은 `"0"`

</details>

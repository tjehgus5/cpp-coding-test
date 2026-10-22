# 여러 인덱스 지우기 (`sort(rbegin, rend)` + `erase`)

| 항목 | 내용 |
|---|---|
| 분류 | 문제 해결 기법 > 문자열·배열 처리 > 원소 삭제 |
| 저장소 위치 | 패턴 |
| 헤더 | `<string>`, `<vector>`, `<algorithm>` (`sort`) |
| 핵심 | 지울 인덱스를 **내림차순 정렬**한 뒤 **뒤에서부터** `erase` |
| 코딩테스트 중요도 | ★★★☆☆ |
| 실행 예제 | [erase_by_indices.cc](erase_by_indices.cc) |
| 사용한 문제 | [프로그래머스 181900 글자 지우기](../../problems/programmers_181900_delete_characters/programmers_181900_delete_characters.md) |

## 목차
0. [배경](#0-배경)
1. [erase 문법](#1-erase-문법)
2. [sort(rbegin, rend)로 내림차순 정렬](#2-sortrbegin-rend로-내림차순-정렬)
3. [왜 뒤에서부터 지워야 하나](#3-왜-뒤에서부터-지워야-하나)
4. [패턴 코드](#4-패턴-코드)
5. [vector에서도 똑같이](#5-vector에서도-똑같이)
6. [다른 방법: 체크 배열](#6-다른-방법-체크-배열)
7. [주의사항](#7-주의사항)
8. [암기 한 줄](#8-암기-한-줄)

---

## 0. 배경

**개념**
문자열이나 배열에서 여러 위치의 원소를 지울 때, 지울 인덱스를 큰 것부터 정렬해서 뒤쪽부터 `erase`하는 방법이다.

**목적**
`erase`로 한 글자를 지우면 그 뒤에 있던 글자가 전부 한 칸씩 앞으로 당겨진다. 앞쪽부터 지우면 아직 안 지운 인덱스가 가리키는 글자가 바뀌어 버린다. 뒤쪽부터 지우면 앞쪽 글자의 위치는 그대로라서 원래 인덱스를 그대로 써도 된다.

코딩테스트에서는 이런 상황에 쓴다.

- "주어진 인덱스의 글자/원소를 지워라" 같은 문자열·배열 기초 문제
- 조건에 맞는 원소 위치를 모아 두었다가 한꺼번에 지울 때

## 1. erase 문법

`string`의 `erase`는 **시작 위치**와 **지울 글자 수**를 받는다.

| 형태 | 의미 | 예시 (`s = "abcde"`) |
|---|---|---|
| `s.erase(pos, len)` | pos부터 len글자 삭제 | `s.erase(1, 1)` → `"acde"` |
| | | `s.erase(1, 3)` → `"ae"` |
| `s.erase(pos)` | pos부터 끝까지 삭제 | `s.erase(2)` → `"ab"` |

```cpp
string s1 = "abcde";
s1.erase(1, 1);
cout << s1 << '\n';  // acde

string s2 = "abcde";
s2.erase(1, 3);
cout << s2 << '\n';  // ae

string s3 = "abcde";
s3.erase(2);
cout << s3 << '\n';  // ab
```

> 한 글자만 지울 때는 꼭 `erase(pos, 1)`로 쓴다. `erase(pos)`만 쓰면 pos부터 끝까지 다 지워진다.

## 2. sort(rbegin, rend)로 내림차순 정렬

`sort(v.begin(), v.end())`는 오름차순이다. `begin`, `end` 대신 `rbegin`, `rend`를 넣으면 **내림차순**이 된다.

```cpp
vector<int> indices = {1, 16, 6, 15, 0, 10, 11, 3};

sort(indices.begin(), indices.end());
// indices: 0 1 3 6 10 11 15 16   (오름차순)

sort(indices.rbegin(), indices.rend());
// indices: 16 15 11 10 6 3 1 0   (내림차순)
```

**rbegin, rend가 뭔가**
`r`은 reverse(거꾸로)다. 배열을 뒤에서부터 보는 반복자(위치를 가리키는 표시)다.

| | 가리키는 곳 |
|---|---|
| `begin()` | 맨 앞 원소 |
| `end()` | 맨 뒤 원소의 다음 칸 |
| `rbegin()` | 맨 뒤 원소 (거꾸로 볼 때의 시작) |
| `rend()` | 맨 앞 원소의 앞 칸 (거꾸로 볼 때의 끝) |

`sort`는 받은 범위를 "앞에서 뒤로 갈수록 커지게" 정렬한다. `rbegin~rend`는 배열을 뒤에서 앞으로 본 범위이므로, 거꾸로 봤을 때 커지게 정렬하면 원래 방향으로는 **작아지는 순서**가 된다.

같은 결과를 내는 다른 방법도 있다.

```cpp
#include <functional>  // greater
sort(indices.begin(), indices.end(), greater<int>());
// indices: 16 15 11 10 6 3 1 0
```

`rbegin, rend` 쪽이 헤더도 필요 없고 짧아서 코딩테스트에서 자주 쓴다.

## 3. 왜 뒤에서부터 지워야 하나

`"abcdef"`에서 0번(`a`)과 1번(`b`)을 지우고 싶다고 하자. 앞에서부터 지우면 이렇게 된다.

```cpp
string step = "abcdef";
step.erase(0, 1);
cout << step << '\n';  // bcdef  ('b'가 0번으로 당겨짐)
step.erase(1, 1);
cout << step << '\n';  // bdef   (원래 2번 'c'가 지워짐)
```

정답은 `"cdef"`인데 `"bdef"`가 나왔다. 첫 번째 `erase` 뒤로 모든 글자가 한 칸씩 당겨졌기 때문이다.

뒤에서부터(1번 → 0번) 지우면 1번을 지워도 0번 글자의 위치는 변하지 않는다. 그래서 원래 인덱스 그대로 지워도 맞는 결과가 나온다.

실제 문제 예제로 보면 차이가 더 크다.

```cpp
// 정렬 없이 주어진 순서대로 erase
string wrong = "apporoograpemmemprs";
vector<int> unsorted = {1, 16, 6, 15, 0, 10, 11, 3};
for (int index : unsorted) {
  wrong.erase(index, 1);
}
cout << wrong << '\n';  // pororapemep  (정답은 programmers)
```

오름차순 `{0, 1, 3, 6, 10, 11, 15, 16}`으로 지우면 아예 프로그램이 죽는다. 6번 지우고 나면 문자열 길이가 13인데 `erase(15, 1)`을 호출하게 되고, `out_of_range` 에러가 난다.

## 4. 패턴 코드

```cpp
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string my_string = "apporoograpemmemprs";
vector<int> indices = {1, 16, 6, 15, 0, 10, 11, 3};

sort(indices.rbegin(), indices.rend());  // 16 15 11 10 6 3 1 0
for (int index : indices) {
  my_string.erase(index, 1);
}
cout << my_string << '\n';  // programmers
```

두 줄만 기억하면 된다.

1. `sort(indices.rbegin(), indices.rend());`
2. `for (int index : indices) s.erase(index, 1);`

## 5. vector에서도 똑같이

`vector`의 `erase`는 인덱스 대신 **반복자**를 받는다. `v.begin() + i`가 i번 원소의 위치다.

```cpp
vector<int> nums = {10, 20, 30, 40, 50};
vector<int> remove_at = {0, 3, 1};

sort(remove_at.rbegin(), remove_at.rend());  // 3 1 0
for (int index : remove_at) {
  nums.erase(nums.begin() + index);
}
// nums: 30 50
```

| | string | vector |
|---|---|---|
| i번 1개 삭제 | `s.erase(i, 1)` | `v.erase(v.begin() + i)` |

## 6. 다른 방법: 체크 배열

지울 위치를 `bool` 배열에 표시해 두고, 표시 안 된 것만 새 문자열에 모으는 방법도 있다.

```cpp
vector<bool> is_deleted(my_string.size(), false);
for (int index : indices) is_deleted[index] = true;

string answer = "";
for (int i = 0; i < (int)my_string.size(); i++) {
  if (!is_deleted[i]) answer += my_string[i];
}
// answer: programmers
```

| | sort + erase | 체크 배열 |
|---|---|---|
| 코드 길이 | 짧음 | 조금 김 |
| 정렬 | 필요 | 불필요 |
| 시간 복잡도 | O(K log K + K·N) | O(N) |
| 언제 쓰나 | 길이가 짧을 때 (N ≤ 수천) | 길이가 길거나 지울 게 많을 때 |

N = 문자열 길이, K = 지울 개수. `erase`는 지울 때마다 뒤쪽 글자를 전부 당기므로 한 번에 O(N)이 든다. N이 10만 이상인데 지울 게 많으면 체크 배열을 쓴다.

## 7. 주의사항

1. **정렬을 빼먹지 않는다.** 정렬 안 하면 결과가 틀리고, 오름차순이면 범위 초과로 프로그램이 죽을 수 있다.
2. **`erase(pos)`와 `erase(pos, 1)`을 헷갈리지 않는다.** 길이를 빼먹으면 끝까지 다 지워진다.
3. **인덱스에 중복이 있으면** 같은 위치를 두 번 지워서 다른 글자가 사라진다. 중복 가능성이 있으면 체크 배열이 안전하다.
4. **입력이 크면** erase 반복이 느려진다. 6번의 체크 배열로 바꾼다.

## 8. 암기 한 줄

여러 인덱스 지우기: `sort(v.rbegin(), v.rend());` 후 큰 것부터 `erase(i, 1)`

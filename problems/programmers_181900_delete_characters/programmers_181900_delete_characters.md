# 프로그래머스 181900 글자 지우기

| 항목 | 내용 |
|---|---|
| 문제 | [글자 지우기](https://school.programmers.co.kr/learn/courses/30/lessons/181900) |
| 사이트 | 프로그래머스 > 코딩 기초 트레이닝 |
| 분류 | 문제 해결 기법 > 문자열 처리 > 원소 삭제 |
| 사용한 패턴 | [여러 인덱스 지우기 (`sort(rbegin, rend)` + `erase`)](../../patterns/erase_by_indices/erase_by_indices.md) |
| 시간 복잡도 | O(K log K + K·N) (N = 문자열 길이, K = 지울 개수) |
| 코딩테스트 중요도 | ★★★☆☆ |
| 제출 코드 | [programmers_181900_delete_characters.cc](programmers_181900_delete_characters.cc) |

## 목차
0. [배경](#0-배경)
1. [문제 요약](#1-문제-요약)
2. [입력·출력과 제한 조건](#2-입력출력과-제한-조건)
3. [접근 방법](#3-접근-방법)
4. [코드](#4-코드)
5. [다른 풀이: 체크 배열](#5-다른-풀이-체크-배열)
6. [시간 복잡도](#6-시간-복잡도)
7. [틀리기 쉬운 부분과 회고](#7-틀리기-쉬운-부분과-회고)

---

## 0. 배경

**개념**
문자열에서 여러 위치의 글자를 지우고 나머지를 이어 붙이는 문제다.

**목적**
`erase`로 지우면 뒤쪽 글자가 앞으로 당겨진다는 점을 직접 겪어 보는 문제다. 지울 인덱스를 `sort(rbegin, rend)`로 내림차순 정렬하고 뒤에서부터 지우면 이 문제가 사라진다. 이 방법은 다른 문제에도 그대로 쓸 수 있어서 [패턴 문서](../../patterns/erase_by_indices/erase_by_indices.md)로 따로 정리했다.

## 1. 문제 요약

문자열 `my_string`과 정수 배열 `indices`가 주어진다. `indices`에 있는 위치의 글자를 지우고 남은 글자를 이어 붙인 문자열을 return한다.

## 2. 입력·출력과 제한 조건

- 1 ≤ `indices` 길이 < `my_string` 길이 ≤ 100
- `my_string`은 영소문자만
- `indices`의 원소는 0 이상 `my_string` 길이 미만, **모두 서로 다름**
- `indices`는 **정렬되어 있지 않다**

| my_string | indices | result |
|---|---|---|
| `"apporoograpemmemprs"` | `[1, 16, 6, 15, 0, 10, 11, 3]` | `"programmers"` |

| index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 글자 | a | p | p | o | r | o | o | g | r | a | p | e | m | m | e | m | p | r | s |
| 지움 | ✔ | ✔ | | ✔ | | | ✔ | | | | ✔ | ✔ | | | | ✔ | ✔ | | |

## 3. 접근 방법

처음엔 `indices`를 돌면서 바로 `erase(index, 1)`하면 될 것 같다. 그런데 첫 번째로 1번 글자를 지우는 순간 그 뒤 글자가 전부 한 칸씩 당겨진다. 원래 16번이던 `p`는 15번이 되고, 다음 차례의 `erase(16, 1)`은 원래 17번 `r`을 지워 버린다.

뒤쪽 글자를 지우는 건 앞쪽 글자 위치에 영향을 주지 않는다. 그래서 순서를 이렇게 잡는다.

1. `indices`를 내림차순 정렬한다: `sort(indices.rbegin(), indices.rend())` → `16 15 11 10 6 3 1 0`
2. 정렬된 순서대로 `my_string.erase(index, 1)`을 호출한다.

| 순서 | 지울 인덱스 | 지운 글자 | 지운 뒤 문자열 |
|---|---|---|---|
| 1 | 16 | p | apporoograpemmemrs |
| 2 | 15 | m | apporoograpemmers |
| 3 | 11 | e | apporoograpmmers |
| 4 | 10 | p | apporoogrammers |
| 5 | 6 | o | apporogrammers |
| 6 | 3 | o | approgrammers |
| 7 | 1 | p | aprogrammers |
| 8 | 0 | a | programmers |

뒤에서부터 지우니까 매 단계에서 아직 안 지운 인덱스(더 작은 값)의 글자는 제자리에 있다.

## 4. 코드

```cpp
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string solution(string my_string, vector<int> indices) {
  sort(indices.rbegin(), indices.rend());  // 내림차순: 16 15 11 10 6 3 1 0
  for (int index : indices) {
    my_string.erase(index, 1);  // index 위치에서 1글자 삭제
  }
  return my_string;
}

// solution("apporoograpemmemprs", {1, 16, 6, 15, 0, 10, 11, 3})
// 반환값: "programmers"
```

> 프로그래머스가 함수 이름을 `solution`으로 정해 두었기 때문에 Google 스타일(PascalCase) 대신 그대로 쓴다.

**새로 나온 문법**

| 문법 | 의미 |
|---|---|
| `sort(v.rbegin(), v.rend())` | v를 내림차순 정렬. `rbegin`, `rend`는 배열을 뒤에서부터 보는 반복자 |
| `s.erase(pos, len)` | 문자열 s의 pos 위치부터 len글자 삭제 |
| `for (int x : v)` | 범위 기반 for. v의 원소를 앞에서부터 하나씩 x에 담아 반복 |

자세한 설명은 [패턴 문서](../../patterns/erase_by_indices/erase_by_indices.md)에 있다.

## 5. 다른 풀이: 체크 배열

지울 위치를 `true`로 표시해 두고, 표시 안 된 글자만 새 문자열에 붙인다. 원본을 건드리지 않으니 인덱스가 밀리는 문제가 처음부터 없다.

```cpp
string SolveByCheckArray(string my_string, vector<int> indices) {
  vector<bool> is_deleted(my_string.size(), false);  // 크기 N, 전부 false
  for (int index : indices) {
    is_deleted[index] = true;
  }

  string answer = "";
  for (int i = 0; i < (int)my_string.size(); i++) {
    if (!is_deleted[i]) {
      answer += my_string[i];  // 문자열 끝에 글자 붙이기
    }
  }
  return answer;
}

// 반환값: "programmers"
```

`(int)my_string.size()`: `size()`는 부호 없는 정수를 돌려주기 때문에 `int i`와 비교하면 컴파일러 경고가 난다. `(int)`로 형 변환해서 경고를 없앴다.

## 6. 시간 복잡도

| 풀이 | 시간 복잡도 | 이 문제에서 |
|---|---|---|
| sort + erase | O(K log K + K·N) | N ≤ 100이라 충분 |
| 체크 배열 | O(N) | 충분 |

`erase` 한 번에 뒤쪽 글자를 전부 당기므로 최대 O(N)이 든다. 이 문제는 길이가 100 이하라 상관없지만, 길이가 수십만인 문제에서 지울 게 많으면 체크 배열을 쓴다.

## 7. 틀리기 쉬운 부분과 회고

1. **정렬 없이 erase**: 결과가 `"pororapemep"`로 틀린다.
2. **오름차순으로 정렬하고 erase**: 6번 지운 뒤 길이가 13인데 `erase(15, 1)`을 호출해서 `out_of_range` 에러로 프로그램이 죽는다.
3. **`erase(index)`로 길이를 빼먹음**: index부터 끝까지 다 지워진다.

**회고**
- 글자 삭제는 `erase`로 한 줄에 끝난다.
- 여러 인덱스를 지울 때는 `sort(rbegin, rend)`로 뒤집어 정렬하고 뒤에서부터 지운다.

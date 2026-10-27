# sort()의 사용자 정의 비교 함수 (`Compare`)

| 항목 | 내용 |
|---|---|
| 분류 | 함수 > STL `<algorithm>` > 정렬 |
| 저장소 위치 | 패턴 |
| 헤더 | `<algorithm>` (`sort`, `stable_sort`), `<functional>` (`greater`) |
| 핵심 | `Compare(a, b)`가 `true`면 `a`를 `b`보다 앞에 둔다 |
| 코딩테스트 중요도 | ★★★★★ |
| 실행 예제 | [sort_custom_compare.cc](sort_custom_compare.cc) |

## 목차
0. [배경](#0-배경)
1. [문법 및 인자·반환값](#1-문법-및-인자반환값)
2. [실행 예제](#2-실행-예제)
3. [관련 함수 및 문법](#3-관련-함수-및-문법)
4. [주의사항](#4-주의사항)
5. [암기용 요약](#5-암기용-요약)

---

## 0. 배경

C++의 `sort()`는 원소를 정렬하는 함수이다. 기본적으로 오름차순으로 정렬하지만, 세 번째 인수로 **비교 함수**(Comparator)를 전달하면 원하는 기준으로 정렬할 수 있다.

```cpp
sort(v.begin(), v.end());           // 기본 오름차순
sort(v.begin(), v.end(), Compare);  // 사용자 정의 기준
```

`Compare`는 STL에 내장된 함수 이름이 아니라 개발자가 직접 정하는 함수 이름이다. `Cmp`, `ByScore` 등으로 바꾸어도 된다. (이 저장소는 Google 스타일에 따라 함수 이름을 대문자로 시작한다.)

| 항목 | 내용 |
|---|---|
| 헤더 | `#include <algorithm>` |
| 관련 함수 | `std::sort()` |
| 비교 함수의 역할 | 두 원소의 앞뒤 우선순위를 판단 |
| 비교 함수의 반환형 | `bool` |
| `sort()`의 반환형 | `void` |

## 1. 문법 및 인자·반환값

```cpp
bool Compare(int a, int b) {
  return a < b;
}

sort(v.begin(), v.end(), Compare);
```

| 구성 | 의미 |
|---|---|
| `a`, `b` | `sort()`가 비교를 위해 전달한 두 원소 |
| `true` | `a`가 `b`보다 앞에 와야 한다는 뜻 |
| `false` | `a`가 `b`보다 앞에 와야 한다는 조건이 성립하지 않음 |
| `v.begin()` | 정렬 범위의 시작 |
| `v.end()` | 정렬 범위의 끝 바로 다음 위치(포함되지 않음) |
| `Compare` | 함수 이름을 전달하며, `Compare()`처럼 호출하지 않음 |

### 원소가 여러 개인데 비교 함수의 인수는 왜 2개일까?

`sort()`가 정렬 과정에서 비교할 두 원소를 선택해 `Compare(a, b)`를 여러 번 호출하기 때문이다. 비교 함수는 전체 순열을 검사할 필요 없이 두 원소의 우선순위 규칙만 정의한다.

- 원소 5개의 순열은 5! = 120가지이다.
- 하지만 정렬은 120가지 순열을 전부 생성하여 비교하지 않는다.
- `std::sort()`는 C++ 표준상 O(N log N)회의 비교를 수행한다. 단, 비교 함수 자체의 실행 비용은 별도로 고려해야 한다.
- 실제 비교 호출 순서는 C++ 라이브러리 구현 및 입력에 따라 달라질 수 있다.

## 2. 실행 예제

### 2-1. 오름차순

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool Compare(int a, int b) {
  return a < b;
}

int main() {
  vector<int> v = {4, 1, 5, 2, 3};
  sort(v.begin(), v.end(), Compare);

  for (int n : v) cout << n << ' ';
  // 출력: 1 2 3 4 5
}
```

### 2-2. 내림차순

```cpp
bool Compare(int a, int b) {
  return a > b;
}

// {4, 1, 5, 2, 3} 정렬 결과: {5, 4, 3, 2, 1}
```

### 2-3. 문자열을 이어 붙인 크기로 정렬 — 「가장 큰 수」

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Compare(const string& a, const string& b) {
  return a + b > b + a;
}

int main() {
  vector<string> v = {"3", "30", "34", "5", "9"};
  sort(v.begin(), v.end(), Compare);

  for (const string& s : v) cout << s << ' ';
  // 출력: 9 5 34 3 30
}
```

`a = "3"`, `b = "30"`일 때:

| 식 | 결과 |
|---|---|
| `a + b` | `"330"` |
| `b + a` | `"303"` |
| `a + b > b + a` | `true` → `"3"`이 앞 |

여기서는 비교하는 두 문자열 `a + b`, `b + a`의 길이가 항상 같으므로, 숫자로 변환하지 않고 사전식 문자열 비교를 해도 어느 쪽이 큰 수를 만드는지 판단할 수 있다.

문제 전체를 해결할 때는 정렬과 별개로 `{0, 0, 0}`이 `"000"`이 아닌 `"0"`으로 반환되도록 예외 처리해야 한다.

### 2-4. 다중 조건 정렬 — 점수는 내림차순, 번호는 오름차순

```cpp
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

bool Compare(const pair<int, int>& a, const pair<int, int>& b) {
  if (a.first != b.first) {
    return a.first > b.first;  // 점수가 높으면 먼저
  }
  return a.second < b.second;  // 점수가 같으면 번호가 작을수록 먼저
}

int main() {
  // {점수, 번호}
  vector<pair<int, int>> v = {{90, 2}, {80, 3}, {90, 1}};
  sort(v.begin(), v.end(), Compare);

  for (const auto& p : v) cout << p.first << ' ' << p.second << '\n';
  // 출력:
  // 90 1
  // 90 2
  // 80 3
}
```

> **패턴:** 첫 번째 기준이 다르면 그 기준으로 비교하고, 같으면 두 번째 기준으로 비교한다.

## 3. 관련 함수 및 문법

### 3-1. 람다 함수: 별도의 Compare() 정의 생략

```cpp
sort(v.begin(), v.end(), [](int a, int b) {
  return a > b;  // 내림차순
});
```

비교 기준이 짧고 한 곳에서만 사용된다면 람다를 사용해도 된다.

### 3-2. `greater<int>()`: 간단한 내림차순

```cpp
#include <functional>

sort(v.begin(), v.end(), greater<int>());
```

내림차순만 필요하다면 직접 비교 함수를 만들 필요가 없다.

### 3-3. stable_sort(): 동등한 원소들의 입력 순서 유지

```cpp
stable_sort(v.begin(), v.end(), Compare);
```

비교 기준에서 동등하다고 판단되는 원소끼리는 입력 순서를 유지해야 할 때 사용한다. `sort()`는 이러한 순서 보존을 보장하지 않는다.

## 4. 주의사항

### 4-1. `<=` 또는 `>=` 사용 금지

```cpp
bool Wrong(int a, int b) {
  return a <= b;  // 잘못된 정렬 비교 함수
}

bool Correct(int a, int b) {
  return a < b;
}
```

`Wrong(3, 3)`은 `true`가 된다. 정렬 비교 함수는 **자기 자신과 비교하면 반드시 false**여야 한다. 이는 C++ 표준이 요구하는 엄격 약순서(strict weak ordering) 조건의 일부다.

### 4-2. false가 반드시 역순을 뜻하지는 않음

```cpp
Compare(3, 3);  // false (오름차순 기준)
```

`Compare(a, b) == false`는 `b`가 반드시 `a`보다 먼저 와야 한다는 뜻이 아니다. 두 원소가 동등한 순위일 수도 있다.

### 4-3. 비교 기준이 일관되어야 함

`Compare(a, b)`와 `Compare(b, c)`가 `true`라면 `Compare(a, c)`도 `true`여야 한다(추이성). 비교할 때마다 무작위 결과를 내거나 모순된 순서를 정의하면 정렬의 전제조건을 위반한다.

### 4-4. 원소의 자료형과 인수형 맞추기

| 정렬 대상 | 비교 함수 인수 예시 |
|---|---|
| `vector<int>` | `int a, int b` |
| `vector<string>` | `const string& a, const string& b` |
| `vector<pair<int, int>>` | `const pair<int, int>& a, const pair<int, int>& b` |

`const T&`는 불필요한 복사를 피하면서 원소를 변경하지 않도록 할 때 유용하다. `int`처럼 작은 자료형은 값으로 전달해도 일반적이다.

---

## 5. 암기용 요약

| 목적 | `Compare(a, b)`의 핵심 코드 |
|---|---|
| 오름차순 | `return a < b;` |
| 내림차순 | `return a > b;` |
| 문자열 결합 기준 | `return a + b > b + a;` |
| 1순위 내림차순, 2순위 오름차순 | `if (a.first != b.first) return a.first > b.first; return a.second < b.second;` |

> **암기할 한 문장:** `Compare(a, b)`의 반환값이 `true`라면 `a`를 `b`보다 앞에 배치한다.

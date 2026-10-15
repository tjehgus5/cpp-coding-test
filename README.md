# C++ 코딩테스트 정리

코딩테스트 합격을 목표로 C++ 패턴과 문제 풀이를 정리하는 저장소.

## 폴더 구조

```
cpp-coding-test/
├── README.md
├── patterns/                 # 자주 쓰는 코드 패턴
│   ├── README.md             # 패턴 목록
│   └── char_to_int/
│       ├── char_to_int.md    # 설명
│       └── char_to_int.cc    # 실행 가능한 예제
└── problems/                 # 문제 풀이
    └── README.md             # 문제 목록
```

| 폴더 | 무엇을 넣나 |
|---|---|
| `patterns/` | 여러 문제에서 반복해서 쓰는 코드 조각과 문법 (변환, 입출력, 정렬 기준 등) |
| `problems/` | 문제 하나의 전체 풀이 과정 (문제 분석 → 접근 → 코드 → 회고) |

## 이름 규칙

[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) 기준.

| 대상 | 규칙 | 예시 |
|---|---|---|
| 폴더, 파일 | 소문자 + 밑줄 | `char_to_int/`, `char_to_int.md` |
| 소스 파일 확장자 | `.cc` | `char_to_int.cc` |
| 함수 | 대문자로 시작하는 단어 연결 (PascalCase) | `AddBig()` |
| 변수 | 소문자 + 밑줄 (snake_case) | `number_str`, `alphabet_count` |
| 상수 | `k` + PascalCase | `kMaxSize` |
| 들여쓰기 | 공백 2칸 | |

문제 폴더는 `<사이트>_<번호>_<제목>` 형식으로 만든다. 예: `problems/boj_11720_sum_of_digits/`

> Google 가이드는 `using namespace std;`를 금지하지만, 코딩테스트 코드는 짧고 시간이 중요해서 이 저장소에서는 허용한다.

## 컴파일

```bash
g++ -std=c++17 -o char_to_int patterns/char_to_int/char_to_int.cc
./char_to_int
```

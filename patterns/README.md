# 패턴

여러 문제에서 반복해서 쓰는 코드 조각과 문법.

| 패턴 | 분류 | 한 줄 요약 | 중요도 |
|---|---|---|---|
| [char_to_int](char_to_int/char_to_int.md) | 문법 > 문자·자료형 변환 | 숫자 문자 → 정수: `c - '0'` | ★★★★★ |
| [erase_by_indices](erase_by_indices/erase_by_indices.md) | 문제 해결 기법 > 원소 삭제 | 여러 인덱스 지우기: `sort(rbegin, rend)` 후 뒤에서부터 `erase` | ★★★☆☆ |
| [sort_custom_compare](sort_custom_compare/sort_custom_compare.md) | 함수 > STL `<algorithm>` > 정렬 | 정렬 기준 직접 정하기: `Compare(a, b)`가 `true`면 `a`가 앞 | ★★★★★ |

## 추가 방법

1. `patterns/<패턴_이름>/` 폴더를 만든다. (소문자 + 밑줄)
2. 안에 `<패턴_이름>.md`(설명)와 `<패턴_이름>.cc`(실행 예제)를 넣는다.
3. 위 표에 한 줄 추가한다.

# cub3d
**cub3d**는 간단한 2D 맵 데이터를 바탕으로 레이 캐스팅을 사용하여 3D처럼 보이는 1인칭 시점을 구현하는 프로젝트입니다. 이 프로젝트는 42서울 커리큘럼의 일환으로, 그래픽스 프로그래밍의 기초 개념을 학습하는 것을 목표로 합니다.

# 프로젝트의 목표
- 레이 캐스팅(ray casting)을 이용한 3D 시각화
- 키보드를 통한 플레이어 이동 및 회전 구현
- 기본적인 충돌 처리 시스템
- 2D 맵 파싱 및 유효성 검사

# 주요 기능
## mandatory
- WASD 키를 통한 이동, 방향키를 통한 회전
- 벽에 닿았을 때 이동 차단
- 텍스처를 입힌 벽면 랜더링
- 단일 .cub 맵 파일을 읽어 초기화
## bonus
- 마우스로 회전 구현
- E를 입력해 문 상호작용
- 간단한 minimap 구현
- Space bar를 입력해 모션 애니메이션 재생

# 프로그램 구조
<img width="3043" alt="Untitled" src="https://github.com/user-attachments/assets/b70f7981-a507-4eb0-bd46-cbdc6eac2884" />

기능 명세서 [링크](https://docs.google.com/spreadsheets/d/1zbRwd6gnVwAyFKsiN_fW3u1D4u0lJJvJl_f5ZlufPTs/edit?gid=0#gid=0)

# 실행 방법
본 프로그램은 Unix(macOS)에서만 실행 가능합니다.
```bash
git clone https://github.com/juhyeon98/Cub3d.git
cd Cub3d
```
### mandantory
```bash
make
```
### bonus
```bash
make bonus
```
# 주의 사항 : 맵 파일
- 맵 파일은 `.cub` 확장자의 파일이어야 합니다.
- 파일 내부에 있어야 할 데이터는 아래와 같습니다.
```text
## 텍스처 리스트
NO texture/north.xpm
SO texture/south.xpm
WE texture/west.xpm
EA texture/east.xpm

## 천장 색상과 바닥 생상
C 31,229,207
F 22,156,1

## 2차원 맵 데이터
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111110111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
- 텍스처는 반드시 4개를 지정해야 하며, 중복되어선 안됩니다.
- 생상은 반드시 RGB 형식(RGB-A는 지원하지 않습니다)이어야 합니다.
- 플레이어는 반드시 방 안에 있어야 합니다.
- 맵 데이터에 있어야할 데이터는 다음과 같습니다.
    - 벽면 : 1
    - 통로 : 0
    - 플레이어(방향에 따라) : N/S/W/E
- 당연히 플레이어는 하나만 있어야 합니다.
## bonus
- bonus를 실행하기 위한 맵 파일에는 아래와 같은 요소를 추가할 수 있습니다.
    - 아이템 : A
    - 문 : D

# 참고 자료
[Ray casting 설명](https://lodev.org/cgtutor/raycasting.html)

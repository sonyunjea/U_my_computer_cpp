#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

// 맵의 크기를 정의
const int MAP_SIZE = 5;

// 위치를 나타내는 구조체
struct Position {
    int x;
    int y;
};

// 랜덤한 방향으로 움직임
void moveRandom(Position& pos) {
    int direction = rand() % 4; // 0: 위, 1: 아래, 2: 왼쪽, 3: 오른쪽
    switch (direction) {
    case 0: if (pos.y > 0) pos.y--; break;
    case 1: if (pos.y < MAP_SIZE - 1) pos.y++; break;
    case 2: if (pos.x > 0) pos.x--; break;
    case 3: if (pos.x < MAP_SIZE - 1) pos.x++; break;
    }
}

// 맵을 출력
void printMap(const Position& a, const Position& b, const Position& h, bool combined) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (x == a.x && y == a.y && !combined) cout << "A ";
            else if (x == b.x && y == b.y && !combined) cout << "B ";
            else if (x == h.x && y == h.y) cout << "H ";
            else if (combined && x == a.x && y == a.y) cout << "C ";
            else cout << "- ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(NULL)); // 랜덤 시드 초기화

    // 초기 위치 설정
    Position a = { rand() % MAP_SIZE, rand() % MAP_SIZE };
    Position b = { rand() % MAP_SIZE, rand() % MAP_SIZE };
    Position h = { rand() % MAP_SIZE, rand() % MAP_SIZE };

    bool combined = false;

    // h 위치가 a나 b와 겹치지 않게 설정
    while ((a.x == h.x && a.y == h.y) || (b.x == h.x && b.y == h.y)) {
        h = { rand() % MAP_SIZE, rand() % MAP_SIZE };
    }

    // 게임 루프
    while (true) {
        system("cls"); // 콘솔 화면 클리어
        printMap(a, b, h, combined);

        // a와 b가 만나면 결합
        if (a.x == b.x && a.y == b.y) {
            combined = true;
        }

        // 움직임 처리
        if (!combined) {
            moveRandom(a);
            moveRandom(b);
        }
        else {
            moveRandom(a); // a의 위치가 c의 위치가 됨
        }

        // c가 h 위치에 도달하면 게임 종료
        if (combined && a.x == h.x && a.y == h.y) {
            cout << "C reached H. Game Over!" << endl;
            break;
        }

        // 딜레이
        Sleep(15); // 300 밀리초 동안 프로그램을 일시 중지합니다.
    }

    return 0;
}

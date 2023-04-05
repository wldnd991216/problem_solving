#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <Windows.h>

using namespace std;

// 위치를 표현하는 구조체
struct Position {
    int x;
    int y;
};

// 두 위치 간의 맨해튼 거리 계산
int manhattanDistance(Position pos1, Position pos2) {
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
}

// 최단 경로 찾기
vector<Position> findShortestPath(Position start, Position end) {
    // 방문 여부와 이전 위치 저장을 위한 2차원 배열
    vector<vector<bool>> visited(5, vector<bool>(5, false));
    vector<vector<Position>> prev(5, vector<Position>(5));

    // 우선순위 큐를 사용하여 다익스트라 알고리즘 적용
    priority_queue<pair<int, Position>, vector<pair<int, Position>>, greater<pair<int, Position>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        Position curr = pq.top().second;
        pq.pop();

        // 목적지에 도달하면 이전 위치들을 따라가며 경로 추적
        if (curr.x == end.x && curr.y == end.y) {
            vector<Position> path;
            while (curr.x != start.x || curr.y != start.y) {
                path.push_back(curr);
                curr = prev[curr.x][curr.y];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        // 현재 위치에서 이동 가능한 위치들 큐에 추가
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // 현재 위치는 제외
                int nextX = curr.x + dx;
                int nextY = curr.y + dy;
                // 맵을 벗어나는 위치는 제외
                if (nextX < 0 || nextX >= 5 || nextY < 0 || nextY >= 5) continue;
                // 이미 방문한 위치는 제외
                if (visited[nextX][nextY]) continue;

                // 현재 위치에서 다음 위치까지의 맨해튼 거리 계산
                int dist = manhattanDistance(curr, { nextX, nextY });
                pq.push({ dist, {nextX, nextY} });

                // 방문 여부와 이전 위치 갱신
                visited[nextX][nextY] = true;
                prev[nextX][nextY] = curr;
            }
        }
    }

    // 도달할 수 없는 경우 빈 경로 반환
    return {};
}

int main() {
    Position playerPos = { 0, 0 };
    Position enemyPos = { 4, 4 };

    // 맵 초기화
    vector<vector<char>> map(5, vector<char>(5, '.'));

    // 플레이어와 적 배치
    map[playerPos.x][playerPos.y] = 'P';
    map[enemyPos.x][enemyPos.y] = 'E';

    // 최단 경로 찾기
    vector<Position> shortestPath = findShortestPath(playerPos, enemyPos);

    // 최단 경로 색칠
    for (Position pos : shortestPath) {
        if (pos.x == playerPos.x && pos.y == playerPos.y) continue; // 플레이어 위치는 제외
        if (pos.x == enemyPos.x && pos.y == enemyPos.y) continue; // 적 위치는 제외
        map[pos.x][pos.y] = 'X';
    }

    // 맵 출력
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    // 최단 경로 출력
    cout << "Shortest path: ";
    for (Position pos : shortestPath) {
        cout << "(" << pos.x << ", " << pos.y << ") ";
    }
    cout << endl;

    // 콘솔창 윈도우 유지
    system("pause");

    return 0;
}
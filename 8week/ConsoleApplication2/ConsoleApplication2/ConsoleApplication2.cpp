#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <utility>

using namespace std;

const int HANG = 10; // 행 
const int YEOL = 10; // 열 

class Map {
private: char map[HANG][YEOL];

public: Map() {

	for (int i = 0; i < HANG; i++) {
		for (int j = 0; j < YEOL; j++) {
			map[i][j] = '.';
		}
	}
}

	  void set_point(int x, int y, char ch) {
		  map[x][y] = ch;
	  }

	  char get_point(int x, int y) const {
		  return map[x][y];
	  }

	  void print_map() {
		  for (int i = 0; i < HANG; i++) {
			  for (int j = 0; j < YEOL; j++) {
				  cout << map[i][j] << ' ';
			  }
			  cout << endl;
		  }
	  }
};

class ObstacleGenerator {
public: static void generate_obstacles(Map& game_map) {
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		int x = rand() % HANG;
		int y = rand() % YEOL;
		game_map.set_point(x, y, 'x');
	}
}
};

class StartGoalGenerator {
private: int start_x,
	start_y;
	   int goal_x,
		   goal_y;

public: StartGoalGenerator(Map& game_map) {
	srand(time(NULL));
	do {
		start_x = rand() % HANG;
		start_y = rand() % YEOL;
	} while (game_map.get_point(start_x, start_y) != '.');
	game_map.set_point(start_x, start_y, 'E');

	do {
		goal_x = rand() % HANG;
		goal_y = rand() % YEOL;
	} while (game_map.get_point(goal_x, goal_y) != '.');
	game_map.set_point(goal_x, goal_y, 'P');
}

	  int get_start_x() const {
		  return start_x;
	  }
	  int get_start_y() const {
		  return start_y;
	  }
	  int get_goal_x() const {
		  return goal_x;
	  }
	  int get_goal_y() const {
		  return goal_y;
	  }
};

class Pathfinder {
private: const Map& game_map;
	   const StartGoalGenerator& sg_gen;

public: Pathfinder(const Map& game_map,
	const StartGoalGenerator& sg_gen) : game_map(game_map),
	sg_gen(sg_gen) {}

	  int bfs(Map& path_map) {
		  int dx[] = {
			-1,
			0,
			1,
			0
		  };
		  int dy[] = {
			0,
			1,
			0,
			-1
		  };
		  queue < pair < int, int >> q;
		  int dist[HANG][YEOL] = {
			0
		  };

		  q.push({
			sg_gen.get_start_x(),
			sg_gen.get_start_y()
			  });
		  dist[sg_gen.get_start_x()][sg_gen.get_start_y()] = 1;

		  while (!q.empty()) {
			  int x = q.front().first;
			  int y = q.front().second;
			  q.pop();

			  for (int i = 0; i < 4; i++) {
				  int nx = x + dx[i];
				  int ny = y + dy[i];

				  if (nx >= 0 && nx < HANG && ny >= 0 && ny < YEOL && game_map.get_point(nx, ny) != 'x' && dist[nx][ny] == 0) {
					  q.push({
						nx,
						ny
						  });
					  dist[nx][ny] = dist[x][y] + 1;

					  if (game_map.get_point(nx, ny) == 'P') {
						  int cx = nx;
						  int cy = ny;
						  while (game_map.get_point(cx, cy) != 'E') {
							  if (game_map.get_point(cx, cy) == '.') {
								  path_map.set_point(cx, cy, '*');
							  }
							  for (int j = 0; j < 4; j++) {
								  int nx2 = cx + dx[j];
								  int ny2 = cy + dy[j];
								  if (nx2 >= 0 && nx2 < HANG && ny2 >= 0 && ny2 < YEOL && dist[nx2][ny2] == dist[cx][cy] - 1) {
									  cx = nx2;
									  cy = ny2;
									  break;
								  }
							  }
						  }
						  return dist[nx][ny] - 1;
					  }
				  }
			  }
		  }
		  return -1;
	  }
};

int main() {
	Map game_map;
	ObstacleGenerator::generate_obstacles(game_map);
	StartGoalGenerator sg_gen(game_map);
	Pathfinder pathfinder(game_map, sg_gen);
	Map path_map = game_map;
	int shortest_path = pathfinder.bfs(path_map);

	cout << "P 출발 / E 도착 / . 땅 / * 경로 / x 장애물 \n" << endl;

	cout << "===== P, E, x 배치 =====" << endl;
	game_map.print_map();
	cout << endl;

	cout << "======= 경로 표시 ======" << endl;
	path_map.print_map();

	cout << endl;

	if (shortest_path > 0) {
		cout << "최단 거리: " << shortest_path << endl;
	}
	else {
		cout << "경로 존재 x" << endl;
	}

	return 0;
}
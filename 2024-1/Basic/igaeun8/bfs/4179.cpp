// 불이 전파 되는 시간을 먼저 구하고 q1
// 지훈이가 탈출하는 시간을 구하기 Q2
// 해당 거리까지 이동 시간보다 불이 전파되는 시간이 빠르면 이동 가능

#include<iostream>
#include<string>
#include<queue>
#include<utility>

#define X first
#define Y second

using namespace std;


string board[1001];

int dist1[1001][1001]; //불의 전파 시간
int dist2[1001][1001]; // 탈출 속도

int n, m;

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	queue<pair<int, int>> Q1; //불
	queue<pair<int, int>> Q2; //탈출

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> board[i];
	}

	for (int i = 0; i < n; i++) {
		fill(dist1[i], dist1[i] + m, -1);
		fill(dist2[i], dist2[i] + m, -1);
	}
	
	// Q1에 불이 난 위치 저장
	// Q2에 지훈이의 위치 저장
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'F') {
				Q1.push({ i,j });
				dist1[i][j] = 0;
			}
			if (board[i][j] == 'J') {
				Q2.push({ i,j });
				dist2[i][j] = 0;
			}
		}
	}
	
	// 불의 전파 시간 구하기
	while (!Q1.empty()) {
		auto cur = Q1.front(); Q1.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (dist1[nx][ny] >= 0 || board[nx][ny] == '#') continue;
			dist1[nx][ny] = dist1[cur.X][cur.Y] + 1;
			Q1.push({ nx,ny });

		}
	}

	// 지훈이의 위치를 구하기
	// 미로의 가장자리를 넘어오는 순간이 오면 가장 빠른 탈출 시간 출력
	while (!Q2.empty()) {
		auto cur = Q2.front(); Q2.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
				cout << dist2[cur.X][cur.Y] + 1;
				return 0;
			}
			if (dist2[nx][ny] >= 0 || board[nx][ny] == '#') continue;
			if (dist1[nx][ny] != -1 && dist1[nx][ny] <= dist2[cur.X][cur.Y] + 1) continue;
			dist2[nx][ny] = dist2[cur.X][cur.Y] + 1;
			Q2.push({ nx,ny });

		
 		}
	}
	cout << "IMPOSSIBLE";

}

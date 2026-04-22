#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int main(void)
{
	struct Position {
		int row;
		int col;
	};
	struct Position queue[MAX_ROW * MAX_COL];
	struct Position parent[MAX_ROW][MAX_COL];
	int visited[MAX_ROW][MAX_COL] = {0};
	int direction_row[4] = {1, 0, -1, 0};
	int direction_col[4] = {0, 1, 0, -1};
	int front = 0;
	int rear = 0;
	int found = 0;

	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			parent[row][col].row = -1;
			parent[row][col].col = -1;
		}
	}

	queue[rear].row = 0;
	queue[rear].col = 0;
	rear++;
	visited[0][0] = 1;

	while (front < rear) {
		struct Position current = queue[front++];

		if (current.row == MAX_ROW - 1 && current.col == MAX_COL - 1) {
			found = 1;
			break;
		}

		for (int dir = 0; dir < 4; dir++) {
			int next_row = current.row + direction_row[dir];
			int next_col = current.col + direction_col[dir];

			if (next_row < 0 || next_row >= MAX_ROW ||
				next_col < 0 || next_col >= MAX_COL) {
				continue;
			}

			if (maze[next_row][next_col] == 1 || visited[next_row][next_col]) {
				continue;
			}

			visited[next_row][next_col] = 1;
			parent[next_row][next_col] = current;
			queue[rear].row = next_row;
			queue[rear].col = next_col;
			rear++;
		}
	}

	if (!found) {
		printf("No path!\n");
		return 0;
	}

	{
		struct Position path[MAX_ROW * MAX_COL];
		int count = 0;
		struct Position current;

		current.row = MAX_ROW - 1;
		current.col = MAX_COL - 1;

		while (current.row != -1 && current.col != -1) {
			path[count++] = current;
			current = parent[current.row][current.col];
		}

		for (int i = 0; i < count; i++) {
			printf("(%d, %d)\n", path[i].row, path[i].col);
		}
	}


	return 0;
}
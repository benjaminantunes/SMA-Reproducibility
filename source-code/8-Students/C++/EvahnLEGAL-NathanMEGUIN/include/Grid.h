#ifndef GRID_H
#define GRID_H

#define MAX_LENGTH 300
#define MAX_HEIGHT 300

class Grid {
public:
	Grid(int length, int height);

	int getLength() const;
	int getHeight() const;
	int& getSquare(int x, int y);

private:
	int length;
	int height;
	int grid[MAX_HEIGHT][MAX_LENGTH];
};

#endif

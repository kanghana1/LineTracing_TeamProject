#define MAX_POINTS 100 // max points
#define MAX_DISTANCE 1000000000 // max distance
#define INF 987654321
typedef struct Point {
	int x;
	int y;
} Point;


float Calculate(Point point1, Point point2){
	return abs((point1.x + point1.y) - (point2.x + point2.y));
}

float findShortestDistance(Point currentPosition, Point redPoint, int redPointCount){
	float shortestDistance = MAX_DISTANCE;

	for (int i = 0; i < redPointCount; i++){
		float distance = Calculate(currentPosition, redPoint);
		if (distance < shortestDistance) {
			shortestDistance = distance;
		}
	}

	return shortestDistance;
}


Point currentPosition = {0, 0};
bool isPointZero(Point point){
	return (point.x == 0 && point.y == 0);
}

void bell_ford(grid, Point start, Point end){
	rows = len(grid);
	cols = len(grid[0]);
	float distance[rows][cols];


	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			distance[i][j] = grid[i][j];}}
	}

task main()
{
	Point redPoint[MAX_POINTS];
	int redPointCount = 0; //add points

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			if (colorMapping[i][j] == 2){ // if red;
				redPoint[redPointCount].x = i;
				redPoint[redPointCount].y = j;
				redPointCount++;}
		}
	}
	//redPoint location store.
	findShortestDistance();
	ff();



}

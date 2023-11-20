#define MAX_POINTS 100 // max points
#define MAX_DISTANCE 1000000000 // max distance
#define INF 987654321

/*explanation function & variables
1. point = the location of point(x, y)
2. calculate = calcualte the distance of point1 and point2. return distance.
			 = it will help comparing the distance of red patches and current location. 
3. findshortestDistance = to find the shortest distance among redponits. 
						its parameters are 1) current location x, y 2) red patches location x, y 3) the number of red patches.
4. first current poisition will be (4, 4)
5. isPointzero is to check whether robot is on (0, 0) or not. 
6. bell_ford = to find weights between verteces and edges
7. redpoint[max_point] is the location of red patches. it will help to compare distance between red patches and current position
*/

// not reversed, same order array for now. 

/*operate
1. When robot go to first red patch, drop the that red patch in redpoint[], and redcount--;*/


typedef struct Point {
	int x;
	int y;
} Point;


float Calculate(Point point1, Point point2){ //calculate the distance of point1 and point2. 
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


Point currentPosition = {4, 4};
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

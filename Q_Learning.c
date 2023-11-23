#define MAX_POINTS 100 // max points
#define MAX_DISTANCE 1000000000 // max distance
#define INF 987654321

Point redPoint[MAX_POINTS];
int redPointCount = 0; //add points
float QMap[5][5];
//colorMapping must be a global variable
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
	int r;
	int c;
} Point;

Point currentPosition = {4, 4}; // start point. 

int score = 0; // the number of red patches that robot gets.

float oneQmap(Point p1) { // 예를 들어 레드포인트가 0,1 일 떄
	int r, c;
	int Qmap[5][5]; // 큐맵 중 한 개
	

	for (int i = 0 ; i < 5 ; i++) { // 파란점 외에는 0으로 초기화
		for (int j = 0 ; j < 5 ; j++) {
			if (colorMapping[i][j] == -1) QMap[i][j] = -1; 
			else QMap[i][j] = 0;
		}
	}
	Qmap[p1.r][p1.c] = 1; // 레드포인트 한 개만 넣기

	for (int i = 0 ; i < 5 ; i++) {
		for (int j = 0 ; j < 5 ; j++) {
			if (QMap[i][j] == 0) { 
				if (abs(p1.r - i) + abs(p1.c - j) == 1) {
					QMap[i][j] = 0.9;
					cnt++;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 2) {
					QMap[i][j] = 0.72;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 3) {
					QMap[i][j] = 0.5;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 4) {
					QMap[i][j] = 0.3;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 5) {
					QMap[i][j] = 0.15;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 6) {
					QMap[i][j] = 0.06;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 7) {
					QMap[i][j] = 0.02;
				}
				else if (abs(p1.r - i) + abs(p1.c - j) == 7) {
					QMap[i][j] = 0.004;
				}
			}
		}
	}
	return QMap;
}



int row, rr, cc, col; 
task main()
{
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			if (colorMapping[i][j] == 1){ // if red;
				redPoint[redPointCount].x = i;
				redPoint[redPointCount].y = j;
				redPointCount++;}
		}
	}

	//redPoint location store.
	Point togo = findShortestDistance(currentPosition, redPoint, redPointCount); // first
	weight(currentPosition, togo);
	
	row = currentPosition.r;
	col = currentPosition.c;
	rr = togo.r;
	cc = togo.c;
	while (rr != row || cc != col){
		if (rr == currentPosition.r)
	}
	


	
}

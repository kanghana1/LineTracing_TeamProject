#define MAX_POINTS 100 // max points
#define MAX_DISTANCE 1000000000 // max distance
#define INF 987654321

Point redPoint[MAX_POINTS];
 int redPointCount = 0; //add points
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

 


/*
float Calculate(Point point1, Point point2){ //calculate the distance of point1 and point2. 
	return abs((point1.r + point1.c) - (point2.r + point2.c));
}

Point findShortestDistance(Point currentPosition, Point redPoint[], int redPointCount){ // send redPoint array. compare each elements
	float shortestDistance = MAX_DISTANCE;
	Point shortest_redPatch; // 최단거리 레드패치의 좌표

	for (int i = 0; i < redPointCount; i++){
		float distance = Calculate(currentPosition, redPoint[i]);
		if (distance < shortestDistance) {
			shortestDistance = distance;
			shortest_redPatch.r = redPoint[i].r;
			shortest_redPatch.c = redPoint[i].c;
		}
	}

	return shortest_redPatch; // it returns shortest_redPatch location x, y
}

bool isPointZero(Point point){
	return (point.r == 0 && point.c == 0);
}


void bell_ford(Point start, Point end, int array[5][5]){ // Pointer memory ? ?? 
	for (int i = 0; i< 5; i++){
		for (int j = 0; j < 5; j++){
			array[i][j] = 0; // give initial values 
		}
	}

	int offset_r, offset_c, limit_r, limit_c;

	if (start.r > end.r){limit_r = start.r; offset_r = end.r;}
	else{limit_r = end.r; offset_r = start.r;}

	if (start.c > end.c){limit_c = start.c; offset_c = end.c;}
	else{limit_c = end.c; offset_c = start.c;}
	// to copy array 


	// copy array 
	for (int r = offset_r; r <= limit_r; r++){
		for (int c = offset_c; c <= limit_c; c++){
			array[r][c] = colorMapping[r][c];
		}
	}

	return array;
} 

// 과연 그 부분만 배열을 따오는 함수가 필요한가? 필요함. 무조건 0. 
int weight_array[5][5]; // !!!!! 전역변수면 bell_ford의 인자로 넣을 필요가 있을까 ?
int** weight(Point start, Point end){ // !!!!! start ~ end 2차원배열 반환
	bell_ford(start, end, weight_array);
	// find weight / use lecture reference
	if (end.r - start.r <= 0 && end.c - start.c <= 0) {// left, up{}
		for (int i = start.r; i >= end.r; i--){
			for (int j = start.c; j >= end.c; j--){
				if (i == start.r && j == start.c) weight_array[i][j] = colorMapping[i][j];
				else if (i == start.r) weight_array[i][j] = weight_array[i][j+1] + colorMapping[i][j];
				else if (j == start.c) weight_array[i][j] = weight_array[i+1][j] + colorMapping[i][j];
				else weight_array[i][j] = max(weight_array[i+1][j], weight_array[i][j+1]) + colorMapping[i][j];
			}
		}
	}
	else if (end.r - start.r >= 0 && end.c - start.c <= 0) {// left, down 
		for (int i = start.r; i <= end.r; i++){
			for (int j = start.c; j >= end.c; j--){
				if (i == start.r && j == start.c) weight_array[i][j] = colorMapping[i][j];
				else if (i == start.r) weight_array[i][j] = weight_array[i][j+1] + colorMapping[i][j];
				else if (j == start.c) weight_array[i][j] = weight_array[i-1][j] + colorMapping[i][j];
				else weight_array[i][j] = max(weight_array[i-1][j], weight_array[i][j+1]) + colorMapping[i][j];
			}
		}
	}
	else {// right, up
		for (int i = start.r; i >= end.r; i--){
			for (int j = start.c; j <= end.c; j++){
				if (i == start.r && j == start.c) weight_array[i][j] = colorMapping[i][j];
				else if (i == start.r) weight_array[i][j] = weight_array[i][j-1] + colorMapping[i][j];
				else if (j == start.c) weight_array[i][j] = weight_array[i+1][j] + colorMapping[i][j];
				else weight_array[i][j] = max(weight_array[i+1][j], weight_array[i][j-1]) + colorMapping[i][j];
			}
		}
	}

	return weight_array;
}

*/

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

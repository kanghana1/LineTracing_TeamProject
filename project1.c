#pragma config(Sensor, S1, c1, sensorEV3_Color) // left color
#pragma config(Sensor, S2, c2,  sensorEV3_Color) // middle color
#pragma config(Sensor, S3, c3, sensorEV3_Color) // right color
#pragma config(Motor,  motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rm, tmotorEV3_Large, PIDControl, encoder)

// define color
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6

#define W_BOUND 31 // Boundary area white
#define Y_BOUND 21 // Boundary area yellow

// This code reter to lecture paper.
int speed = 20;
int r, g, b;
int row = 0;
int col = 0;

// These varibles will be a control point.
int count = -1; // count = 0,0 start, because first point has a cross line.
int val = 7; // for control speed.

int S[5][5]; // change the name, it was "colorMapping" before
int beforeArray[50];
int size = 0;
int redCount = 5;

int red_or_green(int red, int green, int blue){
   displayBigTextLine(10, "%d %d %d", red, green, blue);
    if (red >= 10)
    {
      if ((blue >= 30)) return White; // red
      else if (green >= 20) return Yellow; // yellow
      else return Red;
    }
    else return Green;
}
int white_or_not(int red, int green, int blue)
{
  if (blue >= W_BOUND) return White;
  else return Yellow;
}

void tracing() // Boundary area linetracing
{
  int r, g, b;
  getColorRGB(c2, r, g, b);

  int color;
  color = white_or_not(r, g, b);

  displayBigTextLine(5, "traicing %d", color);

  if (color != White) // 4: yellow
  {
    setMotorSpeed(lm, speed - val);
    setMotorSpeed(rm, speed + val);
  }
  else {
    setMotorSpeed(lm, speed + val);
    setMotorSpeed(rm, speed - val);
  }
}

void go(){ // go straight following points. if meet crossline -> stop. -> color censor -> store -> go
  int r, g, b;
  getColorRGB(c2, r, g, b);
  int color;
  color = white_or_not(r, g, b);

  displayBigTextLine(5, "go %d", color);
  if (color != White) // 4: yellow
  {
    setMotorSpeed(lm, speed - val);
    setMotorSpeed(rm, speed + val);
  }
  else
  {
    setMotorSpeed(lm, speed + val);
    setMotorSpeed(rm, speed - val);
  }
  if (getColorName(c1) == Yellow || getColorName(c3) == Yellow)
  { // if cross line, stop, color censor operate.
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    count++;
    sleep(100);

    setMotorSpeed(lm, 5);
    setMotorSpeed(rm, -3);
    sleep(700);

    getColorRGB(c2, r, g, b);
    color = red_or_green(r, g, b);
    if(row % 2 == 0){
    if (color == Red) {S[row][count] = 1; playTone(100, 20); sleep(80);} // for accuracy
    else if (color == Green) {S[row][count] = -1; playTone(500, 20); sleep(80);} // for accuracy
    }
    else{
      if (color == Red) {S[row][4-count] = 1; playTone(100, 20); sleep(80);} // for accuracy
      else if (color == Green) {S[row][4-count] = -1; playTone(500, 20); sleep(80);} // for accuracy
    }
    displayBigTextLine(5, "go %d", color);

    setMotorSpeed(lm, -3);
    setMotorSpeed(rm, 5);
    sleep(700);
    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, 20);
    sleep(500);
  }
}

void turnLeft(){
  displayBigTextLine(5, "turnLeft");
  int r, g, b;
  getColorRGB(c2, r, g, b);
  int color;
  color = white_or_not(r, g, b);
  while(color != 6){
    setMotorSpeed(lm, -speed * 7/10);
    setMotorSpeed(rm, speed * 7/10);
    displayBigTextLine(5, "turnLeft %d", color);
    getColorRGB(c2, r, g, b);
    color = white_or_not(r, g, b);
  }
  while (color == 6) {
    setMotorSpeed(lm, -speed * 7/10);
    setMotorSpeed(rm, speed * 7   /10);
    displayBigTextLine(5, "turnLeft %d", color);
    getColorRGB(c2, r, g, b);
    color = white_or_not(r, g, b);
  }
  sleep(150);
  setMotorSpeed(lm, 0);
  setMotorSpeed(rm, 0);
  sleep(100);
}

void turnRight(){
  displayBigTextLine(5, "turnRight");
  int r, g, b;
  getColorRGB(c2, r, g, b);
  int color;
  color = white_or_not(r, g, b);

  while(color != 6){
    setMotorSpeed(lm, speed * 7/10);
    setMotorSpeed(rm, -speed * 7/10);
    displayBigTextLine(5, "turnRight 1", color);
    getColorRGB(c2, r, g, b);
    color = white_or_not(r, g, b);
  }
  while(color == 6){
    setMotorSpeed(lm, speed * 7/10);
    setMotorSpeed(rm, -speed * 7/10);
    displayBigTextLine(5, "turnRight 2", color);
    getColorRGB(c2, r, g, b);
    color = white_or_not(r, g, b);
  }
  sleep(150);
  setMotorSpeed(lm, 0);
  setMotorSpeed(rm, 0);
  sleep(100);
}

void completeSearch(){
  while(1){
    go();
    displayBigTextLine(1, "%d %d", row, count);
    displayBigTextLine(10, "completeSearch");

    if (count == 4)
    {
      if (row == 4) return; //finish
      if (row % 2 == 0)
      {
        setMotorSpeed(lm, 25);
        setMotorSpeed(rm, 20);
        sleep(100);
        turnRight();
      }
      else
      {
        setMotorSpeed(lm, 20);
        setMotorSpeed(rm, 25);
        sleep(100);
        turnLeft();
      }
      if (row % 2 == 0){
        while (getColorName(c3) == 6){tracing();}
          setMotorSpeed(lm, 25);
          setMotorSpeed(rm, 20);
          sleep(800);
          turnRight(); // stop. c2 yellow turn
      }
      else{
          while(getColorName(c1) == 6) {tracing();}
          setMotorSpeed(lm,20);
          setMotorSpeed(rm, 25);
          sleep(800);
          turnLeft();
      }
      setMotorSpeed(lm, 0);
      setMotorSpeed(rm, 0);
      sleep(10);
      row++;

      setMotorSpeed(lm, -speed);
      setMotorSpeed(rm, -speed);
      sleep(850);
      count = -1;
    }
  }
}

void print_patch(){
    int j = 0;
    for (int i = 0; i < 5; i++){
      displayBigTextLine(i + j, "%d %d %d %d %d", S[i][0], S[i][1], S[i][2], S[i][3], S[i][4]);
      j += 1;
    }
}

void goup(){
   while (1){
      if (getColorName(c1) == Yellow) {setMotorSpeed(lm, speed); setMotorSpeed(rm, speed); sleep(700); return;}
      else if (getColorName(c3) == Yellow) {setMotorSpeed(lm, speed); setMotorSpeed(rm, speed); sleep(700); return;}
      else tracing();
   }
}

typedef struct Point {
  int r;
  int c;
  float v;
} Point;

Point currentPoint;
Point *p;

void initPoint(Point *point, int ir, int ic, float iv) // initialize Point variable function
{
  (*point).r = ir;
  (*point).c = ic;
  (*point).v = iv;
}

float QMap[5][5];
float finalQMap[5][5];
void oneQmap(Point* p1) {
  for (int i = 0; i < 5; i++)
  { //  initalized to 0 excluding the blue point.
    for (int j = 0; j < 5; j++)
    {
      if (S[i][j] == -1)
        QMap[i][j] = -1;
      else
        QMap[i][j] = 0;
    }
  }

  QMap[p1->r][p1->c] = 1; // input redpoint
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++)
    {
      if (QMap[i][j] == 0)
      {
        if (abs(p1->r - i) + abs(p1->c - j) == 1) {QMap[i][j] = 0.9;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 2) {QMap[i][j] = 0.72;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 3) {QMap[i][j] = 0.5;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 4) {QMap[i][j] = 0.3;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 5) {QMap[i][j] = 0.15;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 6) {QMap[i][j] = 0.06;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 7) {QMap[i][j] = 0.02;}
        else if (abs(p1->r - i) + abs(p1->c - j) == 8) {QMap[i][j] = 0.004;}
      }
    }
  }
}

void sumQmap(Point* redArr)
{
  for (int i = 0; i < redCount; i++)
  { // repeat redPatch length
    oneQmap(&redArr[i]);
    for (int j = 0; j < 5; j++)
    { // add all weights and make finalQmap
      for (int k = 0; k < 5; k++)
      {
        finalQMap[j][k] += QMap[j][k];
      }
    }
  }
}

int directionNext(Point start,Point end){ // It determines the direction to move. It is easier to
  if (start.r - 1 == end.r) return 1; //up
  else if (start.r + 1 == end.r) return 3; //down
  else if (start.c - 1 == end.c) return 4; //left
  else return 2; // right
}

int score = 0;
void gotoBigQWeight() // move and count score
{
  Point next; // store next point
  int direc;
  while (currentPoint.r != 0 || currentPoint.c != 0) {
    Point up, down, left, right;
    Point *p1; Point *p2; Point *p3; Point *p4;
    p1 = &up; p2 = &down; p3 = &left; p4 = &right;

    if (S[currentPoint.r][currentPoint.c] == 1){score++; S[currentPoint.r][currentPoint.c] = 0;} // score ++

    if (currentPoint.r == 4 || currentPoint.c == 4) // (0,4) (1,4) (2, 4) (3, 4) (4,4) // (4,0) (4,1) (4,2)(4,3)(4,4)
    {
        if (currentPoint.r == 4 && currentPoint.c == 4) {
            initPoint(p1, currentPoint.r - 1, currentPoint.c,finalQMap[currentPoint.r - 1][currentPoint.c]);
            initPoint(p3, currentPoint.r, currentPoint.c - 1,finalQMap[currentPoint.r][currentPoint.c - 1]);
            if (up.v > left.v) next = up;
            else next = left;
        }
        else if (currentPoint.r == 4 && currentPoint.c == 0) {
            initPoint(p1, currentPoint.r - 1, currentPoint.c,finalQMap[currentPoint.r - 1][currentPoint.c]);
            initPoint(p4, currentPoint.r, currentPoint.c + 1,finalQMap[currentPoint.r][currentPoint.c + 1]);
            if (up.v > right.v) next = up;
            else next = right;
        }
        else if (currentPoint.r == 0 && currentPoint.c == 4){
            initPoint(p2, currentPoint.r + 1, currentPoint.c,finalQMap[currentPoint.r + 1][currentPoint.c]);
            initPoint(p3, currentPoint.r, currentPoint.c - 1,finalQMap[currentPoint.r][currentPoint.c - 1]);
            if (down.v > left.v) next = down;
            else next = left;
        }
        else if (currentPoint.r == 4){
            initPoint(p1, currentPoint.r - 1, currentPoint.c,finalQMap[currentPoint.r - 1][currentPoint.c]);
            initPoint(p3, currentPoint.r, currentPoint.c - 1,finalQMap[currentPoint.r][currentPoint.c - 1]);
            initPoint(p4, currentPoint.r, currentPoint.c + 1,finalQMap[currentPoint.r][currentPoint.c + 1]);
            if (right.v > up.v){
                if (right.v > left.v) next = right;
                else next = left;
            }
            else {
                if (up.v > left.v) next = up;
                else next = left;
            }
        }
        else{
            initPoint(p1, currentPoint.r - 1, currentPoint.c,finalQMap[currentPoint.r - 1][currentPoint.c]);
            initPoint(p2, currentPoint.r + 1, currentPoint.c,finalQMap[currentPoint.r + 1][currentPoint.c]);
            initPoint(p3, currentPoint.r, currentPoint.c - 1,finalQMap[currentPoint.r][currentPoint.c - 1]);
            if (down.v > up.v){
                if (down.v > left.v) next = down;
                else next = left;
            }
            else {
                if (up.v > left.v) next = up;
                else next = left;
            }
        }
    }
    else if (currentPoint.r == 0 || currentPoint.c == 0)
    { // (0, 1) (0,2) (0,3) // (3,0) (0,2)(0,1)
      if (currentPoint.r == 0)
      {
        initPoint(p2, currentPoint.r + 1, currentPoint.c,finalQMap[currentPoint.r + 1][currentPoint.c]);
        initPoint(p3, currentPoint.r, currentPoint.c - 1,finalQMap[currentPoint.r][currentPoint.c - 1]);
        initPoint(p4, currentPoint.r, currentPoint.c + 1, finalQMap[currentPoint.r][currentPoint.c + 1]);
        if (down.v > left.v) {
          if (down.v > right.v)
            next = down;
          else
            next = right;
        } else {
          if (left.v > right.v)
            next = left;
          else
            next = right;
        }
      }
      else if (currentPoint.c == 0)
      {
        initPoint(p1, currentPoint.r - 1, currentPoint.c,finalQMap[currentPoint.r - 1][currentPoint.c]);
        initPoint(p2, currentPoint.r + 1, currentPoint.c,finalQMap[currentPoint.r + 1][currentPoint.c]);
        initPoint(p4, currentPoint.r, currentPoint.c + 1,finalQMap[currentPoint.r][currentPoint.c + 1]);
        if (up.v > down.v) {
          if (up.v > right.v)
            next = up;
          else
            next = right;
        } else {
          if (down.v > right.v)
            next = down;
          else
            next = right;
        }
      }
    }
    else
    {
        initPoint(p1, currentPoint.r - 1, currentPoint.c,finalQMap[currentPoint.r - 1][currentPoint.c]);
        initPoint(p2, currentPoint.r + 1, currentPoint.c,finalQMap[currentPoint.r + 1][currentPoint.c]);
        initPoint(p3, currentPoint.r, currentPoint.c - 1,finalQMap[currentPoint.r][currentPoint.c - 1]);
        initPoint(p4, currentPoint.r, currentPoint.c + 1,finalQMap[currentPoint.r][currentPoint.c + 1]);
        next = up;
        if (down.v > next.v) next = down;
        if (left.v > next.v) next = left;
        if (right.v >= next.v) next = right;
    }
    direc = directionNext(currentPoint, next);
    finalQMap[currentPoint.r][currentPoint.c] = finalQMap[currentPoint.r][currentPoint.c] - 2;
    currentPoint = next;
    beforeArray[size] = direc;
    size++;
  }
  if (S[currentPoint.r][currentPoint.c] == 1) score++;
}



task main(){
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++){
      S[i][j] = 0;
    }
  }
  completeSearch();
  setMotorSpeed(lm,20);
  setMotorSpeed(rm,20);
  sleep(500);
  turnRight();


  setMotorSpeed(lm, 0);
  setMotorSpeed(rm, 0);
  print_patch();
  sleep(3000);

  int k = 0;
  Point redPatch[5]; // this Point was error.

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (S[i][j] == 1) {
        redPatch[k].r = i;
        redPatch[k].c = j;
        redPatch[k].v = 1;
        k += 1;
      }
    }
  }

  sumQmap(redPatch);
  sleep(1000);

  p = &currentPoint;
  initPoint(p, 4, 4, finalQMap[4][4]);
  displayBigTextLine(1, "init");
  gotoBigQWeight();
  displayBigTextLine(1, "gotoBigQWeight");

  int previous = 4;
  for (int i = 0; i < size; i++){
  int current = beforeArray[i];
  if ((previous - current == 2) || (previous - current == -2))
  {
    turnRight();
    turnRight();
    goup();
  }
  else if (previous != current)
  {
    if ((current - previous == 1) || (current - previous) == -3)
    {
      turnRight();
      goup();
    }
    else
    {
      turnLeft();
      goup();
    }
  }
  else if (previous == current)
  {
    goup();
  }
  previous = current;
  }
}

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
#define INF 1000000
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
int Dt[5][5];


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

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}
int score;
void makeDt()
{
    for(int i=4; i>=0; i--)
    {
        for(int j=4; j>=0; j--)
        {
            if(i == 4 && j == 4) {Dt[i][j] = S[i][j];}
            else if(i == 4 && j != 4) {Dt[i][j] = Dt[i][j+1] + S[i][j] -1;}
            else if(i != 4 && j == 4) {Dt[i][j] = Dt[i+1][j] + S[i][j] -1;}
            else {Dt[i][j] = max(Dt[i+1][j], Dt[i][j+1]) + S[i][j] -1;}
        }
    }
    score = Dt[0][0];

    int i = 0;
    int j = 0;
    while(i < 4 && j < 4)
    {
        if(i == 0 && j == 0) {
          Dt[i][j] = INF;
        }
        if(Dt[i+1][j] > Dt[i][j+1])
        {
            Dt[i+1][j] = INF;
            i++;
        }
        else
        {
            Dt[i][j+1] = INF;
            j++;
        }
    }
    if (i == 4) {
      while (j <= 4) {
        Dt[i][j] = INF;
        j++;
      }
    }
    else if (j == 4) {
      while (i <= 4) {
        Dt[i][j] = INF;
        i++;
      }
    }

}
void initS()
{
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(S[i][j] == 1) {S[i][j] = 5;}
            else if(S[i][j] == -1) {S[i][j]= -3;}
        }
    }
}

int beforeArray[50];
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

    initS();
    makeDt();


    int k = 0;
    int i = 4; int j = 4;
    while (i > 0 || j > 0){
    	if (Dt[i][j-1] == INF) {beforeArray[k] = 4; j -= 1;}
    	else if (Dt[i-1][j] == INF) {beforeArray[k] = 1; i -= 1;}
    	k++;
    }
    int previous = 4;
    for (int t = 0; t < k; t++){
        int current = beforeArray[t];
        if (current != previous)
        {
            if (current - previous == -3)
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
        else
        {
            goup();
        }
    previous = current;
    }
    //if (i == 0){turnLeft(); for (int s = 0; s < j; s++){goup();}}
    //if (j == 0){turnRight(); for (int s = 0; s < i; s++) goup();}


}

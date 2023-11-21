#pragma config(Sensor, S1, csl, sensorEV3_Color)
#pragma config(Sensor, S2, cs,  sensorEV3_Color)
#pragma config(Sensor, S3, csr, sensorEV3_Color)
#pragma config(Motor,  motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rm, tmotorEV3_Large, PIDControl, encoder)

// define color
#define YELLOW_COLOR 0
#define RED_COLOR   1
#define BLUE_COLOR  -1
#define WHITE_COLOR 4

#define W_BOUND 31 // Boundary area white
#define Y_BOUND 21 // Boundary area yellow


int speed = 20;
int x = 0;
int y = 0;
int start_val = 0;
int bound;
int colorMapping[5][5];


void go(int s) {
      setMotorSpeed(lm, s);
      setMotorSpeed(rm, s);
}


void tracing() // Boundary area linetracing
{

      int r,g,b;
      sleep(1); // Sensor synchronization
      getColorRGB(cs,r,g,b);

      if (b > W_BOUND) // When the center sensor leaves the yellow line, turn right
      {
            setMotorSpeed(lm,speed);
            setMotorSpeed(rm,0);
      }
      else if (b < Y_BOUND)// When the center sensor leaves the white line, turn left
      {
            setMotorSpeed(lm,0);
            setMotorSpeed(rm,speed);
      }
      else{ // go foward
            go(speed);
      }


}




void turnRight() { 
      setMotorSpeed(rm, -(speed));
      setMotorSpeed(lm, speed);
      sleep(2000); // sleep값 다시 찾기
}

void turnLeft() { 
      setMotorSpeed(lm, -(speed));
      setMotorSpeed(rm, speed);
      sleep(2000);
}

int getColorFront() { 
      int r,g,b;
      int red = 0, green = 0, blue = 0;

      for (int i = 0 ; i < 20 ; i++) {
            getColorRGB(cs,r,g,b);
            red += r;
            green += g;
            blue += b;
            sleep(15);

      }
      red /= 20;
      blue /= 20;
      green /= 20;

      if (red >= 20) {
            if ((green <= 20)) return 1; // red
            else if (blue <= 30) return 0; // yellow
            else return 4;
      }
      else return -1;
}

int getColorLeft() {
      int r,g,b;
      int red = 0, green = 0, blue = 0;

      for (int i = 0 ; i < 20 ; i++) {
            getColorRGB(csl,r,g,b);
            red += r;
            green += g;
            blue += b;
            sleep(15);

      }
      red /= 20;
      blue /= 20;
      green /= 20;

      if (blue >= 20) return 4;
      else return 0;
}

int getColorRight() {
      int r,g,b;
      int red = 0, green = 0, blue = 0;

      for (int i = 0 ; i < 20 ; i++) {
            getColorRGB(csr,r,g,b);
            red += r;
            green += g;
            blue += b;
            sleep(15);
      }
      red /= 20;
      blue /= 20;
      green /= 20;

      if (blue >= 35) return 4;
      else return 0;
}

void printPatch() { //
      int i, j;
      int line = 1;
      for (i = 0 ; i < 5 ; i++) {
            for(j = 0 ; j < 5 ; j++) {
                  if (colorMapping[i][j] == 2) displayBigTextLine(line, "red(%d, %d)",i,j);
                  else if (colorMapping[i][j] == 3) displayBigTextLine(line, "blue(%d, %d)",i,j);
            }
            line++;
      }
}

// move robot
void moveRobot() {
      while(1) {

            tracing();

            if (y == 4 && x == 4) {
            	go(0);
            	sleep(5000);
            	break;
            }
            if (start_val == 0 && getColorRight() == YELLOW_COLOR) {
                  colorMapping[y][x] = getColorFront(); // 0,0에 색 넣기
                  go(speed); // don't count the cross on start point
                  sleep(500);
                  start_val = 1;
            }

            while (x >= 0 && x <= 4) {
                  tracing();
                  if ((getColorLeft() == YELLOW_COLOR || getColorRight() == YELLOW_COLOR) && y % 2 == 0) { // cross
                        go(0);
                        sleep(500);
                        x++;
                        colorMapping[y][x] = getColorFront();
                        displayBigTextLine(1,"%d, %d",y,x);
                        if (x == 4) break;
                        go(speed); // 재측정 방지로 500ms동안 밀어주기
                        sleep(500);
                  }
                  else if ((getColorLeft() == YELLOW_COLOR || getColorRight() == YELLOW_COLOR) && y % 2 == 1) {
                        x--;
                        colorMapping[y][x] = getColorFront();
                        displayBigTextLine(1,"%d, %d",y,x);
                        if (x == 0) break;
                        go(speed); // 재측정 방지로 500ms동안 밀어주기
                        sleep(500);
                  }

            }
            if (y % 2 == 0 && (x)) { 
                  turnRight();
                  while(getColorRight() == WHITE_COLOR){
                        tracing();
                  }
                  go(0);
                  sleep(200);
                  y++;
                  colorMapping[y][x] = getColorFront();
                  turnRight();
                  go(speed); // 재측정 방지로 500ms동안 밀어주기
                  sleep(500);               

            }
            else if (y % 2 == 1) {
                  turnLeft();
                  while(getColorLeft() == WHITE_COLOR) {
                        tracing();
                  }
                  go(0);
                  sleep(200);
                  y++;
                  colorMapping[y][x] = getColorFront();
                  turnLeft();
                  go(speed); // 재측정 방지로 500ms동안 밀어주기
                  sleep(500);
                  
            }

      }

}



task main() {
	
      moveRobot();
      printPatch();
}
#pragma config(Sensor, S1, csl, sensorEV3_Color)
#pragma config(Sensor, S2, cs,  sensorEV3_Color)
#pragma config(Sensor, S3, csr, sensorEV3_Color)
#pragma config(Motor,  motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rm, tmotorEV3_Large, PIDControl, encoder)


// 한글 설명: 
/* 제 생각이지만, 굳이 go(speed)를 일일이 줄 이유가 없어보입니다. 어차피 tracing 함수 안에는 go(speed)가 포함되어 있기 때문에,
getcolorRGB를 상시로 해주고, 그에 맞게 tracing(r, g, b)를 한다면 트레이싱을 하면서 갈 것으로 생각됩니다. 
시작과 끝 부분의 코드를 제외한 부분에서는 tracing(r, g, b)를 계속 실행시키면 알아서 그에 맞게 갈 것으로 생각됩니다. 
go(speed)는 결국 트레이싱을 이용해서 앞으로 직진하는 것이기 때문에, 저희 코드가 많이 왔다갔다 하더라도 앞으로 갈 것이라 생각됩니다. */
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


void tracing(int r, int g, int b) // Boundary area linetracing
{
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
      setMotorSpeed(rm, -(speed/2));
      setMotorSpeed(lm, speed/2);
      sleep(2000);
}

void turnLeft() {
      setMotorSpeed(lm, -(speed/2));
      setMotorSpeed(rm, speed/2);
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
            int r, g, b;
            sleep(1); // Sensor synchronization
            getcolorRGB(r, g, b);

            
            if (y == 4 && x == 4) {

            	go(0);
            	sleep(5000);
            	break;

            }
            if (start_val == 0 && getColorRight() == YELLOW_COLOR) {
                  colorMapping[y][x] = getColorFront();
                  go(speed); // don't count the cross on start point
                  sleep(500);
                  start_val = 1;
            }
            tracing(r, g, b);
            // this 

            while (x < 4) { // redefine
                  if ((getColorLeft() == YELLOW_COLOR || getColorRight() == YELLOW_COLOR) && y % 2 == 0) { // cross
                        x++;
                        colorMapping[y][x] = getColorFront();
                        sleep(500);
                  }
                  else if ((getColorLeft() == YELLOW_COLOR || getColorRight() == YELLOW_COLOR) && y % 2 == 1) {
                        colorMapping[y][x] = getColorFront();
                        x--;
                        sleep(500);
                  }
                  displayBigTextLine(1,"%d, %d",y,x);

            }
            if (y % 2 == 0) {
                  turnRight();
                  while(getColorRight() == WHITE_COLOR){
                        tracing(r, g, b);

                  }
                  go(0);
                  sleep(200);
                  turnRight();
                  y++;
            }
            else if (y % 2 == 1) {
                  turnLeft();
                  while(getColorLeft() == WHITE_COLOR) {
                        tracing(r, g, b);
                  }
                  go(0);
                  sleep(200);
                  turnLeft();
                  y++;
            }

      }

}



task main() {

      moveRobot();
      printPatch();
}

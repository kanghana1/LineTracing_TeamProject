#pragma config(Sensor, S1, csl, sensorEV3_Color)
#pragma config(Sensor, S2, cs,  sensorEV3_Color)
#pragma config(Sensor, S3, csr, sensorEV3_Color)
#pragma config(Motor,  motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rm, tmotorEV3_Large, PIDControl, encoder)

// define color
#define YELLOW_COLOR 1
#define RED_COLOR   2
#define BLUE_COLOR  3
#define WHITE_COLOR 4

int speed = 15;
int x = 0;
int y = 0;
int start_val = 0;
int bound;
int colorMapping[5][5];




void go(int s) // 앞으로 가기
{
      setMotorSpeed(lm, s);
      setMotorSpeed(rm, s);
}

void turnRight() { // i가 짝수일 때 오른쪽으로 턴 (i = 0, 2, 4)
      setMotorSpeed(rm, -(speed/2));
      setMotorSpeed(lm, speed/2);
      sleep(2000);
}

void turnLeft() { // i가 홀수일 때 왼쪽으로 턴 (i = 1, 3)
      setMotorSpeed(lm, -(speed/2));
      setMotorSpeed(rm, speed/2);
      sleep(2000);
}

int getColorFront() { // 가운데 센서 색 따기
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
            if ((green <= 20)) return 2; // red
            else if (blue <= 25) return 1; // yellow
            else return 4;
      }
      else return 3;
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
      else return 1;
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
      else return 1;
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

            if (y == 4 && x == 4) break; // (4,4) 일 때 종료
            if (start_val == 0 && getColorRight() == 1) {
                  colorMapping[y][x] = getColorFront(); // 0,0에 색 넣기
                  go(speed); // don't count the cross on start point
                  sleep(100);
                  start_val = 1;
            }

            while (getColorFront() != 4) { // 앞에 길이 있을 때
                  go(speed);
                  if ((getColorLeft() == 1 || getColorRight() == 1) && y % 2 == 0) { // cross
                        x++;
                        colorMapping[y][x] = getColorFront();
                        go(speed);
                        sleep(100);
                  }
                  else if ((getColorLeft() == 1 || getColorRight() == 1) && y % 2 == 1) {
                        colorMapping[y][x] = getColorFront();
                        x--;
                        go(speed);
                        sleep(100);

                  }
            }
            if (y % 2 == 0 && getColorRight() == 1) { // (y가 0임과 동시에 오른쪽길이 노랑색)
                  turnRight();
                  while(getColorRight() == 4){
                        go(speed);

                  }
                  go(0);
                  sleep(200);
                  turnRight();
                  y++;
            }
            else if (y % 2 == 1 && getColorLeft() == 1) {
                  turnLeft();
                  while(getColorLeft() == 4) {
                        go(speed);
                  }
                  go(0);
                  sleep(200);
                  turnLeft();
                  y++;
            }


      }

}



int calcBound(){ // boundary value
      int bound;
      int yellow = 0;
      int white = 0;
      int r,g,b;

      for(int i = 0 ; i < 20 ; i++) {
            getColorRGB(cs,r,g,b);
   		yellow += b; // yellow and white have the big gap between value b
            sleep(10);
	}
      setMotorSpeed(lm,0);
      setMotorSpeed(rm,40);
      sleep(300);
      setMotorSpeed(lm,0);
      setMotorSpeed(rm,0);

      for(int i =0;i<20;i++){
            getColorRGB(cs,r,g,b);
   		white += b ;   // yellow and white have the big gap between value b
            sleep(10);
	}

	bound = (white / 20 + yellow / 20) / 2;
	return bound;
}

/*
이거 위 calcBound에서 구한 bound값을 이용해 트레이싱 하는 알고리즘으로 바꾼 후,
moveRobot 함수 안에 넣어야 하지 않을까요??

void cross(){

		while(1) {
		      int left = getColorLeft();
		      int right = getColorRight();
		      int cnt_blue = 0;
		      int cnt_red = 0;
		      int cnt_none = 0;
		      int front = getColorFront();

   			if ((left == 1 && right ==4)||(left == 4 && right ==1)){
      		      go(10);
      		      sleep(500);
      		      if (front == 2){
        			      cnt_red++;
     			      }
     			      else if (front == 3){
        			      cnt_blue++;
     			      }
      		      else {
        			      cnt_none++;
     			      }
     			      go(10);
     			      sleep(500);
   		}
	}
} */



task main() {
      moveRobot();
      printPatch();
}


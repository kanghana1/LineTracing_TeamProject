#pragma config(Sensor, S1, c1, sensorEV3_Color) // left color
#pragma config(Sensor, S2, c2,  sensorEV3_Color) // middle color
#pragma config(Sensor, S3, c3, sensorEV3_Color) // right color
#pragma config(Motor,  motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rm, tmotorEV3_Large, PIDControl, encoder)

// define color
#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7
// these colors are not used yet.
// If tracing works, then I will use getColorRGB.

#define W_BOUND 31 // Boundary area white
#define Y_BOUND 21 // Boundary area yellow

// This code reter to lecture paper.
int speed = 20;
int r, g, b;
int row = 0;
int col = 0;

// These varibles will be a control point.
int count = -1; // count = 0,0 start, because first point has a cross line. 
int val; // for control speed. 

int S[5][5]; // change the name, it was "colorMapping" before

// it works well, but we add getColorName for accuracy later. 
int getColorFront(int red, int green, int blue){
	displayBigTextLine(10, "%d %d %d", red, green, blue);
	 if (red >= 10) {
	    //red yello green value
	 	// yellow white blue value
        if ((blue >= 30)) return White; // red
        else if (green >= 20) return Yellow; // yellow
        else return Red;
     }
     else return Green;
}

void tracing() // Boundary area linetracing
{
	int sum_r = 0; int sum_g = 0; int sum_b = 0;
	int max_r = 0; int max_g = 0; int max_b = 0;
	int min_r = 200; int min_g = 200; int min_b = 200;
	for (int i = 0; i < 9; i++){
		getColorRGB(c2, r, g, b);
		sum_r += r;
		sum_g += g;
		sum_b += b;
		if (max_r < r) max_r = r;
		if (max_g < g) max_g = g;
		if (max_b < b) max_b = b;

		if (min_r > r) min_r = r;
		if (min_g > g) min_g = g;
		if (min_b > b) min_b = b;
		sleep(10);
	}
	sum_r -= max_r;
	sum_r -= min_r;

	sum_g -= max_g;
	sum_g -= min_g;

	sum_b -= max_b;
	sum_b -= min_b;

	sum_r /= 8;
    sum_g /= 8;
	sum_b /= 8;
	int color;
	color = getColorFront(sum_r, sum_g, sum_b);


	displayBigTextLine(5, "tracing %d", color);
    val = 3;

    if (color == Yellow || getColorName(c2) == 4) // 4: yellow
    {
       setMotorSpeed(lm, speed - val + 1);
       setMotorSpeed(rm, speed);
    }
    else {
        setMotorSpeed(lm, speed + val);
        setMotorSpeed(rm, speed - val);
    }
}

void go(){ // go straight following points. if meet crossline -> stop. -> color censor -> store -> go
	int sum_r = 0; int sum_g = 0; int sum_b = 0;
	int max_r = 0; int max_g = 0; int max_b = 0;
	int min_r = 200; int min_g = 200; int min_b = 200;
	for (int i = 0; i < 9; i++){
		getColorRGB(c2, r, g, b);
		sum_r += r;
		sum_g += g;
		sum_b += b;
		if (max_r < r) max_r = r;
		if (max_g < g) max_g = g;
		if (max_b < b) max_b = b;
		if (min_r > r) min_r = r;
		if (min_g > g) min_g = g;
		if (min_b > b) min_b = b;
		sleep(10);
	}
    sum_r -= max_r;
	sum_r -= min_r;
	sum_g -= max_g;
	sum_g -= min_g;
	sum_b -= max_b;
	sum_b -= min_b;
	sum_r /= 8;
	sum_g /= 8;
	sum_b /= 8;
	int color;
	color = getColorFront(sum_r, sum_g, sum_b);

	displayBigTextLine(5, "go %d", color);
    val = 3;
    if (color == Yellow || getColorName(c2) == Yellow) // 4: yellow
    {
      setMotorSpeed(lm, speed - val + 1);
      setMotorSpeed(rm, speed);
    }
    else 
    {
        setMotorSpeed(lm, speed + val);
        setMotorSpeed(rm, speed - val);
    }
    if (getColorName(c1) == 4 || getColorName(c3) == 4) 
    { // if cross line, stop, color censor operate. 
    	setMotorSpeed(lm, 0);
    	setMotorSpeed(rm, 0);
    	count++;
    	sleep(100);
    		
    	if (color == Red || getColorName(c2) == Red) S[row][count] = 1; // for accuracy 
    	else if (color == Green || getColorName(c2) == Green) S[row][count] = -1; // for accuracy 
    	setMotorSpeed(lm, 20); // delay
    	setMotorSpeed(rm, 20);
    	sleep(500);
	}
}

void turnLeft(){
	displayBigTextLine(5, "turnLeft");
    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, 25);
    sleep(300);
    while (getColorName(c1) > 4){
        setMotorSpeed(lm, -speed * 6/10);
        setMotorSpeed(rm, speed * 6/10);
        sleep(10);
    }

    while (getColorName(c2) > 4){
        setMotorSpeed(lm, -speed * 6/10);
        setMotorSpeed(rm, speed * 6/10);
        sleep(5);
    }
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(100);
}

void turnRight(){
	displayBigTextLine(5, "turnRight");
    setMotorSpeed(lm, 25);
    setMotorSpeed(rm, 20);
    sleep(300);
    while (getColorName(c3) > 4){
        setMotorSpeed(lm, speed * 6/10);
        setMotorSpeed(rm, -speed * 6/10);
        sleep(10);
    }
    /*while (getColorName(c3) == 4 && getColorName(c1) >= 4){
    	setMotorSpeed(lm, speed * 6/10);
    	setMotorSpeed(rm, -speed * 6/10);
    	sleep(50);
    	}*/
    while (getColorName(c2) > 4){
        setMotorSpeed(lm, speed * 6/10);
        setMotorSpeed(rm, -speed * 6/10);
        sleep(5);
    }
    sleep(100);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(100);
}

void stopMotor(){
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
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
            for (int i = 0; i < 4; i++)
            { 
        	    if (getColorName(c2) == 5)
            	{ // red
          	        if (row % 2 == 0) S[row][count] = 1;
                    else S[row][4-count] = 1;
                    playTone(440, 20);
                    sleep(30);
                }
                else if (getColorName(c2) == 2 || getColorName(c2) == 3)
                { // blue or green
          	        if (row % 2 == 0) S[row][count] = -1;
                    else S[row][4-count] = -1;
                    playTone(400, 20);
                    sleep(30);
                }
                else sleep(30);
            }
            turnRight();
        }
        else
        {
            setMotorSpeed(lm, 20);
            setMotorSpeed(rm, 25);
            for(int i = 0; i < 3; i++){ // before 3. after 9
                if (getColorName(c2) == 5)
                {
                    if (row % 2 == 0) S[row][count] = 1;
                    else S[row][4-count] = 1;
                    playTone(440, 20);
                    sleep(30);
                }
                else if (getColorName(c2) == 3)
                {
                    if (row % 2 == 0) S[row][count] = -1;
                    else S[row][4-count] = -1;
                    playTone(400, 20);
                    sleep(30);
                }
                else sleep(30);
            }
            turnLeft();
        }

        if (row % 2 == 0){
        	while (getColorName(c3) == 6){tracing();}
            setMotorSpeed(lm, speed + 10);
			setMotorSpeed(rm, speed);
			sleep(450);
        	turnRight(); // stop. c2 yellow turn
        }
        else{
            while(getColorName(c1) == 6) {tracing();}
            setMotorSpeed(lm, speed);
            setMotorSpeed(rm, speed + 10);
            sleep(450);
            turnLeft();
        }
        row++;
        count = -1;

        setMotorSpeed(lm, -30);
        setMotorSpeed(rm, -30);
        sleep(800);
        }
    }
}


void print_patch(){
    int j = 0;
    for (int i = 0; i < 5; i++){

        displayBigTextLine(i + j, "%d %d %d %d %d", S[i][0], S[i][1], S[i][2], S[i][3], S[i][4]);
        j += 2;
    }
}
task main(){
    completeSearch();
    setMotorSpeed(lm,20);
    setMotorSpeed(rm,20);
    sleep(1000);
    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, -20);
    sleep(1650);

    count = row = 0;
}








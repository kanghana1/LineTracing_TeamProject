#pragma config(Sensor, S1, c1, sensorEV3_Color) // left color
#pragma config(Sensor, S2, c2,  sensorEV3_Color) // middle color 
#pragma config(Sensor, S3, c3, sensorEV3_Color) // right color 
#pragma config(Motor,  motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rm, tmotorEV3_Large, PIDControl, encoder)

// define color
#define YELLOW 0
#define RED 1
#define BLUE -1
#define WHITE 4
// these colors are not used yet. 
// If tracing works, then I will use getColorRGB. 

#define W_BOUND 31 // Boundary area white
#define Y_BOUND 21 // Boundary area yellow


// This code reter to lecture paper. 

int speed = 35;
int r = 0;
int c = 0;

int row = 0;
int col = 0;

// These varibles will be a control point. 
int vertex = 0;
int count = 0;

int start_val = 0;
int val;

int S[5][5]; // change the name, it was "colorMapping" before. 


void go(){ // go straight following points. 
    val = 7;

    if (getColorName(c2) == 5) // 5 : red // if middle color censor meets red. 
    {
        if (row % 2 == 0) S[row][count] = 1; 
        else S[row][4-count] = 1; // because of reversing. 
        playTone(440, 20); sleep(100);
    }

    if (getColorName(c2) == 3 || getColorName(c2) == 2) // green or blue, because those have similiar r,g,b values. 
    {
        if (row % 2 == 0) S[row][count] = -1;
        else S[row][4-count] = -1;
        playTone(440, 20); sleep(100);
    }

    if (getColorName(c2) == 4) // 4: yellow
    {
        setMotorSpeed(lm, speed - val);
        setMotorSpeed(rm, speed + val);
    }
    else {
        setMotorSpeed(lm, speed + val);
        setMotorSpeed(rm, speed - val);
    }

    if (getColorName(c1) == 4 || getColorName(c3) == 4) vertex++; // cross point
    else vertex = 0;

   if (vertex == 1) count++;
}

void turnLeft(){
    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, 35);
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
    setMotorSpeed(lm, 30);
    setMotorSpeed(rm, 30);
    sleep(100);
    while (getColorName(c3) > 4){
        setMotorSpeed(lm, speed * 6/10);
        setMotorSpeed(rm, -speed * 6/10);
        sleep(10);
    }
    while (getColorName(c2) > 4){
        setMotorSpeed(lm, speed * 6/10);
        setMotorSpeed(rm, -speed * 6/10);
        sleep(5);
    }
    sleep(200);
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
        if (count == 4){
            if (row == 4) return; //finish
            if (row % 2 == 0){
                setMotorSpeed(lm, 40);
                setMotorSpeed(rm, 35);
                for (int i = 0; i < 4; i++){
                    if (getColorName(c2) == 5){ // red 
                        if (row % 2 == 0) S[row][count] = 1;
                        else S[row][4-count] = 1;
                        playTone(440, 20);
                        sleep(80);
                    }
                    else if (getColorName(c2) == 2 || getColorName(c3) == 3){ // blue or green 
                        if (row % 2 == 0) S[row][count] = -1;
                        else S[row][4-count] = -1;
                        playTone(400, 20);
                        sleep(80);
                    }
                    else sleep(90);
                }
                turnRight();
            }
            else {
                for(int i = 0; i < 3; i++){
                    if (getColorName(c2) == 5){
                        if (row % 2 == 0) S[row][count] = 1;
                        else S[row][4-count] = 1;
                        playTone(440, 20);
                        sleep(80);
                    }
                    else if (getColorName(c2) == 2){
                        if (row % 2 == 0) S[row][count] = -1;
                        else S[row][4-count] = -1;
                        playTone(400, 20);
                        sleep(80);
                    }
                    else sleep(90);
                }
                turnLeft();
            }
            
            if (row % 2 == 0){
                while(getColorName(c3) == 6) go(); // white.
                setMotorSpeed(lm, 35);
                setMotorSpeed(rm, 30);
                sleep(400);
                turnRight();
            }
            else{
                while(getColorName(c1) == 6) go();
                setMotorSpeed(lm, 30);
                setMotorSpeed(rm, 35);
                sleep(400);
                turnLeft();
            }
            row++;
            count = 0;
            setMotorSpeed(lm, -30);
            setMotorSpeed(rm, -30);
            sleep(410);
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
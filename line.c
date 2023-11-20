#pragma config(StandardModel, "EV3_REMBOT")
#pragma config(Sensor, S1, c1, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl , encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl , encoder)

int color_1, color_2, color_3, r, g, b, bound, countred, countblue;
int yellow_bound = 0;
int white_bound = 0;
short white, yellow, green, red;
int vertex = 0, count = 0, row = 0;

// 센서 (1), (3) 을 getColorReflected로 따고, 센서 (2) getColorRGB로 따는 방식으로 해봤습니다
// 색깔 따고 1번 항목 하는 중입니다.

int bound_yellow() // 시작하기 전 yellow 평균값 구하기
{
	for (int i = 0; i < 5; i++)
	{
		yellow_bound += getColorReflected(c1);
		yellow_bound += getColorReflected(c3);
		sleep(10);
	}
	return yellow_bound;
}

int bound_white() // 시작하기 전 white 평균값 구하기
{
	for (int i = 0; i< 5; i++)
	{
		white_bound += getColorReflected(c1);
		white_bound += getColorReflected(c3);
		sleep(10);
	}
	return white_bound;
}

int calcBound2() // 평균값 구하기
{
	bound = (yellow_bound/10 + white_bound/10) / 2;
	return bound;
}

/* task leftWheel() // void align 작동 안할 때 임시 방편 
{
	while(1)
	{
		if(getColorReflected(c1) >= bound)
			setMotorSpeed(lm, 5);
		else
			setMotorSpeed(lm, 0);
		sleep(10);
	}
}

task rightWheel() 
{
	while(1)
	{
		if(getColorReflected(c3) >= bound)
			setMotorSpeed(rm, 5);
		else
			setMotorSpeed(rm, 0);
		sleep(10);
	}
} */

/* void move2Cross(int gray) 
{
	while(1)
	{
		int left = getColorReflected(c1);
		int right = getColorReflected(c3);

		if(left>=bound && right>=bound)
		{
			setMotorSpeed(lm, 5);
			setMotorSpeed(rm, 5);
		}
		else if(left>=bound && right<bound)
		{
			setMotorSpeed(lm, 5);
			setMotorSpeed(rm, -5);
		}
		else if(left<bound && right>=bound)
		{
			setMotorSpeed(lm, -5);
			setMotorSpeed(rm, 5);
		}
		else
		{
			setMotorSpeed(lm, 0);
			setMotorSpeed(rm, 0);
			break;
		}
	}
} */

void go() // 평상시 이동
{
    setMotorSpeed(lm, 5);
    setMotorSpeed(rm, 5);
}

void align(int bound)  //왼쪽 센서가 bound 넘어갔을 때, 살짝 오른쪽으로 조정 및 오른쪽 센서가 bound 넘어갔을 때, 살짝 왼쪽으로 조정
{
	int left = getColorReflected(c1);
	int right = getColorReflected(c3);

	while(left<bound && right<bound)
	{
		setMotorSpeed(lm, 5);
		setMotorSpeed(rm, 5);
		left = getColorReflected(c1);
		right = getColorReflected(c3);
	}

	while(left<=bound || right<=bound)
	{
		if(left <= bound)
		{
			setMotorSpeed(lm, 3);
			setMotorSpeed(rm, 0);
		}
		else
			{
			setMotorSpeed(lm, 0);
			setMotorSpeed(rm, 3);
		}
		left = getColorReflected(c1);
		right = getColorReflected(c3);
	}
}

void countRed() // 빨간점 개수 
{
    getColorRGB(c2)
    if (color_2 == red)
    {
        countred += 1
    }
}

void countBlue() // 파란점 개수
{
    getColorRGB(c2)
    if (color_2 == green)
    {
        countgreen += 1
    }
} 

void turnLeft() // 앞에 더 이상 선이 없으면 맨끝이므로 좌회전
{
    getColorRGB(c2)
    if(color2 != yellow)
    {
	setMotorSpeed(lm, -5);
	setMotorSpeed(rm, 5);
	sleep(100);
}
}

void turnRight() // 앞에 더 이상 선이 없으면 맨끝이므로 우회전
{
    getColorRGB(c2)
    if(color2 != yellow)
    {
	setMotorSpeed(lm, 5);
	setMotorSpeed(rm, -5);
	sleep(100);
    }
}


// 색깔
  if((20<=r && r<=42) && (28<=g && g<=53) && (32<=b && b<=48))
  {
  	color_1 = white;
  }
	if((25<=r && r<=40) && (25<=g && g<=43) && (2<=b && b<=12))
  {
  	color_1 = yellow;
  }
	if((33<=r && r<=45) && (58<=g && g<=73) && (45<=b && b<=55))
  {
  	color_2 = white;
 	}
  if((35<=r && r<=45) && (45<=g && g<=60) && (5<=b && b<=18))
  {
  	color_2 = yellow;
  }
  if((26<=r && r<=35) && (3<=g && g<=11) && (3<=b && b<=11))
  {
  	color_2 = red;
 	}
  if((3<=r && r<=8) && (21<=g && g<=29) && (7<=b && b<=14))
  {
  	color_2 = green;
  }
  if((40<=r && r<=55) && (58<=g && g<=72) && (56<=b && b<=75))
  {
  	color_3 = white;
 	}
  if((42<=r && r<=52) && (48<=g && g<=60) && (8<=b && b<=25))
  {
  	color_3 = yellow;
  }

#pragma config(Sensor, S3,     vpered,         sensorEV3_IRSensor)
#pragma config(Sensor, S4,     vbok,           sensorEV3_IRSensor)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int leftMotor = 0;
int rightMotor = 0;
#define wall 15

int g_ahead = 0;
int g_right = 0;

int getAheadSensorValue()
{
	int newDistance = getIRDistance(vpered);
	g_ahead = g_ahead + newDistance;
	g_ahead = g_ahead / 2;
	return g_ahead;
}

int getRightSensorValue()
{
	int newDistance = getIRDistance(vbok);
	g_right = g_right + newDistance;
	g_right = g_right / 2;
	return g_right;
}

void stable()
{
		int distanceRight = getRightSensorValue();
		int delta = 0;

		//a - left motor
		//distanceRight = SensorValue[vbok];
		//distanceAhead = SensorValue[vpered];

		//distanceRight = getUSDistance(vbok);
		//distanceAhead = getUSDistance(vpered);

		delta = wall - distanceRight;

		leftMotor = 100 - (delta * 1.5);
		rightMotor = 100 + (delta * 1.5);

		//displayTextLine(1, "ahead = %d", distanceAhead);
		displayTextLine(2, "rightIR = %d --> delta = %d", distanceRight, delta);
}

void turns()
{
		int distanceAhead = getAheadSensorValue();

		if(distanceAhead < (wall * 2))
		{
			leftMotor = 20;
			rightMotor = 20;
		}

		if(distanceAhead < wall)
		{
			leftMotor = 0;
			rightMotor = 0;
		}

		displayTextLine(3, "headIR = %d <--", distanceAhead);
}

task main()
{
	while(true)
	{
		stable();
		turns();


		displayTextLine(6, "left engine = %d", leftMotor);
		displayTextLine(7, "right engine = %d", rightMotor);

		motor[motorA] = leftMotor;
		motor[motorB] = rightMotor;
		wait1Msec(50);
	}
}
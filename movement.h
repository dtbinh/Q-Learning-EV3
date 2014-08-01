/* This collection of functions allows basic movement capabilities in the least efficient manner possible.  */
/* If something goes wrong while calling one of these functions, be sure to read the comments above each		*/
/* individual function as well as which variables it peruses.																								*/
/* ---------------------------------------------------------------------------------------------------------*/

//startMotor function starts the motor. It takes a motor and integer speed as parameters, and speed is limited to 100.

void startMotor(tMotor target, int speed)
{
	if(speed > 100)
	{
		speed = 100;
	}
	if(speed < -100)
	{
		speed = -100;
	}
	motor[target] = speed;
}

//turnDegrees takes a direction, degree value, and two integer values for slower and faster motors.
//*****FUNCTION REQUIRES THAT THERE BE MOTORS CALLED LEFTMOTOR AND RIGHTMOTOR, A GYRO CALLED GYRO, AND RIGHT = 1 and LEFT = 0

void turnDegrees(int direction, int degrees, int fasterMotor, int slowerMotor, tMotor rightMotor, tMotor leftMotor, tSensors gyro) //Turns the robot to a certain angle with whatever
{
	int RIGHT = 1;
	int LEFT = 0;																//motor speeds you would like.
	int initial = SensorValue[gyro];	//Take an initial gyro value so that degrees of change can be calculated.

	if(direction == RIGHT)				//Set the motor speeds based on which direction you are turning using the given speeds.
	{
		motor[leftMotor] = fasterMotor;
		motor[rightMotor] = slowerMotor;
	}
	else if (direction == LEFT)
	{
		motor[leftMotor] = slowerMotor;
		motor[rightMotor] = fasterMotor;
	}

	while(abs(initial - SensorValue[gyro]) < degrees)	//Wait until the absolute distance between the initial value and the
	{																									//current gyro value becomes greater than the requested degrees.

	}

	motor[leftMotor] = motor[rightMotor] = 0;					//Stop the robot.

}

//turnTime is similar to turnDegrees, but it turns for a certain duration in milliseconds.
//********************************** NOTE THAT THIS FUNCTION WILL USE AND RESET TIMER 4 **************************************
//*****FUNCTION REQUIRES THAT THERE BE MOTORS CALLED LEFTMOTOR AND RIGHTMOTOR, RIGHT = 1, LEFT = 0


void turnTime(int direction, int timeMilliseconds, int fasterMotor, int slowerMotor, tMotor rightMotor, tMotor leftMotor) //Turns the robot for a certain duration with whatever
{
	int RIGHT = 1;
	int LEFT = 0;													//motor speeds you would like.
	clearTimer(T4);	//Take an initial timer value so that time change can be calculated.

	if(direction == RIGHT)				//Set the motor speeds based on which direction you are turning using the given speeds.
	{
		motor[leftMotor] = fasterMotor;
		motor[rightMotor] = slowerMotor;
	}
	else if (direction == LEFT)
	{
		motor[leftMotor] = slowerMotor;
		motor[rightMotor] = fasterMotor;
	}

	while(time1[T4]< timeMilliseconds)	//Wait until the timer's time is up.
	{

	}
}

//moveWithEncoders allows you to move precisely with motor encoders. It can (hopefully) move much more accurately than with time.

void moveWithEncoders(int millimeters, int speed, tMotor rightMotor, tMotor leftMotor)
{
	nMotorEncoder[leftMotor] = 0;
	int reqEncoderVal = millimeters / (56 * PI) * 360;
	motor[leftMotor] = motor[rightMotor] = speed;

	while(abs(nMotorEncoder[leftMotor]) < reqEncoderVal)
	{
		if(nMotorEncoder[leftMotor] < -32700 || nMotorEncoder[leftMotor] >= 32700)
 		{
			reqEncoderVal -= abs(nMotorEncoder[leftMotor]);
			nMotorEncoder[leftMotor] = 0;
 		}
 	}

	motor[leftMotor] = motor[rightMotor] = 0;

}

//moveWithTime allows you to move somewhat inconsistently but is nice when you just want the robot to move in an approximate
//direction for an approximate distance.

void moveWithTime(int timeMSec, int speed, tMotor rightMotor, tMotor leftMotor)
{
	motor[rightMotor] = motor[leftMotor] = speed;
	wait1Msec(timeMSec);
	motor[leftMotor] = motor[rightMotor] = 0;

}

int joyPin1 = 0;
int joyPin2 = 1;
int motorForwardPin1 = 0;
int motorReversePin1 = 0;
int motorForwardPin2 = 0;
int motorReversePin2 = 0;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	driveMotor(
		getXAxial(joyPin1),
		getYAxial(joyPin2),
		getSlidePotentiometerValue(),
		motorForwardPin1,
		motorReversePin1,
		motorForwardPin2,
		motorReversePin2
	);
}

// Motor Logic

void driveMotor(int xAxial, int yAxial, int maxSpeed, int forwardPin1, int reversePin1, int forwardPin2, int reversePin2)
{
	bool isReverse = false;

	if(yAxial < 0)
	{
		isReverse = true;
		yAxial = -yAxial;
	}

	int speed = maxSpeed * (yAxial / 100);

	if(xAxial == 0)
	{
		if(!isReverse)
		{
			analogWrite(forwardPin1, speed);
			analogWrite(reversePin1, 0);

			analogWrite(forwardPin2, speed);
			analogWrite(reversePin2, 0);
		}
		else
		{
			analogWrite(forwardPin1, 0);
			analogWrite(reversePin1, speed);

			analogWrite(forwardPin2, 0);
			analogWrite(reversePin2, speed);
		}
	}
	else if (xAxial > 0)
	{
		if(!isReverse)
		{
			analogWrite(forwardPin1, getSpeedFromRawData(speed, xAxial));
			analogWrite(reversePin1, 0);

			analogWrite(forwardPin2, speed);
			analogWrite(reversePin2, 0);
		}
		else
		{
			analogWrite(forwardPin1, 0);
			analogWrite(reversePin1, getSpeedFromRawData(speed, xAxial));

			analogWrite(forwardPin2, 0);
			analogWrite(reversePin2, speed);
		}
	}
	else if (xAxial < 0)
	{
		if(!isReverse)
		{
			analogWrite(forwardPin1, speed);
			analogWrite(reversePin1, 0);

			analogWrite(forwardPin2, getSpeedFromRawData(speed, xAxial));
			analogWrite(reversePin2, 0);
		}
		else
		{
			analogWrite(forwardPin1, 0);
			analogWrite(reversePin1, speed);

			analogWrite(forwardPin2, 0);
			analogWrite(reversePin2, getSpeedFromRawData(speed, xAxial));
		}
	}
}

int getSpeedFromRawData(int maxSpeed, int xAxial)
{
	return maxSpeed * ((100 - xAxial) / 100);
}

// Joystick Logic

int maxJSValue = 1023;
int middleYJSValue = 508;
int middleXJSValue = 515;

// Get X-Axis Value
int getXAxial(int pin)
{
	return getPercentageFromRawData(maxJSValue, middleXJSValue, analogRead(pin));
}

// Get Y-Axis Value
int getYAxial(int pin)
{
	return getPercentageFromRawData(maxJSValue, middleYJSValue, analogRead(pin));
}

// Format values from joystick
int getJSPercentageFromRawData(int maxValue, int middleValue, int currentValue)
{
	bool isNegative = true;

	if(currentValue > middleValue)
	{
		isNegative = false;
		currentValue = currentValue - middleValue;
		middleValue = maxValue - middleValue;
	}

	int diff = middleValue - currentValue;
	int result = ceil(((diff / middleValue) * 100));

	if(isNegative)
	{
	    result = -result;
	}

	return result;
}

// Get slide potentiometer value
int getSlidePotentiometerValue()
{
	return 255;
}
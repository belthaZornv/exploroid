// Documentation
/// Available Methods
///--- getDistance(String units, bool showUnits)
///--- getTemperature()
///--- getHumidity()
///--- getCompassDegrees()
///--- getCompassDirection()
///--- getPressure()
///--- getAltitude()
///--- getPitch()
///--- getRoll()
///--- driveMotor(int forwardPin, int reversePin, String toDirection, int motorSpeed)


// Including Libraries
#include <DHT.h>
#include <NewPing.h>
#include <ADXL345.h>
#include <HMC5883L.h>
#include <Adafruit_BMP085.h>


// Pinouts
/// Digital
#define FORWARD_BUTTON 22
#define REVERSE_BUTTON 23
#define LEFT_BUTTON 24
#define RIGHT_BUTTON 25
#define TEMP_BUTTON 26
#define DIRECTION_BUTTON 27
#define PRESSURE_BUTTON 28
#define HUMIDITY_BUTTON 29
/// PWM
#define MOTOR1_FORWARD_PIN 2
#define MOTOR1_REVERSE_PIN 3
#define MOTOR2_FORWARD_PIN 4
#define MOTOR2_REVERSE_PIN 5
#define DHT11_DHTPIN 6
#define HCSR04_ECHO_PIN 7
#define HCSR04_TRIGGER_PIN 8

// Constants
#define HCSR04_MAX_DISTANCE 400
#define DHT11_DHTTYPE DHT11
const float alpha = 0.5;

// HC-SR04 Setup
NewPing sonar(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN, HCSR04_MAX_DISTANCE);

// DHT-11 Setup
DHT dht(DHT11_DHTPIN, DHT11_DHTTYPE);

// ADXL345 Setup
ADXL345 acc;

// HMC5883L Setup
HMC5883L compass;

// BMP085 Setup
Adafruit_BMP085 bmp;



void setup()
{
	Serial.begin(115200);

	// Magnetometer Setup
	compass.setRange(HMC5883L_RANGE_1_3GA);
	compass.setMeasurementMode(HMC5883L_CONTINOUS);
	compass.setDataRate(HMC5883L_DATARATE_30HZ);
	compass.setSamples(HMC5883L_SAMPLES_8);
	compass.setOffset(0, 0);

	// Accelerator Setup
	acc.begin();

	// Initialize Pin Modes
	pinMode(FORWARD_BUTTON, INPUT);
	pinMode(REVERSE_BUTTON, INPUT);
	pinMode(LEFT_BUTTON, INPUT);
	pinMode(RIGHT_BUTTON, INPUT);
	pinMode(TEMP_BUTTON, INPUT);
	pinMode(DIRECTION_BUTTON, INPUT);
	pinMode(PRESSURE_BUTTON, INPUT);
	pinMode(HUMIDITY_BUTTON, INPUT);
}

void loop()
{
	if(digitalRead(FORWARD_BUTTON) == HIGH)
	{
		driveMotor(MOTOR1_FORWARD_PIN, MOTOR1_REVERSE_PIN, "Forward", 255);
		driveMotor(MOTOR2_FORWARD_PIN, MOTOR2_REVERSE_PIN, "Forward", 255);
		Serial.println("Forward");
	}
	else if(digitalRead(REVERSE_BUTTON) == HIGH)
	{
		driveMotor(MOTOR1_FORWARD_PIN, MOTOR1_REVERSE_PIN, "Reverse", 255);
		driveMotor(MOTOR2_FORWARD_PIN, MOTOR2_REVERSE_PIN, "Reverse", 255);
		Serial.println("Reverse");
	}
	else if(digitalRead(LEFT_BUTTON) == HIGH)
	{
		driveMotor(MOTOR1_FORWARD_PIN, MOTOR1_REVERSE_PIN, "Reverse", 255);
		driveMotor(MOTOR2_FORWARD_PIN, MOTOR2_REVERSE_PIN, "Forward", 255);
		Serial.println("Left");
	}
	else if(digitalRead(RIGHT_BUTTON) == HIGH)
	{
		driveMotor(MOTOR1_FORWARD_PIN, MOTOR1_REVERSE_PIN, "Forward", 255);
		driveMotor(MOTOR2_FORWARD_PIN, MOTOR2_REVERSE_PIN, "Reverse", 255);
		Serial.println("Left");
	}
	else if(digitalRead(TEMP_BUTTON) == HIGH)
	{
		Serial.println(getTemperature());
	}
	else if(digitalRead(DIRECTION_BUTTON) == HIGH)
	{
		Serial.println(getCompassDirection());
	}
	else if(digitalRead(PRESSURE_BUTTON) == HIGH)
	{
		Serial.println(getPressure());
	}
	else if(digitalRead(HUMIDITY_BUTTON) == HIGH)
	{
		Serial.println(getHumidity());
	}
	else
	{
		driveMotor(MOTOR1_FORWARD_PIN, MOTOR1_REVERSE_PIN, "Stop", 0);
		driveMotor(MOTOR2_FORWARD_PIN, MOTOR2_REVERSE_PIN, "Stop", 0);
	}
}



// Distance Sensor Functionality (HC-SR04)
/// Example: getDistance("cm", false)
String getDistance(String units, bool showUnits)
{
	float distance = sonar.ping_cm();

	if(units == "mm")
	{
		if(showUnits)
		{
			return String(distance * 10, 2) + "mm";
		}
		else
		{
			return String(distance * 10, 2);
		}
	}
	else if(units == "cm")
	{
		if(showUnits)
		{
			return String(distance, 2) + "cm";
		}
		else
		{
			return String(distance, 2);
		}
	}
	else if (units == "m")
	{
		if(showUnits)
		{
			return String(distance / 100, 2) + "m";
		}
		else
		{
			return String(distance / 100, 2);
		}
	}
}


// Temperature and Humidity Sensor Functionality (DHT-11)
/// Example: getTemperature()
float getTemperature()
{
	return dht.readTemperature();
}

/// Example: getHumidity()
float getHumidity()
{
	return dht.readHumidity();
}


// Magnetometer Functionality (HMC5883L)
/// Example: getCompassDegrees()
float getCompassDegrees()
{
	Vector norm = compass.readNormalize();

	float heading = atan2(norm.YAxis, norm.XAxis);

	float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
	heading += declinationAngle;

	// Correct for heading < 0deg and heading > 360deg
	if (heading < 0)
	{
		heading += 2 * PI;
	}
	if (heading > 2 * PI)
	{
		heading -= 2 * PI;
	}

	float headingDegrees = heading * 180/M_PI;

	return headingDegrees;
}

/// Example: getCompassDirection()
String getCompassDirection()
{
	float headingDegrees = getCompassDegrees();

	if(headingDegrees > 354.38 && headingDegrees <= 360 || headingDegrees > 0 && headingDegrees < 39.38)
	{
		return "N";
	}
	else if (headingDegrees > 39.38 && headingDegrees < 84.38)
	{
		return "NE";
	}
	else if (headingDegrees > 84.38 && headingDegrees < 129.38)
	{
		return "E";
	}
	else if (headingDegrees > 129.38 && headingDegrees < 174.38)
	{
		return "SE";
	}
	else if (headingDegrees > 174.38 && headingDegrees < 219.38)
	{
		return "S";
	}
	else if (headingDegrees > 219.38 && headingDegrees < 264.38)
	{
		return "SW";
	}
	else if (headingDegrees > 264.38 && headingDegrees < 309.38)
	{
		return "W";
	}
	else if (headingDegrees > 309.38 && headingDegrees < 354.38)
	{
		return "NW";
	}
}


// Pressure & Temperature Sensor Functionality (BMP085)
/// Example: getPressure()
float getPressure()
{
	return bmp.readPressure();
}

/// Example: getAltitude()
float getAltitude()
{
	return bmp.readAltitude();
}


// Accelerator Functionality (ADXL345)
/// Example: getPitch()
double getPitch()
{
	double pitch, Xg, Yg, Zg;
	acc.read(&Xg, &Yg, &Zg);

	double fXg = Xg * alpha + (fXg * (1.0 - alpha));
	double fYg = Yg * alpha + (fYg * (1.0 - alpha));
	double fZg = Zg * alpha + (fZg * (1.0 - alpha));

	pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;

	return pitch;
}

/// Example: getRoll()
double getRoll()
{
	double roll, Xg, Yg, Zg;
	acc.read(&Xg, &Yg, &Zg);

	double fXg = Xg * alpha + (fXg * (1.0 - alpha));
	double fYg = Yg * alpha + (fYg * (1.0 - alpha));
	double fZg = Zg * alpha + (fZg * (1.0 - alpha));

	roll  = (atan2(-fYg, fZg)*180.0)/M_PI;

	return roll;
}


// Motor Driver Functionality (L298N)
/// Example: driveMotor(FORWARD_PIN, REVERSE_PIN, "Forward", 255)
void driveMotor(int forwardPin, int reversePin, String toDirection, int motorSpeed)
{
	if(toDirection == "Forward")
	{
		analogWrite(forwardPin, motorSpeed);
		analogWrite(reversePin, 0);
	}
	else if(toDirection == "Reverse")
	{
		analogWrite(forwardPin, 0);
		analogWrite(reversePin, motorSpeed);
	}
	else if(toDirection == "Stop")
	{
		analogWrite(forwardPin, 0);
		analogWrite(reversePin, 0);
	}
}

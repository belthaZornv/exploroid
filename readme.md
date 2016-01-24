# Exploroid Code
<br>

Libraries
---------
<br>

Copy and paste the libraries to your libraries file to use the GY-80, DHT-11 and the HC-SR04. This code covers the code for:

* GY-80: This covers gyro, accelerometer, magnetometer and barometer. Implemented functions:
	- getCompassDegrees()
	- getCompassDirection()
	- getPressure()
	- getAltitude()
	- getPitch()
	- getRoll()
* DHT-11: This covers temperature and humidity. Implemented functions:
	- getTemperature()
	- getHumidity()
* HC-SR04: This covers ultrasonic distance sensor. Implemented functions:
	- getDistance(String units, bool showUnits)
* L298N: This covers motor driver. Implemented functions:
	- driveMotor(int forwardPin, int reversePin, String toDirection, int motorSpeed)

<br>
To Do:
---------
<br>

* GY-80
	- Get gyro details.
* L298N
	- Drive motor with input of the joystick.
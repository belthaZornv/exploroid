int joyPin1 = 0;
int joyPin2 = 1;
int value1 = 0;
int value2 = 0;

int middleXJSValue = 515;
int middleYJSValue = 508;

int maxJSValue = 1023;

void setup() {
  Serial.begin(9600);
}

void loop()
{
  Serial.println(getXAxisValue());
  Serial.println(getYAxisValue());

  delay(1000);
}

int formatRawJSData(int maxValue, int middleValue, int currentValue)
{
  if(currentValue < middleValue)
  {
    int diff = middleValue - currentValue;
    int result = ceil(((diff / middleValue) * 100));
    
    return result;
  }
  else
  {
    int diff = 
  }
}

int getXAxisValue()
{
  return analogRead(joyPin1);
}

int getYAxisValue()
{
  return analogRead(joyPin2);
}


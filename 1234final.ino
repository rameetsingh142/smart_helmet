#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 11;
const int trigPin2 = 3;
const int echoPin2 = 2;
const int ledPin2 = 4;
const int ledPin3 = 8;

// defines variables
long duration;
int distance;
int safetyDistance;
long duration2;
int distance2;
int safetyDistance2;

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
  
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  }  
  Serial.println(" Hz");  
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- "); 
  
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  }  
  Serial.println(" g");  
}

void setup(void) 
{
  pinMode(ledPin3, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 pinMode(ledPin, OUTPUT);
 pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
 pinMode(ledPin2, OUTPUT);

 #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  // displaySetRange(ADXL345_RANGE_2_G);
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
}

void loop(void) 
{


  sensors_event_t event; 
  accel.getEvent(&event);
  int x=event.acceleration.x;  
  int z=event.acceleration.z;
  if((x >=2)  ) 
 {  
  digitalWrite(ledPin3, HIGH);
 
 } 
 else

 {
  digitalWrite(ledPin3, LOW);
   
 }

     Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500);
  if (safetyDistance2 <= 20 && safetyDistance <= 20){
  int i;
  for(i=0;i<=3;i++){
  digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin, HIGH);
  delay(150);
  digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin, LOW);
  delay(150);}
}
else{
  
  digitalWrite(ledPin2, LOW);
}
  
  digitalWrite(trigPin, LOW);
delay(100);
digitalWrite(trigPin2, LOW);
delay(100);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(1000);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;

 

 if (safetyDistance <= 30){
  int i;
  for(i=0;i<=15;i++){
  digitalWrite(ledPin, HIGH);
  delay(150);
  digitalWrite(ledPin, LOW);
  delay(150);}
}
else{
  
  digitalWrite(ledPin, LOW);
}
if (safetyDistance2 <= 20 && safetyDistance <= 20){
  int i;
  for(i=0;i<=30;i++){
  digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin, HIGH);
  delay(150);
  digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin, LOW);
  delay(150);}
}
else{
  
  digitalWrite(ledPin2, LOW);
}
digitalWrite(trigPin2, HIGH);
delayMicroseconds(1000);
digitalWrite(trigPin2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);

// Calculating the distance
distance2= duration2*0.034/2;

safetyDistance2 = distance2;
 if (safetyDistance2 <= 30){
  int i;
  for(i=0;i<=15;i++){
  digitalWrite(ledPin2, HIGH);
  delay(150);
  digitalWrite(ledPin2, LOW);
  delay(150);}
}
else{
  
  digitalWrite(ledPin2, LOW);
}
if (safetyDistance2 <= 20 && safetyDistance <= 20){
  int i;
  for(i=0;i<=30;i++){
  digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin, HIGH);
  delay(150);
  digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin, LOW);
  delay(150);}
}
else{
  
  digitalWrite(ledPin2, LOW);
}
 
}

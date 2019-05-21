/*Program to measure RPM using hall effect sensor 
  and store it in SD card*/
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {
    Serial.begin(9600);
    pinMode(2,INPUT); 
    pinMode(3,INPUT);
    attachInterrupt(0,sense1,RISING);
    attachInterrupt(1,sense2,RISING);

    
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

uint32_t start1,sto1,count1=0,tim1,res1,start2,sto2,count2=0,tim2,res2;
String dataString = "";

void loop() {
}
//ISR
void sense1(){
  if(count1 == 0){
    start1  = micros();
    }
     count1++;
  if(count1 == 2){
    sto1 = micros();
    tim1 = sto1-start1;
    res1 = 178750000/(3*tim1);
 
    dataString=String(res1);
    File dataFile = SD.open("rpm1.txt", FILE_WRITE);
    if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
    }
    else {
    Serial.println("error opening rpm1.txt");
  }
    count1 = 0;
  }
 }
 //ISR
 void sense2(){
  if(count2 == 0){
    start2  = micros();
    }
     count2++;
  if(count2 == 2){
    sto2 = micros();
    tim2 = sto2-start2;
    res2 = 178750000/(3*tim2);

    dataString=String(res2);
    File dataFile = SD.open("rpm2.txt", FILE_WRITE);
    if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
    }
    else {
    Serial.println("error opening rpm2.txt");
  }
    count2 = 0;
  }
 }

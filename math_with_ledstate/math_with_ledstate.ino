



#include "pitches.h"
#include <string.h>
#include <math.h> // Math Library for using functions (sqrt(num), square(num) ... ) to solve equations 

#define SIZE 10
#define totalShapes 5
#define pi 3.142

const int l1 = 2;
const int l2 = 3;
const int l3 = 4;
const int l4 = 5;
const int l5 = 6;

int speakerPin=8;
int Area=0;

int firstTerm=0, secondTerm=1, nextTerm=0;
int numOfTerms=0;
    

int frequency [SIZE]={
  NOTE_B0  
, NOTE_C1  
, NOTE_CS1 
, NOTE_D1  
, NOTE_DS1 
, NOTE_E1  
, NOTE_F1  
, NOTE_FS1 
, NOTE_G1  
, NOTE_GS1 }; // Total 10 Frequency of Different values


int frequency2[SIZE]={
 NOTE_DS6, 
 NOTE_E6  ,
 NOTE_F6  ,
 NOTE_FS6 ,
 NOTE_G6  ,
 NOTE_GS6 ,
 NOTE_A6  ,
 NOTE_AS6 ,
 NOTE_B6  ,
 NOTE_C7  
  
  };
String  shapesName[totalShapes]={"Square", "Rectangle", "Parallelogram", "Triangle", "Circle"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initializing our Serial monitor bits per second data transfer
  Serial.println("Press Keys for Generating tones of these shapes");


  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
  
 
  for(int counter=0; counter<5; counter++)
  {
    Serial.print(counter+1);
    Serial.print("                                         ");
    Serial.println(shapesName[counter]);
  }
   
  Serial.println("Series and Equations");
  Serial.println("6                                        Fibonacci Series");
  Serial.println("7                                        Quadratic Equation");
       
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()> 0)
  {
    int incomingByte=Serial.read() ; // Because IT returns ascii value of key you press
     Serial.println(incomingByte);
    switch(incomingByte)
   
    {
      // 1 for Generating Sound from Area of Square=s^2  
      case 1:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      for(int index=0; index<SIZE; index++)
      {
         Area=square(frequency[index]);
        playAreaSound(Area);
      }
      break;
      
      // 2 for Generating Sound from Area of Rectangle=l*w
      case 2:
      digitalWrite(l1, LOW);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      for(int index=0; index<SIZE; index=index+2) //This for loop runs 5 times if you observe the condition
      {
        Area=frequency[index]*frequency[index+1];
        playAreaSound(Area);
      }
      break;
     
      // 3 for Generating Sound from Area of Parallelogram=b*h
      case 3:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, HIGH);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      for(int index=9; index > 0; index=index-2) //This for loop runs 5 times if you observe the condition but this time from reverse condition
      {
        Area=frequency[index]*frequency[index-1];
        playAreaSound(Area);
      }     
      break;
      
      // 4 for Generating Sound from Area of Triangle=(1/2)*b*h
      case 4:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, HIGH);
      digitalWrite(l5, LOW);
      for(int index=0; index<SIZE-1; index++)
      {
        Area=(frequency[index]*frequency[index+1])/2;
        playAreaSound(Area);
      }
      break;
      
      // 5 for Generating Sound from Area of Circle=pi*r^2
      case 5:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, HIGH);
      for(int index=0; index<SIZE; index++)
      {
        Area=pi*square(frequency[index]);
        playAreaSound(Area);
      }
      
      break;

      // 6 for Fibonacci Series in which next term =sum of Two preceding Terms (1, 1, 2, 3, 5, 8, 13 ...and so on)
      case 6:
      digitalWrite(l1, LOW);  
      Serial.println("Starting Ten Terms of Fibonacci Series !  ");
      
      while(numOfTerms < 10) // Starting 10 Terms will Generate fibonacci sound 
      {
        nextTerm=firstTerm+secondTerm;// These three statements generates next Term
        firstTerm=secondTerm;
        secondTerm=nextTerm;
        Area=nextTerm;
        Serial.print(Area);
        Serial.print(",");
        playAreaSound(Area*frequency[numOfTerms]);
        numOfTerms++;
      }
      Serial.println("");
     //initializing variables to its inital values 
      numOfTerms=0;
      firstTerm=0; 
      secondTerm=1; 
      nextTerm=0;
      
      break;

      //For Quadratic Equation
      case 7:

      for(int index=0; index<SIZE; index++)
      {
        playAreaSound(frequency2[index]);
      }
      
      break;
   
      
    } 
  }
  
}

void playAreaSound(int freq)
{
  tone(speakerPin, freq, 500);
  delay(10);
}

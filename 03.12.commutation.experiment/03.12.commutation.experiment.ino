#include <TimerOne.h>
/*The below code is for testing the spinning of our switched reluctance motor
Written by: Jaiden Martinson-Hatt

sensorC val = yellow_B on
*/
int val = 255;
#define ORANGE_A 5
#define YELLOW_B 7
#define GREEN_C 6
#define A 2
#define B 3

#define sensorA 51 //orange keep 
#define sensorB 53 //Yellow
#define sensorC 52 //Green
//#define sensorD 45 // keep 
//#define sensorE 47 //
//#define sensorF 49 // no longer colour coded keep 

//#define sensorA 45 // keep 
//#define sensorB 49 //
//#define sensorC 51 //


volatile int count = 0;
double grades=0, pgrades=10; /*variable to store converted value*/ // pid stuff
byte state = 0;
int encA = 0, encB = 0;
int psensorValA=0,psensorValB=0,psensorValC=0,psensorValD=0,psensorValE=0,psensorValF=0;
int sensorValA=0,sensorValB=0,sensorValC=0,sensorValD=0,sensorValE=0,sensorValF=0;
int temp = 0;

int count_switches = 0;
int prev_case = 0;
int delay_start = 0;

void startup();
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize output pins 
  pinMode(ORANGE_A, OUTPUT);
  pinMode(YELLOW_B, OUTPUT);
  pinMode(GREEN_C, OUTPUT);

  
  temp = 0;
   //start serial connection
  Serial.begin(9600);
  
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
  pinMode(sensorC, INPUT);
  

  pinMode(A, INPUT); 
  pinMode(B, INPUT); 

  //attachInterrupt(0, doA, CHANGE);
  //attachInterrupt(1, doA, CHANGE); 

  encA = digitalRead(A);
  encB = digitalRead(B);
  
  if (encA^encB == 0){
    if (encA = 0)state = 0;
    else state = 2;
  }
  else{
    if (encA = 1) state = 1;
    else state = 3;
  }

  Timer1.initialize(10000);
  Timer1.attachInterrupt(compute);
  
  Serial.setTimeout(100000);
}


void loop() {
  //if (Serial.available() > 0){
  //val = Serial.parseInt();
 // }
  //Serial.println(val);}
  /*
    if (grades != pgrades){
    Serial.println(grades);
    pgrades = grades;
    }*/
//Serial.println(temp);

  if ((sensorValA != psensorValA)||(sensorValB != psensorValB)||(sensorValC != psensorValC)){ 
  Serial.print(sensorValA);
  Serial.print(sensorValB);
  Serial.print(sensorValC);
  
  Serial.println();

  psensorValA=sensorValA;
  psensorValB=sensorValB;
  psensorValC=sensorValC;

 count_switches++;
    }
}

void compute() {
 
   sensorValA = digitalRead(sensorA);
   sensorValB = digitalRead(sensorB);
   sensorValC = digitalRead(sensorC);
   

  int sens = ((sensorValA<<2)|(sensorValB<<1)|(sensorValC));


  if (delay_start < 50){
    delay_start++;
  }

  switch (sens) {
    case 1:{
    case 6:{
                prev_case = 1;
                if (/*(prev_case == (1||6)) &&*/ (delay_start == 50) || (prev_case == 0)){
                  delay_start = 0;
                  startup();
                }
                else {
                analogWrite(GREEN_C,LOW);// turn the pole on (val is the voltage level)
                analogWrite(ORANGE_A,LOW);
                analogWrite(YELLOW_B,val);
                
                break;
                }
    }}
    case 3:{
    case 4:{
                prev_case = 3;
                if (/*(prev_case == (3||4)) &&*/ (delay_start == 50)){
                  delay_start = 0;
                  startup();
                }
                else{
                analogWrite(GREEN_C,val);// turn the pole on (val is the voltage level)
                analogWrite(ORANGE_A,LOW);
                analogWrite(YELLOW_B,LOW);
                break;
                }
    }}
     case 2: {
     case 5: {
                prev_case = 2;
                if (/*(prev_case == (2||5)) &&*/ (delay_start == 50)){
                  delay_start = 0;
                  startup();
                }
                else{
                analogWrite(GREEN_C,LOW);// turn the pole on (val is the voltage level)
                analogWrite(ORANGE_A,val);
                analogWrite(YELLOW_B,LOW);
                break;
                }
     }}
  } 
} 

void startup(){
  if (count_switches > 6){
    count_switches = 0;
    Serial.println("NOT restarting");
    return;
  }
  else{
    Serial.print(prev_case);
  }
  if (prev_case == (1||0)){
                Serial.println("restarting A");
                digitalWrite(YELLOW_B, val);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                /*digitalWrite(YELLOW_B, val);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, val);
                delay(50);*/
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, val);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, val);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                Serial.println("restarting A done");
                count_switches = 0;
                return;
  }
  else if (prev_case == (3)){
                Serial.println("restarting B");
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, val);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, val);
                digitalWrite(GREEN_C, val);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, val);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, val);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                count_switches = 0;
                return;
  }
  else if (prev_case == (2)){
                Serial.println("restarting C");
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, val);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, val);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, val);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, val);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);// turn the pole on (val is the voltage level)
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, val);
                delay(4000);
                count_switches = 0;
                return;
  }
  else {
    Serial.println("fuck you");
    return;
  }
}

  void doA(){
  encA = digitalRead(A);
  encB = digitalRead(B);
  if (count == 400) count = 0;
  if (count == -1) count = 399;
  switch(state){
    case 0: {if(encA == 1 && encB == 0){
              count++;
              state = 1;
              }
            else{
              count--;
              state = 3;
              }
            break;}
    case 1: {if(encA == 1 && encB == 1){
              count++;
              state = 2;
              }
            else{
              count--;
              state = 0;
              }
            break;}
    case 2: {if(encA == 0 && encB == 1){
              count++;
              state = 3;
              }
            else{
              count--;
              state = 1;
              }
            break;}
    case 3: {if(encA == 0 && encB == 0){
              count++;
              state = 0;
              }
            else{
              count--;
              state = 2;
            }
            break;}
       }

        grades = (count*360L/400);
}

void startup();

#include <TimerOne.h>
/*testing of function for running motor
*/

#define ORANGE_A 5
#define YELLOW_B 7
#define GREEN_C 6
#define A 2
#define B 3

#define sensorA 51 //Orange Phase 
#define sensorB 53 //Yellow Phase
#define sensorC 52 //Green Phase


//global variables for PID
int val=255; //pwm variable
volatile int count = 0;
double grades=0, pgrades=10; /*variable to store converted value*/ // pid stuff
byte state = 0;
int encA = 0, encB = 0;

//global variables for running motor
int psensorValA=0,psensorValB=0,psensorValC=0,psensorValD=0,psensorValE=0,psensorValF=0;
int sensorValA=0,sensorValB=0,sensorValC=0,sensorValD=0,sensorValE=0,sensorValF=0;
int count_switches = 0;
int prev_case = 0;
int delay_start = 0;

//function prototype for startup routines
void startup_clockwise(int pwm);
void startup_counter_clockwise(int pwm);

//functions for motor state
void idle_motor(); 
void clockwise(int pwm);
void counter_clockwise(int pwm);


//setup for pins, serial etc. 
void setup() {
  //start serial connection, baud rate 9600
  Serial.begin(9600);

  //initialize output pins
  pinMode(ORANGE_A, OUTPUT);
  pinMode(YELLOW_B, OUTPUT);
  pinMode(GREEN_C, OUTPUT);

  //initialize hall sensor pins
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
  pinMode(sensorC, INPUT);
  
  //initialize timer interupts for testing
  Timer1.initialize(100000);
  Timer1.attachInterrupt(compute);
 // Serial.setTimeout(100000);
}

void loop() {
  //printing serial monitor values, only when they change
  if ((sensorValA != psensorValA)||(sensorValB != psensorValB)||(sensorValC != psensorValC)){ 
  
  //printing the digital value of hall sensors
  Serial.print(sensorValA);
  Serial.print(sensorValB);
  Serial.print(sensorValC);
  
  Serial.println();

  psensorValA=sensorValA;
  psensorValB=sensorValB;
  psensorValC=sensorValC; 

  count_switches++; //counter for startup logic
    }

// parse for direction and stop
//if (Serial.available() > 0){
  //val = Serial.parseInt();
  //Serial.println(val);
 // }
  

}

//Interrupt Service Routine
void compute() {
  
  if (val>0){
  clockwise(val); //call clockwise function
  }
  else if (val<0){
  counter_clockwise(val);
  }
  else if (val==0){
    idle_motor();
  }
  
  
}




























/* routine for running motor in clockwise direction.
motor needs to be wired as defined above and will need
many of the global variables in this program
*/
void clockwise(int pwm){
  
  //read hall sensors
  sensorValA = digitalRead(sensorA);
  sensorValB = digitalRead(sensorB);
  sensorValC = digitalRead(sensorC);
  
  //concatenate sensor values into 3 bit value for case statement
  int sens = ((sensorValA<<2)|(sensorValB<<1)|(sensorValC));

//logic for exiting function when pwm is zero or negative
 if (pwm<=0){
   return;
 }
  //logic for determining startup
  if (delay_start < 50){
    delay_start++;
  }

  switch (sens) {
    case 1:{
    case 6:{
                prev_case = 1;
                if ( (delay_start == 50) || (prev_case == 0)){
                  delay_start = 0;
                  startup_clockwise(pwm);
                }
                else {
                  analogWrite(GREEN_C,LOW);// turn the pole on (val is the voltage level)
                  analogWrite(ORANGE_A,LOW);
                  analogWrite(YELLOW_B,pwm);
                
                break;
                }
    }}
    case 3:{
    case 4:{
                prev_case = 3;
                if (delay_start == 50){
                  delay_start = 0;
                  startup_clockwise(pwm);
                }
                else{
                  analogWrite(GREEN_C,pwm);// turn the pole on (val is the voltage level)
                  analogWrite(ORANGE_A,LOW);
                  analogWrite(YELLOW_B,LOW);
                break;
                }
    }}
     case 2: {
     case 5: {
                prev_case = 2;
                if (delay_start == 50){
                  delay_start = 0;
                  startup_clockwise(pwm);
                }
                else{
                  analogWrite(GREEN_C,LOW);// turn the pole on (val is the voltage level)
                  analogWrite(ORANGE_A,pwm);
                  analogWrite(YELLOW_B,LOW);
                break;
                }
     }}
  } 
} 


/* startup routine, will be called by clockwise direction spinning 
routine */ 
void startup_clockwise(int pwm){
  
  if (count_switches > 6){
    count_switches = 0;
    Serial.println("NOT restarting");
    return;
  }
  else{
    Serial.print(prev_case);
  }
  if (prev_case == (1||0)){
                Serial.println("restarting A"); //print statements for debugging purposes
                digitalWrite(YELLOW_B, pwm);
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, pwm);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, pwm);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                Serial.println("restarting A done");
                count_switches = 0;
                return;
  }
  else if (prev_case == (3)){
                Serial.println("restarting B"); //print statements for debugging purposes
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, pwm);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, pwm);
                digitalWrite(GREEN_C, pwm);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, pwm);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, pwm);
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                count_switches = 0;
                return;
  }
  else if (prev_case == (2)){
                Serial.println("restarting C");//print statements for debugging purposes
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, pwm);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, pwm);
                digitalWrite(ORANGE_A, pwm);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, pwm);
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, LOW);
                digitalWrite(GREEN_C, pwm);
                delay(4000);
                count_switches = 0;
                return;
  }
  else {
    Serial.println("fuck you"); //print statements for debugging purposes
    return;
  }
}



/* routine for running motor in clockwise direction.
motor needs to be wired as defined above and will need
many of the global variables in this program
*/
void counter_clockwise(int pwm){
  
  //read hall sensors
  sensorValA = digitalRead(sensorA);
  sensorValB = digitalRead(sensorB);
  sensorValC = digitalRead(sensorC);
  
  //concatenate sensor values into 3 bit value for case statement
  int sens = ((sensorValA<<2)|(sensorValB<<1)|(sensorValC));

  //logic for exiting function when pwm is zero or positive
 if (pwm>=0){
   return;
 }


  //logic for determining startup
  if (delay_start < 50){
    delay_start++;
  }

  switch (sens) {
    case 1:{
    case 6:{
                prev_case = 1;
                if ( (delay_start == 50) || (prev_case == 0)){
                  delay_start = 0;
                  startup_counter_clockwise(abs(pwm));
                }
                else { 
                  //analogWrite(GREEN_C,LOW);// old
                  analogWrite(YELLOW_B,LOW); //new
                  analogWrite(ORANGE_A,LOW);
                  //analogWrite(YELLOW_B,pwm); //old
                  analogWrite(GREEN_C,abs(pwm)); //new
                
                break;
                }
    }}
    case 3:{
    case 4:{
                prev_case = 3;
                if (delay_start == 50){
                  delay_start = 0;
                  startup_counter_clockwise(abs(pwm));
                }
                else{
                  //analogWrite(GREEN_C,pwm); // old
                  analogWrite(YELLOW_B,abs(pwm)); //new
                  analogWrite(ORANGE_A,LOW);
                  //analogWrite(YELLOW_B,LOW); //old
                  analogWrite(GREEN_C,LOW); //new
                break;
                }
    }}
     case 2: {
     case 5: {
                prev_case = 2;
                if (delay_start == 50){
                  delay_start = 0;
                  startup_counter_clockwise(abs(pwm));
                }
                else{
                  analogWrite(GREEN_C,LOW); //both low anyways so it's fine
                  analogWrite(ORANGE_A,abs(pwm));
                  analogWrite(YELLOW_B,LOW);
                break;
                }
     }}
  } 
} 


/* startup routine, will be called by clockwise direction spinning 
routine */ 
void startup_counter_clockwise(int pwm){
  
  if (count_switches > 6){
    count_switches = 0;
    Serial.println("NOT restarting");
    return;
  }
  else{
    Serial.print(prev_case);
  }
  if (prev_case == (1||0)){
                Serial.println("restarting A"); //print statements for debugging purposes


                //digitalWrite(YELLOW_B, val); //old
                digitalWrite(GREEN_C, abs(pwm)); //new
                digitalWrite(ORANGE_A, LOW);
                //digitalWrite(GREEN_C, LOW); //old
                digitalWrite(YELLOW_B, LOW); //new

                delay(4000);
                //digitalWrite(YELLOW_B, LOW); //old 
                digitalWrite(GREEN_C, LOW); //new
                digitalWrite(ORANGE_A, LOW);
                //digitalWrite(GREEN_C, pwm); //old 
                digitalWrite(YELLOW_B, abs(pwm)); //new

                delay(4000);
                digitalWrite(YELLOW_B, LOW); //don't change
                digitalWrite(ORANGE_A, abs(pwm));
                digitalWrite(GREEN_C, LOW);

                delay(4000);
                Serial.println("restarting A done");
                count_switches = 0;
                return;
  }
  else if (prev_case == (3)){
                Serial.println("restarting B"); //print statements for debugging purposes
                //digitalWrite(YELLOW_B, LOW); //old
                digitalWrite(GREEN_C, LOW); //new
                digitalWrite(ORANGE_A, LOW);
                //digitalWrite(GREEN_C, pwm); //old 
                digitalWrite(YELLOW_B, abs(pwm)); //new

                delay(4000);
                //digitalWrite(YELLOW_B, LOW); //old
                digitalWrite(GREEN_C, LOW); //new
                digitalWrite(ORANGE_A, abs(pwm));
                //digitalWrite(GREEN_C, pwm); //old
                digitalWrite(YELLOW_B, pwm); //new

                delay(4000);
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, abs(pwm));
                digitalWrite(GREEN_C, LOW);

                delay(4000);
                //digitalWrite(YELLOW_B, pwm); //old
                digitalWrite(GREEN_C, abs(pwm)); //new
                digitalWrite(ORANGE_A, LOW);
                //digitalWrite(GREEN_C, LOW); //old
                digitalWrite(YELLOW_B, LOW); //new

                delay(4000);
                count_switches = 0;
                return;
  }
  else if (prev_case == (2)){
                Serial.println("restarting C");//print statements for debugging purposes
                digitalWrite(YELLOW_B, LOW);
                digitalWrite(ORANGE_A, abs(pwm));
                digitalWrite(GREEN_C, LOW);
                delay(4000);
                //digitalWrite(YELLOW_B, pwm); //old
                digitalWrite(GREEN_C,LOW); //new
                digitalWrite(ORANGE_A, abs(pwm));
                //digitalWrite(GREEN_C, LOW); //old
                digitalWrite(YELLOW_B, LOW); //new

                delay(4000);
                //digitalWrite(YELLOW_B, pwm); //old
                digitalWrite(GREEN_C, abs(pwm)); //new
                digitalWrite(ORANGE_A, LOW);
                //digitalWrite(GREEN_C, LOW); //old
                digitalWrite(YELLOW_B, LOW); //new

                delay(4000);
                //digitalWrite(YELLOW_B, LOW); //old
                digitalWrite(GREEN_C, LOW); //new 
                digitalWrite(ORANGE_A, LOW);
                //digitalWrite(GREEN_C, pwm); //old 
                digitalWrite(YELLOW_B, abs(pwm)); //new

                delay(4000);
                count_switches = 0;
                return;
  }
  else {
    Serial.println("fuck you"); //print statements for debugging purposes
    return;
  }
}

void idle_motor(){
  digitalWrite(YELLOW_B, LOW);
  digitalWrite(ORANGE_A, LOW);
  digitalWrite(GREEN_C, LOW);
  return;
}

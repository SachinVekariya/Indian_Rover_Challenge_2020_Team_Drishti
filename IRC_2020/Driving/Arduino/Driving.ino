

#include <avr/wdt.h>

//int cam_mot1=43;
//int cam_pwm1=10;
//int cam_mot2=24;
//int cam_pwm2=5;


int l1_dir1=24;
int l1_dir2=22; ///////HERCULES EXTRA BACK UP /////////////////

int l2_dir1=25;
//int l2_dir2=23;

int l3_dir1=23;
//int l3_dir2=31;

int r1_dir1=53;
int r1_dir2=47; ///////HERCULES EXTRA BACK UP /////////////////

int r2_dir1=45;
//int r2_dir2=49;

int r3_dir1=51;
int r3_dir2=52; ///////HERCULES EXTRA BACK UP /////////////////

int l1_pwm=5;
int r1_pwm=4;

int l2_pwm=7;
int r2_pwm=9;

int l3_pwm=6;
int r3_pwm=8;


//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////EXTRA/////////////////

int l293d_en1=31;
int l293d_en2=33;
int l293d_pwm1=2;

int l293d_pwm2=3;
int l293d_en3=37;
int l293d_en4=35;

int dual_dir1=41;
int dual_dir2=43;
int dual_pwm1=11;
int dual_pwm2=10;


void(*resetFunc) (void) = 0;//declare the reset function @ address 0



void setup() {

  Serial.begin(9600);

  pinMode(l1_dir1,OUTPUT);
  pinMode(l2_dir1,OUTPUT);
  pinMode(l3_dir1,OUTPUT);
  
  
  pinMode(r1_dir1,OUTPUT);
  pinMode(r2_dir1,OUTPUT);
  pinMode(r3_dir1,OUTPUT);

  pinMode(l1_pwm,OUTPUT);
  pinMode(r1_pwm,OUTPUT);

  pinMode(l2_pwm,OUTPUT);
  pinMode(r2_pwm,OUTPUT);

  pinMode(l3_pwm,OUTPUT);
  pinMode(r3_pwm,OUTPUT);

  //pinMode(cam_mot1,OUTPUT);
  // pinMode(cam_mot2,OUTPUT);
  //pinMode(cam_pwm1,OUTPUT);
  //pinMode(cam_pwm2,OUTPUT);

  pinMode(l293d_en1,OUTPUT);
  pinMode(l293d_en2,OUTPUT);
  pinMode(l293d_en3,OUTPUT);
  pinMode(l293d_en4,OUTPUT);
  pinMode(l293d_pwm1,OUTPUT);
  pinMode(l293d_pwm2,OUTPUT);
  
  pinMode(dual_dir1,OUTPUT);
  pinMode(dual_dir2,OUTPUT); 
  pinMode(dual_pwm1,OUTPUT); 
  pinMode(dual_pwm2,OUTPUT); 
  
   
   wdt_reset();
   wdt_disable();


}

void Reset()
{
  wdt_reset();
  wdt_enable(WDTO_15MS);   
  
}

void loop() {

  Serial.setTimeout(5000000);
  int a,b,c,d,e,e_1,d_1;
  
  a=Serial.parseInt();  
  b=Serial.parseInt();
  c=Serial.parseInt();
  d=Serial.parseInt();
  e=Serial.parseInt();
  //Serial.println(a);
  //Serial.println(b);

  if(a>=0) //Forward
  {
    digitalWrite(l1_dir1,LOW); 
    digitalWrite(l2_dir1,LOW);
    digitalWrite(l3_dir1,LOW);
    digitalWrite(l1_dir2,HIGH);
    //digitalWrite(l2_dir2,HIGH);
    //digitalWrite(l3_dir2,HIGH);

    
    analogWrite(l1_pwm,a);
    analogWrite(l2_pwm,a);
    analogWrite(l3_pwm,a);
  }
  else //Backward
  {
    int a_1=(-1*a);
   digitalWrite(l1_dir1,HIGH); 
    digitalWrite(l2_dir1,HIGH);
    digitalWrite(l3_dir1,HIGH);
    digitalWrite(l1_dir2,LOW);
    //digitalWrite(l2_dir2,LOW);
    //digitalWrite(l3_dir2,LOW);
    analogWrite(l1_pwm,a_1);
    analogWrite(l2_pwm,a_1);
    analogWrite(l3_pwm,a_1);
  }
  if(b>=0) //Forward
  {
    
    digitalWrite(r1_dir1,LOW);
    digitalWrite(r2_dir1,LOW);
    digitalWrite(r3_dir1,LOW);
    digitalWrite(r1_dir2,HIGH);
    //digitalWrite(r2_dir2,HIGH);
    digitalWrite(r3_dir2,HIGH);

    
    analogWrite(r1_pwm,b);
    analogWrite(r2_pwm,b);
    analogWrite(r3_pwm,b);
  }
  else //Backward
  {
    int b_1=(-1*b);
    digitalWrite(r1_dir1,HIGH);
    digitalWrite(r2_dir1,HIGH);
    digitalWrite(r3_dir1,HIGH);
    digitalWrite(r1_dir2,LOW);
    //digitalWrite(r2_dir2,LOW);
    digitalWrite(r3_dir2,LOW);

    
    analogWrite(r1_pwm,b_1);
    analogWrite(r2_pwm,b_1);
    analogWrite(r3_pwm,b_1);
  }
  
  if(d>=0)
  {
    //digitalWrite(cam_mot1,HIGH);
    //analogWrite(cam_pwm1,d);
  ////////////////////EXTRA//////////////////////
  
  digitalWrite(l293d_en1,HIGH);///////////l293d motor 1 /////////////////
  digitalWrite(l293d_en2,LOW);
  analogWrite(l293d_pwm1,d);
  
  ///////////////////EXTRA/////////////////////
  digitalWrite(dual_dir1,HIGH);  /////////DUAL's CHANNEL 1///////////////
  analogWrite(dual_pwm1,d);
  
  }
  else
  {
    d_1=(-1*d);
    //digitalWrite(cam_mot1,LOW);
    //analogWrite(cam_pwm1,d_1);
    ///////////////////////////EXTRA////////////////////
    
    digitalWrite(l293d_en2,LOW);///////////l293d motor 1 /////////////////
    digitalWrite(l293d_en1,HIGH);
    analogWrite(l293d_pwm1,d_1);

/////////////////////////EXTRA///////////////////////
  digitalWrite(dual_dir1,LOW);  /////////DUAL's CHANNEL 1///////////////
  analogWrite(dual_pwm1,d_1);
  
  }
  
  if(e>=0)
  {
    //digitalWrite(cam_mot2,LOW);
    //analogWrite(cam_pwm2,e);
    //////////////////////EXTRA/////////////

  digitalWrite(l293d_en3,HIGH);///////////l293d motor 2 /////////////////
  digitalWrite(l293d_en4,LOW);
  analogWrite(l293d_pwm2,e);

    ///////////////////EXTRA/////////////////////////
  digitalWrite(dual_dir2,HIGH);  /////////DUAL's CHANNEL 2///////////////
  analogWrite(dual_pwm2,e);
  
  }
  
  else
  {
    e_1=(-1*e);
    //digitalWrite(cam_mot2,HIGH);
    //analogWrite(cam_pwm2,e_1);
  /////////////////////EXTRA/////////////////
  
  digitalWrite(l293d_en3,LOW);///////////l293d motor 2 /////////////////
  digitalWrite(l293d_en4,HIGH);
  analogWrite(l293d_pwm2,e_1);

  /////////////////////////////EXTRA///////////////////
  digitalWrite(dual_dir2,LOW);  /////////DUAL's CHANNEL 2///////////////
  analogWrite(dual_pwm2,e_1);
  
  }
  
  if(c){
       Reset();
   
    }

 }

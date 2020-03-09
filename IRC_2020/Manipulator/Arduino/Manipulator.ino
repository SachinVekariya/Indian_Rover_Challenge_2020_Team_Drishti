int motor_1,motor_2,motor_3,motor_4,motor_5,motor_6;
int pwm_mo1=5,pwm_mo2=12,pwm_mo3=11,pwm_mo4=10,pwm_mo5=9,pwm_mo6=6;

//hercules pins
int dir_mo11=49,dir_mo12=51;  
//cytron pins
int dir_mo2=53;    
int dir_mo3=A9;   
int dir_mo4=31;  
int dir_mo5=28;   
int dir_mo6=24;

//////////////////////////////////////////////////////////////////////////////////////////////////
//EXTRA//
// "e" suffix represent extra//// 

// for motor1(hercules)
int pwm_mo1e=3;
int dir_mo11e=43;
int dir_mo12e=39;

// for motor2 (l293d)
int pwm_mo2e=3;
int dir_mo21e=43;
int dir_mo22e=41;

//for motor3  (l293d)
int pwm_mo3e=3;
int dir_mo31e=39;
int dir_mo32e=37;

// for motor4 (cytron)
int pwm_mo4e=7;
int dir_mo4e=23;

//// for motor5 (cytron)
int pwm_mo5e=8;
int dir_mo5e=27;


////// for motor6 (hercules)
int pwm_mo6e=6;
int dir_mo61e=22;
int dir_mo62e=24;

/////////////////////////////////////////////////////////////////

void setup() 
{
    Serial.begin(9600);
    pinMode(dir_mo11, OUTPUT);
    pinMode(dir_mo12, OUTPUT);
    pinMode(dir_mo2, OUTPUT);
    pinMode(dir_mo3, OUTPUT);
    pinMode(dir_mo4, OUTPUT);
    pinMode(dir_mo5, OUTPUT);
    pinMode(dir_mo6, OUTPUT);

    pinMode(pwm_mo1, OUTPUT);
    pinMode(pwm_mo2, OUTPUT);
    pinMode(pwm_mo3, OUTPUT);
    pinMode(pwm_mo4, OUTPUT);
    pinMode(pwm_mo5, OUTPUT);
    pinMode(pwm_mo6, OUTPUT);
    

   

    digitalWrite(pwm_mo1,0);
    digitalWrite(pwm_mo2,0);
    digitalWrite(pwm_mo3,0);
    digitalWrite(pwm_mo4,0);
    digitalWrite(pwm_mo5,0);
    digitalWrite(pwm_mo6,0);

///////////////////////////////////////////////////////////////////////
    
    pinMode(dir_mo11e, OUTPUT);
    pinMode(dir_mo12e, OUTPUT);
    //pinMode(dir_mo2e, OUTPUT);
    //pinMode(dir_mo3, OUTPUT);
    pinMode(dir_mo4e, OUTPUT);
    pinMode(dir_mo5e, OUTPUT);
    pinMode(dir_mo61e, OUTPUT);
    pinMode(dir_mo62e, OUTPUT);

    pinMode(pwm_mo1e, OUTPUT);
    //pinMode(pwm_mo2, OUTPUT);
    //pinMode(pwm_mo3, OUTPUT);
    pinMode(pwm_mo4e, OUTPUT);
    pinMode(pwm_mo5e, OUTPUT);
    pinMode(pwm_mo6e, OUTPUT);
    

   

    digitalWrite(pwm_mo1e,0);
    //digitalWrite(pwm_mo2,0);
   // digitalWrite(pwm_mo3,0);
    digitalWrite(pwm_mo4e,0);
    digitalWrite(pwm_mo5e,0);
    digitalWrite(pwm_mo6e,0);
}
void loop()
{
   Serial.setTimeout(5000000);
   while(Serial.available()== 0){};
   motor_1=Serial.parseInt();
   motor_2=Serial.parseInt();
   motor_3=Serial.parseInt();
   motor_4=Serial.parseInt();
   motor_5=Serial.parseInt();
   motor_6=Serial.parseInt();

   if(motor_1>0)
   {
      digitalWrite(dir_mo11,1);
      digitalWrite(dir_mo12,0);
      analogWrite(pwm_mo1,motor_1);
  ///////////////////////////////////////
      digitalWrite(dir_mo11e,1);
      digitalWrite(dir_mo12e,0);
      analogWrite(pwm_mo1e,motor_1);

   }

   else
   {
      digitalWrite(dir_mo11,0);
      digitalWrite(dir_mo12,1);
      analogWrite(pwm_mo1,(-1*motor_1));
      ///////////////////////////////////////
      
      digitalWrite(dir_mo11e,0);
      digitalWrite(dir_mo12e,1);
      analogWrite(pwm_mo1e,(-1*motor_1));
   }//0,0,0,0,0,0*

    if(motor_2>0)
   {
      digitalWrite(dir_mo2,1);
      analogWrite(pwm_mo2,motor_2);
   }

   else
   {
      digitalWrite(dir_mo2,0);
      analogWrite(pwm_mo2,(-1*motor_2));
   }

   if(motor_3>0)
   {
      digitalWrite(dir_mo3,1);
      analogWrite(pwm_mo3,motor_3);
   }

   else
   {
      digitalWrite(dir_mo3,0);
      analogWrite(pwm_mo3,(-1*motor_3));
   }

   
   if(motor_4>0)
   {
      digitalWrite(dir_mo4,1);
      analogWrite(pwm_mo4,motor_4);
      ////////////////////////////////////
        digitalWrite(dir_mo4e,1);
      analogWrite(pwm_mo4e,motor_4);
   }

   else
   {
      digitalWrite(dir_mo4,0);
      analogWrite(pwm_mo4,(-1*motor_4));
      ///////////////////////////////////////
      digitalWrite(dir_mo4e,0);
      analogWrite(pwm_mo4e,(-1*motor_4));
   }

   if(motor_5>0)
   {
      digitalWrite(dir_mo5,1);
      analogWrite(pwm_mo5,motor_5);
      ///////////////////////////////////////
      digitalWrite(dir_mo5e,1);
      analogWrite(pwm_mo5e,motor_5);
   }

   else
   {
      digitalWrite(dir_mo5,0);
      analogWrite(pwm_mo5,(-1*motor_5));
      ///////////////////////////////////////
      digitalWrite(dir_mo5e,0);
      analogWrite(pwm_mo5e,motor_5);
   }
    
   if(motor_6>0)
   {
      digitalWrite(dir_mo6,1);
      analogWrite(pwm_mo6,motor_6);
      /////////////////////////////////////
     digitalWrite(dir_mo61e,1);
      digitalWrite(dir_mo62e,0);
      analogWrite(pwm_mo6e,motor_6);
     
   }

   else
   {
      digitalWrite(dir_mo6,0);
      analogWrite(pwm_mo6,(-1*motor_6));
          /////////////////////////////////////
      digitalWrite(dir_mo61e,0);
      digitalWrite(dir_mo62e,1);
      analogWrite(pwm_mo6e,(-1*motor_6));
      ///////////////////////////////////////////
      
   }
     
}

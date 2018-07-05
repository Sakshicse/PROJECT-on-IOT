//for battery

float samples= 10;
float sum = 0;                    // sum of samples taken
float sample_count = 0;          // current sample number
float battery = 0.00 ;            // calculated voltage
int solar=A3, mains=4;

//for day-night detection
int LDR_DN = A1;         
int LDR_value ;      
int led = 13;

//for PIR
int sensor = 8; 
int value;               

//for fault detection
int LDR_FAULT=A0;


void setup() { // declare the ledPin as an OUTPUT:

Serial.begin(115200);

pinMode(LDR_FAULT,INPUT);
pinMode(LDR_DN,INPUT);
pinMode(mains,INPUT);
pinMode(solar,INPUT);
pinMode(led, OUTPUT);
pinMode(sensor, INPUT);    // initialize PIR as an input
 }

void loop()

{ int fault= analogRead(LDR_FAULT);

 while (sample_count <samples) 
    {
        sum += analogRead(solar);
        sample_count++;
        delay(40);
    }
   
    battery = (sum /samples * 5.015)/ 1024.0;
    
    
    Serial.print(battery);
    Serial.print (" V  ");

    Serial.print( battery*100/6);
    Serial.print(" % ");
    delay(300);
    sample_count = 0;
    sum = 0;
    
   if((battery*100/6)<=32)
   {
    //digitalWrite(solar,LOW);
    //digitalWrite(mains,HIGH);
    Serial.println("Running on Mains");
    
LDR_value = analogRead(LDR_DN);

Serial.println(LDR_value);

if (LDR_value < 745)
 
{ Serial.print("Night  ");
  value=digitalRead(sensor);
  if(value==1)
  {
    digitalWrite(led,0);
  Serial.print("Motion detected  ");
  Serial.println(value); // Printing output to serial monitor
  //value=0;
  if(fault>820)        //Fault detection
   { Serial.print("                 light is OK");}
  else
   { Serial.print("      FAULT!! Light not getting on  "); }
   value=0;
  }
  else

  {  digitalWrite(led,1);
     Serial.print(" No motion  ");
    Serial.println(value);

   if(fault<821)        //Fault detection
   { Serial.print("                 light is OK");}
  else
   { Serial.print("      FAULT!! Light not getting off  "); }
   
  
  }

}
else
{
 Serial.print("Day  ");
digitalWrite(led,1);
Serial.println(" light is OFF"); 

 if(fault<821)        //Fault detection
   { Serial.print("                 light is OK");}
  else
   { Serial.print("      FAULT!! Light not getting off  "); }
   

}} 
  if((battery*100/6)>32)
   {
    //digitalWrite(solar,HIGH);
    //digitalWrite(mains,LOW);
    Serial.println("Running on Solar");

LDR_value = analogRead(LDR_DN);

Serial.println(LDR_value);

if (LDR_value < 745)
 
{ Serial.print("Night  ");
  value=digitalRead(sensor);
  if(value==1)
  {
    digitalWrite(led,0);
  Serial.print("Motion detected  ");
  Serial.println(value); // Printing output to serial monitor
  //value=0;
  if(fault>820)        //Fault detection
   { Serial.print("                 light is OK");}
  else
   { Serial.print("      FAULT!! Light not getting on  "); }
   value=0;
  }
  else

  {  digitalWrite(led,1);
     Serial.print(" No motion  ");
    Serial.println(value);

   if(fault<821)        //Fault detection
   { Serial.print("                 light is OK");}
  else
   { Serial.print("      FAULT!! Light not getting off  "); }
   
  
  }

}
else
{
 Serial.print("Day  ");
digitalWrite(led,1);
Serial.println(" light is OFF"); 

 if(fault<821)        //Fault detection
   { Serial.print("                 light is OK");}
  else
   { Serial.print("      FAULT!! Light not getting off  "); }
   
}
}
//delay(1000);
}



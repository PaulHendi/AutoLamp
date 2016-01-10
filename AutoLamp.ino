/*
  \brief : 
 \Author : 
 
 */

//#define debug

int sensorPin = 8;    // Movement detector pin
int ledPin = 12;      // Lamp pin
int modepin = 2;      // Mode pin

// variable to store the value coming from the sensor and the switch
int sensorValue = 0;  
int Mode = 0;

// Manage Minimum time Lamp is on
int lampOnTime = 1, countTime = 0;
double loopTime = 0.01;

// Filter parameters
int filterCount = 5, countOne = 0;

// Flag if a human has been detected
int HumanDetected = 0; 

// Lamp Consigne
int lastCns = 0;



// Set up 
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);

  // declare modePin and sensorPin as INPUTS:
  pinMode(modepin,INPUT);
  pinMode(sensorPin,INPUT);

  // Define the serial speed
  Serial.begin(115200);
  

}



// filter if sensor detects human for filterCount consecutives loop => Avoid wrong detections
void filter(int Val)
{
  Val? countOne++:countOne = 0;
  countOne >= filterCount? HumanDetected = 1:HumanDetected = 0;    
}




void loop() {

  // Read modePin and sensorPin values
  Mode = digitalRead(modepin);
  sensorValue = digitalRead(sensorPin);    

  //  Print out mode and humand detection   
  #ifdef debug
      Serial.print("Mode : ");
      Mode? Serial.println("Auto") : Serial.println("Manual");
  #endif


  if (Mode){ // Automatic mode

    filter(sensorValue);
    
    #ifdef debug
      Serial.print("Sensor says : ");
      HumanDetected? Serial.println("Human Detected") : Serial.println("Human not detected");
    #endif

     

    

    if (HumanDetected || Cns)  // If human is detected or was detected 
    {
      Cns = 1;
      countTime++;
    }  
    if ((countTime >= lampOnTime/loopTime) && !HumanDetected){ // If human isn't detected and TimeLampOn > TimeMin 
       Cns = 0;
       countTime = 0;
    }
   
    digitalWrite(ledPin,Cns); // In case human isn't detected and TimeLampOn < TimeMin Cns will be automatically 0 from the last iteration
     

  }

  else digitalWrite(ledPin,HIGH); // Manual mode => usual switch use 
  
  delay(loopTime*1000);                  

}


 
int ledPin = 13;                 // LED connected to digital pin 13
int incomingByte = 0;   // for incoming serial data

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  Serial.begin(38400);
}

void loop()
{
   digitalWrite(ledPin,HIGH );   // sets the LED on
   // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(10000);                  // waits for a second

   if (Serial.available() > 0) {
                  Serial.print("I received: ");
                  
                 digitalWrite(ledPin,LOW );   // sets the LED on
                 delay(10000);  
                delay(1000);
                
                // read the incoming byte:
                incomingByte = Serial.read();
             
     }
}


const int Volt1 = A2;
const int sensorPin1 = A0;
const int Volt2 = A3;
const int sensorPin2 = A1;

int t=0;
float humedad1, humedad2;
float voltaje1, voltaje2;

void setup()
{
     Serial.begin(9600);
}

void loop(){
     int x;
     humedad1, humedad2 = 0;
     voltaje1, voltaje2 = 0;
     for(x=0; x<100; x++){
            delay(10);
            humedad1 = analogRead(sensorPin1) + humedad1;
            voltaje1 = analogRead(Volt1) + voltaje1;
            humedad2 = analogRead(sensorPin2) + humedad2;
            voltaje2 = analogRead(Volt2) + voltaje2;
     
     }
     humedad1 = 100 - humedad1/(1023.);
     voltaje1 = voltaje1*50.0/(1023.0);
     humedad2 = 100 - humedad2/(1023.);
     voltaje2 = voltaje2*50.0/(1023.0);
     
  
     Serial.print(t);
     Serial.print("\t");
     Serial.print(humedad1);
     Serial.print("\t");
     //Serial.print(humedad2);
     //Serial.print("\t");
     Serial.print(voltaje1);
     // Serial.print("\t");
     //Serial.print(voltaje2);
     Serial.print("\n");
     t= t+10;
     delay(9e3);
}

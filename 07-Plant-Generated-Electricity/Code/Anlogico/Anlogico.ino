const int Volt = A1;
const int sensorPin = A0;
int t=0;
unsigned int humedad;
unsigned int voltaje;

void setup()
{
     Serial.begin(9600);
}

void loop(){
     int x;
     humedad = 0;
     voltaje = 0;
     for(x=0; x<100; x++){
            delay(10);
            humedad = analogRead(sensorPin) + humedad;
            voltaje = analogRead(Volt) + voltaje;
     }
     humedad = humedad/(100);
     voltaje = voltaje*5000.0/(100.0*1023.0);
     
  
     Serial.print(t);
     Serial.print("\t");
     Serial.print(humedad);
     Serial.print("\t");
     Serial.print(voltaje);
     Serial.print("\n");
     t= t+10;
     delay(9e3);
}

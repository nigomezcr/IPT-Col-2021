const int sensorPin = 13;
 
void setup()
{
   Serial.begin(9600);
   pinMode(sensorPin, INPUT);
}
 
void loop()
{
   int humedad = digitalRead(sensorPin);
 
   //mandar mensaje a puerto serie en función del valor leido
   if (humedad == HIGH)
   {
      Serial.println("Encendido");   
      //aquí se ejecutarían las acciones
   }
   Serial.print("Paso");
   delay(1000);
}

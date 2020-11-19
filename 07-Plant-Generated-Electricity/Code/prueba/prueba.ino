const int sensorPin = A0;

void setup(){
  Serial.print("Algo\n");
  Serial.begin(9600);
}

void loop(){
  int humedad = analogRead(sensorPin);
  Serial.print("Algo\n");
  Serial.print(humedad);

  Serial.println("Encendido");
  delay(1000);
}

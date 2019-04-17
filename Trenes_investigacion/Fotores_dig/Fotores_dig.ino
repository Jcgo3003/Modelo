const int foto = 11; // Pin analogico 1 para la lectura del Fototransistor
const int OutPin = 2;      // Pin para el led indicador

int sensorValue = 0;        // Inicializamos el valor del sensor

void setup() {
  // Inicializamos la comunicacion serial a 9600 bps:
  Serial.begin(9600); 
  pinMode(OutPin, OUTPUT);
}

void loop() {
  // leemos el pin para y asignamos el valor a la variable.
  sensorValue = digitalRead(foto);            
  Serial.println(sensorValue);
  // Si el valor obtenido es mayor a 900 se activa el LED
  if(sensorValue ==  HIGH )
  {
    digitalWrite(OutPin, HIGH);
    Serial.println("On");
  }
  else
  {
    digitalWrite(OutPin, LOW);
    Serial.println("Off");
  }
   
  delay(100);                     
}

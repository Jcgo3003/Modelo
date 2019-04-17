/* TREN 2 B 
 *  Ahora se puede modificar el tiempo de espera entre cada estacion
 *  
 *  Este tren es lento por eso espera menos tiempo en las estaciones  
Modifique el tiempo de espera a 7 segundos para darle tiempo a los PIR de autoajustarse
*/
#include <IRremote.h>

// Pin de lectura IR 
int ir_su = 9; 
// IR inferior
int ir_inf = A2; 
// Foto resistor inferior
const int foto = A0;
// Motor
const int motor = 3;

/* var de ir remote introduce el pin de lectura*/
IRrecv ir_rec(ir_su);
decode_results resultados;

// Var. para guardar resultados de lectura
int conta = 0;
int ir_res = 0;
int foto_val = 0; 
int ir_val = 0; 
int estado_motor = LOW;

// Var. para guardar el tiempo - Default 9.5 segundos
int tiempo = 7000;

void setup()
{
  // Comienzo serial 
  delay(1000);
  // activa la lectura
  ir_rec.enableIRIn(); 
  // activando salida del led
  pinMode(motor , OUTPUT);
  
}

void loop() {
  // Contador para la recepcion de senal IR del control
  conta++;
  
  if ( (ir_rec.decode(&resultados)) && conta%4 == 0   ) {
      ir_res = resultados.value;

      // Main POWER Volumen X
      if (ir_res == -7651 ){
        
        // Funcion Motor
        if (estado_motor == LOW){    
            estado_motor = HIGH;
            digitalWrite(motor , HIGH);
            
          }
        else{// Si motor prendido apagalo
          estado_motor = LOW;
          digitalWrite(motor , LOW);
          
        }
        
      }
      
      // POWER especifico TREN 2 B   >>
      else if (ir_res == 765 ){
        
        // Funcion Motor
        if (estado_motor == LOW){
            estado_motor = HIGH;
            digitalWrite(motor , HIGH);
          }
        else{// Si led prendido apagalo
          estado_motor = LOW;
          digitalWrite(motor , LOW);
        }
      }
      //////////// TIEMPO ////////////
      // Activando tiempo Minimo de espera
      else if ( ir_res == -8161 ){
          // Tiempo de espera minimo de espera sera 7 segundos
          tiempo = 7000;
      }
      // Activando tiempo normal de espera
      else if ( ir_res == -22441 ){
          // Tiempo de espera minimo de espera sera 9.5 segundos
          tiempo = 9500;
      }
      // Activando tiempo Maximo de espera
      else if ( ir_res == -28561 ){
          // Tiempo de espera minimo de espera sera 12.5 segundos
          tiempo = 12500;
      }

        ir_rec.resume(); // empezamos una nueva recepción
  }

  // Stop en estacion
  foto_val = analogRead(foto);

  if ( (foto_val > 400) && (estado_motor == HIGH)){
    estado_motor = LOW;
    digitalWrite(motor , LOW);

    delay(tiempo);
    estado_motor = HIGH;
    digitalWrite(motor , HIGH);

    delay(1000);
  }

  // Stop cuando cerca de otro tren
  ir_val = analogRead(ir_inf);  

  if ( (ir_val > 800 ) && (estado_motor == HIGH)){
    estado_motor = LOW;
    digitalWrite(motor , LOW);

    delay(2000);
    estado_motor = HIGH;
    digitalWrite(motor , HIGH);

  } 

  if (conta == 50)
    conta = 0;
  
}

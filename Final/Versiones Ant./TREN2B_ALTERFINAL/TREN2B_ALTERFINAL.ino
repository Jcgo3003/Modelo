/* TREN 2 B Este tren es lento por eso espera menos tiempo en las estaciones  
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

      // Main POWER
      if( (ir_res == 28807  ) || (ir_res == 18293) || (ir_res == 13372) ){
        
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
      
      // POWER especifico TREN 2 B
      else if ((ir_res == 10603 ) || (ir_res == 27960)  ){
        
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
        
        ir_rec.resume(); // empezamos una nueva recepción
    
  }

  // Stop en estacion
  foto_val = analogRead(foto);

  if ( (foto_val > 400) && (estado_motor == HIGH)){
    estado_motor = LOW;
    digitalWrite(motor , LOW);

    delay(7000);
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

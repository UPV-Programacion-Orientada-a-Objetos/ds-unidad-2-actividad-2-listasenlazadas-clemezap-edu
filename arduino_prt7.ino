/**
 * @file arduino_prt7.ino
 * @brief Código Arduino para enviar tramas PRT-7 por puerto serial
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 * 
 * Este código debe cargarse en el Arduino para simular el envío de tramas
 * del protocolo PRT-7 según el ejemplo del README.
 */

// Tramas a enviar según el ejemplo del README
const char* tramas[] = {
  "L,H",
  "L,O",
  "L,L",
  "M,2",
  "L,A",
  "L,Space",
  "L,W",
  "M,-2",
  "L,O",
  "L,R",
  "L,L",
  "L,D"
};

const int numTramas = 12;
int indiceActual = 0;

void setup() {
  // Inicializar comunicación serial a 9600 baudios
  Serial.begin(9600);
  
  // Esperar a que el puerto serial esté listo
  while (!Serial) {
    ; // Esperar
  }
  
  delay(2000); // Espera inicial
}

void loop() {
  if (indiceActual < numTramas) {
    // Enviar la trama actual
    Serial.println(tramas[indiceActual]);
    
    // Avanzar al siguiente índice
    indiceActual++;
    
    // Esperar 1 segundo antes de la siguiente trama
    delay(1000);
  } else {
    // Reiniciar el ciclo después de una pausa más larga
    delay(5000);
    indiceActual = 0;
  }
}
#include <Arduino_LSM9DS1.h>

// Crear una instancia para el sensor BMM150 (que usa I2C)

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Magnetic Field in uT");
  Serial.println("X\tY\tZ");
}

void loop() {
  // Leer los datos magnéticos del sensor
  float x, y, z;
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(x, y, z);

    // Mostrar los valores de los ejes magnéticos
    Serial.print("X: "); Serial.print(x);
    Serial.print(" Y: "); Serial.print(y);
    Serial.print(" Z: "); Serial.println(z);

    // Determinar la dirección cardinal
    String direccion = determinarDireccion(x, y);
    Serial.print("Dirección: ");
    Serial.println(direccion);

    delay(500);
  }
}

// Función para determinar la dirección cardinal
String determinarDireccion(float x, float y) {
  // Norte
  if (y > x && y > -x + 20) {
    return "Norte";
  }
  // Este
  else if (x > y && x > -y + 20) {
    return "Este";
  }
  // Sur
  else if (y < x && y < -x + 20) {
    return "Sur";
  }
  // Oeste
  else if (x < y && x < -y + 20) {
    return "Oeste";
  }
  // Este punto no debería alcanzarse debido a la lógica ajustada
  return "Error";
}

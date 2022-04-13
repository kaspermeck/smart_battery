#include <Arduino_LSM9DS1.h>

float x, y, z, i;
enum sensors{ACCEL, GYRO, CURRENT} sensor=ACCEL;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println("Acceleration in G's");
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println("Gyroscope in degrees/second");
  Serial.println();
}

void loop() {
  if (IMU.accelerationAvailable() && sensor == ACCEL) {
    IMU.readAcceleration(x, y, z);
    Serial.print("Accel: x: ");
    Serial.print(x);
    Serial.print("\t");
    Serial.print("y: ");
    Serial.print(y);
    Serial.print("\t");
    Serial.print("z: ");
    Serial.println(z);
    sensor = GYRO;
  }

  if (IMU.gyroscopeAvailable() && sensor == GYRO) {
    IMU.readGyroscope(x, y, z);
    Serial.print("Gyro : x: ");
    Serial.print(x);
    Serial.print("\t");
    Serial.print("y: ");
    Serial.print(y);
    Serial.print("\t");
    Serial.print("z: ");
    Serial.println(z);
    sensor = CURRENT;
  }

  if (sensor == CURRENT) {
    // Current sensor not yet build in hardware
    i = 0;
    Serial.print("Current - ");
    Serial.println(i);
    sensor = ACCEL;
  }
}
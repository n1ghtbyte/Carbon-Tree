void setup() {
Serial.begin(9600);
}

void loop() {
float sensor_NO2 = analogRead(A1);
sensor_NO2 = sensor_NO2 / 409.2;

float sensor_CO = analogRead(A2);
sensor_CO = 3.027 * exp(1.0698 * (sensor_CO * (5.0 / 1024)));

float sensor_CO2 = analogRead(A3);
sensor_CO2 = sensor_CO2 * (5000 / 1024.0);

Serial.println(sensor_NO2);
Serial.println(sensor_CO);
Serial.println(sensor_CO2);

delay(12000);
}

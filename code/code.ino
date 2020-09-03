#include <LiquidCrystal.h>

// 0x42 + 31 bytes equal to 32 bytes
#define LENG 31
unsigned char buf[LENG];

// NO2 sensor pin
int NO2_In = A1;
// CO sensor pin
int CO_In = A2;
// CO2 sensor pin
int CO2_In = A3;

// Variable to store the value comming from the analog pin
float raw_NO2 = 0;
// Variable to store the value coming from the analog pin
int raw_CO2 = 0;
// Variable to store the value coming from the analog pin
int raw_CO = 0;

// --> WHY IS "raw_NO2" FLOAT BUT "raw_CO2" & "raw_CO" INT??? <--

// NO2 Sensor Resistance
float NO2_R = 0;
// NO2 ppb value
float NO2_ppb = 0;

// Define PM1.0 value of the air detector module
int PM01Value = 0;
// Define PM2.5 value of the air detector module
int PM2_5Value = 0;
// Define PM10 value of the air detector module
int PM10Value = 0;

// Select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Variable for the time ON first screen
unsigned long screen1Timer = 0;
// Variable for the time ON second screen
unsigned long screen2Timer = 0;
// Variable for the time ON third screen
unsigned long screen3Timer = 0;
// Variable for time exhibition between screens
unsigned long interval = 3000;
// Variable to force first screen
bool secreen1 = true;
// Variable to force second screen
bool screen2 = false;
// Variable to force third screen
bool screen3 = false;

void setup()
{
  // Start the LCD library
  lcd.begin(16, 2);
  // Clean the display before write
  lcd.clear();
  // Message to show
  lcd.print("Medidor Ambiente");
  //time to wait so you can read the message
  delay(interval);

  // Set the default voltage for reference voltage
  analogReference(DEFAULT);

  // Start the Serial comunication with the PM2.5
  Serial.begin(9600);
  // If it does not start ignore
  Serial.setTimeout(1500);
  // Print a first message to Serial Monitor
  Serial.println("BEGINNING DATA MEASUREMENTS");
}

void loop()
{
  // Read the analog in value
  raw_NO2 = analogRead(NO2_In);
  // Conversion formula
  float NO2_Volt = raw_NO2 / 409.2;
  // Find sensor resistance from No2_Volt, using 5V input & 22kOhm load resistor
  NO2_R = 22000 / ((5 / NO2_Volt) - 1);
  // Convert Rs to ppb (parts per billion) concentration of NO2
  NO2_ppb = (.000008 * NO2_R - .0194) * 1000;

  // Read the analog in value
  raw_CO2 = analogRead(CO2_In);
  // Conversion formula
  double CO2_Volt = raw_CO2 * (5000 / 1024.0);
  // Read the analog in value
  raw_CO = analogRead(CO_In);
  // Conversion formula
  double CO_ppm = 3.027 * exp(1.0698 * (raw_CO * (5.0 / 1024)));

  // Look for the 0x42 in the Serial port
  if (Serial.find(0x42))
  {
    // Load the buf with the values
    Serial.readBytes(buf, LENG);

    if (buf[0] == 0x4d)
    {
      if (checkValue(buf, LENG))
      {
        // Count PM1.0 value of the air detector module
        PM01Value = transmitPM01(buf);
        // Count PM2.5 value of the air detector module
        PM2_5Value = transmitPM2_5(buf);
        // Count PM10 value of the air detector module
        PM10Value = transmitPM10(buf);
      }
    }
  }

  if ((millis() - screen1Timer > interval) && secreen1)
  {
    // Load the millis time to the screen2Timer variable
    screen2Timer = millis();
    // Clean the display before write
    lcd.clear();

    secreen1 = false;
    screen2 = true;
    screen3 = false;

    if (CO2_Volt == 0)
    {
      // Message to show
      lcd.print("CO2: ");
      // Message to show
      lcd.print("Fault");
    }

    if (CO2_Volt < 400)
    {
      // Message to show
      lcd.print("CO2: ");
      // Message to show
      lcd.print("preheating");
    }

    else
    {
      int voltage_diference = CO2_Volt - 400;

      // Auxiliar calculation
      float concentration = voltage_diference * (50.0 / 16.0);

      // Message to show
      lcd.print("CO2: ");
      // Print the results to the lcd
      lcd.print(concentration);
      // Message to show
      lcd.print(" ppm");

      // Print the previous CO2 messages/results on Serial Monitor
      Serial.print("CO2: ");
      Serial.print(concentration);
      Serial.println("ppm");
    }

    // Set the LCD cursor position first column(0) and second line(1)
    lcd.setCursor(0, 1);
    // Message to show
    lcd.print("CO: ");
    // Print the results to the lcd
    lcd.print(CO_ppm);
    // Message to show
    lcd.print(" ppm");

    // Print the previous CO messages/results on Serial Monitor
    Serial.print("CO: ");
    Serial.print(CO_ppm);
    Serial.println("ppm");
  }

  if ((millis() - screen2Timer > interval) && screen2)
  {
    //load the millis time to the screen3Timer variable
    screen3Timer = millis();
    //clean the display before write
    lcd.clear();

    secreen1 = false;
    screen2 = false;
    screen3 = true;

    // Message to show
    lcd.print("PM1.0: ");
    // Print the results to the lcd
    lcd.print(PM01Value);
    // Message to show
    lcd.print(" ug/m3");

    // Print the previous PM1.0 messages/results on Serial Monitor
    Serial.print("PM1.0: ");
    Serial.print(PM01Value);
    Serial.println(" ug/m3");

    // Set the LCD cursor position first column(0) and second line(1)
    lcd.setCursor(0, 1);

    // Message to show
    lcd.print("PM2.5: ");
    // Print the results to the lcd
    lcd.print(PM2_5Value);
    // Message to show
    lcd.print(" ug/m3");

    // Print the previous PM2.5 messages/results on Serial Monitor
    Serial.print("PM2.5: ");
    Serial.print(PM2_5Value);
    Serial.println("  ug/m3");
  }

  if ((millis() - screen3Timer > interval) && screen3)
  {
    // Load the millis time to the screen1Timer variable
    screen1Timer = millis();

    // Clean the display before write
    lcd.clear();

    secreen1 = true;
    screen2 = false;
    screen3 = false;

    // Message to show
    lcd.print("PM10: ");
    // Print the results to the lcd
    lcd.print(PM10Value);
    // Message to show
    lcd.print(" ug/m3");

    // Print the previous PM10 messages/results on Serial Monitor
    Serial.print("PM10: ");
    Serial.print(PM10Value);
    Serial.println(" ug/m3");

    // Set the LCD cursor position first column(0) and second line(1)
    lcd.setCursor(0, 1);
    // Message to show
    lcd.print("NO2: ");
    // Print the results to the lcd
    lcd.print(NO2_ppb);
    // Message to show
    lcd.print(" ppb");

    // Print the previous NO2 messages/results on Serial Monitor
    Serial.print("NO2: ");
    Serial.print(NO2_ppb);
    Serial.println(" ppb");
    Serial.println();
    Serial.println();
  }
}

// Subroutines for PM2.5 sensor
char checkValue(unsigned char *thebuf, char leng)
{
  char receiveflag = 0;
  int receiveSum = 0;

  for (int i = 0; i < (leng - 2); i++)
  {
    receiveSum = receiveSum + thebuf[i];
  }
  receiveSum = receiveSum + 0x42;

  // Check the serial data
  if (receiveSum == ((thebuf[leng - 2] << 8) + thebuf[leng - 1]))
  {
    receiveSum = 0;
    receiveflag = 1;
  }
  return receiveflag;
}

int transmitPM01(unsigned char *thebuf)
{
  int PM01Val;
  // Count PM1.0 value of the air detector module
  PM01Val = ((thebuf[3] << 8) + thebuf[4]);
  return PM01Val;
}

// Transmit PM Value to PC
int transmitPM2_5(unsigned char *thebuf)
{
  int PM2_5Val;
  // Count PM2.5 value of the air detector module
  PM2_5Val = ((thebuf[5] << 8) + thebuf[6]);
  return PM2_5Val;
}

// Transmit PM Value to PC
int transmitPM10(unsigned char *thebuf)
{
  int PM10Val;
  // Count PM10 value of the air detector module
  PM10Val = ((thebuf[7] << 8) + thebuf[8]);
  return PM10Val;
}

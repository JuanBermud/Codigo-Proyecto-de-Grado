#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int VOLTAGE_SENSOR_PIN = A0;
const int CURRENT_SENSOR_PIN = A1;
#define ONE_WIRE_BUS 4

const float VOLTAGE_REFERENCE = 5.0;
const float VOLTAGE_SENSOR_MAX = 25.0;
const float ADC_RESOLUTION = 1023.0;
const float CURRENT_SENSOR_SENSITIVITY = 0.040;
const float ZERO_CURRENT_VOLTAGE = 2.480;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);
LiquidCrystal_I2C lcd(0x3f, 20, 4);

float last_tempC = -127.0;

void setup() {
  Serial.begin(9600);
  pinMode(VOLTAGE_SENSOR_PIN, INPUT);
  pinMode(CURRENT_SENSOR_PIN, INPUT);
  tempSensors.begin();
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alternador Monitor:");
}

void loop() {
  int adc_voltage_value = analogRead(VOLTAGE_SENSOR_PIN);
  float measured_voltage = adc_voltage_value * (VOLTAGE_SENSOR_MAX / ADC_RESOLUTION);
  int adc_current_value = analogRead(CURRENT_SENSOR_PIN);
  float current_sensor_voltage = adc_current_value * (VOLTAGE_REFERENCE / ADC_RESOLUTION);
  float measured_current = (current_sensor_voltage - ZERO_CURRENT_VOLTAGE) / CURRENT_SENSOR_SENSITIVITY;

  tempSensors.requestTemperatures();
  float current_tempC = tempSensors.getTempCByIndex(0);
  if (current_tempC != DEVICE_DISCONNECTED_C && current_tempC > -55.0 && current_tempC < 125.0) {
    last_tempC = current_tempC;
  }

  lcd.setCursor(0, 1);
  lcd.print("Voltaje: ");
  lcd.print(measured_voltage, 2);
  lcd.print(" V    ");
  lcd.setCursor(0, 2);
  lcd.print("Corriente:");
  lcd.print(measured_current, 1);
  lcd.print(" A   ");
  lcd.setCursor(0, 3);
  lcd.print("Temp: ");
  if (last_tempC != DEVICE_DISCONNECTED_C) {
    lcd.print(last_tempC, 1);
    lcd.print((char)223);
    lcd.print("C   ");
  } else {
    lcd.print("Error   ");
  }

  Serial.print("V_ADC: "); Serial.print(adc_voltage_value);
  Serial.print(" | Voltaje: "); Serial.print(measured_voltage, 2); Serial.print(" V");
  Serial.print(" | I_ADC: "); Serial.print(adc_current_value);
  Serial.print(" | I_Volt: "); Serial.print(current_sensor_voltage, 3);
  Serial.print(" | Corriente: "); Serial.print(measured_current, 2); Serial.print(" A");
  Serial.print(" | Temp: ");
  if (last_tempC != DEVICE_DISCONNECTED_C) {
    Serial.print(last_tempC, 1); Serial.println(" C");
  } else {
    Serial.println("Error C");
  }

  delay(500);
}
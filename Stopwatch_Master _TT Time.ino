/*
 * Arduino Stopwatch Master for TT Time Totalizer Calibration
 * 
 * This code creates a precision voltage-triggered stopwatch for calibrating
 * Time Totalizer (TT) devices. The system automatically starts timing when
 * input voltage exceeds 4V threshold and stops when voltage drops below.
 * 
 * Features:
 * - Voltage-triggered automatic operation
 * - Millisecond precision timing display
 * - I2C LCD interface for clear readout
 * - Designed for industrial calibration workflows
 * 
 * Hardware:
 * - Arduino Uno/Nano/Pro Mini
 * - 16x2 I2C LCD (0x27 address)
 * - Voltage input on A0 pin
 * 
 * Author: Puneet
 * Version: 1.0
 * Date: June 2025
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (address 0x27, 16 chars, 2 lines)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int voltagePin = A0;    // Analog pin for voltage reading

// Variables for time tracking
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
boolean isRunning = false;

// Time components for display formatting
int hours, minutes, seconds, milliseconds;

// Voltage threshold for trigger (4V)
const float voltageThreshold = 4.0;

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  // Setup analog pin for voltage input
  pinMode(voltagePin, INPUT);
  
  // Display initial status
  lcd.setCursor(0, 0);
  lcd.print("Waiting for 4V");
  lcd.setCursor(0, 1);
  lcd.print("00:00:00.000");
  
  // Optional: Initialize serial for debugging
  // Serial.begin(9600);
  // Serial.println("Stopwatch Master Ready");
}

void loop() {
  // Read voltage from analog pin (0-1023 maps to 0-5V)
  float voltage = (analogRead(voltagePin) * 5.0) / 1023.0;
  
  // Check if voltage exceeds threshold to start timing
  if (voltage >= voltageThreshold) {
    if (!isRunning) {
      // Start timer if it wasn't already running
      isRunning = true;
      startTime = millis() - elapsedTime;  // Account for any previous elapsed time
      
      // Update display status
      lcd.setCursor(0, 0);
      lcd.print("Timer Running   ");
      
      // Optional: Serial debug output
      // Serial.println("Timer Started");
    }
  } else {
    if (isRunning) {
      // Stop timer if voltage drops below threshold
      isRunning = false;
      
      // Update display status
      lcd.setCursor(0, 0);
      lcd.print("Timer Stopped   ");
      
      // Optional: Serial debug output
      // Serial.print("Timer Stopped - Final Time: ");
      // Serial.println(formatTime(elapsedTime));
    }
  }
  
  // Update elapsed time calculation if timer is running
  if (isRunning) {
    elapsedTime = millis() - startTime;
    
    // Convert milliseconds to time components
    hours = (elapsedTime / 3600000) % 100;    // Limit to 99 hours max
    minutes = (elapsedTime / 60000) % 60;     // Minutes (0-59)
    seconds = (elapsedTime / 1000) % 60;      // Seconds (0-59)
    milliseconds = elapsedTime % 1000;        // Milliseconds (0-999)
    
    // Update time display on second line
    updateTimeDisplay();
  }
  
  // Small delay to prevent excessive LCD updates
  delay(10);
}

/*
 * Update the LCD display with current time in HH:MM:SS.mmm format
 */
void updateTimeDisplay() {
  lcd.setCursor(0, 1);
  
  // Display hours (00-99)
  if (hours < 10) lcd.print("0");
  lcd.print(hours);
  lcd.print(":");
  
  // Display minutes (00-59)
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  
  // Display seconds (00-59)
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print(".");
  
  // Display milliseconds (000-999)
  if (milliseconds < 100) lcd.print("0");
  if (milliseconds < 10) lcd.print("0");
  lcd.print(milliseconds);
}

/*
 * Optional: Format time as string for serial output
 * Uncomment if using serial debugging
 */
/*
String formatTime(unsigned long timeMs) {
  int h = (timeMs / 3600000) % 100;
  int m = (timeMs / 60000) % 60;
  int s = (timeMs / 1000) % 60;
  int ms = timeMs % 1000;
  
  String timeStr = "";
  if (h < 10) timeStr += "0";
  timeStr += String(h) + ":";
  if (m < 10) timeStr += "0";
  timeStr += String(m) + ":";
  if (s < 10) timeStr += "0";
  timeStr += String(s) + ".";
  if (ms < 100) timeStr += "0";
  if (ms < 10) timeStr += "0";
  timeStr += String(ms);
  
  return timeStr;
}
*/

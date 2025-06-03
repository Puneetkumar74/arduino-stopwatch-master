# Installation Guide - Arduino Stopwatch Master

## Prerequisites

### Required Software
- Arduino IDE (version 1.8.13 or newer)
- USB drivers for your Arduino board
- Git (optional, for cloning repository)

### Required Hardware
- Arduino Uno, Nano, or Pro Mini
- 16x2 I2C LCD Display
- Breadboard or PCB for connections
- Jumper wires or hookup wire
- USB cable for Arduino programming

### Required Libraries
- Wire.h (included with Arduino IDE)
- LiquidCrystal_I2C library

## Step-by-Step Installation

### 1. Download the Project

#### Option A: Download ZIP from GitHub
1. Go to the project repository on GitHub
2. Click "Code" → "Download ZIP"
3. Extract to your Arduino sketches folder
4. Rename folder to `arduino-stopwatch-master`

#### Option B: Clone with Git
```bash
git clone https://github.com/yourusername/arduino-stopwatch-master.git
cd arduino-stopwatch-master
```

### 2. Install Arduino IDE

#### Windows
1. Download from [arduino.cc](https://www.arduino.cc/en/software)
2. Run installer as administrator
3. Install USB drivers when prompted
4. Launch Arduino IDE

#### macOS
1. Download .dmg file from arduino.cc
2. Drag Arduino to Applications folder
3. Launch and allow security permissions
4. Install any prompted drivers

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install arduino
# Or download latest version from arduino.cc
```

### 3. Install Required Libraries

#### Method 1: Library Manager (Recommended)
1. Open Arduino IDE
2. Go to **Sketch** → **Include Library** → **Manage Libraries**
3. Search for "LiquidCrystal I2C"
4. Install "LiquidCrystal I2C by Frank de Brabander"
5. Click "Install" and wait for completion

#### Method 2: Manual Installation
1. Download library ZIP from GitHub
2. Go to **Sketch** → **Include Library** → **Add .ZIP Library**
3. Select the downloaded ZIP file
4. Restart Arduino IDE

### 4. Hardware Assembly

#### Basic Breadboard Setup
```
Components needed:
- Arduino Uno
- 16x2 I2C LCD
- Breadboard
- 4 jumper wires (male-to-male)
- 2 jumper wires (male-to-female) for voltage input
```

#### Connection Steps
1. **Power the breadboard:**
   - Connect Arduino 5V to breadboard power rail (red)
   - Connect Arduino GND to breadboard ground rail (black)

2. **Connect the LCD:**
   ```
   LCD Pin → Arduino Pin
   VCC     → 5V (red wire)
   GND     → GND (black wire)  
   SDA     → A4 (blue wire)
   SCL     → A5 (yellow wire)
   ```

3. **Prepare voltage input:**
   - Connect wire to Arduino A0 pin
   - Add connector for TT device input
   - Ensure common ground connection

#### Verify Connections
Use multimeter to check:
- Continuity between corresponding pins
- 5V present at LCD VCC pin
- Ground continuity throughout circuit

### 5. Software Configuration

#### Load the Code
1. Open Arduino IDE
2. File → Open → Navigate to `Stopwatch_Master.ino`
3. Code should load in the editor

#### Configure Settings (if needed)
```cpp
// Adjust these values if required:
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change address if different
const float voltageThreshold = 4.0;   // Adjust trigger voltage
```

#### Find LCD I2C Address (if needed)
If LCD doesn't work, find its address:

1. Upload this I2C scanner code:
```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;
  
  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }
  
  if (nDevices == 0) Serial.println("No I2C devices found");
  delay(5000);
}
```

2. Open Serial Monitor (Tools → Serial Monitor)
3. Note the address displayed (usually 0x27 or 0x3F)
4. Update the main code with correct address

### 6. Upload and Test

#### Upload Process
1. Connect Arduino to computer via USB
2. Select board: **Tools** → **Board** → **Arduino Uno**
3. Select port: **Tools** → **Port** → **COM3** (Windows) or **/dev/ttyUSB0** (Linux)
4. Click **Upload** button (→)
5. Wait for "Done uploading" message

#### Initial Test
1. LCD should display:
   ```
   Waiting for 4V
   00:00:00.000
   ```

2. Touch a wire from 5V pin to A0 pin briefly
3. Display should change to:
   ```
   Timer Running
   00:00:01.234
   ```

4. Remove the wire, display should show:
   ```
   Timer Stopped
   00:00:01.234
   ```

### 7. Enclosure Assembly (Optional)

#### Recommended Enclosure
- Plastic project box: 120mm x 80mm x 60mm
- Clear acrylic front panel for LCD viewing
- Ventilation holes for heat dissipation

#### Panel Cutouts
1. **LCD Window**: 71mm x 24mm rectangle
2. **USB Access**: 12mm x 8mm for programming
3. **Voltage Input**: 8mm hole for connector
4. **Power LED**: 5mm hole (optional)

#### Mounting
- Use M3 screws for Arduino mounting
- Double-sided tape for LCD module
- Cable strain relief for external connections

### 8. Calibration Verification

#### Quick Accuracy Check
1. Use smartphone stopwatch as reference
2. Start both timers simultaneously
3. Stop after exactly 60 seconds
4. Compare readings (should be within ±0.1 seconds)

#### Professional Calibration
For critical applications:
- Use NIST-traceable time standard
- Document environmental conditions
- Perform multiple test intervals
- Calculate and document accuracy specifications

## Troubleshooting Installation Issues

### Arduino Not Recognized
**Windows:**
- Install CH340 or FTDI drivers
- Check Device Manager for USB serial device
- Try different USB cable

**macOS:**
- Allow driver installation in Security preferences
- Check USB cable and port

**Linux:**
- Add user to dialout group: `sudo usermod -a -G dialout $USER`
- Log out and back in
- Check permissions: `ls -l /dev/ttyUSB*`

### Compilation Errors
```
Error: Library not found
Solution: Reinstall LiquidCrystal_I2C library

Error: Board not selected
Solution: Tools → Board → Arduino Uno

Error: Port not available
Solution: Check USB connection and driver installation
```

### LCD Display Issues
```
Problem: Blank display
Check: Power connections (5V and GND)
Check: I2C wiring (SDA to A4, SCL to A5)
Check: LCD address in code

Problem: Garbage characters
Check: I2C address (try 0x3F instead of 0x27)
Check: Power supply stability
Check: Wire connections for shorts
```

## Post-Installation Checklist

- [ ] Arduino powers on (LED indicator lit)
- [ ] LCD displays startup message
- [ ] Timer responds to voltage input on A0
- [ ] Time display updates smoothly
- [ ] All connections are secure
- [ ] Enclosure assembled (if applicable)
- [ ] Documentation and calibration records

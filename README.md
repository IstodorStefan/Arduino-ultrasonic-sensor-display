##Arduino Radar System with OLED Display & Dual Modes 

Arduino Uno R4 WiFi project featuring a sonar system with two operating modes:
1. Radar sweep mode with real-time visualization in Processing  
2. Parking sensor mode with wave animation on an OLED display  

Both modes are controlled using a button and integrated into a single codebase.

A simple radar system built using Arduino, an ultrasonic sensor, and a servo motor.
The system scans the environment and detects objects in real time, displaying the results both on a small OLED screen and a custom Processing interface.

#🚀 Features
Real-time object detection
Rotating radar using servo motor
Distance measurement with ultrasonic sensor
Live visualization on PC (Processing)
OLED display for distance feedback

#🛠️ Hardware Components
Arduino Uno
HC-SR04 Ultrasonic Sensor
Servo Motor (SG90)
OLED Display (I2C)
Breadboard + wires

#💻 Software
Arduino IDE (C++)
Processing (for radar visualization)

#🎥 Demo Video

[Watch the demo](https://youtube.com/shorts/XGlyk4Z_kOk)

#📷 Project Preview

<p align="center">
  <img src="20260401_223541 (2).jpg" width="300" height="400"/>
  <img src="20260401_223607 (2).jpg" width="300" height="400"/>
</p>

#⚙️ How It Works

Mode 1: The ultrasonic sensor measures the distance to nearby objects while the servo motor rotates, scanning the area.
The Arduino sends the data to a Processing application, which displays a radar-like visualization in real time.
Mode 2: The ultrasonic sensor stays still while the OLED keeps displaying the distance via a wave animation and a live Dist. tracker.

#▶️ How to Run

Upload the Arduino code to your board
Connect all components as shown
Run the Processing sketch
Open the correct COM port
Watch the radar in action


#📌Improvements

Feel free to suggest improvements or optimizations!



👨‍💻 Author
Istodor Stefan-Valentin 

# Arduino-ultrasonic-sensor-display
Arduino Uno R4 WiFi. Radar sweep mode in Processing that activates when I press a button. Second Mode: parking sensor with a wave animation on the small OLED display. Both modes are integrated into a single codebase. I also have a video demonstrating how the servo motor and ultrasonic sensor work and how the modes switch with a button press.


A simple radar system built using Arduino, an ultrasonic sensor, and a servo motor.
The system scans the environment and detects objects in real time, displaying the results both on a small OLED screen and a custom Processing interface.

🚀 Features
Real-time object detection
Rotating radar using servo motor
Distance measurement with ultrasonic sensor
Live visualization on PC (Processing)
OLED display for distance feedback

🛠️ Hardware Components
Arduino Uno
HC-SR04 Ultrasonic Sensor
Servo Motor (SG90)
OLED Display (I2C)
Breadboard + wires

💻 Software
Arduino IDE (C++)
Processing (for radar visualization)
🎥 Demo Video

https://youtube.com/shorts/XGlyk4Z_kOk


📷 Images



⚙️ How It Works

The ultrasonic sensor measures the distance to nearby objects while the servo motor rotates, scanning the area.
The Arduino sends the data to a Processing application, which displays a radar-like visualization in real time.

▶️ How to Run
Upload the Arduino code to your board
Connect all components as shown
Run the Processing sketch
Open the correct COM port
Watch the radar in action
📌 Future Improvements
Better accuracy (filtering noise)
3D printed case
Wireless version (Bluetooth/WiFi)
Faster scanning
👨‍💻 Author

Your Name

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

// --- Pin definitions ---
const int trigPin = 9, echoPin = 10, servoPin = 11;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// --- Display and servo objects ---
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo myServo;

// --- Radar center and servo movement ---
int cx = 64, cy = 63;
int angle = 0, direction = 1;

// --- Distance measurement variables ---
float duration, distanceCM;

// --- Button for toggling sweep mode ---
const int buttonPIN = 2;
bool lastButtonState = HIGH;
bool sweepMode = false;

void setup() {
  Serial.begin(9600);

  // --- Initialize pins ---
  pinMode(buttonPIN, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin); // attach servo
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // --- Draw radar frame once on startup ---
  for(int i=0; i<=40; i+=10) drawArc(cx, cy, i, 45, 135, SSD1306_WHITE);
  drawRadialLine(cx, cy, 45, 45);
  drawRadialLine(cx, cy, 45, 135);
  display.display();

  // --- Display initial distance text ---
  display.fillRect(0,0,128,20,SSD1306_BLACK);
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.print("Dist: "); display.print((int)distanceCM); display.println("cm");
  display.display();
}

void loop() {
  // --- HC-SR04 distance reading ---
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000); // read echo pulse duration
  distanceCM = (duration*0.034)/2;           // convert to cm
  if(distanceCM<2) distanceCM=2;            // minimum distance clamp
  if(distanceCM>99) distanceCM=99;        // maximum distance clamp

  // --- Check button press to toggle sweep mode ---
  bool currentState = digitalRead(buttonPIN);
  if (currentState == LOW && lastButtonState == HIGH) {
    sweepMode = !sweepMode;
  }
  lastButtonState = currentState;

  if(sweepMode){
    // --- Sweep servo back and forth ---
    myServo.write(angle);
    if(angle>=180) direction=-1;
    if(angle<=0) direction=1;
    angle+=direction;

    // --- Print servo angle and distance for debugging ---
    Serial.print(angle); Serial.print(" | "); Serial.println((int)distanceCM);

    // --- Clear display while sweeping ---
    display.clearDisplay();
    display.display();

  } else {
    angle=90; myServo.write(angle); // keep servo centered in normal mode

    // --- Display distance value ---
    display.fillRect(0,0,128,20,SSD1306_BLACK);
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.print("Dist: "); display.print((int)distanceCM); display.println("cm");
    display.display();

    // --- Draw radar arcs depending on distance ---
    if(distanceCM <= 10){
      drawAreaArc(cx, cy, 1, 9, 46, 134, SSD1306_WHITE);
      drawAreaArc(cx, cy, 1, 9, 46, 134, SSD1306_BLACK);
    } else if(distanceCM <= 20){
      drawAreaArc(cx, cy, 11,19,46,134,SSD1306_WHITE);
      drawAreaArc(cx, cy, 11,19,46,134,SSD1306_BLACK);
    } else if(distanceCM <= 30){
      drawAreaArc(cx, cy, 21,29,46,134,SSD1306_WHITE);
      drawAreaArc(cx, cy, 21,29,46,134,SSD1306_BLACK);
    } else if(distanceCM <= 40){
      drawAreaArc(cx, cy, 31,39,46,134,SSD1306_WHITE);
      drawAreaArc(cx, cy, 31,39,46,134,SSD1306_BLACK);
    }
  }
}

// --- Draw a single arc with given radius and angles ---
void drawArc(int x0,int y0,int radius,int startAngle,int endAngle,int color){
  for(int a=startAngle;a<=endAngle;a++){
    float rad = a*3.14159/180.0;
    display.drawPixel(x0+radius*cos(rad), y0-radius*sin(rad), color);
  }
}

// --- Draw a radial line from center at a given angle ---
void drawRadialLine(int x0,int y0,int radius,int angle){
  float rad = angle*3.14159/180.0;
  display.drawLine(x0,y0,x0+radius*cos(rad),y0-radius*sin(rad),SSD1306_WHITE);
}

// --- Draw a filled area arc for radar display ---
void drawAreaArc(int x0,int y0,int minR,int maxR,int startAngle,int endAngle,int color){
  for(int r=minR;r<=maxR;r++){
    drawArc(cx,cy,r,startAngle,endAngle,color);       // draw arc line
    drawRadialLine(cx,cy,45,45); drawRadialLine(cx,cy,45,135); // redraw radar frame
    display.display();
    for(int i=0;i<=40;i+=10) drawArc(x0,y0,i,45,135,SSD1306_WHITE); // redraw circles
  }
}
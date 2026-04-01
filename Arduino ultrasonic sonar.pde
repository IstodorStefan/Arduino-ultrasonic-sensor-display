import processing.serial.*;

Serial myPort;
float angle = 0; 
float distance = 0;

float maxRadarRadius = 40; // Max distance the radar can scan (cm)
float scaleFactor = 10;    // Conversion: 1 cm = 10 pixels

void setup() {
  
  
  myPort = new Serial(this, "COM3", 9600); // COM port for Arduino
  myPort.bufferUntil('\n'); 
  size(1000, 1000); //Window size
  
}
void radarMAP(float cx, float cy, float maxRadiusPix) // Draws the radar arcs, guiding lines, and distance labels
{
  pushMatrix();
  noFill();
  strokeWeight(1);
  stroke(255);

  arc(cx, cy, maxRadiusPix*2, maxRadiusPix*2,PI, TWO_PI);
  arc(cx, cy, maxRadiusPix*1.5, maxRadiusPix*1.5,PI, TWO_PI);
  arc(cx, cy, maxRadiusPix, maxRadiusPix,PI, TWO_PI);
  arc(cx, cy, maxRadiusPix*0.5, maxRadiusPix*0.5,PI, TWO_PI);
 for(int a = 0; a <= 180; a += 30){
  float x = cx + maxRadiusPix * cos(radians(a));
  float y = cy - maxRadiusPix * sin(radians(a));
  line(cx, cy, x, y);
  fill(255); 
textSize(18);
textAlign(CENTER, TOP); 
  float Offset = 50;
  text(a + "°", x + cos(radians(a)) * Offset, y - sin(radians(a)) * Offset);
  
}
fill(255); 
textSize(18);
textAlign(LEFT, CENTER); 


float yOffset = 10;


for (int i = 1; i <= 4; i++) {
  float r = (maxRadiusPix / 4) * i; 
  text(i*10 + "cm", cx + r, cy + yOffset);
}

  popMatrix();
  
}

void draw() {
  // Center of radar
  fill(0, 15); 
  noStroke();
  rect(0, 0, width, height);
  // Center of radar
  float centerX = width/2; 
  float centerY = height/2;

  
  float maxRadiusPix = maxRadarRadius * scaleFactor;
  // End point of radar sweep line
  float xEnd = centerX + maxRadiusPix * cos(radians(angle));
  float yEnd = centerY - maxRadiusPix * sin(radians(angle));

  
  float objectDistance = min(distance, maxRadarRadius); 
  // Object position
  float objX = centerX + objectDistance * scaleFactor * cos(radians(angle));
  float objY = centerY - objectDistance * scaleFactor * sin(radians(angle));

  // Now we draw a green line to the object
  stroke(0, 255, 0);
  line(centerX, centerY, objX, objY);

  // Now we draw a red line until the end of the radar coordonates if the object is in range
  if(distance < maxRadarRadius){
    stroke(255, 0, 0); 
    line(objX, objY, xEnd, yEnd);
  }
  radarMAP(centerX,centerY, maxRadiusPix); // We call the radarMap function for the text and guiding lines
  textAlign(CENTER,TOP);
  text("Distance: ", centerX - 40, centerY + 10); // This just show the distance that we got form the sensor to the object 
  text(objectDistance + "cm", centerX + 30, centerY + 10); 

}



void serialEvent(Serial p)  // This function pulls the data form the Arduino and splits it in two the angle and the distance 
{
  String data = p.readStringUntil('\n');
  if(data != null){
    data = trim(data);
    String[] parts = split(data, '|');
    if(parts.length == 2){
      angle = float(parts[0]);
      distance = float(parts[1]);
    }
  }
}

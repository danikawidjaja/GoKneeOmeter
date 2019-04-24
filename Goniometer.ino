#include <LiquidCrystal.h>
// INITIALIZATION

/* LCD Initialization
 * Must initialize the library by associating the LCD interface pin with the Arduino pin it is connected to
 */
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Goniometer Initialization
const int FLEX_PIN_1 = A0; 
const int FLEX_PIN_2 = A1;

// Button Init
const int BUTTON_PIN_1 = 2;
int buttonState = 0;
bool buttonToggle = true;

// Actual voltage and resistor used
const float VCC = 4.8; // Measured voltage of Ardunio 5V line
const float R_DIV = 61000; // Measured resistance of 3.3k resistor

// Approximate resistance value from the flex sensor at certain degree. Adjust to calibrate
const float STRAIGHT_RESISTANCE = 10399.31; // resistance when straight
const float BEND_RESISTANCE = 20148.25; // resistance at 90 deg

void setup(){
  // Initializing flex pins to input
  pinMode(FLEX_PIN_1, INPUT);
  pinMode(FLEX_PIN_2, INPUT);
  
  // Initializing the LCD columns and rows
  lcd.begin(16, 2);

  // Init Button
  pinMode(BUTTON_PIN_1, INPUT);

  Serial.begin(9600);
}

void loop(){
  batterylevel(15,0); // Displaying battery level

  // Printing company name
  lcd.setCursor(0, 0);
  lcd.print("Go-Knee-oMeter");  
  
  buttonState = digitalRead(BUTTON_PIN_1);
  if (buttonState == HIGH){
    if (buttonToggle == true){
      buttonToggle = false;
    }
    else{
      buttonToggle = true;
    }
    //buttonToggle = !buttonToggle;
    Serial.println(millis());
    Serial.println(buttonToggle);
    
  }
  else{
    //lcd.print("not pressed");
  }

  if (buttonToggle == true){
    // Flex Sensor 1
    // Read the ADC, and calculate voltage and resistance from it
    int flexADC_1 = analogRead(FLEX_PIN_1);
    float flexV = flexADC_1 * VCC / 1023.0;
    float flexR = R_DIV * (VCC / flexV - 1.0);
    
    // Use the calculated resistance to estimate the sensor'sbend angle:
    float angle = mapfloat(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);                            
  
    // Flex Sensor 2
    int flexADC_2 = analogRead(FLEX_PIN_2);
    float flexV_2 = flexADC_2 * VCC / 1023.0;
    float flexR_2 = R_DIV * (VCC / flexV_2 - 1.0);
    float angle_2 = mapfloat(flexR_2, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  
    angle += angle_2;
    // Printing sum of angles to LCD
    lcd.setCursor(0, 1);
    lcd.print(angle,1);
    lcd.setCursor(9,1);
    lcd.print("degrees");              
    //lcd.print(String(angle + angle_2) + (char)223);  
    //lcd.print((char)223);   
  
    delay(500);
    //lcd.clear();
  }
  delay(400);
}


float mapfloat(long x, long in_min, long in_max, long out_min, long out_max){
  return (float)(x-in_min)*(out_max - out_min) / (float)(in_max - in_min) + out_min;
}
void batterylevel(int xpos,int ypos)
{
  //read the voltage and convert it to volt
  double curvolt = double( readVcc() ) / 1000;
  // check if voltge is bigger than 4.2 volt so this is a power source
  if(curvolt > 4.2)
  {
    byte batlevel[8] = {
    B01110,
    B11111,
    B10101,
    B10001,
    B11011,
    B11011,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt <= 4.2 && curvolt > 4.0)
  {
    byte batlevel[8] = {
    B01110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt <= 4.0 && curvolt > 3.8)
  {
    byte batlevel[8] = {
    B01110,
    B10001,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt <= 3.8 && curvolt > 3.6)
  {
    byte batlevel[8] = {
    B01110,
    B10001,
    B10001,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt <= 3.6 && curvolt > 3.4)
  {
    byte batlevel[8] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B11111,
    B11111,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt <= 3.4 && curvolt > 3.2)
  {
    byte batlevel[8] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt <= 3.2 && curvolt > 3.0)
  {
    byte batlevel[8] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
  if(curvolt < 3.0)
  {
    byte batlevel[8] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    };
    lcd.createChar(0 , batlevel);
    lcd.setCursor(xpos,ypos);
    lcd.write(byte(0));
  }
}
//read internal voltage
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

#include <LiquidCrystal.h>

//b,y,g,bl
const int rs = 5 ,en =6,d4=9,d5=10,d6=11,d7=12;
const int controlIn =A0,controlOut =13,buttonIn =A1;

int buttonSensor=0;
int sensorValue=0;
int w =0;

char userName[6];
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

char whichChar (int num){
  int remainder;
  double newNum;
  int multiple;
  char alphabet [35]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','$'};
  char returnChar;
  remainder = num %(6);
  newNum = num-remainder;
  multiple = newNum/(6);
  if (multiple>2){
    multiple = multiple-3;
  }
  returnChar = alphabet[multiple];
  //Serial.println(multiple);
  return returnChar;
}

void viewSensorValues (int sensorValue, int  buttonSensor){
  Serial.print("sensor = ");
  Serial.println(sensorValue);
  Serial.print("Button Status = ");
  Serial.println(buttonSensor);
  //delay(500);

}

void pinAccess (int& sensorValue, int&  buttonSensor){
  sensorValue = analogRead(controlIn);
  digitalWrite(controlOut,HIGH);
  buttonSensor = analogRead(buttonIn);  
}

void charStorer (int& i,char buttonChar,int& sensor,bool& done ){
  if (sensor <500){
    if (buttonChar != '$'){
      userName[i]=buttonChar;
      i=i+1;
      //Serial.println(i);
      //Serial.println(sensor);
      delay(500);
    }else {
      done = true;
    }
  }
}

void lcdPrinter (int& i,int j,char displayChar){
  lcd.setCursor(i,j);
  lcd.print(displayChar);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //lcd.begin(16,2);
  //cd.print("Hell0 , World!");

}

int fstLoop=0;
bool next= false;
void loop() {
  // put your main code here, to run repeatedly:
  if (fstLoop == 0){
    //const int msgLen;
    char msg []="Username :";
    for (int j=0;j<sizeof(msg)-1;j++){
      char x = msg[j];
      lcdPrinter(j,0,x);
    }
    pinAccess(sensorValue,buttonSensor);
    viewSensorValues(sensorValue,buttonSensor);
    char displayChar = whichChar(sensorValue);
    charStorer(w,displayChar,buttonSensor,next);   
    lcd.setCursor(w,1);
    lcd.print(displayChar);

    if (next == true){
      fstLoop++ ;   
      next =false;   
    } 
  }

  if (fstLoop ==1){
    for (int j=0;j<15;j++){
      lcdPrinter(j,0,' ');
    }
    for (int j=0;j<15;j++){
      lcdPrinter(j,1,' ');
    }  
  }
}

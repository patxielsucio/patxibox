#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
Servo gate;

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},                            //libraries setup
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {8, 7, 6}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27,20,4);  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int red = 11;
int green = 12;
int lockstate = 0;

char password1 = '0'; 
char password2 = '0'; 
char password3 = '0'; 
char password4 = '0'; 

char pass1 = '0'; 
char pass2 = '0'; 
char pass3 = '0'; 
char pass4 = '0'; 

int data = 0;
int printdone = 0;
int getoption = 0;
char option;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                      //Functions
void opengate(){
  gate.write(170);
  }

  void closegate(){
  gate.write(0);
  }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
   lcd.setCursor(3,0);      //lcd welcome splash screeen
  lcd.print("Welcome to");
  lcd.setCursor(4,1);
  lcd.print("Patxibox");
  delay(2000);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pinMode(green, OUTPUT);
pinMode(red, OUTPUT);       //pin mode declarations
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gate.attach(9);
                           //servo setup
closegate();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  
  while(printdone == 0){
  lcd.clear();
  lcd.home();
  lcd.print("Password:");
  printdone++;
  } 
  printdone = 0;
  data = 0;
 while(data != 5){
while(data == 0){
  pass1 = keypad.getKey(); 
  if(pass1){
    lcd.print(pass1);
    break;   
    }
  }
  while(data == 1){
  pass2 = keypad.getKey();   //Getting the password from the keypad
  if(pass2){
    lcd.print(pass2);
    break;   
    }
  }
  while(data == 2){
  pass3 = keypad.getKey();
   if(pass3){
   lcd.print(pass3);
    break;   
    }
  }
  while(data == 3){
  pass4 = keypad.getKey();
  if(pass4){
    lcd.print(pass4);
    break;   
    }
  }
  data++;
  }
  
       
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(pass1 == password1){
  if(pass2 == password2){
    if(pass3 == password3){
      if(pass4 == password4){
    lcd.clear();
    lcd.home();
    lcd.print("Good password");
    opengate();
     digitalWrite(green,HIGH);
     delay(1000);
     digitalWrite(green,LOW);
     lockstate = 1;
      }
else//eslse del 4
{
    lcd.clear();                                  
    lcd.home();
    lcd.print("Bad password");
     digitalWrite(red,HIGH);
    delay(1000);
    digitalWrite(red,LOW);
    } 
    }                                   //Password verify

else// else del 3
{
    lcd.clear();
    lcd.home();
    lcd.print("Bad password");
     digitalWrite(red,HIGH);
    delay(1000);
    digitalWrite(red,LOW);
    } 
    
  }
    
    else{//else del 2
    lcd.clear();
    lcd.home();
    lcd.print("Bad password");
     digitalWrite(red,HIGH);
    delay(1000);
digitalWrite(red,LOW);
    } 
  
  }
  else{//else del 1
    lcd.clear();
    lcd.home();
    lcd.print("Bad password");
    digitalWrite(red,HIGH);
    delay(1000);
 digitalWrite(red,LOW);
    } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  while(lockstate == 1)
{
  while(printdone == 0){
  Serial.print("Executing");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("*->Close");
  lcd.setCursor(0,1);
  lcd.print("#->Change Passwd");
  getoption = 0;
  printdone++;
  }
  
  while(getoption == 0){
    option = keypad.getKey();
    if(option == '*'){
      closegate();
      getoption++;
      lockstate = 0;
      printdone = 0;
      }

      if(option == '#'){
      printdone = 0;
      getoption++;

      while (printdone == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Type New Paswd");
        lcd.setCursor(0,1);                                    //Box opened menu
        lcd.print("->");
        printdone++;
        }
      printdone = 0;
      data = 0;
 while(data != 5){
while(data == 0){
  password1 = keypad.getKey(); 
  if(password1){
    lcd.print(password1);
    break;   
    }
  }
  while(data == 1){
  password2 = keypad.getKey();
  if(password2){
    lcd.print(password2);
    break;   
    }
  }
  while(data == 2){
  password3 = keypad.getKey();
   if(password3){
   lcd.print(password3);
    break;   
    }
  }
  while(data == 3){
  password4 = keypad.getKey();
  if(password4){
    lcd.print(password4);
    break;   
    }
  }
  data++;
  }
  lcd.clear();
  lcd.setCursor(2,0);
   lcd.print("Password");   
   lcd.setCursor(2,1);
   lcd.print("Saved");
   delay(1000);   

      
      }
  }

}



 
    }


 


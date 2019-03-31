#define BITtime 563  //carrier bit is 562.5us
#define LEDpin  2 
unsigned long codeon  =0b11000011001111001000000001111111 ; //set a random address 1100001100111100,
unsigned long codeoff =0b11000011001111000100000010111111;
unsigned long codevolup=0b11000011001111001100000000111111;
unsigned long codevoldown=0b11000011001111000010000011011111;
unsigned long codechlup=0b11000011001111001010000001011111;
unsigned long codechldown=0b11000011001111000110000010011111;
int buttonState = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
const int buttonPinpowon = 2; 
const int buttonPinpowoff = 3; 
const int buttonPinvolup = 4; 
const int buttonPinvoldown = 5; 
const int buttonPinchlup = 6; 
const int buttonPinchldown = 7; 
void setup() {
  // put your setup code here, to run once:
 pinMode(LEDpin, OUTPUT);
 digitalWrite(LEDpin, LOW);
 pinMode(buttonPinpowon, INPUT);
 pinMode(buttonPinpowoff, INPUT);
 pinMode(buttonPinvolup, INPUT);
 pinMode(buttonPinvoldown, INPUT);
  pinMode(buttonPinchlup, INPUT);
   pinMode(buttonPinchldown, INPUT);
}

void IRcarrier(unsigned int IRtimemicroseconds)
{
  for(int i=0; i < (IRtimemicroseconds / 26); i++)
    {
    digitalWrite(LEDpin, HIGH);  
    delayMicroseconds(9);         
    digitalWrite(LEDpin, LOW);  
    delayMicroseconds(9);         
    }
}

void IRsendCode(unsigned long code)
{

  IRcarrier(9000);           
  delayMicroseconds(4500);   
  for (int i=0; i<32; i++)           
    {
    IRcarrier(BITtime);              
    if (code & 0x80000000)       //logic 1     
      delayMicroseconds(3 * BITtime); 
    else // logic 0
      delayMicroseconds(BITtime);     
     code<<=1;                       
    }
  IRcarrier(BITtime);                 
}

void loop() {
  // put your main code here, to run repeatedly:
   buttonState = digitalRead(buttonPinpowon);
   buttonState1 = digitalRead(buttonPinpowoff);
   buttonState2= digitalRead(buttonPinvolup);
   buttonState3 = digitalRead(buttonPinvoldown);
   buttonState4 = digitalRead(buttonPinchlup);
   buttonState5 = digitalRead(buttonPinchldown);

   while(buttonState == HIGH){
    IRsendCode(codeon);
   }
     while(buttonState1 == HIGH){
    IRsendCode(codeoff);
   }
     while(buttonState2 == HIGH){
    IRsendCode(codevolup);
   }
     while(buttonState3 == HIGH){
    IRsendCode(codevoldown);
   }
     while(buttonState4 == HIGH){
    IRsendCode(codechlup);
   }
      while(buttonState5 == HIGH){
    IRsendCode(codechldown);
   }

}

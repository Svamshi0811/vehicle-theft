#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <stdio.h>
//LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int buzzer = 7;
int button = 2;
unsigned char rcv, count, gchr, gchr1, robos = 's';
char rcvmsg[10], pastnumber[11];
int sti = 0;
String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
int password[4];
void okcheck()
{
 unsigned char rcr;
 do {rcr = Serial.read();
 } while (rcr != 'K');
}
void setup()
{
 Serial.begin(9600); // gsm
 pinMode(buzzer, OUTPUT);
 pinMode(button, INPUT);
 digitalWrite(buzzer, 0);

 digitalWrite(button, 1);
 lcd.begin(16, 2);
 lcd.setCursor(0, 0);
 lcd.print(" WELCOME TO THE ");
 lcd.setCursor(0, 1);
 lcd.print(" PROJECT ");
 delay(1500);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("VCHL THFT DECT");
 lcd.setCursor(0, 1);
 lcd.print(" SYS ");
 delay(3000);
 lcd.clear();
 lcd.print("GSM INIT ....");
 gsminit();
 lcd.clear();
}
void loop()
{
 if (digitalRead(button) == 0)
 {
 digitalWrite(buzzer, 1);
 lcd.setCursor(0, 0);
 lcd.print("THEFT ALRT");
 lcd.setCursor(0, 1);
 lcd.print("MSG SENGING.......");
 Serial.write("AT+CMGS=\"");

 Serial.write(pastnumber);
 Serial.write("\"\r\n"); delay(2500);
 Serial.write("THFT DETECT\r\n");
 Serial.write("\r\n");
 Serial.write(0x1A);
 delay(2000);
 digitalWrite(buzzer, 0);
 }
 else
 {
 digitalWrite(buzzer, 0);
 }
}
int readSerial(char result[])
{
 int i = 0;
 while (1)
 {
 while (Serial.available() > 0)
 {
 char inChar = Serial.read();
 if (inChar == '\n')
 {
 result[i] = '\0';
 Serial.flush();
 return 0;
 }
 if (inChar != '\r')

 {
 result[i] = inChar;
 i++;
 }
 }
 }
}
int readSerial1(char result[])
{
 int i = 0;
 while (1)
 {
 while (Serial.available() > 0)
 {
 char inChar = Serial.read();
 if (inChar == '*')
 {
 result[i] = '\0';
 Serial.flush();
 return 0;
 }
 if (inChar != '*')
 {
 result[i] = inChar;
 i++;
 }
 }
 }

}
void gsminit()
{
 Serial.write("AT\r\n"); okcheck();
 Serial.write("ATE0\r\n"); okcheck();
 Serial.write("AT+CMGF=1\r\n"); okcheck();
 Serial.write("AT+CNMI=1,2,0,0\r\n"); okcheck();
 Serial.write("AT+CSMP=17,167,0,0\r\n"); okcheck();
 lcd.clear();
 lcd.print("SEND MSG STORE");
 lcd.setCursor(0, 1);
 lcd.print("MOBILE NUMBER");
 do {
 rcv = Serial.read();
 } while (rcv != '*');
 readSerial(pastnumber);
 lcd.clear();
 lcd.print(pastnumber);
 lcd.setCursor(0, 1);
 Serial.write("AT+CMGS=\"");
 Serial.write(pastnumber);
 Serial.write("\"\r\n"); delay(2500);
 Serial.write("Reg-1\r\n");
 Serial.write(0x1A);
 delay(4000); delay(4000);
 //delay(1000);
}
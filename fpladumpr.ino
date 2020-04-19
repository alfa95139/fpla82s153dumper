
// 82S153 FPLA Dumper for Ensoniq Mirage DSK-8
// 
// Alessandro Fasan, April 12th 2020
// 

#include <stdio.h>

int addrSize = 1024;

#define PA15   1 
#define SA14   2
#define SA13   3
#define SA12   4
#define ED     5
#define RAS_   6
#define CASM_  7
#define BS1    8
#define BS     9

#define BS0    11
#define CAS0_  12
#define CAS1_  13
#define CAS2_  14
#define CROM_  15
#define IOS_   16
#define BROM_  17
#define CAS_   18
#define SA15   19

void setup() {                
  Serial.begin(115200);  
  delay(1000);
  Serial.println("+-----------------------------------------------------------------------+");
  Serial.println("|                    MIRAGE 82S153N FPLA read v0.0                      |");
  Serial.println("+=======================================================================+");
  Serial.println("| B5 B6  B7  B8 | B2  B3  B4 |B9 | I5 I6 B0 | B1 I7 |I0  I1  I2  I3 |I4 |");  
  Serial.println("| 15 16  17  18 | 12  13  14 |19 |  6  7  9 | 11  8 | 1   2   3   4 | 5 |");
  Serial.println("+=======================================================================+");
  Serial.println("| [Peripherals] | [ DRAMS ] |   |[ DOC5503 ]|[ VIA ]|               |   |");
  Serial.println("| C | I | B | C | C | C | C | S | R | C | B | B | B | P | S | S | S | E |");
  Serial.println("| R | O | R | A | A | A | A | A | A | A | S | S | S | A | A | A | A | D |");
  Serial.println("| O | S | O | S | S | S | S | 1 | S | S |     0 | 1 | 1 | 1 | 1 | 1     |");
  Serial.println("| M | _ | M | _ | 0 | 1 | 2 | 5 | _ | M |             5 | 4 | 3 | 2     |");
  Serial.println("| _       _       _ | _ | _           _                                 |");
  Serial.println("                                                                         ");
  delay(100);

  pinMode(PA15, OUTPUT);
  pinMode(SA14, OUTPUT); 
  pinMode(SA13, OUTPUT);  
  pinMode(SA12, OUTPUT);  
  pinMode(ED, OUTPUT);    
  pinMode(RAS_, OUTPUT);  
  pinMode(CASM_, OUTPUT);  
  pinMode(BS1, OUTPUT);   
  pinMode(BS, OUTPUT);    
  pinMode(BS0, OUTPUT); 

  pinMode(CAS0_, INPUT);
  pinMode(CAS1_, INPUT);
  pinMode(CAS2_, INPUT);
  pinMode(CROM_, INPUT);
  pinMode(IOS_ , INPUT);
  pinMode(BROM_, INPUT);
  pinMode(CAS_ , INPUT);
  pinMode(SA15 , INPUT);

}

void loop() {

  int addrPoint;
 // int time4banner = 0;
 
  for (addrPoint = 0; addrPoint < addrSize; addrPoint++) {
    //if (time4banner == 32) {
   //        printBanner();
   //        time4banner = 1;
   //       } else time4banner++;
      printBinary(addrPoint, 10);
  }
  while(1) {} // halt
}


void printBinary(int address, int base) {
  int bitMask;
  int bitCounter;
  
  address = address & 0xFFFF;
 // Serial.println(address, BIN);

  bitMask = (address & (1 <<  9)) ? HIGH : LOW;
  digitalWrite(RAS_, bitMask);
 // Serial.print(bitMask, DEC);


  bitMask = (address & (1 <<  8)) ? HIGH : LOW;
  digitalWrite(CASM_,bitMask);
 // Serial.print(bitMask, DEC);

  bitMask = (address & (1 <<  7)) ? HIGH : LOW;
  digitalWrite(BS,   bitMask);
 // Serial.print(bitMask, DEC);

  bitMask = (address & (1 <<  6)) ? HIGH : LOW;
  digitalWrite(BS0,  bitMask);
 // Serial.print(bitMask, DEC);

  bitMask = (address & (1 <<  5)) ? HIGH : LOW;
  digitalWrite(BS1,  bitMask);
 // Serial.print(bitMask, DEC);
  
  bitMask = (address & (1 <<  4)) ? HIGH : LOW;
  digitalWrite(PA15, bitMask);
 // Serial.print(bitMask, DEC);

  bitMask = (address & (1 <<  3)) ? HIGH : LOW;
  digitalWrite(SA14, bitMask);
 // Serial.print(bitMask, DEC);

 
  bitMask = (address & (1 <<  2)) ? HIGH : LOW;
  digitalWrite(SA13, bitMask);
 // Serial.print(bitMask, DEC);
 
  bitMask = (address & (1 <<  1)) ? HIGH : LOW;
  digitalWrite(SA12, bitMask);
 // Serial.print(bitMask, DEC);

  bitMask = (address & (1 <<  0)) ? HIGH : LOW;
  digitalWrite(ED,   bitMask);
//  Serial.print(bitMask, DEC);

delay(100); // let the signals stabilize

// Now, read the signals from the FPLA
  Serial.print(" ");
  Serial.print(digitalRead(CROM_));// == HIGH ? 1 : 0, DEC); 
  Serial.print(" , ");
  Serial.print(digitalRead(IOS_));//  == HIGH ? 1 : 0, DEC);
  Serial.print(" , ");
  Serial.print(digitalRead(BROM_));// == HIGH ? 1 : 0, DEC); 
  Serial.print(" , ");
  Serial.print(digitalRead(CAS_));//  == HIGH ? 1 : 0, DEC); 
  Serial.print(" , ");
  Serial.print(digitalRead(CAS0_));// == HIGH ? 1 : 0, DEC);
  Serial.print(" , ");
  Serial.print(digitalRead(CAS1_));// == HIGH ? 1 : 0, DEC);
  Serial.print(" , ");
  Serial.print(digitalRead(CAS2_));// == HIGH ? 1 : 0, DEC); 
  Serial.print(" , ");
  Serial.print(digitalRead(SA15));//  == HIGH ? 1 : 0, DEC); 
  
  for (bitCounter = base - 1; bitCounter >= 0; bitCounter--) {
    bitMask = (address & (1 << bitCounter)) ? 1 : 0;
    Serial.print(" , ");
    Serial.print(bitMask, DEC);
  }
 
  Serial.println("");
}

void printBanner() {
  Serial.println("+-----------------------------------------------------------------------+");
  Serial.println("|                    MIRAGE 82S153N FPLA read v0.0                      |");
  Serial.println("+=======================================================================+");
  Serial.println("| B5 B6  B7  B8 | B2  B3  B4 |B9 | I5 I6 B0 | B1 I7 |I0  I1  I2  I3 |I4 |");  
  Serial.println("| 15 16  17  18 | 12  13  14 |19 |  6  7  9 | 11  8 | 1   2   3   4 | 5 |");
  Serial.println("+=======================================================================+");
  Serial.println("| [Peripherals] | [ DRAMS ] |   |[ DOC5503 ]|[ VIA ]|               |   |");
  Serial.println("| C | I | B | C | C | C | C | S | R | C | B | B | B | P | S | S | S | E |");
  Serial.println("| R | O | R | A | A | A | A | A | A | A | S | S | S | A | A | A | A | D |");
  Serial.println("| O | S | O | S | S | S | S | 1 | S | S |     0 | 1 | 1 | 1 | 1 | 1     |");
  Serial.println("| M | _ | M | _ | 0 | 1 | 2 | 5 | _ | M |             5 | 4 | 3 | 2     |");
  Serial.println("| _       _       _ | _ | _           _                                 |");
  Serial.println("                                                                         ");
}

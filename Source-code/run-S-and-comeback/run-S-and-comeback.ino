#define enA 6
#define enB 11

#define inA1 7  //Định nghĩa chân in1 của động cơ A // A is left tire
#define inA2 8//Định nghĩa chân in2 của động cơ A
#define inB1 9 //Định nghĩa chân in3 của động cơ B // B is right tire
#define inB2 10//Định nghĩa chân in4 của động cơ B

#define linesens2 A1 //Định nghĩa chân cảm biến line 1
#define linesens3 A2 //Định nghĩa chân cảm biến line 2
#define linesens4 A3 //Định nghĩa chân cảm biến line 3
#define linesens5 A4 //Định nghĩa chân cảm biến line 1
#define linesens1 A0 //Định nghĩa chân cảm biến line 2

#define MAX_SPEED 90



int online = 1;   // 0 la trai, 1 la giua, 2 la ben phai, 4 thi dung lai
int counter = 0;
void setup() {
    
  // set pin for motor and sensor
    pinMode(inA1, OUTPUT);//Set chân in1 của dc A là output
    pinMode(inA2, OUTPUT);//Set chân in2 của dc A là output
    pinMode(inB1, OUTPUT);//Set chân in1 của dc B là output
    pinMode(inB2, OUTPUT);//Set chân in2 của dc B là output
    pinMode(linesens1, INPUT);//Set chân cảm biến 1 là input
    pinMode(linesens2, INPUT);//Set chân cảm biến 2 là input
    pinMode(linesens3, INPUT);//Set chân cảm biến 3 là input
    pinMode(linesens4, INPUT);//Set chân cảm biến 4 là input
    pinMode(linesens5, INPUT);//Set chân cảm biến 5 là input

    Serial.begin(9600);  

  
}

void loop() {
  
  if(digitalRead(linesens3) == LOW)
    online = 1;
  if(digitalRead(linesens2) == LOW  || digitalRead(linesens1) == LOW)
      online = 0;
  if(digitalRead(linesens4) == LOW || digitalRead(linesens5) == LOW) 
      online = 2;
  if(digitalRead(linesens3) == HIGH  && digitalRead(linesens4) == HIGH  && digitalRead(linesens2) == HIGH ){
      counter++;
      if((counter < 20000)&&(online ==2 ))
        online = 2;
      if((counter < 20000)&&(online ==0 ))
        online = 0;
      if((counter < 20000)&&(online==1 ))
        online = 2;
      if(counter == 20000)
        online = 3;
      
    } 
  
  switch(online){
    case 1: dithang(); break;
    case 0: retrai(); break;
    case 2: rephai();break;
    case 3: dungxe();break;
  }
}
 
void dithang(){
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
}

void retrai(){
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
}

void rephai(){
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);
}

void dungxe(){
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
}

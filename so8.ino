#define enA 6
#define enB 11

#define inA1 7  //Định nghĩa chân in1 của động cơ A // A is left tire
#define inA2 8//Định nghĩa chân in2 của động cơ A
#define inB1 9 //Định nghĩa chân in1 của động cơ B // B is right tire
#define inB2 10//Định nghĩa chân in2 của động cơ B

#define linesens2 A1 //Định nghĩa chân cảm biến line 1
#define linesens3 A2 //Định nghĩa chân cảm biến line 2
#define linesens4 A3 //Định nghĩa chân cảm biến line 3
#define linesens5 A4 //Định nghĩa chân cảm biến line 1
#define linesens1 A0 //Định nghĩa chân cảm biến line 2

#define MAX_SPEED 90


int status = 100; // default 0 

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
 do_line (inB1, inB2, inA1, inA2, linesens1, linesens2, linesens3, linesens4, linesens5);
}

void do_line (byte inR1, byte inR2, byte inL1, byte inL2, byte sen1, byte sen2, byte sen3, byte sen4, byte sen5)
{
  switch (kiemTraSensor (sen1, sen2, sen3,sen4,sen5))
  {
    case -1:
      chuyenDong( inR1, inR2, inL1, inL2, 6);// cứ đèn bên phải sáng mà trái ko sáng thì rẽ phải 
      break;
    case -2:
      chuyenDong( inR1, inR2, inL1, inL2, 6);// cứ đèn bên phải sáng mà trái ko sáng thì rẽ phải 
      break;
    case -3:
      chuyenDong( inR1, inR2, inL1, inL2, 6);// cứ đèn bên phải sáng mà trái ko sáng thì rẽ phải 
      break;
    case 1:
      chuyenDong( inR1, inR2, inL1, inL2, 5);// cứ đèn bên trái sáng mà phảii ko sáng thì rẽ trái 
      break;
    case 2:
      chuyenDong( inR1, inR2, inL1, inL2, 5);// cứ đèn bên trái sáng mà phảii ko sáng thì rẽ trái 
      break;
    case 3:
      chuyenDong( inR1, inR2, inL1, inL2, 5);// cứ đèn bên trái sáng mà phảii ko sáng thì rẽ trái 
      break;
    case 0:// trả ra gtri 0 vi da thuc hien lay status= left- right với left=right). Đoạn này nghĩa là, gặp đoạn giao của số 8 thì cứ chạy thẳng đường mình đang đi nhé. 
      chuyenDong( inR1, inR2, inL1, inL2, 1);// tiến thẳng
      break;
    case 100:// trả ve gtri 100 vì khi này không đen nào sáng ca, xe đi lệch vạch r 
      chuyenDong( inR1, inR2, inL1, inL2, 2);// lệch vạch thì lùi
      break;   
  }
  
}
void chuyenDong (byte inR1, byte inR2, byte inL1, byte inL2, byte chuyenDong)
{
  /*
  inR1 inR2 là 2 chân tín hiệu động cơ bên phải
  inL1 inL2 là 2 chân tín hiệu động cơ bên trái
  chuyenDong= 0 đứng yên
  chuyenDong =1 đi thẳng
  chuyenDong =2 lùi lại
  chuyenDong =3 quay trái
  chuyenDong =4 quay phải
  chuyenDong =5 rẽ trái
  chuyenDong =6 rẽ phải
  */
  switch (chuyenDong)
  {
    case 1://đi thẳng
      motorControlWithSpeed(inR1, inR2, 1, 150, 150);
      motorControlWithSpeed(inL1, inL2, 1, 150, 150);
      break;
    case 2:// lùi lại
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    case 3:// quay trái
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    case 4:// quay phải
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    case 5:// rẽ trái
      motorControlWithSpeed(inR1, inR2, 1, 0, 150);
      motorControlWithSpeed(inL1, inL2, 0, 128, 0); //weak momentum
      break;
    case 6:// rẽ phải
      motorControlWithSpeed(inR1, inR2, 2, 0, 80);
      motorControlWithSpeed(inL1, inL2, 1, 180, 0);
      break;
    default:
      chuyenDong = 0;
      
  }
}


void motorControlNoSpeed (byte in1, byte in2, byte direct)
{
  switch (direct)
  {
    case 0:// Dừng không quay
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      break;
    case 1:// Quay chiều thứ 1
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, MAX_SPEED);
      analogWrite(enB, MAX_SPEED);
      
      break;
    case 2:// Quay chiều thứ 2
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, MAX_SPEED);
      analogWrite(enB, MAX_SPEED);
      
      break;
      //default:
  }
}

void motorControlWithSpeed (byte in1, byte in2, byte direct, int spdA, int spdB)
{
  switch (direct)
  {
    case 0:// Dừng không quay
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      break;
    case 1:// Quay chiều thứ 1
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      if(spdA != 0) analogWrite(enA, spdA);
      if(spdB != 0) analogWrite(enB, spdB);
      
      break;
    case 2:// Quay chiều thứ 2
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      if(spdA != 0) analogWrite(enA, spdA);
      if(spdB != 0) analogWrite(enB, spdB);
      break;
      
      //default:
  }
}

int kiemTraSensor (int ss1, int ss2, int ss3,int ss4, int ss5)
{
  
  int left = analogRead (ss1)+analogRead (ss2 )+analogRead (ss3); //kiểm tra mấy cảm biến trái ở trong màu đen
  int right= analogRead (ss3)+analogRead (ss4)+analogRead (ss5); //kiểm tra mấy cảm biến phải ở trong màu đen

  if ((left!=0) || (right!=0))
  {  
    status = left - right;
    
  }
  
  return status;
}

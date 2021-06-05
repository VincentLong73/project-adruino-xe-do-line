byte SpMaxL=100;
byte SpMaxR=100;


void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);//Set chân in1 của dc A là output
  pinMode(11, OUTPUT);//Set chân in2 của dc A là output
  pinMode(7, OUTPUT);//Set chân in1 của dc A là output
  pinMode(6, OUTPUT);//Set chân in2 của dc A là output
  pinMode(5, OUTPUT);//Set chân in1 của dc B là output
  pinMode(4, OUTPUT);//Set chân in2 của dc B là output
  pinMode(A0, INPUT);//Set chân cảm biến 1 là input
  pinMode(A1, INPUT);//Set chân cảm biến 2 là input
  pinMode(A2, INPUT);//Set chân cảm biến 3 là input
  pinMode(A3, INPUT);//Set chân cảm biến 4 là input
  pinMode(A4, INPUT);//Set chân cảm biến 4 là input
 // analogWrite(10, 200);
  //analogWrite(11, 200);
}


void loop() {
  //Tien();
  //Lui();
  //Retrai();
  //Rephai();
  doline();
  //delay (1000);
  //Serial.println (trangThai5CamBien ());
  //delay(1000);
}

void doline()
{
  switch (trangThai5CamBien())
  {
    case 200:
      //Tien(SpMaxL,SpMaxR-150);
      Lui(100,100);
      //Rephai();
      delay(10);
      break;
    case 0:
      Tien(SpMaxL,SpMaxR);
      delay(10);
      break;
    case 1:
      Tien(SpMaxL,SpMaxR-20);
      delay(10);
      break;
    case 2:
      Tien(SpMaxL,SpMaxR-40);
      delay(10);
      break;
    case 3:
      Tien(SpMaxL,0);
      delay(10);
      break;
    case -1:
      Tien(SpMaxL-20,SpMaxR);
      delay(10);
      break;
    case -2:
      Tien(SpMaxL-40,SpMaxR);
      delay(10);
      break;
    case -3:
      Tien(0,SpMaxR);
      delay(10);
      break;
    default:
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      break;
  }
}
boolean IFSensor (byte PinNumb)
{
  // Có line là 1
  return (!digitalRead (PinNumb));
}

int trangThai5CamBien ()// biến lưu trạng thái cảm biến 5 mắt 
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 2 3
  */
  int sens1 = IFSensor(A0);
  int sens2 = IFSensor(A1);
  int sens3 = IFSensor(A2);
  int sens4 = IFSensor(A3);
  int sens5 = IFSensor(A4);
  switch (lechvach5mat())
  {
    case -3:// 2 ss trái s1, s2 nhận dc tín hiệu 
      return -3;
      break;
    case -2:// cái cảm biến S1 nhận được tín hiệu  
      return -2;
      break;
    case -1:// cái cảm biến S2 nhận được tín hiệu
      return -1;
      break;
    case 0:// ko cái nào nhận được thông tin đường 
      if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5)) == 0)
        return 200;
      else
        return 0;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 2;
      break;
    case 3:
      return 3;
      break;

  }
}
int lechvach5mat()
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 3 2
  */
  int sens1 = IFSensor(A0);
  int sens2 = IFSensor(A1);
  int sens3 = IFSensor(A2);
  int sens4 = IFSensor(A3);
  int sens5 = IFSensor(A4);
  int lechvach = -2 * sens1 - sens2 + sens4 + 2 * sens5;
  switch (lechvach)
  {
    case -3:// cái này là do 2 mắt s1, s2 biên đều chạm vạch
      return -2;
      break;
    case -2: // s1 chạm vạch 
      return -3;
      break;
    case -1://s2 chạm vạch 
      return -1;
      break;
    case 0:// s3 chạm vạch , đi đúng đường 
      return 0;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 2;
      break;

  }

}
void Tien( byte speedL, byte speedR)
{
  analogWrite(11, speedL);
  analogWrite(10, speedR);
  digitalWrite(7, 1);
  digitalWrite(6, 0);
  digitalWrite(5, 1);
  digitalWrite(4, 0);
}
void Retrai( byte speedL, byte speedR)
{
  analogWrite(11, speedL);
  analogWrite(10, speedR);
  digitalWrite(7, 0);
  digitalWrite(6, 0);
  digitalWrite(5, 1);
  digitalWrite(4, 0);
}
void Rephai( byte speedL, byte speedR)
{
  analogWrite(11, speedL);
  analogWrite(10, speedR);
  digitalWrite(7, 1);
  digitalWrite(6, 0);
  digitalWrite(5, 0);
  digitalWrite(4, 0);
}
void Lui(byte SpeedL, byte SpeedR)
{
  analogWrite(11, SpeedL);
  analogWrite(10, SpeedR);
  digitalWrite(7, 0);
  digitalWrite(6, 1);
  digitalWrite(5, 0);
  digitalWrite(4, 1);
}

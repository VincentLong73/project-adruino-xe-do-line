//đường đen là chữ S 
// IR Sensors_ Khai báo 5 chân của sensor 
int sensor1 = A0;      // Left most sensor
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;      
int sensor5 = A4;      // Right most sensor
// Initial Values of Sensors_ Khai báo mảng giá trị của sensor
int sensor[5] = {0, 0, 0,0 , 0};

// Motor Variables_ Khai báo 4 chân động cơ và 2 chân điều khiển 
int ENA = 6;              //Motor Trái
int motorInput1 = 7;
int motorInput2 = 8;
int motorInput3 = 9;
int motorInput4 = 10;
int ENB = 11; 
byte SpMaxL=200;
byte SpMaxR=200;

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  
  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  delay(500);
  // Serial.println("Started !!");
  // delay(1000);
}

void loop() {
  
  doline();
 
}

void doline()
{
  switch (lechvach5mat())
  {
    case 200:// đã đi hết line chữ S  , ta cho xe quay phải đến khi xe gặp lại vạch đen
      
      Tien(SpMaxL,SpMaxR-40);
      
      break;
    case 0:
      Tien(SpMaxL,SpMaxR);
      break;
    case 1:
      Tien(SpMaxL,SpMaxR-20);
      break;
    case 2:
      Tien(SpMaxL,SpMaxR-40);
      break;
    case 3:
      Tien(SpMaxL,0);
      break;
    case -1:
      Tien(SpMaxL-20,SpMaxR);
      break;
    case -2:
      Tien(SpMaxL-40,SpMaxR);
      break;
    case -3:
      Tien(0,SpMaxR);
      break;
    default:// mặc định thì dừng
      digitalWrite(motorInput1, 0);
      digitalWrite(motorInput2, 0);
      digitalWrite(motorInput3, 0);
      digitalWrite(motorInput, 0);
      break;
  }
}
boolean IFSensor (byte PinNumb)
{
  // Có line là 1
  return (!digitalRead (PinNumb));
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
    case -3:// cái này là do 2 mắt biên đều chạm vạch
      return -2;// trả về trạng thái cảm biến bằng -2 do S1+s2 sáng  
      break;
    case -2:
      return -3;// trả về trạng thái cảm biến bằng -3 do  S1 sáng
      break;
    case -1:
      return -1;// trả về trạng thái cảm biến bằng -1 do đèn s2 sáng 
      break;
    case 0:// ở trạng thái này tất cả các đèn cùng tắt hoặc chỉ đèn S3 sáng
      if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5)) == 0)//lấy giá trị tuyệt đối tín hiệu các đèn, Nếu tổng giá trị tuyệt dối bằng 0, đen ko sáng, xe đã đi hết chứ S
              return 200;
      else // còn nếu không thì 
        return 0;
      break;
    case 1:
      return 1;// trả về trạng thái cảm biến bằng 1 do đèn s4 sáng 
      break;
    case 2:
      return 3;// trả về trạng thái cảm biến bằng 3 do đèn s5 sáng 
      break;
    case 3:
      return 2;// trả về trạng thái cảm biến bằng 2 do đèn ss4 +s5 sáng
      break;

  }

}
void Tien( byte speedL, byte speedR)
{
  analogWrite(ENA, speedL);
  analogWrite(ENB, speedR);
  digitalWrite(motorInput1, 1);
  digitalWrite(motorInput2, 0);
  digitalWrite(motorInput3, 1);
  digitalWrite(motorInput4, 0);
}
void Retrai()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(motorInput1, 0);
  digitalWrite(motorInput2, 0);
  digitalWrite(motorInput3, 1);
  digitalWrite(motorInput4, 0);
}
void Rephai()
{
  analogWrite(5, 255);
  analogWrite(10, 255);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(motorInput1, 1);
  digitalWrite(motorInput2, 0);
  digitalWrite(motorInput3, 0);
  digitalWrite(motorInput4, 0);
}
void Lui(byte SpeedL, byte SpeedR)
{
  analogWrite(ENA, speedL);
  analogWrite(ENB, speedR);
  digitalWrite(motorInput1, 0);
  digitalWrite(motorInput2, 1);
  digitalWrite(motorInput3, 0);
  digitalWrite(motorInput4, 1);
}

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
int error;            //Motor Phải

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
void loop()
{
  read_sensor_values();
  Serial.print(error);
  if ((error == -4)||(error == -3)||(error == -2)||(error == -1)) {              
    // Quay sang trái cho tới khi phát hiện ngay giữa line
      left();      
      delay(100);
      analogWrite(ENA, 80);        //Left Motor Speed
      analogWrite(ENB, 90);         //Right Motor Speed
      read_sensor_values();
      }
  else if ((error == 1)||(error == 2)||(error == 3)||(error == 4) ||(error == 100)) {               
    
                             
      right();
      delay(100);
      analogWrite(ENA, 80);        
      analogWrite(ENB, 90);        
      read_sensor_values();
    } 
    else if (error == 0){
    forward();               
  }
}



void read_sensor_values()
{
  sensor[0] = analogRead(sensor1);
  sensor[1] = analogRead(sensor2);
  sensor[2] = analogRead(sensor3);
  sensor[3] = analogRead(sensor4);
  sensor[4] = analogRead(sensor5);
  
// trường hợp bị lệch phải 
  if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))       
    error = -4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -3;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))  
    error = -1;
    //trường hợp xe đi vào chính giữa đường đen
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))  
    error = 0;
    // trường hợp xe bị lệch sáng trái 
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))
    error = 1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 0))
    error = 2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] ==1) && (sensor[4] == 1))  // lệch trái nhiều
    error = 3;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))  // lệch trái nhiều
    error = 4;
    
  // trượng hợp xe không còn trên vạch kẻ đen , đã đi hết chữ S
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)) 
    error = 100;
  }




void forward()//xe đi thẳng phía trước 
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
// void reverse()//xe đi lùi
// {
//   /*The pin numbers and high, low values might be different depending on your connections */
//   digitalWrite(motorInput1, LOW);
//   digitalWrite(motorInput2, HIGH);
//   digitalWrite(motorInput3, LOW);
//   digitalWrite(motorInput4, HIGH);
// }
void right()//xe rẽ phải 
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}
void left()//xe rẽ trái
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}

void stop_bot()//dừng xe 
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}


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
int ENB = 11;             //Motor Phải

//Initial Speed of Motor- Khơi tao gtri tốc độ quay 
int initial_motor_speed = 100;


// PID Constants_ Các hằng số PID
float Kp = 25;
float Ki = 0;
float Kd = 15;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

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
  Serial.println("Started !!");
  delay(1000);
}
void loop()
{
  read_sensor_values();
  Serial.print(error);
  if ((error == 100)||(error == -4)||(error == -3)||(error == -2)||(error == -1)) {               // Rẽ Trái 90* cho đến khi quay lại đường đen    Make left turn untill it detects straight path
    
    do {                            // Quay sang trái cho tới khi phát hiện ngay giữa line
      left();
      delay(100);
      analogWrite(ENA, 80);        //Left Motor Speed
      analogWrite(ENB, 90);         //Right Motor Speed
      read_sensor_values();
    } while (error == 0);
  }
  else if ((error == 1)||(error == 2)||(error == 3)||(error == 4)) {               
    
    do {                            
      right();
      delay(100);
      analogWrite(ENA, 80);        
      analogWrite(ENB, 90);        
      read_sensor_values();
    } while (error == 0);

  }else if (error == 0){
    calculate_pid();                  // Tính giá trị PID
    motor_control();                  // Điều chỉnh motor theo giá trị PID mới tính, cho xe chạy thẳng
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
    
  // trượng hợp xe không còn trên vạch kẻ đen 
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)) 
    error = 100;
  }

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D); // er =3; PID = 120 motor phải chay nhanh hơn

  previous_I = I;
  previous_error = error;
}

void motor_control()// hàm điều khiển tốc độ 
{
  // Calculating the effective motor speed:
  
  int left_motor_speed = initial_motor_speed - PID_value;   //-30
  int right_motor_speed = initial_motor_speed + PID_value;  //210

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);   //0
  right_motor_speed = constrain(right_motor_speed, 0, 255); //210

 
  analogWrite(ENA, left_motor_speed-30); //Left Motor Speed    //0
  analogWrite(ENB, right_motor_speed); //Right Motor Speed  //120

  //following lines of code are to make the bot move forward
  forward();
}

void forward()//xe đi thẳng phía trước 
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
// void reverse()//xe đi vòng ngược lại 
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


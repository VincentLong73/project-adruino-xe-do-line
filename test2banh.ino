//Motor A
int enA = 6;
int in1 = 7;
int in2 = 8; 

//Motor B
int in3 = 9; 
int in4 = 10; 
int enB = 11;  

void setup()
{
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT); 
	pinMode(enB,OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

void MotorRunning()
{
	//Running motor A
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	analogWrite(enA, 200); 
	
	//Speed PWM: 0~255 
	//Running motor B
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	analogWrite(enB, 200); 
	
	//Speed PWM: 0~255
	//Reverse 2s.
	delay(2000);
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);  
	
	//STOP 2s.
	delay(2000);
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
} 

void loop() 
{
	MotorRunning();
	delay(1000);
}

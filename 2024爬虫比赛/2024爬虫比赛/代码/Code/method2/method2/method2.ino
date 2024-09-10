#include <Servo.h>

int Echo = A0;  //  超声波发送  A0 引脚，可改
int Trig = A1;  //  超声波接受  A1 引脚，可改

//超声波上的舵机
Servo myservo1;

Servo myservo2;//后腿
Servo myservo3;//前腿


/*~~~~~~~~~~~~~~~~~~~~~~~~超声波测距~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Distance_test()                // 量出前方距离
{
	digitalWrite(Trig, LOW);             // 给触发脚低电平2μs
	delayMicroseconds(2);
	digitalWrite(Trig, HIGH);            // 给触发脚高电平10μs
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);             // 持续给触发脚低电

	float Fdistance = pulseIn(Echo, HIGH);     // 读取高电平时间(单位：微秒)
	Fdistance = Fdistance / 60;
	return Fdistance;
}


// 行驶
// 参数分别是
// 当前的前腿转机角度，当前的后腿转机角度， now_X
// 前脚步长，后脚步长，step_X
// 前脚延迟时间，后脚延迟时间 delay_X
int walk(int now_front, int now_back, int step_fir, int step_sec, int delay_fir, int delay_sec)
{
	for (int t = 0; t <= 30; ++t)
	{
		myservo2.write(now_back - t); delay(delay_sec);
		myservo3.write(now_front = now_front + step_fir); delay(delay_fir);
	}

	for (int t = 0; t <= 30; ++t)
	{
		myservo2.write(now_back + t); delay(delay_sec);
		myservo3.write(now_front = now_front - step_sec); delay(delay_fir);
	}

	for (int t = 0; t <= 30; ++t)
	{
		myservo2.write(now_back + t); delay(delay_sec);
		myservo3.write(now_front = now_front - step_sec); delay(delay_fir);
	}

	for (int t = 0; t <= 30; ++t)
	{
		myservo2.write(now_back - t); delay(delay_sec);
		myservo3.write(now_front = now_front + step_fir); delay(delay_fir);
	}
	return now_front;
}

void turn(int statu)
{
	if (statu == 1)//right > left
	{
		int now_front = walk(90, 90, 2, 1, 10, 25);
		now_front = walk(now_front, 90, -2, -1, 10, 25);
	}
	else//0
	{
		int now_front = walk(90, 90, -2, -1, 10, 25);
		now_front = walk(now_front, 90, 2, 1, 10, 25);
	}
}

void setup()
{
	pinMode( Echo, INPUT );     // 定义超声波输入
	pinMode( Trig, OUTPUT );    // 定义超声波输出脚

	//爬虫舵机引脚初始化
	myservo1.attach(3);
	myservo2.attach(9);
	myservo3.attach(10);
	//初始化串口
	Serial.begin( 9600 );

	//超声波控制舵机归位
	myservo1.write(90);
	myservo2.write(90);
	myservo3.write(90);
}

/*******************loop 一直循环**********************/

void loop()
{
	while (1)
	{
		if (Distance_test() > 20)
			walk(90, 90, 1, 1, 10, 10);// time = (delay_fir + delay_sec) * 120
		else
		{
			for (int pos0 = 90; pos0 < 130; pos0++)
				myservo1.write(pos0);
			delay(300);
			int Left =  Distance_test() ;//左摆头，测左距离

			myservo1.write(0);

			for (int pos0 = 90; pos0 > 50; pos0--)
				myservo1.write(pos0);
			delay(300);
			int Right = Distance_test();//右摆头，测右距离

			myservo1.write(90);

			turn(Right > Left);

		}
	}
}

#include <Servo.h>


int Echo = A0;  //  超声波发送  A0 引脚，可改
int Trig = A1;  //  超声波接受  A1 引脚，可改

//超声波上的舵机
Servo myservo1;

Servo myservo2;//后
Servo myservo3;//前



/*~~~~~~~~~~~~~~~~~~~~~~~~超声波测距~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Distance_test()                // 量出前方距离
{
	digitalWrite(Trig, LOW);             // 给触发脚低电平2μs
	delayMicroseconds(2);
	digitalWrite(Trig, HIGH);            // 给触发脚高电平10μs
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);             // 持续给触发脚低电

	float Fdistance = pulseIn(Echo, HIGH);     // 读取高电平时间(单位：微秒)
	Fdistance = Fdistance / 58;
	return Fdistance;
}


/* 直线行驶  */
void line()
{
	for (int pos1 = 90; pos1 < 130 ; pos1 += 1)
	{
		myservo2.write(pos1);
		delay(25);
		myservo3.write(180 - pos1);
		delay(25);
	}
	for (int pos1 = 130; pos1 > 90 ; pos1 -= 1)
	{
		myservo2.write(pos1);
		delay(25);
		myservo3.write(180 - pos1);
		delay(25);
	}
	for (int pos1 = 90; pos1 > 50 ; pos1 -= 1)
	{
		myservo2.write(pos1);
		delay(25);
		myservo3.write(180 - pos1);
		delay(25);
	}
	for (int pos1 = 50; pos1 < 90 ; pos1 += 1)
	{
		myservo2.write(pos1);
		delay(25);
		myservo3.write(180 - pos1);
		delay(25);
	}
}

//判断转向
void turn(int statu)
{
	if (statu == 1)
	{
		for (int cycle = 0; cycle <= 40; cycle++)
		{
			for (int pos0 = 90; pos0 < 120 ; pos0 += 1)
			{
				myservo3.write(pos0);
				delay(5);
				myservo2.write(pos0);
				delay(5);
			}
		}
	}
	else
	{
		for (int cycle = 40; cycle >= 0; cycle--)
		{
			for (int pos0 = 120 ; pos0 > 90 ; pos0 -= 1)
			{
				myservo3.write(pos0);
				delay(5);
				myservo2.write(pos0);
				delay(5);
			}
		}

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
			line();
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



#define led 13

void setup()			//初始化部分
{
  pinMode(led, OUTPUT);		//定义led引脚为输出模式
}

void loop()				//主循环
{
  digitalWrite(led, LOW);	//led引脚输出低电平，点亮led
  delay(1000);						//延时1s
  digitalWrite(led, HIGH);	//led引脚输出高电平，熄灭led
  delay(1000);						//延时1s
}


#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 4

void envia(unsigned char header,int num,signed char expo=0)
{
  uint8_t c[8];
  c[0]='*';
  c[1]=header;
  c[2]=num>>24;
  c[3]=num>>16;
  c[4]=num>>8;
  c[5]=num;
  c[6]=expo;
  c[7]='\n';
  Serial.write(c,8);
  Serial.flush();
}

void setup()
{
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
}

void loop()
{
    envia(AXIS_Y,analogRead(A0));
    delay(100);
}


byte speaker=11;
int C=1047;
int D=1175;
int E=1319;
int F=1397;
int G=1568;
int A=1760;
int B=1976;
int Quarter = 200;
int Half= 450;
 
void setup() 
{
pinMode(speaker, OUTPUT);

int ScaleNotes[]={C,D,E,F,G,A,B,2*C};
int NoteLengths[]={Quarter, Quarter, Quarter, Quarter, Quarter, Quarter, Quarter, Half};
for(int index=0; index<8; index++)
{
  note(ScaleNotes[index], NoteLengths[index]);
  }

}

void loop() {

}

void note(int frequency, int NoteDuration)
{
  tone(speaker, frequency);
  delay(NoteDuration);
  noTone(speaker);
  delay(50);
  }

#define ml 4
#define mr 7
#define sl 5
#define sr 6

const int IRpin = A0;          // аналоговый пин для подключения выхода Vo сенсора


int trigPin = 10; 
int echoPin = 11;

int speed = 150;
int fdur = 30;
int ldur = 60;

int newLeft;
int newForward;

void setup() {
  Serial.begin(9600);

  //датчик спереди
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  // подключение колес
  pinMode(ml, OUTPUT);
  pinMode(mr, OUTPUT);
  // регулировка скорости
  pinMode(sl, OUTPUT);
  pinMode(sr, OUTPUT);
}

void loop() {
  stopMove();  
  stopMind();  
  // delay(10);    
}

//функция для определения расстояния спереди
int fdist(){
  int duration;
  float distance;
  // для большей точности установим значение LOW на пине Trig
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  // Теперь установим высокий уровень на пине Trig
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  // Узнаем длительность высокого сигнала на пине Echo
  duration = pulseIn(echoPin, HIGH); 
  // Рассчитаем расстояние
  distance = duration / 58;
  // Выведем значение в Serial Monitor
  // Serial.print(distance); 
  // Serial.println(" cm"); 
  // delay(200);
  return distance;
}
//функция для определения расстояния слева
int ldist(){ 
  //Serial.println(irRead(), DEC);
  // получаем сглаженное значение  и переводим в напряжение
  float volts = analogRead(IRpin) * 0.0048828125;
  // и в расстояние в см 
  float distance = 32 * pow(volts, -1.10);
  // Serial.println(distance);      // выдаем в порт значение
  // delay(200);  
  return distance;                  
  } 

void stopMind(){
  
  while(fdist() > fdur and ldist() < ldur){
    forwardMove();
  }
  // while(fdist() < fdur and ldist() > ldur){
  //   stopMove();
  // }
  while(fdist() <= fdur and ldist() <= ldur){
    rightMove();
        
  }
  while(fdist() > fdur and ldist() > ldur){
    forwardMove();
    leftMove();
    delay(50);
  }
  
}

void stopMove(){

  digitalWrite(ml, LOW);
  analogWrite(sl, 0);

  digitalWrite(mr, LOW);
  analogWrite(sr, 0);
  delay(20);

}

void forwardMove(){

  digitalWrite(ml, HIGH);
  analogWrite(sl, speed);

  digitalWrite(mr, HIGH);
  analogWrite(sr, speed);
  
}

void leftMove(){

  digitalWrite(ml, LOW);
  analogWrite(sl, 0);

  digitalWrite(mr, HIGH);
  analogWrite(sr, speed);
}

void rightMove(){

  digitalWrite(ml, HIGH);
  analogWrite(sl, speed);

  digitalWrite(mr, LOW);
  analogWrite(sr, 0);
}

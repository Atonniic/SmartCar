// โปรแกรมการสั่งงานหุ่นยนต์
int IN8=8; //มอเตอร์ซ้าย
int IN9=9; //มอเตอร์ซ้าย
int IN10=10; //มอเตอร์ขวา
int IN11=11; //มอเตอร์ขวา
int Sensor_IR1= 5 ; //เซนเซอร์ขวา
int Sensor_IR2= 6 ; //เซนเซอร์ซ้าย
int TRIGGER_PIN = 12; //ส่งค่าสัญญาณออก
int ECHO_PIN = 13; //รับค่าสัญญาณเข้า
int distance; //ประกาศตัวแปรใหม่ distance 
int LED_RED = 2; // หลอด LED แดง
int LED_YELLOW =3; // หลอด LED เหลือง
int LED_GREEN =4; // หลอด LED เขียว

void setup() { //กำหนดตัวแปรที่ต้องรับค่าและส่งค่าออก
  pinMode(IN8,OUTPUT);
  pinMode(IN9,OUTPUT);
  pinMode(IN10,OUTPUT);
  pinMode(IN11,OUTPUT);
  pinMode(Sensor_IR1,INPUT);
  pinMode(Sensor_IR2,INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
  Serial.begin(9600); // //การกําหนดอัตราความเร็วการสื่อสารพอร์ตอนุกรมด้วยความเร็ว 9600 บิตต่อวินาที (bps)
}

void loop() { //การกำหนดลูปในการทำงานของฟังก์ชัน
    digitalWrite(13,LOW);
    int Readsensor1 = digitalRead(Sensor_IR1); // ค่าที่อ่านได้จากเซนเซอร์ IR 
    int Readsensor2 = digitalRead(Sensor_IR2); 
    Distance();// ตัวแปรที่กำหนดขึ้นใหม่
    forwordCommand(); //ตัวแปรที่กำหนดใหม่
    Serial.println(Readsensor1); // พิมพ์ค่าออกมา เพื่อให้เข้าใจการอ่านค่า
    Serial.println(Readsensor2);
    
    Serial.println(distance); // พิมพ์ค่าระยะทางออกมา 

    if (Readsensor1 == HIGH && Readsensor2 == HIGH and distance > 15){ //หุ่นยนต์เดินหน้า HIGH (1) คือเปิด , LOW(0) คือปิด
      forwordCommand();
    }
    else if (distance < 15 ){ //หุ่นยนต์หยุด
      breakCar();
    }
    
    else { //หุ่นยนต์ถอยหลัง
      rewordCommand();
      
    }
    
}
void forwordCommand(){ //ฟังก์ชันเดินหน้า
  digitalWrite(IN8,HIGH); //ปล่อยกระแสไฟฟ้าออกเพื่อควบคุมทิศทางการหมุนมอเตอร์ขวา
  digitalWrite(IN9,LOW); //รับกระแสไฟฟ้าเข้าเพื่อให้วงจรไฟฟ้าไหลครบวงจร ของมอเตอร์ขวา
  digitalWrite(IN10,LOW); //รับกระแสไฟฟ้าเข้าเพื่อให้วงจรไฟฟ้าไหลครบวงจร ของมอเตอร์ซ้าย
  digitalWrite(IN11,HIGH);//ปล่อยกระแสไฟฟ้าออกเพื่อควบคุมทิศทางการหมุนมอเตอร์ซ้าย

}
void rewordCommand(){ //ฟังก์ชันถอยหลัง
  digitalWrite(IN8,LOW);
  digitalWrite(IN9,HIGH);
  digitalWrite(IN10,HIGH);
  digitalWrite(IN11,LOW);
}

void rightCommand(){ //ฟังก์ชันเลี้ยวขวา
  digitalWrite(IN8,LOW);
  digitalWrite(IN9,LOW);
  digitalWrite(IN10,LOW);
  digitalWrite(IN11,LOW);
}

void leftCommand(){ //ฟังก์ชันเลี้ยวซ้าย
  digitalWrite(IN8,LOW);
  digitalWrite(IN9,LOW);
  digitalWrite(IN10,LOW);
  digitalWrite(IN11,LOW);
}
void breakCar(){ //ฟังก์ชันหยุด
  digitalWrite(IN8,LOW);
  digitalWrite(IN9,LOW);
  digitalWrite(IN10,LOW);
  digitalWrite(IN11,LOW);
}
void Distance(){ //ฟันก์ชันการอ่านค่าจาก Ultrasonic หน่วยเซนติเมตร
  digitalWrite(TRIGGER_PIN, LOW); //สั่งงานให้ Trigger ปิด
  delayMicroseconds(0); //ดีเลย์ในการทำงาน หน่วยไมโครวินาที
  digitalWrite(TRIGGER_PIN, HIGH); //สั่งงานให้ Trigger เปิด
  delayMicroseconds(0); 
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH); 
  //pulseIn เป็นฟังก์ชันที่ใช้แสดงค่าความกว้างของพัลส์สัญญาณที่เข้ามาที่ขา pin โดยจะกำหนดพัลส์สัญญาณที่ค่า value (HIGH หรือ LOW)

  distance = duration / 29 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if(distance <= 15 ) {
    digitalWrite(LED_RED,HIGH);
    digitalWrite(LED_YELLOW,LOW);
    digitalWrite(LED_GREEN,LOW);
  }

   if(distance <= 30 && distance >15)  {
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_YELLOW,HIGH);
    digitalWrite(LED_GREEN,LOW);
  }

   if(distance >= 31) {
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_YELLOW,LOW);
    digitalWrite(LED_GREEN,HIGH);
  }

  }

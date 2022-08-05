#include <SoftwareSerial.h>
#include <MsTimer2.h> // 타이머 인터럽트 

SoftwareSerial mySerial(2, 3); // RX, TX

unsigned long rtime = millis();

void setup(){
  pinMode(8, OUTPUT);
  Serial.begin(115200);
  mySerial.begin(115200);

//  MsTimer2::set(500,send_msg_server); // 메소드 0.5초마다 호출 
//  MsTimer2::start();//시작
}

char rd;
char tp;

void loop(){
  
  if(mySerial.available()){
    rd = mySerial.read();
    Serial.print(rd);
    
  }

  
  if(rd =='a')
    tp = 'a';
    //Serial.write('a');
  if(rd =='b')
    tp = 'b';
  
  if (tp =='a')
    digitalWrite(8, true);
  else if(tp == 'b')
    digitalWrite(8, false);
  
//  if(Serial.read() == 'e'){ // 인터럽트 스탑 
//    MsTimer2::stop();
//  }

  
  
}

void send_msg_server(){
  mySerial.write('p');
  //Serail.println('p');
  delay(100);
}

#include <SoftwareSerial.h>
#include <DS3231.h>
#include  <Servo.h>
DS3231  rtc(SDA, SCL); // Arduino'muz üzerindeki SDA ve SCl pinlerini kullanarak DS3231 modülümüzü tanımladık.
Servo myservo; //servo nesnesi tanımladık
const int servoPin = 13; //Servo motorumuzun cıkıs pini
SoftwareSerial bt_iletisim(7,6);//tx ve rx
int buzzerPin=9; // Buzzerımızın cıkıs pini
int l1=12; // Birinci ledin cıkıs pini
int l2=11; // İkinci ledin cıkıs pini 
int l3=10; // Ücüncü ledin cıkıs pini
Time  t; //Time nesnesi
String readString; //Bluetooth modülümüzden gelen verileri eklediğimiz değişken
int alarm[6]; // 3 adet alarm bilgisini sakladıgımız dizimiz
String s,d;
   
void setup()
{
 
   myservo.attach(13);//servoyu taktıgımız pini tanıtıyoruz.
  
  pinMode(buzzerPin,OUTPUT); // Buzzer'in bağlı olduğu pini çıkış olarak ayarladık.
  pinMode(l1,OUTPUT); // Birinci ledimizin bağlı olduğu pini çıkış olarak ayarladık.
  pinMode(l2,OUTPUT); // İkinci ledimizin bağlı olduğu pini çıkış olarak ayarladık.
  pinMode(l3,OUTPUT); // Üçüncü ledimizin bağlı olduğu pini çıkış olarak ayarladık.
Serial.begin(9600); // seri ekranımızı baslattık.
bt_iletisim.begin(9600); //Bluetooth seri ekranımızı baslattık
myservo.write(180); //servomuzun ilk konumuna ayarladık
  delay(1000); //1 sn bekleme süresi
  myservo.detach(); 
 rtc.begin();//Yukarıda tanımlamıs oldugmuz rtc modülümüzü baslattık.
 
  
}
//************************SERVO MOTORUMUZU CALISTIRAN FONKSİYONUMUZ************************
  void servocalis()
{
 myservo.attach(servoPin);
    myservo.write(30);
    delay(575);
    myservo.write(180);
    delay(1500);
    myservo.detach();
    delay(5000);
  }
  
//************************SERVO MOTORUMUZU CALISTIRAN FONKSİYONUMUZ************************
   

//************** BUZZER VE LEDLERİ CALISTIRAN FONKSİYONUMUZ**************
 void buzzer()
   {
    for(int i=1;i<=2;i++)
    {
    digitalWrite(l1,HIGH);
    delay(100);
   digitalWrite(l2,HIGH);
   delay(100);
  digitalWrite(l3,HIGH);
  delay(100);
  digitalWrite(l1,LOW);
  delay(100);
  digitalWrite(l2,LOW);
  delay(100);
  digitalWrite(l3,LOW);
 delay(100);
 digitalWrite(buzzerPin,HIGH); //Buzzer'a güç göndererek ses çıkarmasını sağladık.
 delay(1000);    // 1 saniye boyunca çalmasını söyledik.
 digitalWrite(buzzerPin,LOW); //Buzzerın gücünü keserek susmasını sağladık sağladık.
 delay(1000); }}
    //************** BUZZER VE LEDLERİ CALISTIRAN FONKSİYONUMUZ**************
 //*****************ZAMAN HESABI FONKSİYONUMUZ*******************
  void zamanhesabi()
 {
   if (t.hour == alarm[0] && t.min==alarm[1] && t.sec==00)
  {buzzer();servocalis();}
    if (t.hour == alarm[2] && t.min==alarm[3] && t.sec==00)
  {buzzer();servocalis();}
   if (t.hour == alarm[4] && t.min==alarm[5] && t.sec==00)
  {buzzer();servocalis();}
    }
 //*****************ZAMAN HESABI FONKSİYONUMUZ*******************
void loop(){
  
  t = rtc.getTime();   // saat modülümÜzden verileri aldık
 while(bt_iletisim.available()){
  delay(50);
    char c=bt_iletisim.read();
    readString+=c;}
 if(readString.length()>0){
    Serial.println(readString);
    if(readString=="calistir"){buzzer();servocalis();}
    if(readString.substring(0,1)=="1") {s=readString.substring(1,3);d=readString.substring(4,6);  alarm[0]=s.toInt();alarm[1]=d.toInt();}
    if(readString.substring(0,1)=="2") { s=readString.substring(1,3);d=readString.substring(4,6);  alarm[2]=s.toInt();alarm[3]=d.toInt();}
    if(readString.substring(0,1)=="3") { s=readString.substring(1,3);d=readString.substring(4,6);  alarm[4]=s.toInt();alarm[5]=d.toInt();}
      seriyaz();
    
     readString="";
 }
zamanhesabi();
   }

void seriyaz()
{
  for(int i=0;i<6;i++)
  {
  Serial.println(alarm[i]);
  }
  }

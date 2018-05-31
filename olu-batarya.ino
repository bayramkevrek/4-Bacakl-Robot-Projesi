#define battPin1 A7  // V1
#define battPin2 A6   //V2
#define battPin3 A5   //V3
#define akimsensoru A4   //akim sensoru analog degeri
#define mosfet_gate 2 // mosfetin gate kapisina yollanacak sinyalin degisken tanimlamasi



float v1; // 1. hücre voltajı
float v2;// 2. hücre ham voltajı
float v3; // 3. hücre ham voltajı
float vcell1; // 1. hücre 
float vcell2;// 2. hücre 
float vcell3; // 3. hücre 
float akim; // akım ham değeri
int haber; // haberleşmede kullanılacak olan değişken


void setup() {
  Serial.begin(115200);
  digitalWrite(mosfet_gate,LOW);
  pinMode(mosfet_gate,OUTPUT);
 

}

void loop() {
  
  v1 = 0.004814453125 * analogRead(A5);
  vcell1 = v1;
  v2 = 0.012555130859375 * analogRead(A6);
  vcell2 = v2 - v1;
  v3 = 0.0181307490234375 * analogRead(A7);
  vcell3 = v3 - v2;
  

  akim = (4.93 / 1024 * analogRead(akimsensoru) - 2.54) / 0.185;

  if(vcell1<3 || vcell2<3 || vcell3<3){ //HÜCRELERİN GERİLİMLERİ 2 Volt'tan küçük ise 10 saniye bekle ve mosfet ile dc dc çeviricinin irtibatını kes.
   delay(10000);
   digitalWrite(mosfet_gate,LOW); // MOSFET KAPA
   
  }
  Serial.print("1. Hücre = ");
  Serial.print(vcell1);
  Serial.print(" 2. Hücre = ");
  Serial.print(vcell2);
  Serial.print(" 3. Hücre = ");
  Serial.print(vcell3);
  Serial.print(" Toplam Hücre Gerilimleri = ");
  Serial.print(v3);
  Serial.print(" Akım = ");
  Serial.println(akim);

    
     
  delay(100);

  

}

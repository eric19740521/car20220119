//本範例適合初學L298N的人
//在小車裝好後，可用本程式先測試所有線路是否都接正確
//套件可至賣場購買
//https://goods.ruten.com.tw/item/show?21826281062806
//傑森創工製作
// https://www.facebook.com/jasonshow

#include <SoftwareSerial.h>   // 引用程式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(11, 12); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數

// 左馬達控制設定
const byte LEFT1 = 8;  //IN1
const byte LEFT2 = 9;  //IN2
const byte LEFT_PWM = 10;

// 右馬達控制設定
const byte RIGHT1 = 7;  //IN3
const byte RIGHT2 = 6;  //IN4
const byte RIGHT_PWM = 5;

// 設定PWM輸出值（代表的是車子的速度）
byte motorSpeed = 130;

void forward() {  // 前進
  //左輪
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);

  //右輪。因在小車上馬達安裝方向左右兩個是相反的，所以另一隻馬達的設定要相反，兩輪才能配合。）
  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);

  analogWrite(RIGHT_PWM, motorSpeed);
}

void backward() { // 後退
  digitalWrite(LEFT1, LOW);
  digitalWrite(LEFT2, HIGH);
  analogWrite(LEFT_PWM, motorSpeed);

  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(RIGHT_PWM, motorSpeed);
}

void turnLeft() { // 左轉
  //左輪不動，右輪動（速度為0）

  analogWrite(LEFT_PWM, 0);

  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(RIGHT_PWM, motorSpeed);
}

void turnRight() {  // 右轉
  //右輪不動，左輪動（速度為0）

  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);

  analogWrite(RIGHT_PWM, 0);
}

void stopMotor() {  //停止，兩輪速度為0

  analogWrite(LEFT_PWM, 0);

  analogWrite(RIGHT_PWM, 0);
}

void setup() {

  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");

  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(9600);

  //pinMode(4, OUTPUT);


  //設定每一個PIN的模式
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);

  //forward();

}

void loop() {
  //forward();


  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);





    switch (val) {
      //      case '1':
      //        digitalWrite(4, HIGH);   //開燈
      //        break;
      //      case  '0':
      //        digitalWrite(4, LOW);     //關燈
      //        break;
      case 'w':   // 接收到'w'，前進。
        forward();
        break;
      case 'x':   // 接收到'x'，後退。
        backward();
        break;
      case 'a':   // 接收到'a'，左轉。
        turnLeft();
        break;
      case 'd':   // 接收到'd'，右轉。
        turnRight();
        break;
      case 's':   // 接收到's'，停止。
        stopMotor();
        break;
    }

  }
  //delay(500);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);



  //本範例會讓車子向前、向後、向左、向右、停止，各2秒，然後不斷重複

  //  forward();
  //  delay(4000);
  //  backward();
  //  delay(2000);
  //  turnLeft();
  //  delay(2000);
  //  turnRight();
  //  delay(2000);
  //  stopMotor();
  //  delay(2000);
}

/*

Arduino_RFID_check_in_machine

Author : LukeTseng ( 鼓山高中 _ 電腦社社長 )
Date : 2024 / 04 / 11 初製作

Version : 1.0.0 版本

Update : None
 
*/
#include <SPI.h>  // Arduino 內建函式庫
#include <MFRC522.h>  // RFID RC522 函式庫
#define RST_PIN      A0  // 讀卡機的重置腳位
#define SS_PIN       10  // 晶片選擇腳位
#define IDENTIFY_PIN 2 // 晶片識別 UID 按鈕腳位
#define LOADING_PIN 3 // 晶片讀取按鈕腳位
#define RESET_PIN 4 // 重置打卡紀錄按鈕腳位
#define BUZZER_PIN 5 // 蜂鳴器腳位

#include "LiquidCrystal_I2C.h"  // LCD 面板函式庫

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE); // LCD 初始化面板

bool stu[37] = {false}; // 使 stu 陣列所有值為 false, 37 可依據班級人數修改.

bool Is_Identify = false; // 判斷是否為 identify 模式

struct RFIDTag {   // 定義結構, 包含 2 members 
   byte uid[4];   // byte uid[4], 一個 4 位元組 (byte) 的陣列, 用來儲存 RFID 標籤的唯一識別碼 (UID)
   char *name;  // 指向字串的指標, 用來儲存與 RFID 標籤相關的名稱
};
 
struct RFIDTag tags[] = {  // 初始化結構資料 (結構陣列 tags), 請自行修改RFID識別碼
  {{0xB2,0xDB,0x77,0x15}, "Name: Yao"},
  {{0x1,0x2,0x3,0x4}, "Name: Dad"},
};

byte totalTags = sizeof(tags) / sizeof(RFIDTag);  // 計算結構資料筆數, 結果為 1

MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

const int PINS[] = {IDENTIFY_PIN, LOADING_PIN, RESET_PIN}; // 宣告整數陣列常數 PINS

const char* MESSAGES[][2] = {
    {"Identify mode ha", "s enabled."},
    {"Loading mode has", "enabled."},
    {"Record has been", "reset."}
};

void print_message(const char* line_1, const char* line_2, int delay_time) {  // 定義函數 print_message 用於簡化內容
    lcd.setCursor(0, 0);
    lcd.print(line_1);
    lcd.setCursor(0, 1);
    lcd.print(line_2);
    delay(delay_time);
    lcd.clear();
}

void buzz(int sec) {  // 定義函數 buzz 用於簡化蜂鳴器程式碼
    digitalWrite(BUZZER_PIN, HIGH);
    delay(sec);
    digitalWrite(BUZZER_PIN, LOW);
}
 
void setup() {

  pinMode(BUZZER_PIN, OUTPUT); // 蜂鳴器預設輸出
  digitalWrite(BUZZER_PIN, LOW); // 蜂鳴器預設低電位(不發出聲音)
  
  for (int i = IDENTIFY_PIN; i <= RESET_PIN; i++){
    pinMode(i, INPUT); // 按鈕預設輸入
    digitalWrite(i, HIGH); // 按鈕預設高電位
  }

  SPI.begin();
  
  mfrc522.PCD_Init();       // 初始化MFRC522讀卡機模組

  lcd.begin(16,2); // 指定 LCD 尺寸像素格 16 x 2
  lcd.backlight();
  delay(1000); // 延時一秒後繼續

  lcd.setCursor(0,0);
  lcd.print("GuShan Check in");   // 初始化訊息
  lcd.setCursor(0,1);
  lcd.print("Nice to meet you");
  delay(3000); // 延時三秒後繼續
  lcd.clear();
}
 
void loop() {
    for (int i = 0; i < 3; i++) {
        if (digitalRead(PINS[i]) == LOW) {
            switch (i) {
                case 0:
                    Is_Identify = true;
                    break;
                case 1:
                    Is_Identify = false;
                    break;
                case 2:
                    for (int j = 0; j < 37; j++) {
                        stu[j] = false;
                    }
                    break;
            }
            print_message(MESSAGES[i][0], MESSAGES[i][1], 2000);
        }
    }
    // 確認是否有新卡片
    if (Is_Identify == true){
      byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522.uid.size;   // 取得UID的長度
      lcd.setCursor(0,0);
      lcd.print("UID:");
      lcd.setCursor(0,1);
      if ((mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) && Is_Identify == true) {
        for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
          lcd.print(id[i], HEX);       // 以16進位顯示UID值
          lcd.print(" ");
        }
        delay(5000);
        lcd.clear();
      }
    }
    else{
      lcd.setCursor(0,0);
      lcd.print("Waiting for card");
      if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
        byte idSize = mfrc522.uid.size;   // 取得UID的長度
        bool foundTag = false;    // 是否找到紀錄中的標籤，預設為「否」。
        
        // 根據卡片回應的SAK值（mfrc522.uid.sak）判斷卡片類型
        MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        Serial.println();
      
      for (byte i = 0; i < totalTags; i++) {
        if (memcmp(tags[i].uid, id, idSize) == 0) {  // 比對陣列資料值
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(tags[i].name);

            if (stu[0]) {
                lcd.setCursor(0, 1);
                lcd.print("U've checked in");
                buzz(150);
            } else {
                lcd.setCursor(0, 1);
                lcd.print("U check in.");
                buzz(150);
                delay(50);
                buzz(150);
                stu[0] = true;  // 設定 stu[0] 為 true
            }

            delay(3000);
            lcd.clear();
            foundTag = true;  // 設定成「找到標籤了！」
            break;
        }
      }
 
      if (!foundTag) {  // 若掃描到紀錄之外的標籤，則顯示"Wrong card!"。
        lcd.clear();
        lcd.print("Wrong card!");
        buzz(500);
        delay(3000);
        lcd.clear();
        mfrc522.PICC_HaltA();  // 讓卡片進入停止模式      
        }
      } 
    }
}

# Arduino_RFID_check_in_machine

This RFID (Radio Frequency Identification system) was combined into a sign-in machine by me. The motivation for making this set of devices was inspired by my classmates who said to me, "I can create a sign-in machine."

# Version（版本歷史）

1.0.0 - Release

1.0.1 - Make the code look more concise and maintainable.
(使程式碼看起來更簡潔且具維護性)

# Librarys （函式庫）

New-LiquidCrystal : https://github.com/fmalpartida/New-LiquidCrystal/tree/master

MFRC522 : https://www.arduino.cc/reference/en/libraries/mfrc522/

# Material (reference) （素材（參考用））

- Arduino Uno x 1
- RFID x 1
- Button x 3 (For Mode Change x 2, For Clear Record x 1) （給模式切換的 x 2，給清除打卡紀錄的 x 1）
- Arduino 1602 LCD Displayer x 1（1602 LCD 顯示屏幕 x 1）
- BreadBoard x 1 （麵包板 x 1）
- Buzzer x 1 （蜂鳴器 x 1）

# Comments Language & Introduction （註解語言 & 基本介紹）

Comments Language : Traditional Chinese

註解語言：繁體中文

If I have time, I will make another English version of the annotations.

如果我有時間的話，我會另外做一個英文版本的註解。

This program is primarily used to integrate check-in or sign-in processes with RFID technology. It can utilize magnetic cards and RFID devices for sensing.

Simple Explanation of the Principle: Magnetic cards serve as RFID sensors, with each magnetic card having an RFID tag. To identify a magnetic card, we need the RFID tag. Magnetic cards and RFID use electromagnetic induction for detection, with an antenna emitting radio waves that generate an electromagnetic field. When a magnetic card comes close to the RFID, it generates an induced current, and at this point, the RFID detects the presence of the magnetic card through the induced current.

本程式主要用於打卡機（check-in or sign-in）與 RFID 技術的結合，能夠使用磁卡與 RFID 裝置進行感應。

簡易原理解釋 : 磁卡做為 RFID 的感應器，每一個磁卡都具有 RFID Tag，要辨識磁卡我們就需要 RFID Tag。磁卡與 RFID 利用電磁感應進行感應，會透過天線發射無線電波，這些無線電波會產生一個電磁場，而當磁卡靠近 RFID 時，則會產生感應電流，此時 RFID 就會透過感應電流感應到磁卡的存在。

made by LukeTseng ( 鼓山高中 _ 電腦社社長 ).

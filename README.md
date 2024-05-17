# Arduino_RFID_check_in_machine

This RFID (Radio Frequency Identification system) was combined into a sign-in machine by me. The motivation for making this set of devices was inspired by my classmates who said to me, "I can create a sign-in machine."

# Librarys （函式庫）

New-LiquidCrystal : https://github.com/fmalpartida/New-LiquidCrystal/tree/master

MFRC522 : https://www.arduino.cc/reference/en/libraries/mfrc522/

# Comments Language & Introduction （註解語言 & 基本介紹）

Comments Language : Traditional Chinese

註解語言：繁體中文

If I have time, I will make another English version of the annotations.

如果我有時間的話，我會另外做一個英文版本的註解。

This program is primarily used to integrate check-in or sign-in processes with RFID technology. It can utilize magnetic cards and RFID devices for sensing.

Simple explanation of the principle: Magnetic cards function as RFID sensors. Each magnetic card has an RFID tag. To identify the magnetic card, we need an RFID tag. Magnetic cards and RFID use electromagnetic induction for communication. When the magnetic card moves relative to the RFID magnetic field, an induced current will be generated. At this time, the RFID will sense the presence of the magnetic card through the induced current.

本程式主要用於打卡機（check-in or sign-in）與 RFID 技術的結合，能夠使用磁卡與 RFID 裝置進行感應。

簡易原理解釋 : 磁卡做為RFID的感應器，每一個磁卡都具有 RFID Tag，要辨識磁卡我們就需要 RFID Tag。磁卡與 RFID 利用電磁感應進行感應，當磁卡有相對運動在 RFID 磁場周圍時，則會產生感應電流，此時 RFID 就會透過感應電流感應到磁卡的存在。

made by LukeTseng ( 鼓山高中 _ 電腦社社長 ).

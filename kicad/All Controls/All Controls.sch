EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 1100 1250 1550 800 
U 6184ED44
F0 "BasicControls" 50
F1 "BasicControls.sch" 50
F2 "SER_OUT" O R 2650 1400 50 
F3 "CLK" I L 1100 1400 50 
F4 "~CE" I L 1100 1550 50 
F5 "SH\\~LD~" I L 1100 1700 50 
F6 "VCC" I R 2650 1650 50 
F7 "GND" I R 2650 1850 50 
F8 "SER_IN" I L 1100 1850 50 
$EndSheet
$Sheet
S 1150 2700 1550 1650
U 619634B0
F0 "OtherControls" 50
F1 "OtherControls.sch" 50
F2 "SER_OUT" O R 2700 2950 50 
F3 "CLK" I L 1150 2950 50 
F4 "~CE" I L 1150 3100 50 
F5 "SH\\~LD~" I L 1150 3250 50 
F6 "VCC" I R 2700 3100 50 
F7 "GND" I R 2700 3250 50 
F8 "SERCLK" I R 2700 3800 50 
F9 "~OE" I L 1150 3650 50 
F10 "LED_SER_IN" I R 2700 3500 50 
F11 "RCLK" I R 2700 3650 50 
F12 "~SRCLR" I L 1150 3500 50 
F13 "Phase" O R 2700 4000 50 
F14 "Brightness" O R 2700 4100 50 
F15 "Contrast" O R 2700 4200 50 
F16 "Chroma" O R 2700 4300 50 
$EndSheet
Wire Wire Line
	2700 2950 2750 2950
Wire Wire Line
	2750 2950 2750 2500
Wire Wire Line
	2750 2500 1000 2500
Wire Wire Line
	1000 2500 1000 1850
Wire Wire Line
	1000 1850 1100 1850
$Comp
L MCU_Module:Arduino_Nano_Every Arduino1
U 1 1 619E6CF2
P 7350 2250
F 0 "Arduino1" H 7350 1161 50  0000 C CNN
F 1 "Arduino_Nano_Every" H 7350 1070 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 7350 2250 50  0001 C CIN
F 3 "https://content.arduino.cc/assets/NANOEveryV3.0_sch.pdf" H 7350 2250 50  0001 C CNN
	1    7350 2250
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0101
U 1 1 619EE318
P 4500 850
F 0 "#PWR0101" H 4500 700 50  0001 C CNN
F 1 "VCC" H 4515 1023 50  0000 C CNN
F 2 "" H 4500 850 50  0001 C CNN
F 3 "" H 4500 850 50  0001 C CNN
	1    4500 850 
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0102
U 1 1 619EEE7B
P 4850 850
F 0 "#PWR0102" H 4850 650 50  0001 C CNN
F 1 "GNDPWR" H 4854 696 50  0000 C CNN
F 2 "" H 4850 800 50  0001 C CNN
F 3 "" H 4850 800 50  0001 C CNN
	1    4850 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 850  4500 1000
Wire Wire Line
	4850 850  4650 850 
Wire Wire Line
	4650 850  4650 1850
Wire Wire Line
	4650 1850 3000 1850
Wire Wire Line
	3000 1850 3000 3250
Wire Wire Line
	3000 3250 2700 3250
Connection ~ 3000 1850
Wire Wire Line
	3000 1850 2650 1850
Wire Wire Line
	2700 3100 2900 3100
Wire Wire Line
	2900 3100 2900 1650
Wire Wire Line
	2900 1650 2650 1650
Wire Wire Line
	2650 1400 6600 1400
Wire Wire Line
	6600 1400 6600 1750
Wire Wire Line
	6600 1750 6850 1750
Wire Wire Line
	1100 1400 1050 1400
Wire Wire Line
	1050 1400 1050 1150
Wire Wire Line
	1050 1150 2750 1150
Wire Wire Line
	2750 1150 2750 1300
Wire Wire Line
	2750 1300 6500 1300
Wire Wire Line
	6500 1300 6500 1850
Wire Wire Line
	6500 1850 6850 1850
Wire Wire Line
	1100 1550 950  1550
Wire Wire Line
	950  1550 950  1050
Wire Wire Line
	950  1050 2850 1050
Wire Wire Line
	2850 1050 2850 1200
Wire Wire Line
	2850 1200 6400 1200
Wire Wire Line
	6400 1200 6400 1950
Wire Wire Line
	6400 1950 6850 1950
Wire Wire Line
	1100 1700 850  1700
Wire Wire Line
	850  1700 850  950 
Wire Wire Line
	850  950  2950 950 
Wire Wire Line
	2950 950  2950 1100
Wire Wire Line
	2950 1100 6300 1100
Wire Wire Line
	6300 1100 6300 2050
Wire Wire Line
	6300 2050 6850 2050
Wire Wire Line
	1050 1400 1050 2950
Wire Wire Line
	1050 2950 1150 2950
Connection ~ 1050 1400
Wire Wire Line
	950  1550 950  3100
Wire Wire Line
	950  3100 1150 3100
Connection ~ 950  1550
Wire Wire Line
	850  1700 850  3250
Wire Wire Line
	850  3250 1150 3250
Connection ~ 850  1700
Wire Wire Line
	4650 1850 4650 3250
Wire Wire Line
	4650 3250 6250 3250
Connection ~ 4650 1850
Wire Wire Line
	4500 1000 6450 1000
Wire Wire Line
	7250 1000 7250 1250
Wire Wire Line
	2900 1650 6200 1650
Wire Wire Line
	6200 1650 6200 900 
Wire Wire Line
	6200 900  7550 900 
Wire Wire Line
	7550 900  7550 1250
Connection ~ 2900 1650
NoConn ~ 7450 1250
Wire Wire Line
	3100 3800 2700 3800
Wire Wire Line
	3100 2950 6850 2950
Wire Wire Line
	2700 3650 3100 3650
Wire Wire Line
	3100 2950 3100 3650
Connection ~ 3100 3650
Wire Wire Line
	3100 3650 3100 3800
Wire Wire Line
	3100 4450 1050 4450
Connection ~ 3100 3800
Connection ~ 1050 2950
Wire Wire Line
	6850 2750 3200 2750
Wire Wire Line
	3200 2750 3200 3500
Wire Wire Line
	3200 3500 2700 3500
Wire Wire Line
	6850 2850 3300 2850
Wire Wire Line
	3300 4550 950  4550
Wire Wire Line
	950  3650 1150 3650
Wire Wire Line
	1150 3500 850  3500
Wire Wire Line
	850  4650 3400 4650
Wire Wire Line
	3400 2550 6850 2550
Connection ~ 6250 3250
Wire Wire Line
	6250 3250 7350 3250
$Sheet
S 5250 6600 550  650 
U 61BE7C26
F0 "Brightness" 50
F1 "RotaryEncoder.sch" 50
F2 "VCC" I R 5800 6750 50 
F3 "GND" I R 5800 6850 50 
F4 "A" O R 5800 6950 50 
F5 "B" O R 5800 7050 50 
F6 "SW" O R 5800 7150 50 
$EndSheet
$Sheet
S 5250 5650 550  650 
U 61C0EEA4
F0 "Phase" 50
F1 "RotaryEncoder.sch" 50
F2 "VCC" I R 5800 5800 50 
F3 "GND" I R 5800 5900 50 
F4 "A" O R 5800 6000 50 
F5 "B" O R 5800 6100 50 
F6 "SW" O R 5800 6200 50 
$EndSheet
$Sheet
S 5250 4700 550  650 
U 61C1395E
F0 "Chroma" 50
F1 "RotaryEncoder.sch" 50
F2 "VCC" I R 5800 4850 50 
F3 "GND" I R 5800 4950 50 
F4 "A" O R 5800 5050 50 
F5 "B" O R 5800 5150 50 
F6 "SW" O R 5800 5250 50 
$EndSheet
$Sheet
S 5250 3800 550  650 
U 61C13BC1
F0 "Contrast" 50
F1 "RotaryEncoder.sch" 50
F2 "VCC" I R 5800 3950 50 
F3 "GND" I R 5800 4050 50 
F4 "A" O R 5800 4150 50 
F5 "B" O R 5800 4250 50 
F6 "SW" O R 5800 4350 50 
$EndSheet
Wire Wire Line
	6250 6850 5800 6850
Wire Wire Line
	5800 5900 6250 5900
Connection ~ 6250 5900
Wire Wire Line
	6250 5900 6250 6850
Wire Wire Line
	5800 4950 6250 4950
Wire Wire Line
	6250 3250 6250 4050
Connection ~ 6250 4950
Wire Wire Line
	6250 4950 6250 5900
Wire Wire Line
	5800 4050 6250 4050
Connection ~ 6250 4050
Wire Wire Line
	6250 4050 6250 4950
Wire Wire Line
	6450 1000 6450 3950
Wire Wire Line
	6450 6750 5800 6750
Connection ~ 6450 1000
Wire Wire Line
	6450 1000 7250 1000
Wire Wire Line
	5800 5800 6450 5800
Connection ~ 6450 5800
Wire Wire Line
	6450 5800 6450 6750
Wire Wire Line
	5800 4850 6450 4850
Connection ~ 6450 4850
Wire Wire Line
	6450 4850 6450 5500
Wire Wire Line
	5800 3950 6450 3950
Connection ~ 6450 3950
Wire Wire Line
	6450 3950 6450 4850
Wire Wire Line
	7850 2950 7850 4150
Wire Wire Line
	7850 4150 5800 4150
Wire Wire Line
	7850 2850 7950 2850
Wire Wire Line
	7950 2850 7950 4250
Wire Wire Line
	7950 4250 5800 4250
Wire Wire Line
	7850 2750 8050 2750
Wire Wire Line
	8050 2750 8050 5050
Wire Wire Line
	8050 5050 5800 5050
Wire Wire Line
	7850 2650 8150 2650
Wire Wire Line
	8150 2650 8150 5150
Wire Wire Line
	8150 5150 5800 5150
Wire Wire Line
	7850 2550 8250 2550
Wire Wire Line
	8250 2550 8250 6000
Wire Wire Line
	8250 6000 5800 6000
Wire Wire Line
	7850 2450 8350 2450
Wire Wire Line
	8350 2450 8350 6100
Wire Wire Line
	8350 6100 5800 6100
Wire Wire Line
	7850 2350 8450 2350
Wire Wire Line
	8450 2350 8450 6950
Wire Wire Line
	8450 6950 5800 6950
Wire Wire Line
	7850 2250 8550 2250
Wire Wire Line
	8550 2250 8550 7050
Wire Wire Line
	8550 7050 5800 7050
NoConn ~ 7850 1650
NoConn ~ 7850 1750
NoConn ~ 7850 2050
NoConn ~ 6850 2350
NoConn ~ 6850 2450
$Comp
L Interface_UART:MAX485E RS1
U 1 1 61C62019
P 4200 4650
F 0 "RS1" H 4200 3869 50  0000 C CNN
F 1 "MAX485E" H 4200 3960 50  0000 C CNN
F 2 "" H 4200 3950 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX1487E-MAX491E.pdf" H 4200 4700 50  0001 C CNN
	1    4200 4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 3250 4200 3250
Wire Wire Line
	4200 3250 4200 4050
Connection ~ 4650 3250
Wire Wire Line
	6450 5500 4200 5500
Wire Wire Line
	4200 5500 4200 5150
Connection ~ 6450 5500
Wire Wire Line
	6450 5500 6450 5800
Wire Wire Line
	6850 1450 4750 1450
Wire Wire Line
	4750 1450 4750 4450
Wire Wire Line
	4750 4450 4600 4450
Wire Wire Line
	6850 1550 6850 1600
Wire Wire Line
	6850 1600 4850 1600
Wire Wire Line
	4850 1600 4850 4750
Wire Wire Line
	4850 4750 4600 4750
Wire Wire Line
	6850 2150 4950 2150
Wire Wire Line
	4950 2150 4950 4550
Wire Wire Line
	4950 4550 4600 4550
Wire Wire Line
	6850 2250 5050 2250
Wire Wire Line
	5050 2250 5050 4650
Wire Wire Line
	5050 4650 4600 4650
Wire Wire Line
	1050 2950 1050 4450
Wire Wire Line
	950  3650 950  4550
Wire Wire Line
	850  3500 850  4650
Wire Wire Line
	3100 3800 3100 4450
Wire Wire Line
	3300 2850 3300 4550
Wire Wire Line
	3400 2550 3400 4650
Wire Wire Line
	5900 4350 5900 4600
Wire Wire Line
	5900 4600 5150 4600
Wire Wire Line
	5150 4600 5150 5200
Wire Wire Line
	5150 5200 2750 5200
Wire Wire Line
	2750 5200 2750 4200
Wire Wire Line
	2750 4200 2700 4200
Wire Wire Line
	5800 4350 5900 4350
Wire Wire Line
	5800 5250 5900 5250
Wire Wire Line
	5900 5250 5900 5450
Wire Wire Line
	5900 5450 2800 5450
Wire Wire Line
	2800 5450 2800 4300
Wire Wire Line
	2800 4300 2700 4300
Wire Wire Line
	5800 6200 5900 6200
Wire Wire Line
	5900 6200 5900 5550
Wire Wire Line
	5900 5550 2850 5550
Wire Wire Line
	2850 5550 2850 4000
Wire Wire Line
	2850 4000 2700 4000
Wire Wire Line
	5800 7150 5900 7150
Wire Wire Line
	5900 7150 5900 6450
Wire Wire Line
	5900 6450 2900 6450
Wire Wire Line
	2900 6450 2900 4100
Wire Wire Line
	2900 4100 2700 4100
NoConn ~ 3800 4750
NoConn ~ 3800 4450
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 616DE7A9
P 8650 2800
F 0 "A1" H 8650 3981 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 8650 3890 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 8650 2800 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 8650 2800 50  0001 C CNN
	1    8650 2800
	1    0    0    -1  
$EndComp
Entry Wire Line
	8000 2300 8100 2400
Entry Wire Line
	8000 2400 8100 2500
Entry Wire Line
	8000 2500 8100 2600
Entry Wire Line
	8000 2600 8100 2700
Entry Wire Line
	8000 2700 8100 2800
$Comp
L Device:R R1
U 1 1 616E3AD6
P 6550 3650
F 0 "R1" H 6620 3696 50  0000 L CNN
F 1 "R" H 6620 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 6480 3650 50  0001 C CNN
F 3 "~" H 6550 3650 50  0001 C CNN
	1    6550 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 616E4AE1
P 6800 3650
F 0 "R2" H 6870 3696 50  0000 L CNN
F 1 "R" H 6870 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 6730 3650 50  0001 C CNN
F 3 "~" H 6800 3650 50  0001 C CNN
	1    6800 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 616E4DC6
P 7050 3650
F 0 "R3" H 7120 3696 50  0000 L CNN
F 1 "R" H 7120 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 6980 3650 50  0001 C CNN
F 3 "~" H 7050 3650 50  0001 C CNN
	1    7050 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 616E50DC
P 7300 3650
F 0 "R4" H 7370 3696 50  0000 L CNN
F 1 "R" H 7370 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 7230 3650 50  0001 C CNN
F 3 "~" H 7300 3650 50  0001 C CNN
	1    7300 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 616E5346
P 7550 3650
F 0 "R5" H 7620 3696 50  0000 L CNN
F 1 "R" H 7620 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 7480 3650 50  0001 C CNN
F 3 "~" H 7550 3650 50  0001 C CNN
	1    7550 3650
	1    0    0    -1  
$EndComp
Entry Wire Line
	6500 1850 6600 1950
Entry Wire Line
	6750 1850 6850 1950
Entry Wire Line
	7000 1850 7100 1950
Entry Wire Line
	7250 1850 7350 1950
Entry Wire Line
	7500 1850 7600 1950
Wire Wire Line
	6600 1950 6600 2000
Wire Wire Line
	8100 2400 8150 2400
Wire Wire Line
	8100 2500 8150 2500
Wire Wire Line
	8100 2600 8150 2600
Wire Wire Line
	8100 2700 8150 2700
Wire Wire Line
	8100 2800 8150 2800
Text Label 6600 2000 0    50   ~ 0
b0
Text Label 8150 2400 2    50   ~ 0
b0
Entry Wire Line
	8400 4100 8500 4000
Wire Wire Line
	8500 4000 8500 3900
Wire Wire Line
	8500 3900 8550 3900
Entry Wire Line
	6400 4100 6500 4000
Entry Wire Line
	6700 4100 6800 4000
Entry Wire Line
	6950 4100 7050 4000
Entry Wire Line
	7250 4100 7350 4000
Entry Wire Line
	7500 4100 7600 4000
Wire Wire Line
	7600 4000 7600 3800
Wire Wire Line
	7600 3800 7550 3800
Wire Wire Line
	7300 3800 7300 4000
Wire Wire Line
	7300 4000 7350 4000
Wire Wire Line
	7050 3800 7050 4000
Wire Wire Line
	6800 3800 6800 4000
Wire Wire Line
	6550 3800 6550 4000
Wire Wire Line
	6550 4000 6500 4000
$Comp
L project:SW_MEC_5E_copy SW1
U 1 1 6170D811
P 6400 2000
F 0 "SW1" H 6400 1897 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 6445 2248 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 6400 2300 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 6400 2300 50  0001 C CNN
	1    6400 2000
	-1   0    0    1   
$EndComp
Text Label 6550 3800 3    50   ~ 0
g1
Wire Wire Line
	6600 3500 6550 3500
Wire Bus Line
	8850 1600 6000 1600
Entry Wire Line
	8850 1600 8950 1500
Wire Wire Line
	8950 1500 8950 1800
Wire Wire Line
	8950 1800 8850 1800
Entry Wire Line
	6000 2300 6100 2200
Text Label 8850 1800 0    50   ~ 0
5v
Text Label 6200 2100 2    50   ~ 0
5v
$Comp
L project:SW_MEC_5E_copy SW2
U 1 1 61718005
P 6650 2250
F 0 "SW2" H 6650 2147 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 6695 2498 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 6650 2550 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 6650 2550 50  0001 C CNN
	1    6650 2250
	-1   0    0    1   
$EndComp
$Comp
L project:SW_MEC_5E_copy SW3
U 1 1 617189CB
P 6900 2500
F 0 "SW3" H 6900 2397 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 6945 2748 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 6900 2800 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 6900 2800 50  0001 C CNN
	1    6900 2500
	-1   0    0    1   
$EndComp
$Comp
L project:SW_MEC_5E_copy SW5
U 1 1 61719816
P 7400 3000
F 0 "SW5" H 7400 2897 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 7445 3248 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 7400 3300 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 7400 3300 50  0001 C CNN
	1    7400 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	6850 3500 6800 3500
Wire Wire Line
	7100 3500 7050 3500
Wire Wire Line
	7350 3500 7300 3500
Wire Wire Line
	7600 3400 7550 3400
Wire Wire Line
	7550 3400 7550 3500
Wire Wire Line
	6850 1950 6850 2250
Wire Wire Line
	7100 1950 7100 2500
Wire Wire Line
	7350 1950 7350 2750
Wire Wire Line
	7600 1950 7600 3000
Entry Wire Line
	6000 2750 6100 2650
Entry Wire Line
	6000 2900 6100 2800
Entry Wire Line
	6000 3050 6100 2950
Entry Wire Line
	6000 3200 6100 3100
Text Label 6450 2350 2    50   ~ 0
5v
Text Label 6700 2600 2    50   ~ 0
5v
Text Label 6950 2850 2    50   ~ 0
5v
Text Label 7200 3100 2    50   ~ 0
5v
Text Label 6850 2250 0    50   ~ 0
b2
Text Label 7100 2500 0    50   ~ 0
b1
Text Label 7350 2750 0    50   ~ 0
b4
Text Label 7600 3000 0    50   ~ 0
b3
Text Label 8150 2500 2    50   ~ 0
b1
Text Label 8150 2600 2    50   ~ 0
b2
Text Label 8150 2700 2    50   ~ 0
b3
Text Label 8150 2800 2    50   ~ 0
b4
Text Label 6800 3800 3    50   ~ 0
g1
Text Label 7050 3800 3    50   ~ 0
g1
Text Label 7300 3800 3    50   ~ 0
g1
Text Label 7550 3800 3    50   ~ 0
g1
Wire Wire Line
	6600 2100 6600 3500
Wire Wire Line
	6200 2100 6100 2100
Wire Wire Line
	6100 2100 6100 2200
Wire Wire Line
	6450 2350 6450 2650
Wire Wire Line
	6450 2650 6100 2650
Wire Wire Line
	6850 2350 6850 3500
$Comp
L project:SW_MEC_5E_copy SW4
U 1 1 617191B1
P 7150 2750
F 0 "SW4" H 7150 2647 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 7195 2998 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 7150 3050 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 7150 3050 50  0001 C CNN
	1    7150 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	6100 2800 6700 2800
Wire Wire Line
	6700 2800 6700 2600
Wire Wire Line
	7100 2600 7100 3500
Wire Wire Line
	6100 2950 6950 2950
Wire Wire Line
	6950 2950 6950 2850
Wire Wire Line
	7350 2850 7350 3500
Wire Wire Line
	6100 3100 7200 3100
Wire Wire Line
	7600 3400 7600 3100
Text Label 8750 3900 0    50   ~ 0
g2
Text Label 8650 3900 0    50   ~ 0
g1
Entry Wire Line
	8550 4100 8650 4000
Text Label 8550 3900 0    50   ~ 0
g0
NoConn ~ 9150 2400
NoConn ~ 9150 2600
NoConn ~ 9150 2800
NoConn ~ 9150 2900
NoConn ~ 9150 3000
NoConn ~ 9150 3100
NoConn ~ 9150 3200
NoConn ~ 9150 3300
NoConn ~ 9150 3500
NoConn ~ 9150 3600
NoConn ~ 8150 3000
NoConn ~ 8150 3300
NoConn ~ 8150 3200
NoConn ~ 8150 3100
NoConn ~ 8750 1800
NoConn ~ 6200 2000
NoConn ~ 6450 2250
NoConn ~ 6700 2500
NoConn ~ 6950 2750
NoConn ~ 7200 3000
$Comp
L project:TLL_TO_RS485 U1
U 1 1 61766480
P 7850 1350
F 0 "U1" H 7850 1925 50  0000 C CNN
F 1 "TLL_TO_RS485" H 7850 1834 50  0000 C CNN
F 2 "bkm10rduino:TLL_RS485" H 7850 1350 50  0001 C CNN
F 3 "" H 7850 1350 50  0001 C CNN
	1    7850 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3950 9400 1400
Wire Wire Line
	9400 1400 7400 1400
Wire Wire Line
	7400 1300 7400 1350
Wire Wire Line
	8550 1800 8550 1450
Wire Wire Line
	8550 1450 7250 1450
Wire Wire Line
	7250 1450 7250 1000
Wire Wire Line
	7250 1000 7400 1000
Entry Wire Line
	8000 3300 8100 3400
Entry Wire Line
	8000 3400 8100 3500
Entry Wire Line
	8000 2100 8100 2200
Entry Wire Line
	8000 2200 8100 2300
Wire Wire Line
	8100 2200 8150 2200
Wire Wire Line
	8100 2300 8150 2300
Wire Wire Line
	8100 3400 8150 3400
Wire Wire Line
	8100 3500 8150 3500
Text Label 8150 3400 2    50   ~ 0
DE
Text Label 8150 3500 2    50   ~ 0
RE
Entry Wire Line
	7750 1850 7850 1750
Entry Wire Line
	7900 1850 8000 1750
Wire Wire Line
	8000 1750 8000 1550
Wire Wire Line
	8000 1550 8450 1550
Wire Wire Line
	8450 1550 8450 1000
Wire Wire Line
	8450 1000 8300 1000
Wire Wire Line
	7850 1750 7850 1500
Wire Wire Line
	7850 1500 8300 1500
Wire Wire Line
	8300 1500 8300 1300
Text Label 8300 1100 0    50   ~ 0
DE
Text Label 8300 1200 0    50   ~ 0
RE
Entry Wire Line
	8000 1900 8100 1800
Entry Wire Line
	8000 2000 8100 1900
Wire Wire Line
	8350 1100 8300 1100
Wire Wire Line
	8100 1650 8400 1650
Wire Wire Line
	8400 1650 8400 1200
Wire Wire Line
	8400 1200 8300 1200
Wire Wire Line
	8100 1900 8100 1850
Wire Wire Line
	8100 1850 8350 1850
Wire Wire Line
	8350 1100 8350 1850
Wire Wire Line
	8100 1800 8100 1650
Text Label 8150 2200 2    50   ~ 0
RX
Text Label 8150 2300 2    50   ~ 0
TX
Text Label 8300 1300 0    50   ~ 0
RX
Text Label 8300 1000 0    50   ~ 0
TX
$Comp
L project:6_PIN_HEADER H1
U 1 1 61784A0C
P 6300 1100
F 0 "H1" V 5785 1333 50  0000 C CNN
F 1 "6_PIN_HEADER" V 5876 1333 50  0000 C CNN
F 2 "bkm10rduino:6_PIN_HEADER" H 6300 1000 50  0001 C CNN
F 3 "" H 6300 1000 50  0001 C CNN
	1    6300 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	6750 850  7250 850 
Wire Wire Line
	7250 850  7250 1000
Connection ~ 7250 1000
Wire Wire Line
	6750 1350 7400 1350
Connection ~ 7400 1350
Wire Wire Line
	7400 1350 7400 1400
Wire Wire Line
	6750 950  7050 950 
Wire Wire Line
	7050 950  7050 1100
Wire Wire Line
	7050 1100 7400 1100
Wire Wire Line
	6750 1050 6950 1050
Wire Wire Line
	6950 1050 6950 1150
Wire Wire Line
	6950 1150 7400 1150
Wire Wire Line
	7400 1150 7400 1200
NoConn ~ 6750 1150
NoConn ~ 6750 1250
NoConn ~ 9150 2200
NoConn ~ 8150 2900
Wire Wire Line
	8650 3900 8650 4000
Wire Wire Line
	9400 3950 8750 3950
Wire Bus Line
	6000 1600 6000 3350
Wire Bus Line
	6500 1850 8000 1850
Wire Bus Line
	6050 4100 8750 4100
Wire Bus Line
	8000 1850 8000 3500
Wire Wire Line
	8750 3950 8750 3900
$EndSCHEMATC

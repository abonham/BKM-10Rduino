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
P 6750 4250
F 0 "A1" H 6750 5431 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 6750 5340 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 6750 4250 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 6750 4250 50  0001 C CNN
	1    6750 4250
	1    0    0    -1  
$EndComp
Entry Wire Line
	6100 3750 6200 3850
Entry Wire Line
	6100 3850 6200 3950
Entry Wire Line
	6100 3950 6200 4050
Entry Wire Line
	6100 4050 6200 4150
Entry Wire Line
	6100 4150 6200 4250
$Comp
L Device:R R1
U 1 1 616E3AD6
P 4650 5100
F 0 "R1" H 4720 5146 50  0000 L CNN
F 1 "R" H 4720 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 4580 5100 50  0001 C CNN
F 3 "~" H 4650 5100 50  0001 C CNN
	1    4650 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 616E4AE1
P 4900 5100
F 0 "R2" H 4970 5146 50  0000 L CNN
F 1 "R" H 4970 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 4830 5100 50  0001 C CNN
F 3 "~" H 4900 5100 50  0001 C CNN
	1    4900 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 616E4DC6
P 5150 5100
F 0 "R3" H 5220 5146 50  0000 L CNN
F 1 "R" H 5220 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 5080 5100 50  0001 C CNN
F 3 "~" H 5150 5100 50  0001 C CNN
	1    5150 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 616E50DC
P 5400 5100
F 0 "R4" H 5470 5146 50  0000 L CNN
F 1 "R" H 5470 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 5330 5100 50  0001 C CNN
F 3 "~" H 5400 5100 50  0001 C CNN
	1    5400 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 616E5346
P 5650 5100
F 0 "R5" H 5720 5146 50  0000 L CNN
F 1 "R" H 5720 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 5580 5100 50  0001 C CNN
F 3 "~" H 5650 5100 50  0001 C CNN
	1    5650 5100
	1    0    0    -1  
$EndComp
Entry Wire Line
	4600 3300 4700 3400
Entry Wire Line
	4850 3300 4950 3400
Entry Wire Line
	5100 3300 5200 3400
Entry Wire Line
	5350 3300 5450 3400
Entry Wire Line
	5600 3300 5700 3400
Wire Wire Line
	4700 3400 4700 3450
Wire Wire Line
	6200 3850 6250 3850
Wire Wire Line
	6200 3950 6250 3950
Wire Wire Line
	6200 4050 6250 4050
Wire Wire Line
	6200 4150 6250 4150
Wire Wire Line
	6200 4250 6250 4250
Text Label 4700 3450 0    50   ~ 0
b0
Text Label 6250 3850 2    50   ~ 0
b0
Entry Wire Line
	6550 5550 6650 5450
Entry Wire Line
	4550 5550 4650 5450
Entry Wire Line
	4800 5550 4900 5450
Entry Wire Line
	5050 5550 5150 5450
Entry Wire Line
	5300 5550 5400 5450
Entry Wire Line
	5550 5550 5650 5450
Wire Wire Line
	5400 5250 5400 5450
Wire Wire Line
	5150 5250 5150 5450
Wire Wire Line
	4900 5250 4900 5450
Wire Wire Line
	4650 5250 4650 5450
$Comp
L project:SW_MEC_5E_copy SW1
U 1 1 6170D811
P 4500 3450
F 0 "SW1" H 4500 3347 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 4545 3698 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 4500 3750 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 4500 3750 50  0001 C CNN
	1    4500 3450
	-1   0    0    1   
$EndComp
Text Label 4650 5250 3    50   ~ 0
g1
Wire Wire Line
	4700 4950 4650 4950
Wire Bus Line
	6950 3050 4100 3050
Entry Wire Line
	6950 3050 7050 3150
Wire Wire Line
	7050 3250 6950 3250
Entry Wire Line
	4100 3750 4200 3650
Text Label 6950 3250 0    50   ~ 0
5v
Text Label 4300 3550 2    50   ~ 0
5v
$Comp
L project:SW_MEC_5E_copy SW2
U 1 1 61718005
P 4750 3700
F 0 "SW2" H 4750 3597 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 4795 3948 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 4750 4000 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 4750 4000 50  0001 C CNN
	1    4750 3700
	-1   0    0    1   
$EndComp
$Comp
L project:SW_MEC_5E_copy SW3
U 1 1 617189CB
P 5000 3950
F 0 "SW3" H 5000 3847 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 5045 4198 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 5000 4250 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 5000 4250 50  0001 C CNN
	1    5000 3950
	-1   0    0    1   
$EndComp
$Comp
L project:SW_MEC_5E_copy SW5
U 1 1 61719816
P 5500 4450
F 0 "SW5" H 5500 4347 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 5545 4698 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 5500 4750 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 5500 4750 50  0001 C CNN
	1    5500 4450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 4950 4900 4950
Wire Wire Line
	5200 4950 5150 4950
Wire Wire Line
	5450 4950 5400 4950
Wire Wire Line
	5700 4850 5650 4850
Wire Wire Line
	5650 4850 5650 4950
Wire Wire Line
	4950 3400 4950 3700
Wire Wire Line
	5200 3400 5200 3950
Wire Wire Line
	5450 3400 5450 4200
Wire Wire Line
	5700 3400 5700 4450
Entry Wire Line
	4100 4200 4200 4100
Entry Wire Line
	4100 4350 4200 4250
Entry Wire Line
	4100 4500 4200 4400
Entry Wire Line
	4100 4650 4200 4550
Text Label 4550 3800 2    50   ~ 0
5v
Text Label 4800 4050 2    50   ~ 0
5v
Text Label 5050 4300 2    50   ~ 0
5v
Text Label 5300 4550 2    50   ~ 0
5v
Text Label 4950 3700 0    50   ~ 0
b2
Text Label 5200 3950 0    50   ~ 0
b1
Text Label 5450 4200 0    50   ~ 0
b4
Text Label 5700 4450 0    50   ~ 0
b3
Text Label 6250 3950 2    50   ~ 0
b1
Text Label 6250 4050 2    50   ~ 0
b2
Text Label 6250 4150 2    50   ~ 0
b3
Text Label 6250 4250 2    50   ~ 0
b4
Text Label 4900 5250 3    50   ~ 0
g1
Text Label 5150 5250 3    50   ~ 0
g1
Text Label 5400 5250 3    50   ~ 0
g1
Text Label 5650 5250 3    50   ~ 0
g1
Wire Wire Line
	4700 3550 4700 4950
Wire Wire Line
	4300 3550 4200 3550
Wire Wire Line
	4200 3550 4200 3650
Wire Wire Line
	4550 3800 4550 4100
Wire Wire Line
	4550 4100 4200 4100
Wire Wire Line
	4950 3800 4950 4950
$Comp
L project:SW_MEC_5E_copy SW4
U 1 1 617191B1
P 5250 4200
F 0 "SW4" H 5250 4097 50  0000 C CNN
F 1 "SW_MEC_5E_copy" V 5295 4448 50  0001 L CNN
F 2 "bkm10rduino:SW_Tactile_SPDP_12.3_5mm" H 5250 4500 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 5250 4500 50  0001 C CNN
	1    5250 4200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 4250 4800 4250
Wire Wire Line
	4800 4250 4800 4050
Wire Wire Line
	5200 4050 5200 4950
Wire Wire Line
	4200 4400 5050 4400
Wire Wire Line
	5050 4400 5050 4300
Wire Wire Line
	5450 4300 5450 4950
Wire Wire Line
	4200 4550 5300 4550
Wire Wire Line
	5700 4850 5700 4550
Text Label 6850 5350 0    50   ~ 0
g2
Text Label 6750 5350 0    50   ~ 0
g1
Entry Wire Line
	6650 5550 6750 5450
Text Label 6650 5350 0    50   ~ 0
g0
NoConn ~ 7250 3850
NoConn ~ 7250 4050
NoConn ~ 7250 4250
NoConn ~ 7250 4350
NoConn ~ 7250 4450
NoConn ~ 7250 4550
NoConn ~ 7250 4650
NoConn ~ 7250 4750
NoConn ~ 7250 4950
NoConn ~ 7250 5050
NoConn ~ 6250 4450
NoConn ~ 6250 4750
NoConn ~ 6250 4650
NoConn ~ 6250 4550
NoConn ~ 6850 3250
NoConn ~ 4300 3450
NoConn ~ 4550 3700
NoConn ~ 4800 3950
NoConn ~ 5050 4200
NoConn ~ 5300 4450
$Comp
L project:TLL_TO_RS485 U1
U 1 1 61766480
P 5950 2800
F 0 "U1" H 5950 3375 50  0000 C CNN
F 1 "TLL_TO_RS485" H 5950 3284 50  0000 C CNN
F 2 "bkm10rduino:TLL_RS485" H 5950 2800 50  0001 C CNN
F 3 "" H 5950 2800 50  0001 C CNN
	1    5950 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 5400 7500 2850
Wire Wire Line
	7500 2850 5500 2850
Wire Wire Line
	5500 2750 5500 2800
Wire Wire Line
	6650 3250 6650 2900
Wire Wire Line
	6650 2900 5350 2900
Wire Wire Line
	5350 2900 5350 2450
Wire Wire Line
	5350 2450 5500 2450
Entry Wire Line
	6100 4750 6200 4850
Entry Wire Line
	6100 4850 6200 4950
Entry Wire Line
	6100 3550 6200 3650
Entry Wire Line
	6100 3650 6200 3750
Wire Wire Line
	6200 3650 6250 3650
Wire Wire Line
	6200 3750 6250 3750
Wire Wire Line
	6200 4850 6250 4850
Wire Wire Line
	6200 4950 6250 4950
Text Label 6250 4850 2    50   ~ 0
DE
Text Label 6250 4950 2    50   ~ 0
RE
Entry Wire Line
	5850 3300 5950 3200
Entry Wire Line
	6000 3300 6100 3200
Wire Wire Line
	6100 3200 6100 3000
Wire Wire Line
	6100 3000 6550 3000
Wire Wire Line
	6550 3000 6550 2450
Wire Wire Line
	6550 2450 6400 2450
Wire Wire Line
	5950 3200 5950 2950
Wire Wire Line
	5950 2950 6400 2950
Wire Wire Line
	6400 2950 6400 2750
Text Label 6400 2550 0    50   ~ 0
DE
Text Label 6400 2650 0    50   ~ 0
RE
Entry Wire Line
	6100 3350 6200 3250
Entry Wire Line
	6100 3450 6200 3350
Wire Wire Line
	6450 2550 6400 2550
Wire Wire Line
	6200 3100 6500 3100
Wire Wire Line
	6500 3100 6500 2650
Wire Wire Line
	6500 2650 6400 2650
Wire Wire Line
	6200 3350 6200 3300
Wire Wire Line
	6200 3300 6450 3300
Wire Wire Line
	6450 2550 6450 3300
Wire Wire Line
	6200 3250 6200 3100
Text Label 6250 3650 2    50   ~ 0
RX
Text Label 6250 3750 2    50   ~ 0
TX
Text Label 6400 2750 0    50   ~ 0
RX
Text Label 6400 2450 0    50   ~ 0
TX
$Comp
L project:6_PIN_HEADER H1
U 1 1 61784A0C
P 4400 2550
F 0 "H1" V 3885 2783 50  0000 C CNN
F 1 "6_PIN_HEADER" V 3976 2783 50  0000 C CNN
F 2 "bkm10rduino:6_PIN_HEADER" H 4400 2450 50  0001 C CNN
F 3 "" H 4400 2450 50  0001 C CNN
	1    4400 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 2300 5350 2300
Wire Wire Line
	5350 2300 5350 2450
Connection ~ 5350 2450
Wire Wire Line
	4850 2800 5500 2800
Connection ~ 5500 2800
Wire Wire Line
	5500 2800 5500 2850
Wire Wire Line
	4850 2400 5150 2400
Wire Wire Line
	5150 2400 5150 2550
Wire Wire Line
	5150 2550 5500 2550
Wire Wire Line
	4850 2500 5050 2500
Wire Wire Line
	5050 2500 5050 2600
Wire Wire Line
	5050 2600 5500 2600
Wire Wire Line
	5500 2600 5500 2650
NoConn ~ 4850 2600
NoConn ~ 4850 2700
NoConn ~ 7250 3650
NoConn ~ 6250 4350
Wire Wire Line
	6750 5350 6750 5450
Wire Wire Line
	7500 5400 6850 5400
Wire Wire Line
	6850 5400 6850 5350
Wire Wire Line
	7050 3150 7050 3250
Wire Wire Line
	5650 5250 5650 5450
Wire Wire Line
	6650 5350 6650 5450
Wire Bus Line
	4100 3050 4100 4650
Wire Bus Line
	4550 5550 6650 5550
Wire Bus Line
	4600 3300 6100 3300
Wire Bus Line
	6100 3300 6100 4850
$EndSCHEMATC

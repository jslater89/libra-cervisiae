EESchema Schematic File Version 4
LIBS:pcb-cache
EELAYER 26 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Pendulum PCB"
Date "2018-06-28"
Rev "1.0.0-rc.7"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L device:R R3
U 1 1 5B215E85
P 1000 4250
F 0 "R3" V 1080 4250 50  0000 C CNN
F 1 "390k" V 1000 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 930 4250 50  0001 C CNN
F 3 "" H 1000 4250 50  0001 C CNN
	1    1000 4250
	0    -1   -1   0   
$EndComp
$Comp
L regul:MCP1700-3302E_SOT23 U1
U 1 1 5B217881
P 9050 2400
F 0 "U1" H 8900 2525 50  0000 C CNN
F 1 "VREG" H 9050 2525 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9050 2625 50  0001 C CNN
F 3 "" H 9050 2400 50  0001 C CNN
	1    9050 2400
	1    0    0    -1  
$EndComp
$Comp
L tp4056:TP4056 CN2
U 1 1 5B217C78
P 3950 2850
F 0 "CN2" H 3150 3800 60  0000 C CNN
F 1 "TP4056" H 3750 3800 60  0000 C CNN
F 2 "TP4056:TP4056" H 3100 3800 60  0001 C CNN
F 3 "" H 3100 3800 60  0001 C CNN
	1    3950 2850
	0    1    1    0   
$EndComp
$Comp
L conn:Conn_01x01 J1
U 1 1 5B217852
P 3000 2150
F 0 "J1" H 3000 2250 50  0000 C CNN
F 1 "BAT+" H 3000 2050 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 3000 2150 50  0001 C CNN
F 3 "" H 3000 2150 50  0001 C CNN
	1    3000 2150
	-1   0    0    1   
$EndComp
$Comp
L conn:Conn_01x01 J2
U 1 1 5B2178B3
P 3000 2450
F 0 "J2" H 3000 2550 50  0000 C CNN
F 1 "BAT-" H 3000 2350 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 3000 2450 50  0001 C CNN
F 3 "" H 3000 2450 50  0001 C CNN
	1    3000 2450
	-1   0    0    1   
$EndComp
$Comp
L switches:SW_Push SW2
U 1 1 5B21A301
P 6400 4400
F 0 "SW2" H 6450 4500 50  0000 L CNN
F 1 "Flash" H 6400 4340 50  0000 C CNN
F 2 "4x3_SWITCH:4x3_Switch" H 6400 4600 50  0001 C CNN
F 3 "" H 6400 4600 50  0001 C CNN
	1    6400 4400
	0    -1   -1   0   
$EndComp
$Comp
L switches:SW_Push SW1
U 1 1 5B21A409
P 3900 4450
F 0 "SW1" H 3950 4550 50  0000 L CNN
F 1 "Reset" H 3900 4390 50  0000 C CNN
F 2 "4x3_SWITCH:4x3_Switch" H 3900 4650 50  0001 C CNN
F 3 "" H 3900 4650 50  0001 C CNN
	1    3900 4450
	0    -1   -1   0   
$EndComp
$Comp
L device:R R1
U 1 1 5B21A586
P 3400 4800
F 0 "R1" V 3480 4800 50  0000 C CNN
F 1 "10k" V 3400 4800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3330 4800 50  0001 C CNN
F 3 "" H 3400 4800 50  0001 C CNN
	1    3400 4800
	0    -1   -1   0   
$EndComp
$Comp
L device:R R5
U 1 1 5B21A80E
P 5900 5500
F 0 "R5" V 5980 5500 50  0000 C CNN
F 1 "10k" V 5900 5500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5830 5500 50  0001 C CNN
F 3 "" H 5900 5500 50  0001 C CNN
	1    5900 5500
	0    1    1    0   
$EndComp
$Comp
L device:R R4
U 1 1 5B21AA4B
P 3800 5200
F 0 "R4" V 3880 5200 50  0000 C CNN
F 1 "10k" V 3800 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3730 5200 50  0001 C CNN
F 3 "" H 3800 5200 50  0001 C CNN
	1    3800 5200
	0    1    1    0   
$EndComp
$Comp
L device:R R7
U 1 1 5B21AAD4
P 6700 5400
F 0 "R7" V 6780 5400 50  0000 C CNN
F 1 "10k" V 6700 5400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6630 5400 50  0001 C CNN
F 3 "" H 6700 5400 50  0001 C CNN
	1    6700 5400
	0    1    1    0   
$EndComp
Text Label 1800 2650 0    60   ~ 0
USB+
Text Label 1750 2150 0    60   ~ 0
HostTX
Text Label 1750 2050 0    60   ~ 0
HostRX
Text Label 5100 2300 0    60   ~ 0
USB+
Text Label 5100 2400 0    60   ~ 0
GND
Text Label 3900 1850 0    60   ~ 0
CHG+
Text Label 10050 2400 0    60   ~ 0
3.3+
Text Label 9050 3150 1    60   ~ 0
GND
Text Label 3200 2050 1    60   ~ 0
BAT+
Text Label 1800 2250 0    60   ~ 0
GND
Text Label 1950 4250 0    60   ~ 0
BAT+
Text Label 6000 5200 0    60   ~ 0
CLK
Text Label 6000 5300 0    60   ~ 0
DAT
Text Label 6650 5700 0    60   ~ 0
GND
Text Label 5850 5000 0    60   ~ 0
HostRX
Text Label 5850 5100 0    60   ~ 0
HostTX
NoConn ~ 4600 6200
NoConn ~ 4700 6200
NoConn ~ 4800 6200
NoConn ~ 4900 6200
NoConn ~ 5000 6200
NoConn ~ 5100 6200
Text Label 6850 5300 1    60   ~ 0
3.3+
Text Label 2650 4800 0    60   ~ 0
3.3+
Text Label 5150 3850 3    60   ~ 0
GND
$Comp
L device:R R6
U 1 1 5B228DC8
P 6150 5600
F 0 "R6" V 6230 5600 50  0000 C CNN
F 1 "10k" V 6150 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 5600 50  0001 C CNN
F 3 "" H 6150 5600 50  0001 C CNN
	1    6150 5600
	0    1    1    0   
$EndComp
$Comp
L device:C C3
U 1 1 5B2296F3
P 9750 2550
F 0 "C3" H 9775 2650 50  0000 L CNN
F 1 "1uF" H 9775 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9788 2400 50  0001 C CNN
F 3 "" H 9750 2550 50  0001 C CNN
	1    9750 2550
	-1   0    0    1   
$EndComp
$Comp
L ESP8266:ESP-12F U2
U 1 1 5B22CF91
P 4850 5300
F 0 "U2" H 4850 5200 50  0000 C CNN
F 1 "ESP-12F" H 4850 5400 50  0000 C CNN
F 2 "ESP8266:ESP-12E" H 4850 5300 50  0001 C CNN
F 3 "" H 4850 5300 50  0001 C CNN
	1    4850 5300
	1    0    0    -1  
$EndComp
NoConn ~ 1600 1850
NoConn ~ 1600 1950
Text Notes 2900 2550 1    60   ~ 0
Battery Pads\n\n
$Comp
L conn:Conn_01x02 J3
U 1 1 5B22789F
P 3350 1550
F 0 "J3" H 3350 1650 50  0000 C CNN
F 1 "Battery" H 3350 1350 50  0000 C CNN
F 2 "Connector_Molex:Molex_PicoBlade_53048-0410_1x02_P1.25mm_Horizontal" H 3350 1550 50  0001 C CNN
F 3 "" H 3350 1550 50  0001 C CNN
	1    3350 1550
	0    -1   -1   0   
$EndComp
Text Notes 8850 2150 0    60   ~ 0
MCP1700
$Comp
L device:R R2
U 1 1 5B228874
P 1000 4750
F 0 "R2" V 1080 4750 50  0000 C CNN
F 1 "120k" V 1000 4750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 930 4750 50  0001 C CNN
F 3 "" H 1000 4750 50  0001 C CNN
	1    1000 4750
	0    -1   -1   0   
$EndComp
Text Label 1950 4750 0    60   ~ 0
GND
$Comp
L device:C C2
U 1 1 5B241212
P 8500 2550
F 0 "C2" H 8525 2650 50  0000 L CNN
F 1 "1uF" H 8525 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8538 2400 50  0001 C CNN
F 3 "" H 8500 2550 50  0001 C CNN
	1    8500 2550
	-1   0    0    1   
$EndComp
$Comp
L device:C C1
U 1 1 5B2439F8
P 4850 6500
F 0 "C1" H 4875 6600 50  0000 L CNN
F 1 "47uF" H 4875 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4888 6350 50  0001 C CNN
F 3 "" H 4850 6500 50  0001 C CNN
	1    4850 6500
	0    -1   -1   0   
$EndComp
$Comp
L cp2102-breakout:CP2102-BREAKOUT CN1
U 1 1 5B258589
P 950 1800
F 0 "CN1" H 1100 1500 60  0000 C CNN
F 1 "CP2102-BREAKOUT" V 900 1500 60  0000 C CNN
F 2 "CP2102-BRK:CP2102-BREAKOUT" H 950 1800 60  0001 C CNN
F 3 "" H 950 1800 60  0001 C CNN
	1    950  1800
	1    0    0    -1  
$EndComp
Text Label 7300 5700 0    60   ~ 0
HX+
Text Label 7300 5550 0    60   ~ 0
DAT
Text Label 7300 5450 0    60   ~ 0
CLK
Text Label 7300 5350 0    60   ~ 0
GND
Text Notes 9200 4850 2    60   ~ 0
Load Cell
Text Label 3250 5100 0    60   ~ 0
ADC
Text Label 1950 4500 0    60   ~ 0
ADC
Text Label 3600 5500 0    60   ~ 0
DSD
Text Label 3600 5400 0    60   ~ 0
DS+
Text Notes 1150 4050 0    60   ~ 0
Battery Monitor
Text Label 1950 6000 0    60   ~ 0
DSD
Text Label 1950 5900 0    60   ~ 0
DS+
Text Label 2100 6100 2    60   ~ 0
GND
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5B29A23A
P 3200 5600
F 0 "#FLG01" H 3200 5675 50  0001 C CNN
F 1 "PWR_FLAG" V 3250 5450 50  0000 C CNN
F 2 "" H 3200 5600 50  0001 C CNN
F 3 "" H 3200 5600 50  0001 C CNN
	1    3200 5600
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5B22D046
P 3200 5400
F 0 "#FLG02" H 3200 5475 50  0001 C CNN
F 1 "PWR_FLAG" V 3250 5250 50  0000 C CNN
F 2 "" H 3200 5400 50  0001 C CNN
F 3 "" H 3200 5400 50  0001 C CNN
	1    3200 5400
	0    -1   -1   0   
$EndComp
Text Label 3600 5600 0    60   ~ 0
HX+
$Comp
L conn:Conn_01x03 J4
U 1 1 5B29B426
P 950 6000
F 0 "J4" H 950 6200 50  0000 C CNN
F 1 "DS18B20" H 950 5800 50  0000 C CNN
F 2 "Connector_Molex:Molex_PicoBlade_53048-0610_1x03_P1.25mm_Horizontal" H 950 6000 50  0001 C CNN
F 3 "" H 950 6000 50  0001 C CNN
	1    950  6000
	-1   0    0    1   
$EndComp
Text Notes 950  5700 0    60   ~ 0
DS18B20 Molex/Pads
$Comp
L conn:Conn_01x01 J5
U 1 1 5B29D410
P 950 6400
F 0 "J5" H 950 6500 50  0000 C CNN
F 1 "TMP+" H 950 6300 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 950 6400 50  0001 C CNN
F 3 "" H 950 6400 50  0001 C CNN
	1    950  6400
	-1   0    0    1   
$EndComp
$Comp
L conn:Conn_01x01 J6
U 1 1 5B29D8C7
P 950 6700
F 0 "J6" H 950 6800 50  0000 C CNN
F 1 "TMPO" H 950 6600 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 950 6700 50  0001 C CNN
F 3 "" H 950 6700 50  0001 C CNN
	1    950  6700
	-1   0    0    1   
$EndComp
$Comp
L conn:Conn_01x01 J7
U 1 1 5B29D933
P 950 7000
F 0 "J7" H 950 7100 50  0000 C CNN
F 1 "TMP-" H 950 6900 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 950 7000 50  0001 C CNN
F 3 "" H 950 7000 50  0001 C CNN
	1    950  7000
	-1   0    0    1   
$EndComp
$Comp
L conn:Conn_01x01 J11
U 1 1 5B29EF57
P 9300 6200
F 0 "J11" H 9300 6300 50  0000 C CNN
F 1 "RED" H 9300 6100 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 9300 6200 50  0001 C CNN
F 3 "" H 9300 6200 50  0001 C CNN
	1    9300 6200
	0    1    1    0   
$EndComp
$Comp
L conn:Conn_01x01 J10
U 1 1 5B29EFD3
P 9150 4950
F 0 "J10" H 9150 5050 50  0000 C CNN
F 1 "GRN" H 9150 4850 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 9150 4950 50  0001 C CNN
F 3 "" H 9150 4950 50  0001 C CNN
	1    9150 4950
	0    -1   -1   0   
$EndComp
$Comp
L conn:Conn_01x01 J9
U 1 1 5B29F2C4
P 9000 6200
F 0 "J9" H 9000 6300 50  0000 C CNN
F 1 "BLK" H 9000 6100 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 9000 6200 50  0001 C CNN
F 3 "" H 9000 6200 50  0001 C CNN
	1    9000 6200
	0    1    1    0   
$EndComp
$Comp
L conn:Conn_01x01 J8
U 1 1 5B29F33C
P 8850 4950
F 0 "J8" H 8850 5050 50  0000 C CNN
F 1 "WHT" H 8850 4850 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 8850 4950 50  0001 C CNN
F 3 "" H 8850 4950 50  0001 C CNN
	1    8850 4950
	0    -1   -1   0   
$EndComp
$Comp
L hx711_breakout:HX711_BREAKOUT CN3
U 1 1 5B293345
P 8650 5850
F 0 "CN3" H 9150 5250 60  0000 C CNN
F 1 "HX711_BREAKOUT" H 9150 5900 60  0000 C CNN
F 2 "HX711:HX711-MINI" H 8650 5850 60  0001 C CNN
F 3 "" H 8650 5850 60  0001 C CNN
	1    8650 5850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5250 2300 5050 2300
Wire Wire Line
	5250 2400 5050 2400
Wire Wire Line
	3750 2050 3750 1850
Wire Wire Line
	3750 1850 4150 1850
Wire Wire Line
	9050 2700 9050 2850
Wire Wire Line
	9350 2400 9750 2400
Wire Wire Line
	5750 5000 6150 5000
Wire Wire Line
	5750 5100 6150 5100
Wire Wire Line
	5750 5200 6150 5200
Wire Wire Line
	5750 5300 6150 5300
Wire Wire Line
	2950 5700 3850 5700
Wire Wire Line
	5750 5700 6000 5700
Wire Wire Line
	6850 5500 6050 5500
Wire Wire Line
	3900 4650 3900 4800
Wire Wire Line
	3550 4800 3900 4800
Wire Wire Line
	2650 4800 2950 4800
Wire Wire Line
	3900 4250 3900 4100
Connection ~ 3900 4800
Wire Wire Line
	2950 5200 3650 5200
Wire Wire Line
	2950 4800 2950 5200
Connection ~ 2950 4800
Wire Wire Line
	5750 5400 6400 5400
Wire Wire Line
	6400 4600 6400 5400
Connection ~ 6400 5400
Wire Wire Line
	6400 4100 6400 4200
Wire Wire Line
	3900 4100 5150 4100
Wire Wire Line
	5150 4100 5150 3850
Connection ~ 5150 4100
Connection ~ 2950 5200
Wire Wire Line
	6850 5100 6850 5400
Connection ~ 6850 5400
Wire Wire Line
	5750 5600 6000 5600
Wire Wire Line
	6300 5600 6450 5600
Wire Wire Line
	3650 5000 3900 5000
Wire Wire Line
	3200 2150 3200 1850
Connection ~ 3200 2150
Wire Wire Line
	3200 2450 3450 2450
Wire Wire Line
	3350 1750 3350 2150
Connection ~ 3350 2150
Wire Wire Line
	3450 1750 3450 2450
Connection ~ 3450 2450
Wire Wire Line
	3850 5700 3850 6500
Wire Wire Line
	3850 6500 4700 6500
Connection ~ 3850 5700
Wire Wire Line
	6000 6500 5000 6500
Wire Wire Line
	9750 2850 9750 2700
Wire Wire Line
	8500 2850 9050 2850
Connection ~ 9750 2400
Wire Wire Line
	8500 2700 8500 2850
Wire Wire Line
	6000 6500 6000 5700
Connection ~ 6000 5700
Wire Wire Line
	6450 5600 6450 5700
Connection ~ 6450 5700
Connection ~ 9050 2850
Wire Wire Line
	1600 2150 2050 2150
Wire Wire Line
	1600 2050 2050 2050
Wire Wire Line
	7650 5450 7300 5450
Wire Wire Line
	7650 5550 7300 5550
Wire Wire Line
	7650 5350 7300 5350
Wire Wire Line
	7650 5650 7550 5650
Wire Wire Line
	7550 5650 7550 5700
Wire Wire Line
	7550 5750 7650 5750
Wire Wire Line
	7550 5700 7300 5700
Connection ~ 7550 5700
Wire Wire Line
	3950 5100 3250 5100
Wire Wire Line
	3600 5500 3950 5500
Wire Wire Line
	3200 5600 3950 5600
Wire Wire Line
	850  4250 850  4500
Connection ~ 850  4500
Wire Wire Line
	1150 4750 1450 4750
Wire Wire Line
	1150 5900 1200 5900
Wire Wire Line
	1150 6000 1450 6000
Wire Wire Line
	1150 6100 1700 6100
Wire Wire Line
	1200 5900 1200 6400
Connection ~ 1200 5900
Wire Wire Line
	1450 6000 1450 6600
Connection ~ 1450 6000
Wire Wire Line
	1700 6100 1700 7000
Connection ~ 1700 6100
Wire Wire Line
	1150 6400 1200 6400
Wire Wire Line
	1450 6700 1150 6700
Wire Wire Line
	1700 7000 1150 7000
Wire Wire Line
	8650 5450 9150 5450
Wire Wire Line
	8650 5550 8850 5550
Wire Wire Line
	8650 5650 9000 5650
Wire Wire Line
	8650 5750 9300 5750
Wire Wire Line
	9150 5150 9150 5450
Connection ~ 9150 5450
Wire Wire Line
	8850 5150 8850 5550
Connection ~ 8850 5550
Wire Wire Line
	9000 6000 9000 5650
Connection ~ 9000 5650
Wire Wire Line
	9300 6000 9300 5750
Connection ~ 9300 5750
Text Label 8650 5450 0    60   ~ 0
GRN
Text Label 8650 5550 0    60   ~ 0
WHT
Text Label 8650 5650 0    60   ~ 0
BLK
Text Label 8650 5750 0    60   ~ 0
RED
Text Label 1200 6350 1    60   ~ 0
TMP+
Text Label 1450 6350 1    60   ~ 0
TMPO
Text Label 1700 6350 1    60   ~ 0
TMP-
Wire Wire Line
	3950 5400 3200 5400
NoConn ~ 8650 5350
$Comp
L conn:Conn_01x04 J12
U 1 1 5B2A5EFA
P 9700 5550
F 0 "J12" H 9700 5750 50  0000 C CNN
F 1 "Load Cell" H 9700 5250 50  0000 C CNN
F 2 "Connector_Molex:Molex_PicoBlade_53048-0810_1x04_P1.25mm_Horizontal" H 9700 5550 50  0001 C CNN
F 3 "" H 9700 5550 50  0001 C CNN
	1    9700 5550
	1    0    0    -1  
$EndComp
$Comp
L device:C C4
U 1 1 5B2A9325
P 1900 6250
F 0 "C4" H 1950 6150 50  0000 L CNN
F 1 "1uF" H 2000 6250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1938 6100 50  0001 C CNN
F 3 "" H 1900 6250 50  0001 C CNN
	1    1900 6250
	1    0    0    -1  
$EndComp
Connection ~ 1900 6100
Wire Wire Line
	3950 5300 3650 5300
Wire Wire Line
	3650 5300 3650 5000
Connection ~ 3900 5000
Wire Wire Line
	1150 4250 2150 4250
Connection ~ 1200 6400
Connection ~ 8500 2400
Wire Wire Line
	1600 2250 1700 2250
Wire Wire Line
	8150 2400 8500 2400
Text Label 8150 2400 0    60   ~ 0
VREG+
Text Label 3250 2750 0    60   ~ 0
GND
Wire Wire Line
	3750 2150 3350 2150
Wire Wire Line
	3450 2650 3750 2650
Wire Wire Line
	3250 2750 3750 2750
$Comp
L device:D_Schottky D1
U 1 1 5B303989
P 6900 1850
F 0 "D1" H 6900 1950 50  0000 C CNN
F 1 "SS36" H 6900 1750 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 6900 1850 50  0001 C CNN
F 3 "" H 6900 1850 50  0001 C CNN
	1    6900 1850
	-1   0    0    1   
$EndComp
$Comp
L transistors:NTR2101P Q1
U 1 1 5B303A3D
P 6500 2500
F 0 "Q1" V 6700 2300 50  0000 L CNN
F 1 "AO3401" V 6450 2100 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6700 2425 50  0001 L CIN
F 3 "" H 6500 2500 50  0001 L CNN
	1    6500 2500
	0    -1   -1   0   
$EndComp
$Comp
L device:R R8
U 1 1 5B304CC6
P 6500 2950
F 0 "R8" V 6580 2950 50  0000 C CNN
F 1 "10k" V 6500 2950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6430 2950 50  0001 C CNN
F 3 "" H 6500 2950 50  0001 C CNN
	1    6500 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 1850 6000 1850
Wire Wire Line
	7050 1850 7200 1850
Wire Wire Line
	7200 1850 7200 2400
Wire Wire Line
	6700 2400 7200 2400
Connection ~ 7200 2400
Text Label 7250 2400 0    60   ~ 0
VREG+
Text Label 5550 1850 0    60   ~ 0
USB+
Wire Wire Line
	6500 2700 6500 2750
Connection ~ 6500 2750
Wire Wire Line
	5800 3100 6500 3100
Connection ~ 6500 3100
Text Label 5800 3100 0    60   ~ 0
GND
Wire Wire Line
	5550 2400 6300 2400
Text Label 5550 2400 0    60   ~ 0
CHG+
Wire Wire Line
	6000 1850 6000 2750
Wire Wire Line
	6000 2750 6500 2750
Connection ~ 6000 1850
Text Notes 6000 1650 0    60   ~ 0
Battery Disconnector
$Comp
L device:C C5
U 1 1 5B308A6C
P 7200 2750
F 0 "C5" H 7225 2850 50  0000 L CNN
F 1 "47uF" H 7225 2650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7238 2600 50  0001 C CNN
F 3 "" H 7200 2750 50  0001 C CNN
	1    7200 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2900 7200 3100
Connection ~ 7200 3100
$Comp
L device:C C6
U 1 1 5B319707
P 1700 2450
F 0 "C6" H 1725 2550 50  0000 L CNN
F 1 "100nF" H 1800 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1738 2300 50  0001 C CNN
F 3 "" H 1700 2450 50  0001 C CNN
	1    1700 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2650 1700 2650
Wire Wire Line
	1600 2350 1600 2650
Connection ~ 1700 2650
Wire Wire Line
	1700 2600 1700 2650
Wire Wire Line
	1700 2300 1700 2250
Connection ~ 1700 2250
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5B3226ED
P 7500 2500
F 0 "#FLG03" H 7500 2575 50  0001 C CNN
F 1 "PWR_FLAG" H 7250 2500 50  0000 C CNN
F 2 "" H 7500 2500 50  0001 C CNN
F 3 "" H 7500 2500 50  0001 C CNN
	1    7500 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 2500 7500 2400
Connection ~ 7500 2400
$Comp
L device:C C7
U 1 1 5B31BCB8
P 1450 4600
F 0 "C7" H 1475 4700 50  0000 L CNN
F 1 "100nF" H 1475 4500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1488 4450 50  0001 C CNN
F 3 "" H 1450 4600 50  0001 C CNN
	1    1450 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  4500 1300 4500
Wire Wire Line
	1600 4500 2150 4500
Wire Wire Line
	1300 4500 1300 4450
Wire Wire Line
	1300 4450 1450 4450
Wire Wire Line
	1600 4450 1600 4500
Connection ~ 1450 4450
Connection ~ 1450 4750
Wire Wire Line
	3900 4800 3900 5000
Wire Wire Line
	2950 4800 3250 4800
Wire Wire Line
	6400 5400 6550 5400
Wire Wire Line
	5150 4100 6400 4100
Wire Wire Line
	2950 5200 2950 5700
Wire Wire Line
	6850 5400 6850 5500
Wire Wire Line
	3350 2150 3200 2150
Wire Wire Line
	3450 2450 3450 2650
Wire Wire Line
	3850 5700 3950 5700
Wire Wire Line
	9750 2400 10250 2400
Wire Wire Line
	6000 5700 6450 5700
Wire Wire Line
	6450 5700 6850 5700
Wire Wire Line
	9050 2850 9050 3150
Wire Wire Line
	9050 2850 9750 2850
Wire Wire Line
	7550 5700 7550 5750
Wire Wire Line
	850  4500 850  4750
Wire Wire Line
	1200 5900 1550 5900
Wire Wire Line
	1450 6000 2100 6000
Wire Wire Line
	1700 6100 1900 6100
Wire Wire Line
	9150 5450 9500 5450
Wire Wire Line
	8850 5550 9500 5550
Wire Wire Line
	9000 5650 9500 5650
Wire Wire Line
	9300 5750 9500 5750
Wire Wire Line
	1900 6100 2100 6100
Wire Wire Line
	3900 5000 3950 5000
Wire Wire Line
	1200 6400 1900 6400
Wire Wire Line
	8500 2400 8750 2400
Wire Wire Line
	7200 2400 7200 2600
Wire Wire Line
	7200 2400 7500 2400
Wire Wire Line
	6500 2750 6500 2800
Wire Wire Line
	6500 3100 7200 3100
Wire Wire Line
	6000 1850 6750 1850
Wire Wire Line
	7200 3100 7550 3100
Wire Wire Line
	1700 2650 2050 2650
Wire Wire Line
	1700 2250 2050 2250
Wire Wire Line
	7500 2400 7550 2400
Wire Wire Line
	1450 4450 1600 4450
Wire Wire Line
	1450 4750 2150 4750
$Comp
L device:R R9
U 1 1 5B4177F1
P 1550 6450
F 0 "R9" V 1630 6450 50  0000 C CNN
F 1 "10k" V 1550 6450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1480 6450 50  0001 C CNN
F 3 "" H 1550 6450 50  0001 C CNN
	1    1550 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6600 1550 6600
Connection ~ 1450 6600
Wire Wire Line
	1450 6600 1450 6700
Wire Wire Line
	1550 6300 1550 5900
Connection ~ 1550 5900
Wire Wire Line
	1550 5900 2100 5900
$EndSCHEMATC

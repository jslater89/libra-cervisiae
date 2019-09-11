EESchema Schematic File Version 4
LIBS:libra-cervisiae-pcb-cache
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Libra Cervisiae PCB"
Date "2019-08-16"
Rev "0.3.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Linear:MCP1700-3302E_SOT23 U2
U 1 1 5B217881
P 9050 2400
F 0 "U2" H 8900 2525 50  0000 C CNN
F 1 "VREG" H 9050 2525 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9050 2625 50  0001 C CNN
F 3 "" H 9050 2400 50  0001 C CNN
	1    9050 2400
	1    0    0    -1  
$EndComp
Text Label 1800 2650 0    60   ~ 0
USB+
Text Label 1750 2150 0    60   ~ 0
HostTX
Text Label 1750 2050 0    60   ~ 0
HostRX
Text Label 10050 2400 0    60   ~ 0
3.3+
Text Label 9050 3150 1    60   ~ 0
GND
Text Label 1800 2250 0    60   ~ 0
GND
$Comp
L Device:C C8
U 1 1 5B2296F3
P 9750 2550
F 0 "C8" H 9775 2650 50  0000 L CNN
F 1 "1uF" H 9775 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9788 2400 50  0001 C CNN
F 3 "" H 9750 2550 50  0001 C CNN
	1    9750 2550
	-1   0    0    1   
$EndComp
NoConn ~ 1600 1850
NoConn ~ 1600 1950
Text Notes 8850 2150 0    60   ~ 0
MCP1700
$Comp
L Device:C C7
U 1 1 5B241212
P 8500 2550
F 0 "C7" H 8525 2650 50  0000 L CNN
F 1 "1uF" H 8525 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8538 2400 50  0001 C CNN
F 3 "" H 8500 2550 50  0001 C CNN
	1    8500 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 5B2439F8
P 3350 1000
F 0 "C3" H 3375 1100 50  0000 L CNN
F 1 "4.7uF" H 3375 900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3388 850 50  0001 C CNN
F 3 "" H 3350 1000 50  0001 C CNN
	1    3350 1000
	-1   0    0    1   
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
Text Label 6200 5250 0    60   ~ 0
USB+
Text Label 6200 5100 0    60   ~ 0
DAT
Text Label 6200 5000 0    60   ~ 0
CLK
Text Label 6200 4900 0    60   ~ 0
GND
Text Notes 8000 4650 2    60   ~ 0
Load Cells
Text Label 3950 4900 0    60   ~ 0
DSD
Text Label 3950 4800 0    60   ~ 0
DS+
Text Label 3950 5000 0    60   ~ 0
GND
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5B29B426
P 2950 4900
F 0 "J1" H 2950 5100 50  0000 C CNN
F 1 "Wort Temp" H 2950 4700 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2950 4900 50  0001 C CNN
F 3 "" H 2950 4900 50  0001 C CNN
	1    2950 4900
	-1   0    0    1   
$EndComp
Text Notes 3250 4600 0    60   ~ 0
DS18B20s
$Comp
L hx711_breakout:HX711_BREAKOUT CN2
U 1 1 5B293345
P 7550 5400
F 0 "CN2" H 8050 4800 60  0000 C CNN
F 1 "HX711_BREAKOUT" H 8050 5450 60  0000 C CNN
F 2 "HX711:HX711-MINI" H 7550 5400 60  0001 C CNN
F 3 "" H 7550 5400 60  0001 C CNN
	1    7550 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	9050 2700 9050 2850
Wire Wire Line
	9350 2400 9750 2400
Wire Wire Line
	9750 2850 9750 2700
Wire Wire Line
	8500 2850 9050 2850
Connection ~ 9750 2400
Wire Wire Line
	8500 2700 8500 2850
Connection ~ 9050 2850
Wire Wire Line
	1600 2150 2050 2150
Wire Wire Line
	1600 2050 2050 2050
Wire Wire Line
	6550 5000 6200 5000
Wire Wire Line
	6550 5100 6200 5100
Wire Wire Line
	6550 5200 6450 5200
Wire Wire Line
	6450 5200 6450 5250
Wire Wire Line
	6450 5300 6550 5300
Connection ~ 6450 5250
Text Label 7550 5000 0    60   ~ 0
S+
Text Label 7550 5100 0    60   ~ 0
S-
Text Label 7550 5200 0    60   ~ 0
E-
Text Label 7550 5300 0    60   ~ 0
E+
NoConn ~ 7550 4900
$Comp
L Device:C C2
U 1 1 5B2A9325
P 3350 5350
F 0 "C2" V 3400 5200 50  0000 L CNN
F 1 "1uF" V 3500 5300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3388 5200 50  0001 C CNN
F 3 "" H 3350 5350 50  0001 C CNN
	1    3350 5350
	0    1    1    0   
$EndComp
Connection ~ 8500 2400
Wire Wire Line
	1600 2250 1700 2250
Wire Wire Line
	8150 2400 8500 2400
Text Label 8150 2400 0    60   ~ 0
USB+
$Comp
L Device:C C1
U 1 1 5B319707
P 1700 2450
F 0 "C1" H 1725 2550 50  0000 L CNN
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
Wire Wire Line
	9750 2400 10250 2400
Wire Wire Line
	9050 2850 9050 3150
Wire Wire Line
	9050 2850 9750 2850
Wire Wire Line
	6450 5250 6450 5300
Wire Wire Line
	8500 2400 8750 2400
Wire Wire Line
	1700 2650 2050 2650
Wire Wire Line
	1700 2250 2050 2250
$Comp
L Device:R R2
U 1 1 5B4177F1
P 3750 5350
F 0 "R2" V 3830 5350 50  0000 C CNN
F 1 "2.2k" V 3750 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3680 5350 50  0001 C CNN
F 3 "" H 3750 5350 50  0001 C CNN
	1    3750 5350
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 5B44D323
P 6050 5050
F 0 "C6" H 6050 4950 50  0000 L CNN
F 1 "1uF" H 5900 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6088 4900 50  0001 C CNN
F 3 "" H 6050 5050 50  0001 C CNN
	1    6050 5050
	1    0    0    -1  
$EndComp
Connection ~ 6050 4900
Wire Wire Line
	6050 4900 6550 4900
Wire Wire Line
	6050 5200 6050 5250
Connection ~ 6050 5250
Wire Wire Line
	6050 5250 6450 5250
Wire Wire Line
	8400 5550 8550 5550
Wire Wire Line
	8400 5450 8550 5450
Wire Wire Line
	8400 5350 8550 5350
Wire Wire Line
	8400 5250 8550 5250
Text Label 8550 5550 2    60   ~ 0
S+
Text Label 8550 5450 2    60   ~ 0
S-
Text Label 8550 5350 2    60   ~ 0
E-
Text Label 8550 5250 2    60   ~ 0
E+
Wire Wire Line
	7550 5000 7750 5000
Wire Wire Line
	7550 5100 7750 5100
Wire Wire Line
	7550 5200 7750 5200
Wire Wire Line
	7550 5300 7750 5300
Wire Wire Line
	9050 5550 9200 5550
Wire Wire Line
	9050 5450 9200 5450
Wire Wire Line
	9050 5350 9200 5350
Wire Wire Line
	9050 5250 9200 5250
Wire Wire Line
	9050 5150 9200 5150
Wire Wire Line
	9050 5050 9200 5050
Wire Wire Line
	9050 4950 9200 4950
Wire Wire Line
	8400 5150 8550 5150
Wire Wire Line
	8400 5050 8550 5050
Wire Wire Line
	8400 4850 8550 4850
Text Label 8550 5150 2    60   ~ 0
S+
Text Label 9200 5550 2    60   ~ 0
S+
Text Label 9200 5150 2    60   ~ 0
S+
Text Label 9200 5450 2    60   ~ 0
S-
Text Label 9200 5050 2    60   ~ 0
S-
Text Label 8550 5050 2    60   ~ 0
S-
Text Label 9200 5350 2    60   ~ 0
E-
Text Label 9200 4950 2    60   ~ 0
E-
Text Label 8550 4950 2    60   ~ 0
E-
Text Label 9200 5250 2    60   ~ 0
E+
Text Label 9200 4850 2    60   ~ 0
E+
Text Label 8550 4850 2    60   ~ 0
E+
Wire Wire Line
	3150 4900 3900 4900
Wire Wire Line
	3150 4800 3200 4800
Wire Wire Line
	3150 5000 3500 5000
Connection ~ 3200 4800
Wire Wire Line
	3200 4800 3600 4800
Connection ~ 3500 5000
Wire Wire Line
	3500 5000 4100 5000
Connection ~ 3600 4800
Wire Wire Line
	3600 4800 4100 4800
Connection ~ 3900 4900
Wire Wire Line
	3900 4900 4100 4900
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5B523E0B
P 2950 5850
F 0 "J2" H 2950 6050 50  0000 C CNN
F 1 "Ambient Temp" H 2950 5650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2950 5850 50  0001 C CNN
F 3 "" H 2950 5850 50  0001 C CNN
	1    2950 5850
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 4800 3200 5350
Wire Wire Line
	3500 5000 3500 5350
Wire Wire Line
	3150 5750 3200 5750
Wire Wire Line
	3150 5950 3500 5950
Text Label 3950 5750 0    60   ~ 0
DS+
Text Label 3950 5850 0    60   ~ 0
DSD
Text Label 3950 5950 0    60   ~ 0
GND
Wire Wire Line
	3200 5350 3200 5750
Connection ~ 3200 5350
Connection ~ 3200 5750
Wire Wire Line
	3500 5350 3500 5950
Connection ~ 3500 5350
Connection ~ 3500 5950
Wire Wire Line
	3500 5950 4100 5950
Wire Wire Line
	3150 5850 3900 5850
Wire Wire Line
	3200 5750 3600 5750
Wire Wire Line
	3600 4800 3600 5350
Wire Wire Line
	3600 5350 3600 5750
Connection ~ 3600 5350
Connection ~ 3600 5750
Wire Wire Line
	3600 5750 4100 5750
Wire Wire Line
	3900 4900 3900 5350
Wire Wire Line
	3900 5350 3900 5850
Connection ~ 3900 5350
Connection ~ 3900 5850
Wire Wire Line
	3900 5850 4100 5850
$Comp
L Device:C C4
U 1 1 5B88593E
P 3650 1000
F 0 "C4" H 3675 1100 50  0000 L CNN
F 1 "100nF" H 3675 900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3688 850 50  0001 C CNN
F 3 "" H 3650 1000 50  0001 C CNN
	1    3650 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:C C5
U 1 1 5B8B1FD8
P 5650 5050
F 0 "C5" H 5700 4950 50  0000 L CNN
F 1 "100nF" H 5400 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5688 4900 50  0001 C CNN
F 3 "" H 5650 5050 50  0001 C CNN
	1    5650 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4900 6050 4900
Wire Wire Line
	5650 5250 5650 5200
Wire Wire Line
	5650 5250 6050 5250
$Comp
L Connector_Generic:Conn_02x08_Top_Bottom J3
U 1 1 5B8A5278
P 8750 5150
F 0 "J3" H 8800 5667 50  0000 C CNN
F 1 "Load Cells" H 8800 5576 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 8750 5150 50  0001 C CNN
F 3 "~" H 8750 5150 50  0001 C CNN
	1    8750 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4850 9200 4850
Wire Wire Line
	8400 4950 8550 4950
Text Notes 8350 5000 2    60   ~ 0
1
Text Notes 8350 5400 2    60   ~ 0
2
Text Notes 9300 5000 2    60   ~ 0
3
Text Notes 9300 5400 2    60   ~ 0
4
$Comp
L RF_Module:ESP32-WROOM-32 U1
U 1 1 5D3B9C32
P 5100 2500
F 0 "U1" H 5000 2850 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 5000 2750 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 5100 1000 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 4800 2550 50  0001 C CNN
	1    5100 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1100 5100 650 
Text Label 4600 650  0    60   ~ 0
3.3+
Wire Wire Line
	5100 3900 5100 4350
Wire Wire Line
	5100 4350 4600 4350
Text Label 4600 4350 0    60   ~ 0
GND
Wire Wire Line
	5700 1400 6500 1400
Wire Wire Line
	5700 1600 6500 1600
Text Label 6200 1400 0    60   ~ 0
HostRX
Text Label 6200 1600 0    60   ~ 0
HostTX
Text Label 3750 1300 0    60   ~ 0
GND
$Comp
L Device:R R1
U 1 1 5D4DE447
P 4450 950
F 0 "R1" V 4530 950 50  0000 C CNN
F 1 "10k" V 4450 950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4380 950 50  0001 C CNN
F 3 "" H 4450 950 50  0001 C CNN
	1    4450 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 800  4450 650 
Connection ~ 4450 650 
Wire Wire Line
	4450 650  5100 650 
Wire Wire Line
	4450 1100 4450 1300
Wire Wire Line
	4450 1300 4500 1300
$Comp
L Switch:SW_Push SW1
U 1 1 5D4FC8D2
P 4250 1300
F 0 "SW1" H 4300 1400 50  0000 L CNN
F 1 "Reset" H 4250 1240 50  0000 C CNN
F 2 "4x3_SWITCH:4x3_Switch" H 4250 1500 50  0001 C CNN
F 3 "" H 4250 1500 50  0001 C CNN
	1    4250 1300
	-1   0    0    1   
$EndComp
Connection ~ 4450 1300
Connection ~ 5100 650 
$Comp
L Device:R R3
U 1 1 5D5306D3
P 5700 950
F 0 "R3" V 5780 950 50  0000 C CNN
F 1 "10k" V 5700 950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5630 950 50  0001 C CNN
F 3 "" H 5700 950 50  0001 C CNN
	1    5700 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	5100 650  5700 650 
Wire Wire Line
	5700 1100 5700 1300
Wire Wire Line
	5700 800  5700 650 
Connection ~ 5700 650 
Wire Wire Line
	5700 650  6500 650 
$Comp
L Switch:SW_Push SW2
U 1 1 5D542D6A
P 5900 1300
F 0 "SW2" H 5850 1150 50  0000 L CNN
F 1 "Flash" H 5900 1240 50  0000 C CNN
F 2 "4x3_SWITCH:4x3_Switch" H 5900 1500 50  0001 C CNN
F 3 "" H 5900 1500 50  0001 C CNN
	1    5900 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	6100 1300 6500 1300
Text Label 6350 1300 0    60   ~ 0
GND
Wire Wire Line
	5700 2700 6500 2700
Wire Wire Line
	5700 2800 6500 2800
Text Label 6350 2800 0    60   ~ 0
CLK
Text Label 6350 2700 0    60   ~ 0
DAT
Wire Wire Line
	5700 2500 6500 2500
Wire Wire Line
	5700 2600 6500 2600
Text Label 6350 2500 0    60   ~ 0
DS+
Text Label 6350 2600 0    60   ~ 0
DSD
NoConn ~ 4500 1500
NoConn ~ 4500 1600
NoConn ~ 4500 2500
NoConn ~ 4500 2600
NoConn ~ 4500 2700
NoConn ~ 4500 2800
NoConn ~ 4500 2900
NoConn ~ 4500 3000
NoConn ~ 5700 3600
NoConn ~ 5700 3500
NoConn ~ 5700 3400
NoConn ~ 5700 3300
NoConn ~ 5700 3200
NoConn ~ 5700 3100
NoConn ~ 5700 3000
NoConn ~ 5700 2900
NoConn ~ 5700 2400
NoConn ~ 5700 2300
NoConn ~ 5700 2100
NoConn ~ 5700 2000
NoConn ~ 5700 1900
NoConn ~ 5700 1800
NoConn ~ 5700 1700
NoConn ~ 5700 1500
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D62D329
P 6500 2500
F 0 "#FLG01" H 6500 2575 50  0001 C CNN
F 1 "PWR_FLAG" V 6500 2800 50  0000 C CNN
F 2 "" H 6500 2500 50  0001 C CNN
F 3 "" H 6500 2500 50  0001 C CNN
	1    6500 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 650  3350 850 
Wire Wire Line
	3350 650  3650 650 
Wire Wire Line
	3350 1150 3350 1300
Wire Wire Line
	3350 1300 3650 1300
Wire Wire Line
	3650 650  3650 850 
Connection ~ 3650 650 
Wire Wire Line
	3650 650  4450 650 
Wire Wire Line
	3650 1150 3650 1300
Connection ~ 3650 1300
Wire Wire Line
	3650 1300 4050 1300
$Comp
L Switch:SW_Push SW3
U 1 1 5D785ABF
P 6100 2050
F 0 "SW3" H 6050 1900 50  0000 L CNN
F 1 "Hotspot" H 6100 1990 50  0000 C CNN
F 2 "4x3_SWITCH:4x3_Switch" H 6100 2250 50  0001 C CNN
F 3 "" H 6100 2250 50  0001 C CNN
	1    6100 2050
	-1   0    0    1   
$EndComp
Connection ~ 5700 1300
Wire Wire Line
	5700 2200 5900 2200
Wire Wire Line
	5900 2200 5900 2050
Wire Wire Line
	6300 2050 6500 2050
Text Label 6300 2050 0    60   ~ 0
3.3+
Wire Wire Line
	5900 2200 5900 2350
Connection ~ 5900 2200
$Comp
L Device:R R4
U 1 1 5D79D805
P 6100 2350
F 0 "R4" V 6180 2350 50  0000 C CNN
F 1 "10k" V 6100 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6030 2350 50  0001 C CNN
F 3 "" H 6100 2350 50  0001 C CNN
	1    6100 2350
	0    1    -1   0   
$EndComp
Wire Wire Line
	5900 2350 5950 2350
Wire Wire Line
	6250 2350 6500 2350
Text Label 6350 2350 0    60   ~ 0
GND
$EndSCHEMATC

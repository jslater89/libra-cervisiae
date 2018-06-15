EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ftdi
LIBS:ESP8266
LIBS:gy-521
LIBS:tp4056
LIBS:bob-13263
LIBS:pcb-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Pendulum PCB"
Date "2018-06-14"
Rev "0.0.2"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R3
U 1 1 5B215E85
P 2400 5550
F 0 "R3" V 2480 5550 50  0000 C CNN
F 1 "390k" V 2400 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 2330 5550 50  0001 C CNN
F 3 "" H 2400 5550 50  0001 C CNN
	1    2400 5550
	0    -1   -1   0   
$EndComp
$Comp
L GY-521 U4
U 1 1 5B2168A0
P 8900 6100
F 0 "U4" H 8100 7050 60  0000 C CNN
F 1 "GY-521" H 8700 7050 60  0000 C CNN
F 2 "GY521:GY521" H 8050 7050 60  0001 C CNN
F 3 "" H 8050 7050 60  0001 C CNN
	1    8900 6100
	1    0    0    -1  
$EndComp
$Comp
L MCP1700-3302E_SOT23 U5
U 1 1 5B217881
P 9450 2250
F 0 "U5" H 9300 2375 50  0000 C CNN
F 1 "VREG" H 9450 2375 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9450 2475 50  0001 C CNN
F 3 "" H 9450 2250 50  0001 C CNN
	1    9450 2250
	1    0    0    -1  
$EndComp
$Comp
L TP4056 U3
U 1 1 5B217C78
P 6700 3050
F 0 "U3" H 5900 4000 60  0000 C CNN
F 1 "TP4056" H 6500 4000 60  0000 C CNN
F 2 "TP4056:TP4056" H 5850 4000 60  0001 C CNN
F 3 "" H 5850 4000 60  0001 C CNN
	1    6700 3050
	0    1    1    0   
$EndComp
$Comp
L Conn_01x01 J1
U 1 1 5B217852
P 5750 2350
F 0 "J1" H 5750 2450 50  0000 C CNN
F 1 "BAT+" H 5750 2250 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 5750 2350 50  0001 C CNN
F 3 "" H 5750 2350 50  0001 C CNN
	1    5750 2350
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x01 J2
U 1 1 5B2178B3
P 5750 2650
F 0 "J2" H 5750 2750 50  0000 C CNN
F 1 "BAT-" H 5750 2550 50  0000 C CNN
F 2 "Extra_Pads:SolderWirePad_single_SMD_5x3mm" H 5750 2650 50  0001 C CNN
F 3 "" H 5750 2650 50  0001 C CNN
	1    5750 2650
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG01
U 1 1 5B217D4E
P 3800 1600
F 0 "#FLG01" H 3800 1675 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 1750 50  0000 C CNN
F 2 "" H 3800 1600 50  0001 C CNN
F 3 "" H 3800 1600 50  0001 C CNN
	1    3800 1600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 5B219669
P 3800 1800
F 0 "#FLG02" H 3800 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 1950 50  0000 C CNN
F 2 "" H 3800 1800 50  0001 C CNN
F 3 "" H 3800 1800 50  0001 C CNN
	1    3800 1800
	-1   0    0    1   
$EndComp
$Comp
L SW_Push SW2
U 1 1 5B21A301
P 5150 5000
F 0 "SW2" H 5200 5100 50  0000 L CNN
F 1 "Flash" H 5150 4940 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-1000P" H 5150 5200 50  0001 C CNN
F 3 "" H 5150 5200 50  0001 C CNN
	1    5150 5000
	0    -1   -1   0   
$EndComp
$Comp
L SW_Push SW1
U 1 1 5B21A409
P 2650 5050
F 0 "SW1" H 2700 5150 50  0000 L CNN
F 1 "Reset" H 2650 4990 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-1000P" H 2650 5250 50  0001 C CNN
F 3 "" H 2650 5250 50  0001 C CNN
	1    2650 5050
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 5B21A586
P 2150 5400
F 0 "R1" V 2230 5400 50  0000 C CNN
F 1 "10k" V 2150 5400 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 2080 5400 50  0001 C CNN
F 3 "" H 2150 5400 50  0001 C CNN
	1    2150 5400
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 5B21A80E
P 4650 6100
F 0 "R5" V 4730 6100 50  0000 C CNN
F 1 "10k" V 4650 6100 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4580 6100 50  0001 C CNN
F 3 "" H 4650 6100 50  0001 C CNN
	1    4650 6100
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5B21AA4B
P 2550 5800
F 0 "R4" V 2630 5800 50  0000 C CNN
F 1 "10k" V 2550 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 2480 5800 50  0001 C CNN
F 3 "" H 2550 5800 50  0001 C CNN
	1    2550 5800
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 5B21AAD4
P 5450 6000
F 0 "R7" V 5530 6000 50  0000 C CNN
F 1 "10k" V 5450 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5380 6000 50  0001 C CNN
F 3 "" H 5450 6000 50  0001 C CNN
	1    5450 6000
	0    1    1    0   
$EndComp
Text Label 3950 1650 0    60   ~ 0
USB+
Text Label 2950 1450 0    60   ~ 0
HostTX
Text Label 2950 1350 0    60   ~ 0
HostRX
Text Label 7850 2500 0    60   ~ 0
USB+
Text Label 7850 2600 0    60   ~ 0
USB-
Text Label 6250 3150 0    60   ~ 0
GND
Text Label 6650 2050 0    60   ~ 0
CHG+
Text Label 8750 2250 0    60   ~ 0
CHG+
Text Label 10450 2250 0    60   ~ 0
3.3+
Text Label 9850 2700 0    60   ~ 0
GND
Text Label 5950 2250 1    60   ~ 0
BAT+
Text Label 3950 1750 0    60   ~ 0
USB-
Text Label 1800 5550 0    60   ~ 0
BAT+
Text Label 4750 5800 0    60   ~ 0
SCL
Text Label 4750 5900 0    60   ~ 0
SDA
Text Label 5400 6300 0    60   ~ 0
GND
Text Label 7500 5300 0    60   ~ 0
GY+
Text Label 7500 5400 0    60   ~ 0
GND
Text Label 7500 5500 0    60   ~ 0
SCL
Text Label 7500 5600 0    60   ~ 0
SDA
Text Label 7500 5900 0    60   ~ 0
GND
Text Label 4600 5600 0    60   ~ 0
HostRX
Text Label 4600 5700 0    60   ~ 0
HostTX
NoConn ~ 7800 5700
NoConn ~ 7800 5800
NoConn ~ 7800 6000
NoConn ~ 3350 6800
NoConn ~ 3450 6800
NoConn ~ 3550 6800
NoConn ~ 3650 6800
NoConn ~ 3750 6800
NoConn ~ 3850 6800
Text Label 5600 5900 1    60   ~ 0
3.3+
Text Label 1750 5400 0    60   ~ 0
3.3+
Text Label 3900 4450 3    60   ~ 0
GND
Text Label 2000 6000 0    60   ~ 0
GY+
$Comp
L R R6
U 1 1 5B228DC8
P 4900 6200
F 0 "R6" V 4980 6200 50  0000 C CNN
F 1 "10k" V 4900 6200 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4830 6200 50  0001 C CNN
F 3 "" H 4900 6200 50  0001 C CNN
	1    4900 6200
	0    1    1    0   
$EndComp
NoConn ~ 2700 5900
NoConn ~ 2700 6100
NoConn ~ 2700 6200
$Comp
L C C1
U 1 1 5B2296F3
P 10150 2250
F 0 "C1" H 10175 2350 50  0000 L CNN
F 1 "1uF" H 10175 2150 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 10188 2100 50  0001 C CNN
F 3 "" H 10150 2250 50  0001 C CNN
	1    10150 2250
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 5B22C3B3
P 10400 2100
F 0 "#FLG03" H 10400 2175 50  0001 C CNN
F 1 "PWR_FLAG" H 10400 2250 50  0000 C CNN
F 2 "" H 10400 2100 50  0001 C CNN
F 3 "" H 10400 2100 50  0001 C CNN
	1    10400 2100
	1    0    0    -1  
$EndComp
$Comp
L ESP-12F U2
U 1 1 5B22CF91
P 3600 5900
F 0 "U2" H 3600 5800 50  0000 C CNN
F 1 "ESP-12F" H 3600 6000 50  0000 C CNN
F 2 "ESP8266:ESP-12E" H 3600 5900 50  0001 C CNN
F 3 "" H 3600 5900 50  0001 C CNN
	1    3600 5900
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 5B22D046
P 2350 6050
F 0 "#FLG04" H 2350 6125 50  0001 C CNN
F 1 "PWR_FLAG" H 2350 6200 50  0000 C CNN
F 2 "" H 2350 6050 50  0001 C CNN
F 3 "" H 2350 6050 50  0001 C CNN
	1    2350 6050
	-1   0    0    1   
$EndComp
$Comp
L BOB-13263 U1
U 1 1 5B21DE34
P 2600 2000
F 0 "U1" H 2950 1750 60  0000 C CNN
F 1 "BOB-13263" H 2900 950 60  0000 C CNN
F 2 "BOB13263:BOB-13263-TOP" H 2600 2000 60  0001 C CNN
F 3 "" H 2600 2000 60  0001 C CNN
	1    2600 2000
	1    0    0    -1  
$EndComp
NoConn ~ 3100 1800
NoConn ~ 2700 1800
NoConn ~ 3450 2350
NoConn ~ 3450 2450
NoConn ~ 3450 2550
NoConn ~ 3450 2650
NoConn ~ 3450 2750
NoConn ~ 3450 2850
NoConn ~ 3450 2950
NoConn ~ 2400 2950
NoConn ~ 2400 2850
NoConn ~ 2400 2750
NoConn ~ 2400 2650
NoConn ~ 2400 2550
NoConn ~ 2400 2450
NoConn ~ 2400 2350
$Comp
L PWR_FLAG #FLG05
U 1 1 5B2225EE
P 6250 3200
F 0 "#FLG05" H 6250 3275 50  0001 C CNN
F 1 "PWR_FLAG" H 6250 3350 50  0000 C CNN
F 2 "" H 6250 3200 50  0001 C CNN
F 3 "" H 6250 3200 50  0001 C CNN
	1    6250 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3000 1650 4200 1650
Wire Wire Line
	3000 1650 3000 1800
Connection ~ 3800 1650
Wire Wire Line
	8000 2500 7800 2500
Wire Wire Line
	8000 2600 7800 2600
Wire Wire Line
	6500 2950 6500 3150
Wire Wire Line
	6500 3150 6250 3150
Wire Wire Line
	6500 2250 6500 2050
Wire Wire Line
	6500 2050 6900 2050
Wire Wire Line
	8750 2250 9150 2250
Wire Wire Line
	9450 2550 9450 2700
Wire Wire Line
	9450 2700 10000 2700
Wire Wire Line
	9750 2250 10000 2250
Wire Wire Line
	5950 2350 6500 2350
Wire Wire Line
	4500 5600 4900 5600
Wire Wire Line
	4500 5700 4900 5700
Wire Wire Line
	4500 5800 4900 5800
Wire Wire Line
	4500 5900 4900 5900
Wire Wire Line
	1700 6300 2700 6300
Wire Wire Line
	4500 6300 5600 6300
Wire Wire Line
	7500 5300 7800 5300
Wire Wire Line
	7500 5400 7800 5400
Wire Wire Line
	7500 5500 7800 5500
Wire Wire Line
	7500 5600 7800 5600
Wire Wire Line
	7500 5900 7800 5900
Wire Wire Line
	5600 6100 4800 6100
Wire Wire Line
	2650 5250 2650 5600
Wire Wire Line
	2300 5400 2650 5400
Wire Wire Line
	1700 5400 2000 5400
Wire Wire Line
	2650 4850 2650 4700
Connection ~ 2650 5400
Wire Wire Line
	1700 5800 2400 5800
Wire Wire Line
	1700 5400 1700 6300
Connection ~ 1700 5400
Wire Wire Line
	2000 6000 2700 6000
Wire Wire Line
	4500 6000 5300 6000
Wire Wire Line
	5150 5200 5150 6000
Connection ~ 5150 6000
Wire Wire Line
	5150 4700 5150 4800
Wire Wire Line
	2650 4700 5150 4700
Wire Wire Line
	3900 4700 3900 4450
Connection ~ 3900 4700
Connection ~ 1700 5800
Wire Wire Line
	5600 5700 5600 6100
Connection ~ 5600 6000
Wire Wire Line
	4500 6200 4750 6200
Wire Wire Line
	5050 6200 5200 6200
Wire Wire Line
	5200 6200 5200 6300
Connection ~ 5200 6300
Wire Wire Line
	2650 5600 2700 5600
Wire Wire Line
	10300 2250 10650 2250
Wire Wire Line
	10400 2100 10400 2250
Connection ~ 10400 2250
Wire Wire Line
	2350 6050 2350 6000
Connection ~ 2350 6000
Wire Wire Line
	5950 2350 5950 2050
Connection ~ 5950 2350
Wire Wire Line
	3200 1800 3200 1750
Wire Wire Line
	3200 1750 4200 1750
Wire Wire Line
	3800 1600 3800 1650
Wire Wire Line
	3800 1800 3800 1750
Connection ~ 3800 1750
Wire Wire Line
	2800 1800 2800 1350
Wire Wire Line
	2800 1350 3250 1350
Wire Wire Line
	2900 1450 2900 1800
Wire Wire Line
	2900 1450 3250 1450
Wire Wire Line
	5950 2650 6500 2650
Wire Wire Line
	6500 2650 6500 2850
Wire Wire Line
	6250 3150 6250 3200
Wire Wire Line
	6100 1950 6100 2350
Connection ~ 6100 2350
Text Notes 5450 2500 0    60   ~ 0
Pad
$Comp
L Conn_01x02 J3
U 1 1 5B22789F
P 6100 1750
F 0 "J3" H 6100 1850 50  0000 C CNN
F 1 "Molex" H 6100 1550 50  0000 C CNN
F 2 "Connectors_Molex:Molex_PicoBlade_53048-0210_02x1.25mm_Angled" H 6100 1750 50  0001 C CNN
F 3 "" H 6100 1750 50  0001 C CNN
	1    6100 1750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6200 1950 6200 2650
Connection ~ 6200 2650
Text Notes 9250 2000 0    60   ~ 0
MCP1700
$Comp
L R R2
U 1 1 5B228874
P 2200 5700
F 0 "R2" V 2280 5700 50  0000 C CNN
F 1 "120k" V 2200 5700 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 2130 5700 50  0001 C CNN
F 3 "" H 2200 5700 50  0001 C CNN
	1    2200 5700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1800 5550 2250 5550
Wire Wire Line
	2550 5550 2550 5700
Wire Wire Line
	2350 5700 2700 5700
Connection ~ 2550 5700
Wire Wire Line
	2050 5700 1800 5700
Text Label 1800 5700 0    60   ~ 0
GND
$EndSCHEMATC

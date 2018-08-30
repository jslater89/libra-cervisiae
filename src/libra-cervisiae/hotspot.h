#ifndef HOTSPOT_H
#define HOTSPOT_H

void hotspotSetup();
void startServer();
void hotspotLoop();
bool tryConnect();
void handleLiveUpdate();
void updateTare();
void updateEquipmentWeight();
void updateCalibration();
void getConfig();
void updateConfig();
void getTempSensors();

#endif

#ifndef STORAGE_HPP
#define STORAGE_HPP


int read_int(int address);
void write_int(int address, int value);

void writeBatteryState(int BatteryAddress, int state);
int readBatteryState(int BatteryAddress);

void writeCO2State(int CO2Address, int state);
int readCO2State(int CO2Address);

#endif

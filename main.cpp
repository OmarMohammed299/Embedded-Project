#include "mbed.h"

// Pin assignments for the shift register control
DigitalOut shiftDataPin(D8);    // Serial data (Shift Register)
DigitalOut shiftClockPin(D7);   // Clock for the shift register
DigitalOut latchPin(D4);        // Latch pin for shift register

// Pin assignments for input switches and voltage sensor
AnalogIn voltagePin(A0);        // Voltage sensor input (Analog)
DigitalIn resetButton(A1);      // Reset button (S1)
DigitalIn voltageButton(A3);    // Show voltage button (S3)

// Segment pattern for 0-9 digits (common anode, active LOW)
const uint8_t segmentDigits[] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};

// Masks for selecting individual digits (D0 to D3)
const uint8_t digitSelectionMask[4] = {
    0b00000001,  // Digit 1 (D0, leftmost)
    0b00000010,  // Digit 2 (D1)
    0b00000100,  // Digit 3 (D2)
    0b00001000   // Digit 4 (D3, rightmost)
};

// Function to send 16 bits of data to shift register (segments and digit selection)
void shiftDataToRegister(uint8_t segmentData, uint8_t digitMask) {
    latchPin = 0;

    // Sending segment data (MSB first)
    for (int i = 7; i >= 0; i--) {
        shiftDataPin = (segmentData >> i) & 0x01;
        shiftClockPin = 1;
        shiftClockPin = 0;
    }

    // Sending digit select data (MSB first)
    for (int i = 7; i >= 0; i--) {
        shiftDataPin = (digitMask >> i) & 0x01;
        shiftClockPin = 1;
        shiftClockPin = 0;
    }

    latchPin = 1;  // Update the output on the display
}

// Function to display voltage on the 7-segment display
void showVoltage(int voltage) {
    int digits[4] = {
        (voltage / 1000) % 10,  // Thousands (D3)
        (voltage / 100) % 10,   // Hundreds (D2)
        (voltage / 10) % 10,    // Tens (D1)
        voltage % 10            // Ones (D0)
    };

    for (int i = 0; i < 4; i++) {
        uint8_t segmentData = segmentDigits[digits[i]];
        if (i == 1) segmentData &= ~(1 << 7);  // Add decimal point to D3 for voltage
        shiftDataToRegister(segmentData, digitSelectionMask[i]); // Send to display
        wait_us(2000);  // Small delay for stable display
    }
}

// Function to calculate a stable average voltage over multiple readings
float readStableVoltage() {
    const int sampleCount = 50;
    float voltageSum = 0;

    // Taking multiple samples to stabilize the reading
    for (int i = 0; i < sampleCount; i++) {
        voltageSum += voltagePin.read();  // Read voltage (0.0 to 1.0)
        wait_us(100);  // Small delay between readings
    }

    return (voltageSum / sampleCount) * 5.0f;  // Return voltage in range (0V to 5V)
}

// Function to display time on the 7-segment display
void showTime(int minutes, int seconds) {
    int timeDigits[4] = {
        (minutes / 10) % 10,  // Tens place of minutes (D3)
        minutes % 10,          // Ones place of minutes (D2)
        (seconds / 10) % 10,   // Tens place of seconds (D1)
        seconds % 10           // Ones place of seconds (D0)
    };

    for (int i = 0; i < 4; i++) {
        uint8_t segmentData = segmentDigits[timeDigits[i]];
        shiftDataToRegister(segmentData, digitSelectionMask[i]);  // Send to display
        wait_us(2000);  // Small delay for stable display
    }
}

// Global variables for timekeeping
long long lastUpdateTime = 0;
int secondsCounter = 0;
int minutesCounter = 0;

int main() {
    lastUpdateTime = get_ms_count();  // Initialize last update time

    while (true) {
        long long currentTime = get_ms_count();  // Get the current system time in milliseconds

        // Update the time every second (1000 ms)
        if (currentTime - lastUpdateTime >= 1000) {
            lastUpdateTime = currentTime;
            secondsCounter++;
            if (secondsCounter >= 60) {
                secondsCounter = 0;
                minutesCounter++;
            }
        }

        // Show voltage if voltageButton is pressed
        if (voltageButton == 0) {
            float stableVoltage = readStableVoltage();  // Get stable voltage value
            int voltageInCentivolts = (int)(stableVoltage * 100);  // Convert to integer (centivolts)
            showVoltage(voltageInCentivolts);  // Display voltage
        } else {
            showTime(minutesCounter, secondsCounter);  // Display time in minutes and seconds
        }

        // Reset time if resetButton is pressed or 100 minutes have passed
        if (resetButton == 0 || minutesCounter >= 100) {
            minutesCounter = 0;
            secondsCounter = 0;
        }
    }
}
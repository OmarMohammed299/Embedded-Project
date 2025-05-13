<p>
  <img src="https://github.com/OmarMohammed299/Embedded-Project/blob/main/Video%20and%20Report/WhatsApp%20Image%202025-05-13%20at%2000.52.29_bc019460.jpg" alt="Download Icon" width="400" align="left"/>
</p>
<br clear="all"/>


<table style="width: 100%; text-align: center; border-collapse: collapse;">
  <tr>
    <th style="border: 2px solid black; padding: 10px;">Name</th>
    <th style="border: 2px solid black; padding: 10px;">ID</th>
  </tr>
  <tr>
    <td style="border: 2px solid black; padding: 10px;">Omar Mohammed Mehany</td>
    <td style="border: 2px solid black; padding: 10px;">2201058</td>
  </tr>
  <tr>
    <td style="border: 2px solid black; padding: 10px;">Ammar Ahmed Mostafa</td>
    <td style="border: 2px solid black; padding: 10px;">2200262</td>
  </tr>
<tr>
    <td style="border: 2px solid black; padding: 10px;">Tarek Hazem Salah</td>
    <td style="border: 2px solid black; padding: 10px;">2200680</td>
  </tr>

</table>




# Embedded Project: Real-Time Clock and Voltage Display

## Overview
This project integrates the **STM32 Nucleo F401RE** board with the **Arduino Multi-Function Shield** to display a **real-time clock (RTC)** and **voltage readings** on a **4-digit 7-segment display**. The voltage is read using a **potentiometer** and displayed when the **S3 switch** is pressed, while the RTC continues tracking elapsed time.

## Features
- 🕒 **Real-time clock** displayed on the 7-segment display.
- 🔋 **Voltage display** from a potentiometer when **S3** is pressed.
- 🔄 **Reset functionality** when **S1** is pressed or after 100 minutes.

## Components
- **STM32 Nucleo F401RE**
- **Arduino Multi-Function Shield**
  - 4-digit 7-segment display
  - Potentiometer
  - 3 switches (**S1, S2, S3**)

## Pin Setup
- **Shift Register Pins** (7-segment display control):
  - `DigitalOut serPin(D8)`  - Serial Data
  - `DigitalOut clkPin(D7)`  - Clock
  - `DigitalOut latchPin(D4)` - Latch
- **Inputs**:
  - `AnalogIn voltagePin(A0)`  - Potentiometer
  - `DigitalIn s1Switch(A1)`   - Reset
  - `DigitalIn s3Switch(A3)`   - Show Voltage

## Functionality
- The program runs in **single-threaded mode**, updating the **RTC** every second.
- Pressing **S3** displays the voltage reading from the potentiometer.
- Pressing **S1** or reaching **100 minutes** resets the timer to `00:00`.

## Build Instructions

### Option 1: Using **Mbed OS**
1. **Install Mbed OS**  
   Follow the official guide: [Mbed OS Installation](https://os.mbed.com/studio/)
2. **Import the Project**  
   Clone the repository or download the project files.
3. **Build and Flash**  
   Connect your **Nucleo F401RE** board via USB, then run the following command:
   ```bash
   mbed compile -m NUCLEO_F401RE -t GCC_ARM --flash

### Option 2: Using **Using Keil MDK**
1. **Install Keil MDK**  
   - Download and install Keil MDK from: [Keil MDK](https://www.keil.com/download/)
2. **Import the Project**  
   Clone the repository or download the project files- Open Keil uVision.
- Select Project > Open and browse to your project folder.
- Import the appropriate .uvprojx file.
- Compile & Run.
- Click on Build to compile the program.
- Connect your Nucleo F401RE via USB.
- Click Download to flash the program onto the board.
- Press Run to execute the program.
3. **Build and Flash**  
   Connect your **Nucleo F401RE** board via USB, then run the following command:
   ```bash
   mbed compile -m NUCLEO_F401RE -t GCC_ARM --flash

## Project Resources

<h2>📹 Project Video </h2>

<a href="https://drive.google.com/file/d/1xihj5X5wrXCdcJjtQfc0rjgoPRfWbtPO/view?usp=sharing">
  <img src="https://github.com/OmarMohammed299/Embedded-Project/blob/main/Video%20and%20Report/WhatsApp%20Image%202025-05-13%20at%2001.03.10_2032ee3c.jpg" alt="Watch the video" width="300"/>
</a>

<h2>📄 Project Report</h2>

<a href="https://github.com/OmarMohammed299/Embedded-Project/blob/main/Video%20and%20Report/Project%20Report.pdf>
  <img src="https://github.com/OmarMohammed299/Embedded-Project/blob/main/Video%20and%20Report/WhatsApp%20Image%202025-05-13%20at%2001.13.29_22d70351.jpg" alt="Open Project Report" width="300"/>
</a>



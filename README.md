# 🚗 Car Black Box

The **Car Black Box** project is designed to monitor critical vehicle parameters and record essential data for accident investigation and vehicle maintenance. It utilizes a **PIC18F4580 microcontroller** to process sensor data and manage the dashboard interface, enhancing vehicle safety and accident analysis through real-time monitoring and data logging.

---

## 🛠 Project Features

- **Accident Data Logging:** Stores critical parameters like speed, gear position, and collision impact for post-accident analysis.
- **Collision Detection:** Detects crashes, logs events, and disables gear shifts during an accident.
- **Microcontroller-Based System:** Uses **PIC18F4580** for sensor data processing and gear control.
- **User Interface:** Matrix Digital Keypad (**MKP**) for system interaction and LCD for status display.
- **Memory Storage:** Logs accident data in **EEPROM** for later retrieval and analysis.

---

## 🧰 Technology Stack

- **Microcontroller:** PIC18F4580
- **Sensors:** Speed, collision detection (GPS optional)
- **Interface:** MKP and LCD display
- **Memory Storage:** EEPROM
- **Communication:** I2C and UART

---

## 🔄 Project Workflow

1. **Sensor Data Acquisition:** Collects speed, gear position, and impact data.
2. **Processing & Storage:** Microcontroller processes and logs data into **EEPROM**.
3. **User Interaction:** Through the **MKP**.
4. **Collision Handling:** Disables gear shifts when a collision is detected.
5. **Data Retrieval:** Logs downloaded via **UART** for analysis.

---

## 📂 File Structure

- `main.c` - Main control loop for system states and operations.
- `adc.c` - Manages **ADC** conversion for sensor inputs.
- `clcd.c` - Controls the **LCD display**.
- `dashboard.c` - Manages dashboard state and **MKP** interactions.
- `eeprom.c` - **EEPROM** read/write operations for data logging.
- `ds1307.c` - Handles real-time clock (**RTC**) functionality.
- `download_log.c` - Retrieves logs via **UART**.
- `clearlog.c` - Clears **EEPROM** logs.

---

## 🚀 Future Enhancements

- **GPS Integration:** Accident tracking with location data.
- **Wireless Data Transmission:** Real-time access through **Bluetooth/WiFi**.
- **Cloud Storage:** Remote access to accident data.
- **AI Processing:** Predictive analytics for detecting dangerous driving patterns.

---

## 📧 Contact

For any questions, feel free to reach out:

- **Vivek**
- Email: [gopivivek57@gmail.com](mailto:gopivivek57@gmail.com)
- LinkedIn: [Vivek](https://www.linkedin.com/in/vivek57/)

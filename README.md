# HestiaGuard Smart Power & Safety System

A distributed home management and power-control system built around ESP32 microcontrollers. HestiaGuard combines environmental monitoring, electrical usage tracking, and centralized control to improve household safety and energy efficiency.

## 📋 Table of Contents

- [System Overview](#system-overview)
- [Hardware Components](#hardware-components)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Uploading Configuration to Hardware](#uploading-configuration-to-hardware)
- [Features](#features)
- [Technologies](#technologies)
- [Project Objectives](#project-objectives)

## 🏠 System Overview

HestiaGuard is a two-layer IoT system:

- **Sensor Node Layer**: Multiple ESP32 units distributed throughout your home, each monitoring environmental and electrical conditions in different rooms
- **Central Control Layer**: ESP32-S3-BOX acts as the control hub with a visual dashboard and automated decision-making capabilities

The system enables localized sensing while maintaining centralized control, creating a scalable and efficient smart home platform.

## 🔧 Hardware Components

### Required Components

| Component             | Quantity | Purpose                                           |
| --------------------- | -------- | ------------------------------------------------- |
| **ESP32-S3-BOX-3**    | 1        | Central controller with touchscreen UI            |
| **ESP32-WROOM**       | 1+       | Secondary sensor nodes (one per room or zone)     |
| **Arduino Pro Micro** | 1+       | Optional local control modules for specific zones |

### Sensors & Peripherals (per Sensor Node)

| Component            | Model               | Purpose                         |
| -------------------- | ------------------- | ------------------------------- |
| Gas/Smoke Sensor     | MQ-2                | Detects harmful gases and smoke |
| Flame Sensor         | IR Flame Detector   | Detects fire/heat presence      |
| Temperature/Humidity | DHT22               | Environmental monitoring        |
| Current Sensor       | ACS712 (5A/20A/30A) | Electrical consumption tracking |
| Relay Module         | 2-Channel 5V Relay  | Local power switching           |

### Additional Components

- USB-C cables for ESP32-S3-BOX programming
- Micro-USB cables for ESP32-WROOM programming
- Jumper wires and breadboards for prototyping
- 5V power supply for ESP32 nodes
- AC relay module for power control (rated for household current)

## 🏗️ System Architecture

### Layer 1️⃣: Sensor Node Layer (Secondary ESP32 Units)

Each room contains a dedicated ESP32-WROOM sensor node connected to environmental and electrical sensors:

- **Gas/Smoke Detection**: MQ-2 sensor monitors for dangerous gas levels
- **Flame Detection**: Flame sensor identifies active fire/heat
- **Climate Monitoring**: DHT22 tracks temperature and humidity
- **Power Usage Tracking**: ACS712 current sensors measure electrical consumption per room
- **Local Power Control**: Relay modules enable/disable power delivery to room circuits
- **Data Transmission**: Sends collected data to central controller via UART or Wi-Fi

**Benefits of Distributed Architecture:**

- Localized sensing for better accuracy
- Independent operation even if central controller is offline
- Scalable design—easily add sensors to new rooms
- Reduced wiring complexity

### Layer 2️⃣: Central Control Layer (ESP32-S3-BOX)

The ESP32-S3-BOX-3 serves as the system's brain and user interface:

- **Data Collection**: Receives sensor readings from all room nodes
- **Visual Dashboard**: LVGL-based graphical interface displays real-time data
- **User Control**: Touch interface to enable/disable power per room
- **Automated Responses**: Triggers safety actions based on sensor conditions
- **Decision Making**: Centralizes logic for power distribution and safety protocols

**Automated Safety Features:**

- 🚨 **Gas Detection Response**: Auto-cuts power when dangerous gas levels detected
- 🔥 **Flame Detection**: Immediate response to flame/heat detection
- ⚡ **Load Management**: Adjusts power availability based on consumption patterns
- 📊 **Real-Time Monitoring**: Continuous display of all environmental and electrical metrics

## 📦 Installation

### Prerequisites

- Arduino IDE or PlatformIO
- ESP-IDF tools (for ESP32 development)
- USB cables for programming
- Home Assistant (optional, for integration)

### Step 1: Clone the Repository

```bash
git clone https://github.com/yourusername/HestiaGuard.git
cd HestiaGuard
```

### Step 2: Install Development Environment

Use **Arduino IDE** (recommended):

1. Install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Open Arduino IDE → Preferences
3. Add ESP32 board URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
4. Go to Tools → Board Manager → Search "ESP32" → Install

**OR use PlatformIO:**

```bash
pip install platformio
pio project init --board esp32doit-devkit
```

### Step 3: Connect Hardware

**For ESP32-S3-BOX-3 (Central):**

- Connect via USB-C to your computer
- Select Board: "ESP32-S3-BOX-3" in Arduino IDE

**For ESP32-WROOM nodes (Sensors):**

- Connect via Micro-USB to your computer
- Select Board: "ESP32 WROOM-32" in Arduino IDE

### Step 4: Upload Firmware

Arduino sketch files are available:

- `Arduino-micro.ino` - For Arduino Pro Micro modules

Use Arduino IDE to upload:

1. File → Open → Select `.ino` file
2. Tools → Board → Select correct board
3. Tools → Port → Select COM port
4. Click Upload button (→)

## 📤 Uploading Configuration to Hardware

HestiaGuard uses YAML configuration files for easier setup without recompiling code.

### YAML Configuration Files

- `ESP32-S3-BOX-3.yaml` - Central controller configuration
- `secondary-esp32-node.yaml` - Sensor node configuration

### Method 1: Using ESPHome (Recommended)

ESPHome allows you to upload YAML configurations directly to ESP32 devices without programming.

#### Installation

```bash
pip install esphome
```

#### Upload Central Controller

1. Connect ESP32-S3-BOX-3 via USB-C
2. Run the following command:

```bash
esphome run ESP32-S3-BOX-3.yaml --device /dev/ttyUSB0
```

On Windows, find your COM port and use:

```bash
esphome run ESP32-S3-BOX-3.yaml --device COM3
```

#### Upload Sensor Nodes

1. Connect ESP32-WROOM via Micro-USB
2. Run:

```bash
esphome run secondary-esp32-node.yaml --device COM4
```

**Note:** Replace `COM3`, `COM4` with your actual COM ports. To find COM ports:

- **Windows**: Device Manager → Ports (COM & LPT)
- **Linux/Mac**: `ls /dev/tty*`

### Method 2: Using Arduino IDE with YAML (Alternative)

1. Open your YAML file in a text editor
2. Copy the ESPHome YAML content
3. Use the [ESPHome Dashboard](https://web.esphome.io/) to compile and flash

### Method 3: Manual Configuration

If not using ESPHome, edit the configuration files and:

1. Create a new Arduino sketch incorporating the YAML settings
2. Update pins, sensors, and communication settings
3. Upload using Arduino IDE

### Verification

After uploading, verify the configuration:

1. Open Serial Monitor (Tools → Serial Monitor)
2. Set baud rate to 115200
3. Check for startup logs confirming sensor connections
4. Verify Wi-Fi/UART connection to other nodes

## ✨ Features

### Environmental Monitoring

- Real-time gas/smoke detection
- Flame and heat sensing
- Temperature and humidity tracking
- Multi-sensor fusion for safety

### Electrical Management

- Per-room power consumption tracking
- Remote relay control for room circuits
- Load-based power distribution
- Energy efficiency insights

### User Interface

- Touchscreen LVGL dashboard on ESP32-S3-BOX
- Real-time sensor data visualization
- One-tap power control per room
- Safety alert notifications

### Automation

- Automatic power cutoff on gas detection
- Emergency response to flame detection
- Load balancing across rooms
- Threshold-based alerts

### Scalability

- Easily add new sensor nodes to additional rooms
- Modular sensor architecture
- Distributed processing model
- Hybrid communication (UART/Wi-Fi)

## 🛠️ Technologies

- **Microcontrollers**: ESP32, ESP32-S3, Arduino Pro Micro
- **Frameworks**: Arduino, ESPHome, ESP-IDF
- **UI Framework**: LVGL (Light and Versatile Graphics Library)
- **Communication**: UART, SPI, I2C, Wi-Fi
- **Integration**: Home Assistant compatible
- **Development Tools**: Arduino IDE, PlatformIO, ESPHome

## 🎯 Project Objectives

- ✅ Improve home safety through comprehensive environmental monitoring
- ✅ Enable intelligent power distribution and load management
- ✅ Provide a centralized visual dashboard for system monitoring
- ✅ Demonstrate scalable IoT node architecture
- ✅ Integrate hardware control with modern embedded UI frameworks
- ✅ Create a hybrid system combining local autonomy with centralized decision-making

## 🔑 Key Design Concepts

| Concept                         | Implementation                                              |
| ------------------------------- | ----------------------------------------------------------- |
| **Distributed Sensing**         | Multiple ESP32 nodes per room for localized monitoring      |
| **Centralized Decision Making** | ESP32-S3-BOX processes all data and makes control decisions |
| **Real-Time Awareness**         | Continuous environmental + electrical monitoring            |
| **Hardware-Level Safety**       | Relay-based power control at the circuit level              |
| **Expandable Architecture**     | Easy addition of new sensor nodes and room zones            |
| **Hybrid Communication**        | UART for reliability, Wi-Fi for flexibility                 |

## 📱 Integration with Home Assistant

HestiaGuard can be integrated with Home Assistant for extended automation:

1. Deploy ESPHome nodes in your Home Assistant instance
2. Add the YAML files to your Home Assistant config
3. Configure automations based on HestiaGuard sensor data
4. Create custom Lovelace dashboards

## 🚀 Getting Started

### Quick Start (Central Controller)

1. Connect ESP32-S3-BOX-3 via USB-C
2. Upload `ESP32-S3-BOX-3.yaml` using ESPHome
3. Access the touchscreen interface
4. View real-time sensor data from connected nodes

### Quick Start (Sensor Node)

1. Connect ESP32-WROOM via Micro-USB
2. Connect sensors (MQ-2, DHT22, ACS712, Flame sensor)
3. Upload `secondary-esp32-node.yaml` using ESPHome
4. Verify data transmission to central controller

## 📝 Configuration

Edit the YAML files to customize:

- Wi-Fi credentials
- Sensor pin assignments
- Safety thresholds
- Update intervals
- Communication settings

## 🤝 Contributing

Contributions welcome! Areas for enhancement:

- Additional sensor types
- Web dashboard interface
- Mobile app integration
- Machine learning-based anomaly detection
- Advanced power scheduling

## 📜 License

[Specify your license here]

## 📧 Contact & Support

For issues, questions, or suggestions, please open an issue on GitHub.

---

**HestiaGuard** - _Intelligent Home Safety Through Distributed Sensing_

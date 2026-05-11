UNLOX: Integrated Smart Home Automation & Security Ecosystem
Project Overview
This project is an industry-grade IoT ecosystem designed to simulate the architectural principles of modern residential automation. It integrates autonomous environmental sensing, edge-based decision-making, and real-time actuation to create a responsive "Living Space".

The core engineering achievement of this project is the **Asynchronous, Non-Blocking Logic Engine**. By abandoning traditional `delay()` functions and utilizing a `millis()`-based **Finite State Machine (FSM)**, the central microcontroller achieves true parallel processing—monitoring climate, illumination, and security simultaneously without system latency.

Core Modules & Logic
1. Adaptive Climate Control (HVAC): Autonomous thermal management using a DHT22 sensor. It triggers a localized cooling response (Blue LED) when the ambient temperature exceeds 30.0°C.
2. Intelligent Ambient Illumination: An energy conservation module utilizing a Photoresistor (LDR). It automatically activates indoor lighting during low-light conditions (< 2000 ADC).
3. Proactive Intrusion Detection: A primary defense layer that triggers aggressive auditory and visual alarms upon detecting unauthorized motion when the system is "Armed".
4. Automated Access & Entry: A smart door simulation using an SG90 Servo motor. It features a doorbell trigger and a non-blocking 5-second auto-close sequence to ensure structural integrity.
5. Global State Governance: A hardware-driven mode toggle (Slide Switch) that shifts the system between Normal Mode (Comfort) and Security Mode (High-Sensitivity).

Technical Stack
Microcontroller: NodeMCU (ESP8266) & ESP32 for high-precision simulation.
Sensors: DHT22 (Digital Temp/Humidity), LDR (Light), PIR/IR (Motion).
Actuators: SG90 Micro Servo, Piezo Buzzer, Status LEDs.
Architecture: C++ (Arduino IDE) with Millis-based timing logic.
Simulation: Wokwi Digital Twin for hardware-software validation.

System Architecture
The system uses a Continuous Event Loop to check all sensors thousands of times per second. This ensures that high-priority security interrupts are never missed, even while the door access or climate modules are active.

Key Learning Outcomes
- Mastered Non-Blocking Firmware Design to eliminate system latency.
- Implemented Software Hysteresis to prevent sensor "flickering" at threshold limits.
- Validated hardware designs through Digital Twin simulation before physical deployment.
- Engineered a Finite State Machine to manage complex global system states.

Developed by: Shreesha V P




* 
**Hysteresis Mention:** It shows you solved the real-world problem of sensor noise and flickering.



Good luck with your presentation tomorrow, Harish! Given your strict 2,250-calorie goal, make sure you're well-fueled so you can answer these technical questions with high energy!

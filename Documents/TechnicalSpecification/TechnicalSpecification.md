<details>
<summary>Table of Contents</summary>

- [I. Audience](#i-audience)
- [II. Overview](#ii-overview)
- [III. Requirements](#iii-requirements)
- [IV. Priorities](#iv-priorities)
- [V. Nice to have](#v-nice-to-have)
- [VI. Technical Architecture](#vi-technical-architecture)
  - [1. Technology used](#1-technology-used)
  - [2. Key functions, operations, and algorithms](#2-key-functions-operations-and-algorithms)
      - [2.1. Battery management](#21-battery-management)
      - [2.2. NFC chip](#22-nfc-chip)
      - [2.3. Alarm management](23-alarm-management)
      - [2.4. Bluetooth low energy (BLE)](#24-bluetooth-low-energy-ble)
      - [2.5. GPRS](#25-gprs)
  - [3. Algorithms](#3-algorithms)   
      - [3.1. Battery management algorithm](#31-battery-management-algorithm)
      - [3.2. Alarm management algorithm](32-alarm-management-algorithm)
- [VII. Syntax and Structure](#vii-syntax-and-structure)
  - [1. Folder structure](#1-folder-structure)
  - [2. Program file structure](#2-program-file-structure)
  - [3. Function declaration](#3-function-declaration)
  - [4. Naming](#4-naming)
  - [5. Comments](#5-comments)
- [VIII. Code Design Principles](#viii-code-design-principles)
- [IX. Challenges](#ix-challenges)
- [X. Possible Bugs](#x-possible-bugs)
- [XI. Development Process](#xi-development-process)
- [XII. Glossary](#xii-glossary)
- [XIII. Conclusion](#xiii-conclusion)


 
</details>

---

# I. Audience

This document is primarily intended for:

- **Software developer**:  To understand the user and technical requirements, and to guide decision-making and planning. Help them understand risks and challenges, customer requirements, and additional technical requirements and choices made.

Secondary audiences:

- **Program manager**: To validate against the functional specification, and the client expectations.
- **Quality-Assurance**: To aid in preparing the test plan and to use it for validating issues.
- **Project manager**: To understand the user and technical requirements, and to guide decision-making and planning. Help them understand risks and challenges, customer requirements, and additional technical requirements and choices made.

---

# II. Overview

The goal of this project is to refining the functionality and code base of SportShield. Our goals include optimising battery usage, integrating NFC device management, improving alarm functionality and enhancing security features.

---

# III. Requirements

The improvements made to the project must allow:
  - A battery life of at least 7 days with a daily use of 2 hours.
  - Efficient distribution of battery energy.
  - Good use of the NFC chip.
  - The bluethooth should only decteced the paired phone.
  - The alarm can only be switched off by the user.
  - Sending of http request with geographical coordinates when a theft is detected.
  - Better management of security problems.
  - Must be written in C++ language, and on the Arduino IDE. There is no need to use libraries other than those provided for the hardware to succeed in the project.

We must also be careful not to damage the equipment provided for the project for its proper functioning on the day of the final presentation.

---

# IV. Priorities
1. **Battery Life**
   - The device must maintain functionality for at least **7 days** with **2 hours** of daily use without requiring a recharge.
   - Implements optimized battery management to extend battery life and distribute energy efficiently.

2. **NFC Chip Utilization**
   - Integrates an NFC chip allowing users to easily manage their equipment via a compatible mobile device.

3. **Alarm Desactivation**
   - Ensures the alarm can only be desactivated by the authenticated user, thereby preventing unauthorized deactivation.

4. **Theft Notification**
   - When theft is detected, the device sends an HTTP request with the geographical coordinates to a pre-configured server to alert the user.

5. **Enhanced Security**
   - Enhances security measures to prevent hacking or bypassing the alarm system.

---

# V. Nice to have

- **Battery Conservation Alerts**: Implement a feature within the mobile app that alerts users when the battery level approaches 20%, encouraging them to recharge the device promptly.
- **Remote Device Locator**: Integrate a function allowing users to trigger an audible alarm or light signal via the app to locate the device when it's within range but not visible.

---

# VI. Technical Architecture

---

## 1. Technoloy Used 

The *SportShield* device integrates various electronic components to detect movement, communicate with the mobile app, and physically lock the equipment. 

**The main hardware components include :**
| Component | Photo | Model | Dimensions | Key Features | Functions |
|---|---|---|---|---|---|
| Microcontroller | <img src="imgs/BLE.png">| Xiao BLE Sense nrf52840 | 2 x 2 x 0.5 cm | BLE 5.0, 6 DoF IMU, 11 GPIO (UART, SPI, I2C) |The heart of the device, providing Bluetooth Low Energy (BLE) connectivity for communication with the mobile application, as well as a microcontroller for processing sensor data.|
| GNSS Module | <img src="imgs/GNSS.png"> | GNSS PA1010D | 2.5 x 2.5 x 0.1 cm | Integrated antenna, UART & I2C |GPS module for precise equipment location.|
| GSM/2G Module | <img src="imgs/GSM.png"> | SIM800L | 2.2 x 1.8 x 0.5 cm | GPRS & HTTP UART, SIM Card holder, With 1NCE SIM card  |Provides GPRS connectivity to send notifications and location updates to the server.|
| Electromagnet | <img src="imgs/Electromagnet.png"> | | 2.7 x 1.6 x 1.3 cm | 12V, 500mA |For physical locking.|
| Piezoelectric Buzzer  | <img src="imgs/Buzzer.png"> |  |  | 12V, oscillator control circuit, ~ 90-100 dB |Generates audible alarm signals.|
| Lithium-Polymer Battery | <img src="imgs/Battery.png"> | | 5.1 x 3.5 x 0.6 cm | 3.7V, 1100mAh, 4.1Wh |Provides power supply.|
| NFC Antenna | <img src="imgs/NFC.png"> | | 5.5 x 4.5 x 0.017 cm | 13.56MHz frequency | Allows device management with NFC.|

Electronic structure:
<br> <img src="imgs/Electronic.png">

Also the software used:
- The embedded software on *SportShield* is developed in C/C++ languages and uses several libraries to manage sensors, BLE communication, GPS, and GPRS connections.

Libraries used:

- `NRF52_MBED_TimerInterrupt V1.4.1`
→ Libraries used to manage on-board sensors and the interrupts required for motion detection.

- `ArduinoBLE V1.3.6`
→ Allows you to manage Bluetooth Low Energy connectivity to communicate with the mobile application.

- `Adafruit GPS Library V1.7.4`
→ Makes it easy to integrate and use the PA1010D GNSS module to locate equipment accurately.

- `Sim800L http connector V1.14.0`
→ Used to establish GPRS connections and send data to the backend server via HTTP.

- `Seeed Arduino LSM6DS3 V2.0.3`
→ Libraries used to manage on-board sensors and the interrupts required for motion detection.

- `OneWire V2.3.7`

---


## 2. Key functions, operations, and algorithms


### 2.1. Battery management

##### Smart energy distribution system

The purpose of intelligent battery distribution is to optimise the use of energy according to the priority needs of the SportShield device, ensuring that essential functions remain operational for as long as possible. This strategy is crucial to keeping the device active and functional, even in low battery conditions.

##### Adaptive charging

Adaptive charging aims to extend the life and optimise the capacity of the battery by adjusting the charging process according to the current state of the battery, its temperature and the number of charge cycles already completed. This method preserves the battery's health over the long term, avoiding damage caused by inappropriate charging.


##### Low power mode

The purpose of low power mode is to minimise the device's energy consumption when it is inactive or when the battery reaches a critical level, thereby extending the period of use between charges. This function is essential to ensure the durability of the device in situations where recharging is not immediately possible.

---


### 2.2. NFC chip

One of the key benefits of the NFC chip is that it greatly simplifies the user's interaction with the SportShield device. For example, instead of navigating a mobile application to activate or deactivate the anti-theft alarm, users can simply tap their smartphone against the device. This 'tap-and-go' method of interaction makes using SportShield quicker and more intuitive.

---


### 2.3. Alarm management

The refinement of alarm management within the SportShield project plays a pivotal role in boosting both the security measures and the overall efficacy of the anti-theft device. To achieve this enhancement, the following strategies have been outlined:

**User customisation**

Allow users to customise alarm settings, such as volume, tone, and detection sensitivity, to suit different usage scenarios and personal preferences.


**Reduce false positives**

Minimise accidental alarm triggers by better analysing sensor data and learning normal usage patterns.

**Direct Feedback and Intelligent Deactivation**

Enable rapid and secure deactivation of the alarm via NFC or Bluetooth when the user is nearby, using strong authentication to prevent unauthorised deactivation.
Introduce a temporary "snooze" function for the alarm, which can be activated via the mobile application, for situations where the user is present but wishes to avoid the alarm going off unexpectedly.


---

### 2.4. Bluetooth low energy (BLE)

Bluetooth Low Energy is integrated into SportShield to enable low-energy wireless communication with the user's mobile application. This technology facilitates alarm activation/deactivation, configuration of device settings and initial pairing, providing an intuitive and efficient user experience.

We selected the Xiao BLE Sense nrf52840 module for its broad smartphone compatibility, optimal range and low power consumption. These features ensure that SportShield maintains reliable communication while optimising battery life.

In addition, the BLE module is configured to use power saving mode when the device is inactive, and communications are limited to necessary interactions, minimising power consumption without compromising performance.

To implement it, we use the official BLE libraries to ensure optimal compatibility and performance.

---

### 2.5. GPRS

The GSM/2G SIM800L module is selected for transmitting messages across the 2G network in HTML format. To conserve battery life, this module will enter power-down mode when it's not actively being used. Due to hardware limitations preventing us from testing this module's functionality, we will continue to employ the pre-existing codebase for 2G communications.

---

## 3. Algorithms

### 3.1. Battery management algorithm

#### Smart energy distribution implementation

The implementation starts by assessing the current battery level. If the level is above 80%, all the device's functions are activated, allowing optimal use. Between 50% and 80%, non-essential functions are deactivated and adjusted to save energy. Below 50%, the device switches to power-saving mode, reducing consumption to a minimum by disabling power-hungry features and reducing the frequency of operations. This approach ensures efficient management of the energy available, prolonging the device's autonomy.

<img src="imgs/SEM.png">

#### Adaptive charging implementation 

The device adjusts the charging current according to different criteria. If the battery is too hot or has undergone a large number of charge cycles, the charge current is reduced to prevent any damage. The charging current is also managed according to the current level of the battery: a high current for very low levels (<20%), a normal current for intermediate levels (20-80%), and a reduced current for the last charge phases (>80%), to maximise charging efficiency while preserving the battery.

<img src="imgs/ACI.png">

#### Low power mode implementation

Low power mode is activated automatically under certain conditions. It reduces power consumption by disabling power-hungry functions such as GPS and GPRS, reducing the refresh rate of the sensors (IMU = Inertial Measurement Unit), and putting the device into deep sleep. Continuous monitoring detects any activity or improvement in battery levels to reactivate the necessary functions and exit low power mode, ensuring that the device remains responsive to user needs while conserving energy.

---


### 3.2 Alarm management

**For Direct Feedback and Intelligent Deactivation**

The system will allow the user to deactivate the alarm quickly by simply bringing their phone close to the SportShield device, using secure NFC or Bluetooth communication. A 'snooze' option will also be available in the mobile app, allowing the user to temporarily pause the alarm if required.

---

# VII. Syntax and Structure
## 1. Folder structure

Our file organisation for Project SportShield (2023-2024) is designed to ensure a clear and easy-to-navigate structure, facilitating collaboration within our team.


```txt
📦2023-2024-project-4-sportshield-team-1
└── 📁 .github
|    └── 📁 ISSUE_TEMPLATE
|    |    └── 📄 bug_report.yml
└── 📁 Documents
|    └── 📁 FunctionalSpecification
|    |    └── 📝 FunctionalSpecifications.md
|    |    └── 📁 imgs
|    └── 📁 TechnicalSpecification
|    |    └── 📝 TechnicalSpecification.md
|    |    └── 📁 imgs
|    |    └── 📁 Appendix
|    └── 📁QA
|    |    └── 📝 TestPlan.md
|    |    └── 📝 TestCases.md
|    |    └── 📁 imgs
|    └── 📁 UserManual
|    |    └── 📝 UserManual.md
|    |    └── 📁 imgs
|    └── 📁 Management 
└── 📁 Src
|    └── 📄 Struct.h
|    └── 📄 SS_05-03_anglais-batterycontrol.ino
|    └── 📄 BatteryManagenement.ino 
|    └── 📄 NFC.ino 
|    └── 📄 AlarmManagement.ino 
|    └── 📄 IMU.ino 
└── 📝 README.MD 
```

`.github`/`ISSUE_TEMPLATE`: This folder contains templates for bug reports, enabling the team to submit problems encountered during development in a uniform manner.

`Documents`: It is a centralised directory for all project-related documentation. It includes :

<br>

- `FunctionalSpecification`: 
Contains the `FunctionalSpecifications.md` document, which details the project's functional specifications, as well as an `imgs` subfolder for referenced images. 

<br>

- `TechnicalSpecification`: 
Includes `TechnicalSpecification.md`, which describes the technical specifications, along with an images subfolder (`imgs`) and an `Appendix` subfolder for additional information.

<br>

- `QA`: 
Quality assurance folder, including test plans and test cases (`TestPlan.md` and `TestCases.md`), as well as an `imgs` subfolder for screenshots relating to the tests.

<br>

- `UserManual`: 
Contains the user manual (`UserManual.md`) and an `imgs` subfolder for illustrations.

<br>

- `Management` : 
Includes project management folder, including tools, schedules and team coordination documents.

<br>

`Src`: Contains the core of the project's source code, organised in separate files for each major module.

---

## 2. Program file structure

For the naming convention, we have chosen to name our files in PascalCase.

`Struct.h`
→ This header file defines the data structures and enumerations used throughout the project. It serves as a common foundation to ensure the consistency of the data types manipulated by different modules of the source code.

`SS_05-03_anglais-batterycontrol.ino`
→ The original source code provided by the SportShield company, specifically focused on battery control. This file includes the initial logic for power management and serves as a starting point for improvements and the integration of new battery-related features.


`BatteryManagement.ino` 
→ Developed from the original source code, this file focuses on improving battery management through features such as adaptive charging and activation of energy-saving modes.

`NFC.ino` 
→ This module manages all interactions linked to Near Field Communication (NFC), including initial pairing with the mobile application, device configuration via NFC, and secure user authentication.

`AlarmManagement.ino` 
→ Contains the logic for SportShield's advanced alarm management, offering features such as sensitivity adjustment, customization of alarm tones, and measures to minimize accidental triggering.


`IMU.ino` 
→ This file is responsible for integrating and processing data from the Inertial Measurement Unit (IMU), enabling the detection of movement or attempted theft of equipment protected by SportShield.

---

## 3. Function declaration

To make our code more readable, we need to add for each function, a block comment prologue that gives a short description of what the function does.

---

## 4. Naming

In order to ensure optimum consistency and readability of the code within the SportShield project, we will adopt the following naming conventions. These conventions will help maintain a clear code structure and make it easier for all team members to understand and maintain the code.

- **PascalCase** for **class** and **enumeration names**: Each word begins with a capital letter, with no spaces. Example: `BatteryManager`, `AlarmStatus`.
- **camelCase** for **variable** and **function names**: The first letter is lowercase, and each subsequent word begins with a capital letter. Example: `isAlarmActive`, `setBatteryLevel`.
**UPPER_CASE** for **constant**: All letters in upper case with underscores to separate words. Example: `MAX_BATTERY_LIFE`, `STATUS_OFF`.



---

## 5. Comments

Here's how we're going to add the comments to keep our code readable:

```
//
// Here is a block comment.
// The comment text should be tabbed or spaced over uniformly.
// 
```

---

# VIII. Code Design Principles

In order to guarantee the creation of a robust, maintainable and scalable software product, we are committed to following these code design principles:

- **Modularity**: Structure the codebase into distinct modules with clear responsibilities, facilitating maintenance and future updates.

- **Readability**: Write code that is easy to read and understand, using meaningful variable and function names and adhering to a consistent coding style.

- **Scalability**: Design the system to be easily scalable, allowing the addition of new features or components without significant restructuring.

- **Efficiency**: Optimize code for performance and resource efficiency, especially important for battery life and processing power in embedded systems.

- **Robustness**: Implement error handling and validation checks to make the system resilient to invalid inputs or unexpected states.

---

# IX. Challenges

The development of SportShield presents us with a series of technical and organisational challenges.
Identifying and anticipating these obstacles early in the development process enables us to draw up targeted action plans, minimising their impact on the project and increasing our chances of success. 
This project presents us with the following challenges:

- **Hardware Integration**: Seamlessly integrating various hardware components (NFC, BLE, GPRS, etc.) and ensuring they work reliably together.

- **Battery Life Optimization**: Balancing functionality with power consumption to meet the goal of a 7-day battery life under normal usage conditions.

- **Security Measures**: Implementing robust security protocols to protect against unauthorized access and ensure user data privacy.

---

# X. Possible Bugs

In any software project, the presence of bugs is inevitable, especially in the early stages of development.  
Here are some of the bugs we can expect to encounter:

- **Bluetooth Connectivity Issues**: There exists a possibility for occasional BLE connection disruptions, which could impact the stable communication between the device and the app.

- **Battery Drain Anomalies**: Unforeseen software or hardware issues leading to faster-than-expected battery depletion.

- **False Alarm Triggers**: Inaccurate sensor readings causing unnecessary alarm activations.

- **GPRS Communication Failure**: Occasional failures in data transmission over GPRS, especially in areas with weak signal strength.

---

# XI. Development Process

To effectively implement the improvements envisaged in the SportShield project, our development approach will be based on proven strategies tailored to the specific features of our project. 
These strategies are designed to optimise our work process, guarantee the quality and reliability of our product, and best meet the expectations of our users. We will use the following strategies:

- **Agile Methodology**: Adopt an agile development approach with sprints focusing on incremental delivery of features, allowing for regular feedback and adjustments.
- **Code Reviews**: Implement a peer review process for all code changes to maintain quality and consistency across the codebase.
- **Testing**: Conduct testing sessions at various stages of development to gather feedback on usability, functionality, and overall experience.


---

# XII. Glossary

| **Concept**           | **Definition**                                                                                                                                                                                                                                                                                                                                      | **Links**                                |
|-----------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------|                                     
| **NFC Chip**          | Near-field communication, often referred to by its English acronym NFC, is a short-range, high-frequency wireless communication technology, allowing the exchange of information between devices up to a distance approximately 10 cm in the general case.                                                                                                                                                 | [NFC Chip](https://en.wikipedia.org/wiki/Near-field_communication)     |
| **Arduino**| Arduino is the brand of an open-source prototyping platform that allows users to create interactive electronic objects from hardware-free electronic boards on which a microcontroller is located. The diagrams of these electronic cards are published under a free license.                                                            | [Arduino](https://en.wikipedia.org/wiki/Arduino) |
| **IDE**               | Integrated Development Environment - Software combining tools for software development, including a text editor, compiler/interpreter, debugger, and other features. Enhances programmer efficiency and simplifies development tasks.                                                                                                          | [IDE](https://en.wikipedia.org/wiki/Integrated_development_environment)             |
| **C++ Language**        | C++ is a compiled programming language allowing programming under multiple paradigms, including procedural programming, object-oriented programming, and generic programming.                                                            |                       [C++ language](https://en.wikipedia.org/wiki/C%2B%2B) |

---

# XIII. Conclusion

In conclusion, this technical specification document exhaustively details the key components, development strategies and conventions that will guide the SportShield project to its successful conclusion. By strictly adhering to the requirements, priorities and architectures described, as well as the code design principles and naming conventions, we are laying the foundations for structured and consistent development. Identified challenges and potential bugs will be proactively addressed through an agile and collaborative approach, ensuring smooth progress and optimal responsiveness to the unexpected. 

This document serves not only as a guide for developers, project managers and testers, but also as a reference for all stakeholders, ensuring a shared vision and objectives throughout the SportShield project lifecycle.

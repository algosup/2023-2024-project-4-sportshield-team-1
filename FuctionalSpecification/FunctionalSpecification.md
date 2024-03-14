|              |              |
| ------------ | :----------: |
| Author       | Mathis LEBEL |
| Reviewers    | Lucas MEGNAN |
| Created on   |  2024-03-14  |
| Last updated |  2024-03-18  |

# Virtual processor - Functional specifications

This project was requested by [CORIS INNOVATION](https://www.corisinnovation.com), a French engineering consultancy.

*SportShield* is an advanced anti-theft solution tailored for sports equipment. Equipped with sensors and actuators, it detects movement, triggers alarms and notifies owners of potential theft attempts.

In this project we're focusing on refining the functionality and code base of *SportShield*. Our goals include optimising battery usage, integrating NFC device management, improving alarm functionality and enhancing security features.

<details>
<summary>Table of Contents</summary>

- [Stakeholders](#stakeholders)
  - [Project members](#project-members)
  - [Other stakeholders](#other-stakeholders)
- [Project scope](#project-scope)
- [Functional requirements](#functional-requirements)
- [Deliverables and milestones](#deliverables-and-milestones)
    - [Final product](#final-product)
- [Personas and use cases](#personas-and-use-cases)
  - [Persona 1 - Fabien](#persona-1---fabien)
  - [Persona 2 - Amina](#persona-2---amina)
  - [Persona 3 - Thomas](#persona-3---thomas)
- [Acceptance criteria](#acceptance-criteria)
- [Solution overview](#solution-overview)
  - [Battery Management](#battery-management)
      - [Key Features](#key-features)
      - [Technology Stack](#technology-stack)
      - [Strategy](#strategy)
  - [NFC Chip](#nfc-chip)
      - [Key Features 2](#key-features-2)
      - [Technical Implementation](#technical-implementation)
      - [Advantages](#advantages)
  - [Alarm Management](#alarm-management)
      - [Key Features 3](#key-features-3)
      - [Technical Implementation 2](#technical-implementation-2)
      - [Advantages 2](#advantages-2)
- [ Hardware Components](#hardware-components)
- [Non-functional requirements](#non-functional-requirements)
  - [Performance](#performance)
  - [Maintainability](#maintainability)
  - [Scalability](#scalability)
  - [Portability](#portability)
  - [Usability](#usability)
  - [Security](#security)
- [Risks and assumptions](#risks-and-assumptions)
- [Future improvements](#future-improvements)
- [Glossary](#glossary)
</summary></details>

## Stakeholders

### Project members

| Role               | Photo                                                                                   | Name             | Email                                             | LinkedIn                                                                                         | GitHub                                                                                       |
|--------------------|-----------------------------------------------------------------------------------------|------------------|---------------------------------------------------|---------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------|
| Project Manager    | <img src="https://avatars.githubusercontent.com/u/146005121?v=4" width="30">             | Loris DE MATTIA  | [<img src="imgs/mail.png" width="24px"/>](mailto:loris.demattia@algosup.com) | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/loris-demattia-a27125293/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/Loriisss) |
| Program Manager    | <img src="https://avatars.githubusercontent.com/u/145991354?v=4" width="30">             | Mathis LEBEL     | [<img src="imgs/mail.png" width="24px"/>](mailto:mathis.lebel@algosup.com)  | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/mathis-lebel-429114293/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/mathislebel) |
| Technical Lead     | <img src="https://avatars.githubusercontent.com/u/145995847?v=4" width="30">             | Séréna BAVAROIS  | [<img src="imgs/mail.png" width="24px"/>](mailto:serena.bavarois@algosup.com) | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/s%C3%A9r%C3%A9na-bavarois-619975218/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/NanaChocolat) |
| Technical Writer   | <img src="https://avatars.githubusercontent.com/u/145991254?v=4" width="30">         | Camille GAYAT    | [<img src="imgs/mail.png" width="24px"/>](mailto:camille.gayat@algosup.com)   | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/camille-g-a89114293/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/CamilleGayat)     |
| Software Developer |   <img src="https://avatars.githubusercontent.com/u/100137905?v=4" width="30">            | Rémy CHARLES     | [<img src="imgs/mail.png" width="24px"/>](mailto:remy.charles@algosup.com)    | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/r%C3%A9my-charles-2a8960232/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/RemyCHARLES) |
| Quality Assurance  | <img src="https://avatars.githubusercontent.com/u/145991204?v=4" width="30">             | Lucas MEGNAN     | [<img src="imgs/mail.png" width="24px"/>](mailto:lucas.megnan@algosup.com)    | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/lucas-megnan/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/LucasMegnan) |



### Other stakeholders

| Name | Occupation | Links |
| -------------- | --------------------------- | ------------------------------ |
| CORIS INNOVATION |   Client  | [<img src="imgs/logo.png" width="24px"/>](https://www.corisinnovation.com) |

## Project scope
This project has multiple objectives:

- Improvement of an anti-theft device for sports equipment. 
- Improvement of the battery duration.
- Implementation of an NFC chip.
- Ensure that the user can deactivate the alarm.
- Manage the alarm sound when a theft occurs and send http requests. 
- Improve security issues. 

## Functional requirements

The improvements made to the project must allow :
  - A battery life of at least 7 days with a daily use of 2 hours.
  - More efficient battery management.
  - Efficient distribution of battery energy.
  - Good use of the NFC chip.
  - The alarm can only be switched off by the user.
  - Sending of http request with geographical coordinates when a theft is detected.
  - better management of security problems.


All project objectives must be written in C++ language, and on the arduino IDE. There is no need to use libraries other than those provided for the hardware to succeed in the project.

We must also be careful not to damage the equipment provided for the project for its proper functioning on the day of the final presentation.

## Deliverables and milestones

| Date and time       | Deliverable              |
| ------------------- | ------------------------ |
| 18 March 2024, 5 PM | Functional Specification |
| 26 March 2024, 5 PM | Technical Specification  |
| 10 April 2024, 5 PM | Test Plan                |
| 10 April 2024, 5 PM | User Manual              |
| 10 April 2024, 5 PM | Final product            |


#### Final product

The Final product consists of:
- Improvement of the battery duration.
- A good implementation of the NFC chip.
- Better alarm management.

## Personas and use cases

### Persona 1 - Fabien

<img src="imgs/Fabien.png" width=""/>


### Persona 2 - Amina

<img src="imgs/Amina.png" width=""/>

### Persona 3 - Thomas

<img src="imgs/Thomas.png" width=""/>

## Acceptance Criteria

To ensure the *SportShield* project meets its objectives, the following acceptance criteria have been established:

1. **Battery Life**
   - The device must maintain functionality for at least **7 days** with **2 hours** of daily use without requiring a recharge.

2. **Efficient Battery Management**
   - Implements optimized battery management to extend battery life and distribute energy efficiently.

3. **NFC Chip Utilization**
   - Integrates an NFC chip allowing users to easily manage their equipment via a compatible mobile device.

4. **Alarm Desactivation**
   - Ensures the alarm can only be desactivated by the authenticated user, thereby preventing unauthorized deactivation.

5. **Theft Notification**
   - When theft is detected, the device sends an HTTP request with the geographical coordinates to a pre-configured server to alert the user.

6. **Enhanced Security**
   - Enhances security measures to prevent hacking or bypassing the alarm system.

7. **Documentation and Usage**
   - Provides clear and concise documentation, including a detailed user manual. The source code should be in C++ and compatible with the Arduino IDE, requiring only the libraries provided for the hardware.

8. **Equipment Integrity**
   - Maintains the integrity of the provided equipment throughout the development process to ensure its proper function during the final presentation.

These criterias are designed to ensure that the *SportShield* project meets expectations for functionality, energy efficiency, security, and usability, while adhering to the specified deadlines and technical requirements.

## Solution overview

### battery-management

The battery management system (BMS) for the *SportShield* project is designed with the goal of maximizing the efficiency and lifespan of the battery. This section outlines the key features and technologies employed in our battery management solution.

#### Key Features:

- **Smart Energy Distribution**: Utilizes algorithms to optimize the distribution of power based on device usage patterns, ensuring the most critical functions have priority access to power.

- **Adaptive Charging**: Implements an adaptive charging protocol that adjusts the charging rate based on the battery's condition and history to promote battery health and longevity.

- **Low Power Modes**: Integrates low power modes for the device, automatically transitioning to a power-saving state during periods of inactivity.

- **Real-time Battery Monitoring**: Employs real-time monitoring of battery status, including charge level, health, and temperature, to prevent overcharging, deep discharge, and overheating.

- **NFC Integration**: Leverages the NFC chip not only for device management but also for enabling a quick and efficient setup process for power management settings personalized to the user's preferences.

#### Technology Stack:

- **Programming Language**: The BMS is developed using C++, ensuring compatibility with the Arduino IDE and efficient execution on microcontroller-based systems.

- **Hardware**: Utilizes specific sensors and modules compatible with our microcontroller to monitor and manage the battery's status accurately.

#### Strategy:

1. **Analysis of Usage Patterns**: By analyzing usage patterns, the BMS can predict periods of high and low usage, adjusting power distribution accordingly.

2. **Feedback Loop**: Incorporates a feedback loop from the monitoring system to continuously refine charging and power distribution strategies based on actual device usage and battery performance.

3. **User Customization**: Allows users to customize settings via an NFC-enabled smartphone app, providing control over power-saving features and notifications related to battery health.

By implementing these strategies and features, the *SportShield* project aims to deliver a robust and efficient battery management system that enhances the overall user experience while ensuring the device's reliability and durability.

### NFC Chip

The Near Field Communication (NFC) chip plays a pivotal role in enhancing user interaction with the *SportShield* system. It enables simplified and secure management of the device, facilitating operations such as initial setup, alarm activation/deactivation, and device status checks. This section outlines the integration and key features of the NFC chip in our solution.

#### Key Features 2:

- **Easy Pairing**: Allows users to easily connect their smartphone to *SportShield* by simply bringing the device close. This greatly simplifies the initial pairing and setup process.

- **Secure Management**: Provides an additional layer of security for user authentication before any setting changes or alarm deactivation, ensuring that only authorized users can control the device.

- **Real-time Information Exchange**: Facilitates rapid transmission of information between *SportShield* and the user's smartphone, such as security alerts, battery level, and current device status.

- **Configuration Updates**: Enables users to easily update the settings of their *SportShield* device, like alarm sensitivity or notification preferences, via their smartphone.

#### Technical Implementation:

- **Hardware Integration**: The NFC chip is integrated in a way that minimizes impact on the device's energy consumption while providing an effective communication range.

- **Software Development**: The accompanying mobile application for *SportShield* is designed to fully leverage the capabilities of the NFC chip, offering an intuitive user interface for device management.

#### Advantages:

1. **User Friendliness**: Significantly simplifies user interaction with the device, making the management of *SportShield* more accessible and less time-consuming.

2. **Enhanced Security**: Strengthens device security by only allowing authenticated modifications via NFC, thus reducing the risk of unauthorized tampering.

3. **Flexibility**: Offers users the ability to quickly customize their *SportShield* experience according to their needs, thereby improving satisfaction and the effectiveness of protection.

By integrating NFC technology into the *SportShield* system, we provide a solution that not only enhances the security of sports equipment but also improves the overall user experience through simplified management and more natural user interactions.

### Alarm Management

The Alarm Management component of the *SportShield* system is a critical feature designed to deter theft and notify the user of potential security breaches. It incorporates advanced technologies and strategies to ensure the alarm is both effective. This section outlines the functionalities, technical implementation, and benefits of the Alarm Management system.

#### Key Features 3:

- **Sensitivity Adjustment**: Users can adjust the sensitivity of the alarm, allowing for customization based on the environment in which the sports equipment is stored or used.

- **Immediate Notification**: Upon detecting unauthorized movement or tampering, the system sends an immediate alert to the user's smartphone through a secure connection, ensuring prompt awareness of potential theft.

- **Geolocation Integration**: In the event of a theft, the system can send the equipment's last known location to the user, aiding in recovery efforts.

- **Multiple Alarm Modes**: Includes various alarm modes, such as audible alarms to deter thieves on-site and silent alarms for covert notification of the owner without alerting the thief.

#### Technical Implementation 2:

- **Sensor Integration**: Utilizes motion sensors and accelerometers to detect unauthorized movement or tampering. The system is calibrated to minimize false alarms while ensuring genuine threats are promptly detected.

- **Smartphone App Integration**: The Alarm Management system is fully integrated with the *SportShield* smartphone app, allowing users to manage alarm settings, receive notifications, and view equipment location directly from their phone.

- **Energy-Efficient Design**: Despite its sophisticated functionality, the alarm system is designed to be energy-efficient, minimizing battery consumption and ensuring the device remains operational for extended periods.

#### Advantages 2

1. **Enhanced Security**: Provides a robust deterrent against theft, significantly reducing the risk of sports equipment being stolen.

2. **User Customization**: Allows users to tailor the alarm system to their specific needs, ensuring maximum protection without unnecessary inconvenience.

3. **Peace of Mind**: Offers sports equipment owners peace of mind, knowing their valuables are protected by a sophisticated and responsive alarm system.

By integrating these advanced Alarm Management features into the *SportShield* system, we provide an effective, customizable, and user-friendly solution for protecting valuable sports equipment against theft. This comprehensive approach ensures that users can enjoy their sporting activities with confidence, knowing their equipment is secure.

## Hardware Components

| Component | Photo | Model | Dimensions | Key Features |
|---|---|---|---|---|
| Microcontroller | <img src="imgs/BLE.png">| Xiao BLE Sense nrf52840 | 2 x 2 x 0.5 cm | BLE 5.0, 6 DoF IMU, 11 GPIO (UART, SPI, I2C) |
| GNSS Module | <img src="imgs/GNSS.png"> | GNSS PA1010D | 2.5 x 2.5 x 0.1 cm | Integrated antenna, UART & I2C |
| GSM/2G Module | <img src="imgs/GSM.png"> | SIM800L | 2.2 x 1.8 x 0.5 cm | GPRS & HTTP UART, SIM Card holder, With 1NCE SIM card  |
| Electromagnet | <img src="imgs/Electromagnet.png"> | | 2.7 x 1.6 x 1.3 cm | 12V, 500mA |
| Piezoelectric Buzzer  | <img src="imgs/Buzzer.png"> |  |  | 12V, oscillator control circuit, ~ 90-100 dB |
| Lithium-Polymer Battery | <img src="imgs/Battery.png"> | | 5.1 x 3.5 x 0.6 cm | 3.7V, 1100mAh, 4.1Wh |
| NFC Antenna | <img src="imgs/NFC.png"> | | 5.5 x 4.5 x 0.017 cm | 13.56MHz frequency |
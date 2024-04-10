# <h1 align="center">Sportshield Project Test Plan</h1>
<p align="right">created: 3/14/2024<br>last modified: 4/10/2024</p> 

<details>
<summary>

### Table of contents <i>(Click to expand)</i>
</summary>

- [Sportshield Project Test Plan](#sportshield-project-test-plan)
    - [Table of contents (Click to expand)](#table-of-contents-click-to-expand)
  - [I. Overview](#i-overview)
  - [II. Glossary](#ii-glossary)
  - [III. Test Strategy](#iii-test-strategy)
    - [A. Testing Scope](#a-testing-scope)
    - [B. Out of Scope](#b-out-of-scope)
  - [IV. Ressources and Environment](#iv-ressources-and-environment)
    - [A. Testing Environment](#a-testing-environment)
  - [V. Criteria](#v-criteria)
    - [A. Entry Criteria](#a-entry-criteria)
    - [B. Exit Criteria](#b-exit-criteria)
  - [VI. Schedules](#vi-schedules)
  - [VII. Risks and Assumptions](#vii-risks-and-assumptions)

</details>

## I. Overview

<i>SportShield</i> is an advanced anti-theft solution tailored for sports equipment. Equipped with sensors and actuators, it detects movement, triggers alarms and notifies owners of potential theft attempts.

In this project we're focusing on refining the functionality and code base of <i>SportShield</i>. Our goals include optimising battery usage, integrating NFC device management, improving alarm functionality and enhancing security features.

For more information I invate you to read the [functional specification](/FuctionalSpecification/FunctionalSpecification.md).

## II. Glossary

- Coris Innovation: Multi-sector expertise in systems and process engineering professions, Coris Innovation was created in 2015   
  under the leadership of 2 enthusiasts of innovation and new technologies, Thibault and Stéphane, with the aim of overturning the 
  anchors inherent in the world of service. Website (https://www.corisinnovation.com).

- SportShield: “SportShield is an innovative anti-theft device designed for sports equipment, 
  equipped with sensors and actuators to detect movement, activate an alarm, and 
  notify the owner”.

- GitHub: GitHub is an online software development platform. It's used for storing, tracking, and collaborating on software projects.
  It makes it easy for developers to share code files and collaborate with fellow developers on open-source projects.

- Visual Studio Code: Visual Studio Code is an extensible code editor developed by Microsoft for Windows, Linux and macOS. 
  Features include debugging support, syntax highlighting, smart code completion, snippets, code refactoring, and integrated Git.

- C++: C++ is a compiled programming language allowing programming under multiple paradigms, including procedural programming,    object-oriented programming, and generic programming.

- Arduino: Arduino is the brand of an open-source prototyping platform that allows users to create interactive electronic objects from hardware-free electronic boards on which a microcontroller is located.
  The diagrams of these electronic cards are published under a free license. Website (https://www.arduino.cc).

- Software: All means of use, programs, procedures, documentation of a computer system.

- Hardware: the physical part of the computer, that is, the parts and equipment that make it work.

- NFC: technology that allows data to be transmitted between two devices located in immediate proximity, quickly and without prior manipulation of equipment.

- GNSS: (global navigation satellite systems) provide the position of an element everywhere and in real time. 
  These are the most accurate systems used by geolocation tools.

## III. Test Strategy

### A. Testing Scope

The objective is to focus the tests on the client's requests, ranked in ascending order of importance according to the defined criteria. Additionally, the documents must be approved by at least two people from the group before validation.

| <p align="center">Feature</p> | <p align="center">Full Name</p> | <p align="center">Description</p> |
|---|---|---|
| `BCM` | Battery Consumption Management | - Improve energy efficiency of the system.</br> - Management of a low battery situation.</br> - Increase the battery lifespan. |
| `DMNFC` | Device Management witch NFC | - NFC is an expected feature for the users, in order to activate/deactivate the anti-theft-system & unlock the cable.</br> - Via their smartphone and SportShield app. |
| `AMSA` | Alarm Management and Simultaneous Actions | - Add the possibility to stop the alarm when it rings, even if the ringing cycle is not finished.</br> - Permit the alarm to ring while sending http notification to the server.</br> - Better management of the interruptions. |
| `SI` | Security Issues | - Increase the security level to connect to the key features of the system.</br> - In order to give access to activation/deactivation of the alarm and unlocking of the cable. |

### B. Out of Scope

- Hardware related issues
- Advanced connectivity features (Introducing new connectivity like Wi-Fi or cellular connectivity, is out of scope for this phase of testing.)

## IV. Ressources and Environment

### A. Testing Environment

The client is asking for the anti-theft system to work in urban situations as well as in the mountains, where temperatures can be more extreme and possibly below -10°C. Unfortunately, we are not located in the mountains, so we won't be able to conduct tests with extreme temperatures. However, we can conduct tests in urban environments with moderate temperatures. Our tests will aim to be as close as possible to the usage requested by the client.

And the operating system we used is MacOS, language: C++, arduino IDE: Visual Studio, arduino Libraries are:

- NfcAdapter
- PN532
- SPI

All these librairies can be found here: https://github.com/Seeed-Studio/Seeed_Arduino_NFC

## V. Criteria

### A. Entry Criteria

### B. Exit Criteria

The exit criteria are predefined conditions that signal when testing activities can be concluded. They serve as benchmarks to assess whether the testing objectives have been met and whether the software system is ready for the next phase. By adhering to these criteria, we ensure that testing is terminated without compromising the quality or efficacy of the software.

- Shock detection: 99%
- Unlock: 99%
- Alarm: 98%
- Shock Notification: 95%
- GNSS position acquisition and transmission: 80%
- 7 days of operating duration (6 hours in activation mode + 18 hours in stand-by mode per day)

## VI. Schedules

| Date and time       | Deliverable              | Cheked by                     |
| ------------------- | ------------------------ | ----------------------------- |
| 18 March 2024, 5 PM | Functional Specification | Lucas Megnan, Séréna Bavarois |
| 26 March 2024, 5 PM | Technical Specification  | Lucas Megnan, Mathis Lebel    |
| 10 April 2024, 5 PM | Test Plan                | Lucas Megnan, Séréna Bavarois |
| 10 April 2024, 5 PM | User Manual              | Lucas Megnan, Séréna Bavarois |
| 10 April 2024, 5 PM | Final product            | All team members              |

## VII. Risks and Assumptions

| <p align="center"> Risk </p> | <p align="center"> Mitigation </p> |
|---|---|
| Provided code isn't working | Isolating code's component |
| Hardware failure | Get extra hardware or share with others teams |
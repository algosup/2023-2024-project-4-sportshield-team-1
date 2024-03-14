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
  - [Persona 1 - Oceane Thomas](#persona-1---oceane-thomas)
    - [Goals](#goals)
    - [Challenges](#challenges)
  - [Persona 2 - John Mayers](#persona-2---john-mayers)
    - [Goals](#goals-1)
    - [Challenges](#challenges-1)
  - [Persona 3 - Patricia Farmer](#persona-3---patricia-farmer)
    - [Goals](#goals-2)
    - [Challenges](#challenges-2)
- [Acceptance criteria](#acceptance-criteria)
- [Solution overview](#solution-overview)
  - [System architecture](#system-architecture)
  - [Assembly syntax](#assembly-syntax)
  - [Assembly instructions](#assembly-instructions)
  - [Machine code](#machine-code)
  - [Errors](#errors)
  - [Usage](#usage)
- [Non-functional requirements](#non-functional-requirements)
  - [Performance](#performance)
  - [Maintainability](#maintainability)
  - [Scalability](#scalability)
  - [Portability](#portability)
  - [Usability](#usability)
  - [Security](#security)
- [Example](#example)
- [Risks and assumptions](#risks-and-assumptions)
- [Future improvements](#future-improvements)
- [Glossary](#glossary)
</summary></details>

## Stakeholders

### Project members

| Role               | Photo                                                                                   | Name             | Email                                             | LinkedIn                                                                                         | GitHub                                                                                       |
|--------------------|-----------------------------------------------------------------------------------------|------------------|---------------------------------------------------|---------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------|
| Project Manager    | <img src="https://avatars.githubusercontent.com/u/146005121?v=4" width="30">             | Loris DE MATTIA  | [<img src="imgs/mail.png" width="24px"/>](loris.demattia@algosup.com) | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/wilfried-portet-a882b9293/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/PortetWilfried) |
| Program Manager    | <img src="https://avatars.githubusercontent.com/u/145991354?v=4" width="30">             | Mathis LEBEL     | [<img src="imgs/mail.png" width="24px"/>](mathis.lebel@algosup.com)  | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/r%C3%A9my-charles-2a8960232/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/RemyCHARLES) |
| Technical Lead     | <img src="https://avatars.githubusercontent.com/u/145995847?v=4" width="30">             | Séréna BAVAROIS  | [<img src="imgs/mail.png" width="24px"/>](serena.bavarois@algosup.com) | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/mathis-lebel-429114293/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/mathislebel) |
| Technical Writer   | <img src="https://avatars.githubusercontent.com/u/145991254?v=4" width="30">         | Camille GAYAT    | [<img src="imgs/mail.png" width="24px"/>](camille.gayat@algosup.com)   | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/lucas-megnan/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/LucasMegnan)     |
| Software Developer |   <img src="https://avatars.githubusercontent.com/u/100137905?v=4" width="30">            | Rémy CHARLES     | [<img src="imgs/mail.png" width="24px"/>](remy.charles@algosup.com)    | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/gregory-pagnoux-313b3a251/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/Gregory-Pagnoux) |
| Quality Assurance  | <img src="https://avatars.githubusercontent.com/u/145991204?v=4" width="30">             | Lucas MEGNAN     | [<img src="imgs/mail.png" width="24px"/>](lucas.megnan@algosup.com)    | [<img src="https://www.presse-citron.net/app/uploads/2020/06/linkedin-logo.jpg" width="20px">](https://www.linkedin.com/in/atifa-amiri-565a1225b/) | [<img src="https://cdn.pixabay.com/photo/2022/01/30/13/33/github-6980894_1280.png" width="20px">](https://github.com/Atifabaran) |




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

### Persona 1 - Oceane Thomas

Oceane Thomas is an 18-year-old student working to become a CPU Architect. She already knows x64 assembly and C.

#### Goals
  - Oceane wants to learn a new assembly language to gain insight into the various steps and implementations of assembly.
  - She hopes to better understand CPU architecture choices by exploring how a virtual CPU works.

#### Challenges
  - Oceane is looking for an open-source project that allows her to examine its inner workings.
  - She seeks a virtual processor that enables her to observe processes in greater detail than on physical hardware.
  - She needs an easy-to-learn assembly language, as she does not want to spend too much time on the assembly itself.

### Persona 2 - John Mayers

John is a 34-year-old Computer Architect Researcher at IBM. He has been in this role for a few years and believes that drawing inspiration from external projects will enhance his creativity.

#### Goals
  - He aims to discover innovative ideas for CPU architecture.
  - He is looking for solutions that are practical for general use.

#### Challenges
  - He needs a fresh perspective on assembly, as he is specifically seeking new viewpoints.
  - The instructions must be realistically implementable in hardware.
  - He needs to test and prototype quickly without necessarily having the physical CPU on hand.

### Persona 3 - Patricia Farmer

Patricia Farmer is a 31-year-old CTO at a bank. She recently assumed the position and realized that the bank's internal communication system urgently needs an upgrade.

#### Goals
  - She aims to revamp the bank's internal communication system to make it faster.
  - She also intends to enhance its security.

#### Challenges
  - The language and system architecture must be different from the old one to render existing malware obsolete.
  - She cannot replace all the hardware at once. A virtual CPU is temporarily needed to run the new programs on the old hardware.

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

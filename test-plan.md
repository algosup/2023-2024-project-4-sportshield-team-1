# <h1 align="center">Sportshield Project Test Plan</h1>
<p align="right">created: 3/14/2024<br>last modified: 3/14/2024</p> 

<details>
<summary>

### Table of contents <i>(Click to expand)</i>
</summary>

- [Sportshield Project Test Plan](#sportshield-project-test-plan)
    - [Table of contents (Click to expand)](#table-of-contents-click-to-expand)
  - [1. Overview](#1-overview)
  - [2. Glossary](#2-glossary)
  - [3. Testing](#3-testing)
    - [3.1. Scope of Testing](#31-scope-of-testing)
      - [3.1.1. In-scope for Testing](#311-in-scope-for-testing)
      - [3.1.2. Out-scope for Testing](#312-out-scope-for-testing)
    - [3.2. Unit Tests](#32-unit-tests)
    - [3.3. Testing sessions](#33-testing-sessions)
      - [3.3.1. Overview](#331-overview)
      - [3.3.2. Smoke Test](#332-smoke-test)
        - [3.3.2.1. Smoke Testing Scope](#3321-smoke-testing-scope)
        - [3.3.2.2. Sequence of Smoke Testing](#3322-sequence-of-smoke-testing)
    - [3.4. External Tools](#34-external-tools)
      - [3.4.1. GitHub Actions](#341-github-actions)
        - [3.4.1.1. GitHub Actions Scope](#3411-github-actions-scope)
        - [3.4.1.2. Workflow](#3412-workflow)
        - [3.4.1.3. Configuration](#3413-configuration)
    - [3.4.2. GitHub Issues](#342-github-issues)
    - [3.4.3. Tests and Meetings](#343-tests-and-meetings)
  - [4. Test Criteria](#4-test-criteria)
    - [4.1. Exit Criteria](#41-exit-criteria)
    - [4.2. Suspension Criteria](#42-suspension-criteria)
  - [5. Allocated Ressources](#5-allocated-ressources)
    - [5.1. Time](#51-time)
    - [5.2. Collaborators](#52-collaborators)

</details>

## 1. Overview

<i>SportShield</i> is an advanced anti-theft solution tailored for sports equipment. Equipped with sensors and actuators, it detects movement, triggers alarms and notifies owners of potential theft attempts.

In this project we're focusing on refining the functionality and code base of <i>SportShield</i>. Our goals include optimising battery usage, integrating NFC device management, improving alarm functionality and enhancing security features.

For more information I invate you to read the [functional specification](/FuctionalSpecification/FunctionalSpecification.md).

## 2. Glossary

## 3. Testing

The primary objective is to ensure that the project in its entirety meets the full requirements defined in the functional specifications for each quality requirement. Any changes, additions, or deletions to the requirements document, Functional Specification, or Technical Specification will be documented and tested at the highest level of quality allowed within the remaining time of the project and within the ability of the test team.

### 3.1. Scope of Testing

The tests will focus on both battery optimization elements and alarm management to ensure a reliable product with a long duration of use.

#### 3.1.1. In-scope for Testing

| <p align="center">Feature</p> | <p align="center">Full Name</p> | <p align="center">Description</p> |
|---|---|---|
| `BCM` | Battery Consumption Management | - Improve energy efficiency of the system.</br> - Management of a low battery situation.</br> - Increase the battery lifespan. |
| `DMNFC` | Device Management witch NFC | - NFC is an expected feature for the users, in order to activate/deactivate the anti-theft-system & unlock the cable.</br> - Via their smartphone and SportShield app. |
| `AMSA` | Alarm Management and Simultaneous Actions | - Add the possibility to stop the alarm when it rings, even if the ringing cycle is not finished.</br> - Permit the alarm to ring while sending http notification to the server.</br> - Better management of the interruptions. |
| `SI` | Security Issues | - Increase the security level to connect to the key features of the system.</br> - In order to give access to activation/deactivation of the alarm and unlocking of the cable. |

#### 3.1.2. Out-scope for Testing

These features are not to be tested as they are not included in the requirement specifications

- Adjusting the sensitivity of the alarm shocks.
- Adjusting the sound of the alarm.
- Creating an application that simulates HTTP requests and various features of the anti-theft system.

### 3.2. Unit Tests

### 3.3. Testing sessions

#### 3.3.1. Overview

#### 3.3.2. Smoke Test

##### 3.3.2.1. Smoke Testing Scope

##### 3.3.2.2. Sequence of Smoke Testing

### 3.4. External Tools 

#### 3.4.1. GitHub Actions

##### 3.4.1.1. GitHub Actions Scope

##### 3.4.1.2. Workflow

##### 3.4.1.3. Configuration

### 3.4.2. GitHub Issues

### 3.4.3. Tests and Meetings

## 4. Test Criteria

### 4.1. Exit Criteria

### 4.2. Suspension Criteria 

## 5. Allocated Ressources

### 5.1. Time

### 5.2. Collaborators
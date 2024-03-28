# <h1 align="center">Sportshield Project Test Plan</h1>
<p align="right">created: 3/14/2024<br>last modified: 3/28/2024</p> 

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
    - [B. Testing Environment](#b-testing-environment)
  - [V. Code Test](#v-code-test)
  - [VI. Criteria](#vi-criteria)
    - [A. Testing Criteria Schedule](#a-testing-criteria-schedule)
  - [VII. Test Cases](#vii-test-cases)
  - [VIII. Conclusion](#viii-conclusion)
  - [IX. Documentation Approval](#ix-documentation-approval)

</details>

## I. Overview

<i>SportShield</i> is an advanced anti-theft solution tailored for sports equipment. Equipped with sensors and actuators, it detects movement, triggers alarms and notifies owners of potential theft attempts.

In this project we're focusing on refining the functionality and code base of <i>SportShield</i>. Our goals include optimising battery usage, integrating NFC device management, improving alarm functionality and enhancing security features.

For more information I invate you to read the [functional specification](/FuctionalSpecification/FunctionalSpecification.md).

## II. Glossary

## III. Test Strategy

### A. Testing Scope

The objective is to focus the tests on the client's requests, ranked in ascending order of importance according to the defined criteria. Additionally, the documents must be approved by at least two people from the group before validation.

| <p align="center">Feature</p> | <p align="center">Full Name</p> | <p align="center">Description</p> |
|---|---|---|
| `BCM` | Battery Consumption Management | - Improve energy efficiency of the system.</br> - Management of a low battery situation.</br> - Increase the battery lifespan. |
| `DMNFC` | Device Management witch NFC | - NFC is an expected feature for the users, in order to activate/deactivate the anti-theft-system & unlock the cable.</br> - Via their smartphone and SportShield app. |
| `AMSA` | Alarm Management and Simultaneous Actions | - Add the possibility to stop the alarm when it rings, even if the ringing cycle is not finished.</br> - Permit the alarm to ring while sending http notification to the server.</br> - Better management of the interruptions. |
| `SI` | Security Issues | - Increase the security level to connect to the key features of the system.</br> - In order to give access to activation/deactivation of the alarm and unlocking of the cable. |

### B. Testing Environment

## V. Code Test

## VI. Criteria

### A. Testing Criteria Schedule

## VII. Test Cases

## VIII. Conclusion

## IX. Documentation Approval

<!-- ### 3.2. Unit Tests

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

### 5.2. Collaborators -->
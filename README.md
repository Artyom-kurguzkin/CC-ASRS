# CC-ASRS

Cloud computing IOT project

Contributors: Mauro Turci, Alexandria Foss, Het Patel, Danil Sayus, Ajay Kishan, Artyom Kurguzkin

<br>

---

<br>

The project aims to model Automated Storage and Retrieval System in a pharmacy. The solution controls access and sorting of medications using web dashboard and a robot.

ESP32 acts as a Programmable Logic Controller directly interfacing with sensors and actuators.

Nodered acts as Programmable Automation Controller reposnible for application logic.

We also use Nodered's dashboard capability for building application's web interface.

<br>

---

<br>

## Table of Contents

**[Features & User stories](#features-&-User-stories)**

**[Current work items](#Current-work-items)**

<br>

## Features & User stories

* Loads and retrieves medications from storage. 
* Keeps secure history of load/retrieval
* Staff and Pharmacists can browse medication register
* Only Administrators and Pharmacists can do everything they want with medications. Staff members can only see allowed medications. Staff members cannot see retrieval-loading history.

<br>


## Current work items


Login screen with functional OAuth2 session
* Session should have different features available beased on user role
* Identity-Aware Proxy (IAP) works with Google Identity (can interact with other identity providers as well)

GKE persistent volume
 
Databse that keeps track of medications and their location



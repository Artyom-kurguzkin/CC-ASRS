# CC-ASRS

Cloud computing IOT project

Contributors: Mauro Turci, Alexandria Foss, Het Patel, Danil Sayus, Ajay Kishan, Artyom Kurguzkin

<br>

---

<br>

The project aims to model Automated Storage and Retrieval System in a pharmacy. The solution controls access and sorting of medications using web dashboard and a robot. The initial inspiration came from this video: https://www.youtube.com/watch?v=Br6ByVtJb9o 

[Architecture overview](https://github.com/Artyom-kurguzkin/CC-ASRS/wiki/Architecture-overview)

[How to build the project pieces](https://github.com/Artyom-kurguzkin/CC-ASRS/wiki)


* Robot folder contains the wiring diagram for the robot, source code, and Wokwi project file that can be imported to replicate the wiring layout. 

* nodered contains config files that can be imported in Nodered to replicate the flows used.

* login-redirect contains source code for Firebase cloud functions that are responsible for authenticating users and redirecting them to crrect GUIs.

* planning contains draw.io file with the most recent architectural diagram. 

<br>

---

<br>

## Features & User stories

* Loads and retrieves medications from storage. 
* Keeps secure history of load/retrieval
* Staff and Pharmacists can browse medication register
* Only Administrators and Pharmacists can do everything they want with medications. Staff members can only see allowed medications. Staff members cannot see retrieval-loading history.

<br>

# Demo

https://github.com/user-attachments/assets/be6b6cc2-4155-4d3b-9919-b56bcb925792




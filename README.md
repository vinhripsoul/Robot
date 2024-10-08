Demonstration video: https://www.youtube.com/watch?v=62W_drzbT_k.

This mechatronic system is equipped with arduino uno R3, ultrasonic sensor, servo motor and some wires.
The code in the processing software responsibles for rotating the servo motor from 0 to 180 degrees and simultaneously commanding the ultrasonic sensor to take the distances from the sensor to the object as the servo motor rotates, then creates a data file of the measurements taken.
These files are then loaded into the MATLAB Code that takes in the data, processes it and creates a virtual 3D image of the object that was scanned by the ultrasonic sensor.
The mechatronic system is designed to operate exclusively with the two basic shapes that were programmed (cube and rectangle). It cannot accommodate any other shapes. Additionally, the servo motor's characteristics restrict the functionality of the ultrasonic sensor to the frontal 180 degrees, which limits its ability to scan the surrounding. Moreover, the system relies on several assumptions, such as the distance between the sensor and the nearest point of the object, the object's shape, and the object's orientation.

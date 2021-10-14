# Automated-object-detection-and-sorting-robot
 ## Introduction :rocket: &#8594; ##
an object sorting Robot is made using small 3D printed parts and Servo motors which uses object detection algorithm to identify the object type and then sort accordingly
- Works for upto 80 different objects
- works on IoT
- Real time detection and sorting
![alt text](https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/c0e5f0d4ec5d133fbe3688b8ac6d9976/large.png) 
![alt text](https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/88b4a7b5143113807b57a064004cae8d/large.png)
![alt text](https://github.com/arpitpatawat/Automated-object-detection-and-sorting-robot/blob/main/Picture1.png)
![alt text](https://github.com/arpitpatawat/Automated-object-detection-and-sorting-robot/blob/main/Picture2.png)

## Components :robot: &#8594; ##
 ### Hardware &#8594; ###
 - 3D printed parts of 4 DOF Robotic Arm
 - 4 MG 90 Servo motors
 - NodeMCU
 - Breadboard
 - jumper wires
 - different shaped objects
 - LED's for indication
 ### Software &#8594; ###
 - python
 - weight and configuration file of yolo (please download weight file - [Weight file](https://pjreddie.com/media/files/yolov3.weights))
 - open cv library
 - Arduino ide
 - Thingspeak cloud
 
## Working :gear: &#8594; ##
1. upload the scatch in nodemcu also make changes for wifi ssid, password and thing speak write API's
2. run the python script, it will turn on webcam which will going to detect object
3. whenever our pre defined objects (toy elephent and zebra in my case) will detected it will send 1 or 2 to thing speak cloud
4. nodeMCU will fetch the data from cloud and move the robot using series of algorithm
5. it will move continueously untill we press enter button in our keyboard (null request)
 
## Simulation and video  &#8594; ##
 [Video link](https://drive.google.com/file/d/1TF6mAdieY1y7LwcNcP_3ViE0T7ZFZaRc/view?usp=sharing)

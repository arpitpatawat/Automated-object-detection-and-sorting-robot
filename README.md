# Automated-object-detection-and-sorting-robot
 ## Introduction :rocket: &#8594; ##
an object sorting Robot is made using small 3D printed parts and Servo motors which uses object detection algorithm to identify the object type and then sort accordingly
- Works for upto 80 different objects
- works on IoT
- Real time detection and sorting
- Manual and Automatic control
- Webpanel to control it from remote place
- report whole day activity by sending mail 
![alt text](https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/c0e5f0d4ec5d133fbe3688b8ac6d9976/large.png) 
![alt text](https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/88b4a7b5143113807b57a064004cae8d/large.png)
<span>
<img src="https://user-images.githubusercontent.com/75129076/171142355-81187dfd-a199-4ea8-ae32-457970cd61ed.jpeg" width = "500">
<img src="https://user-images.githubusercontent.com/75129076/171142361-e83f6bd8-2d03-4d26-92fe-243212fa1dca.jpeg" width = "500">
 </span>

![web-panel](https://user-images.githubusercontent.com/75129076/171139512-1f2c94c5-eceb-4f28-b53a-bc11d6079969.png)


## Components :robot: &#8594; ##
 ### Hardware &#8594; ###
 - 3D printed parts of 4 DOF Robotic Arm
 - 4 MG 90 Servo motors
 - NodeMCU
 - LCD
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
 - Web broser (to display web-panel)
## Working :gear: &#8594; ##
1. upload the scatch in nodemcu also make changes for wifi ssid, password and thing speak write API's.
2. ESP8266 will connect with the wifi and display the local IP address of webserver in the LCD.
3. open any web browser and enter IP address and allow access to camera (i have used separate webcam but you can allow access to laptop camera)
4. on the webpanel, you can move slider to control robotic arm, pick and drop object or sort left /right manually using buttons.
5. when you turn off manual control then automatic sorting will begin. 
6. run the python script, it will turn on webcam which will going to detect object
7. whenever our pre defined objects (toy elephent,zebra , sharpner or eraser in my case) will detected it will send different data thing speak cloud
8. nodeMCU will fetch the data from cloud and move the robot using series of algorithm and update the data in the webpanel
9. it will move continueously untill we press enter button in our keyboard (null request) considering it to be implemented in factories/ industries.
 
## Simulation and video  &#8594; ##
 [Video link](https://drive.google.com/file/d/1TF6mAdieY1y7LwcNcP_3ViE0T7ZFZaRc/view?usp=sharing)

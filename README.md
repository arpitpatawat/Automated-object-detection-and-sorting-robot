# Automated-object-detection-and-sorting-robot
 ## Introduction :rocket: &#8594; ##
an object sorting Robot is made using small 3D printed parts and Servo motors which uses object detection algorithm to identify the object type and then sort accordingly
- Works for upto 80 different objects
- Real time detection and sorting
- Manual and Automatic control
- Webpanel to control it from remote place
- report whole day activity by sending mail 
- controlling via BLYNK app
- complete video feed for App/Web work

 ## Project Images ##
![alt text](https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/c0e5f0d4ec5d133fbe3688b8ac6d9976/large.png) 
![alt text](https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/88b4a7b5143113807b57a064004cae8d/large.png)
<span>
<img src="https://github.com/arpitpatawat/Automated-object-detection-and-sorting-robot/blob/main/img.jpeg" width = "400">
<img src="https://github.com/arpitpatawat/Automated-object-detection-and-sorting-robot/blob/main/img1.jpeg" width = "400">
 </span>

![web-panel](https://user-images.githubusercontent.com/75129076/171139512-1f2c94c5-eceb-4f28-b53a-bc11d6079969.png)
<span><img src ="https://github.com/arpitpatawat/Automated-object-detection-and-sorting-robot/blob/main/image11.jpeg" height = "600" width = "400"/>
<img src ="https://github.com/arpitpatawat/Automated-object-detection-and-sorting-robot/blob/main/image6.png" height = "600" width = "400"></span>


## Components :robot: &#8594; ##
 ### Hardware &#8594; ###
 - 3D printed parts of 4 DOF Robotic Arm
 - 4 MG 90 Servo motors
 - NodeMCU
 - LCD module
 - Breadboard
 - jumper wires
 - different shaped objects
 - LED's for indication
 - External camera (webcam)
 ### Software &#8594; ###
 - python
 - weight and configuration file of yolo (please download weight file - [Weight file](https://pjreddie.com/media/files/yolov3.weights))
 - open cv library
 - Arduino ide
 - Thingspeak cloud
 - BLYNK app
 - Web browser (to display web-panel)
## installation & Working :gear: &#8594; ##
1. Upload the sketch(robo_sort_final) in nodemcu also make changes for wifi ssid, password and thing speak write API's and remaining user's variable data.
2. ESP8266 will connect with the wifi and display the local IP address of webserver in the LCD.
3. Open any web browser and enter IP address and allow access to camera (i have used separate webcam but you can allow access to laptop camera)
4. On the webpanel, you can move slider to control robotic arm, pick and drop object or sort left /right manually using buttons.
5. When you turn off manual control then automatic sorting will begin. 
6. Run the python script, it will turn on webcam which will going to detect object
7. Whenever our pre defined objects (toy elephent,zebra , sharpner or eraser in my case) will detected it will send different data thing speak cloud
8. NodeMCU will fetch the data from cloud and move the robot using series of algorithm and update the data in the webpanel
9. It will move continueously untill we press enter button in our keyboard (null request) considering it to be implemented in factories/ industries.
10. At the end click mail button , it will send the whole data of object detection as a link on user's mail ID.
 
## Simulation and video  &#8594; ##
 this was the initial part of the project -> [Old Video](https://drive.google.com/file/d/1TF6mAdieY1y7LwcNcP_3ViE0T7ZFZaRc/view?usp=sharing) .
 
 It has been updated further.  
- [part 1](https://drive.google.com/file/d/1bpnN1DzF4hiwXhy1qhL5fj3gVxKpSGxg/view?usp=sharing).
- [Part 2](https://drive.google.com/file/d/12z3GRziLnBk-6eHneFIRWx7Ja-8JJd28/view?usp=sharing).
- [part 3](https://drive.google.com/file/d/1lMTzhMYUJX97SdcrRcfSsxMbIExO5GUv/view?usp=sharing). 
- [part 4](https://drive.google.com/file/d/1wlPrEMYaEXFvIInjsboRmzkDN_ZBHDEw/view?usp=sharing). 
- [final part](https://drive.google.com/file/d/1cmV0HM9TzIhTqHFFVLiAb00u7v9EkCPl/view?usp=sharing)


import cv2 #importing computer vision library.
import numpy as np #importing numpy library for working with array and matrices.
import urllib
from bs4 import BeautifulSoup
import urllib.request as ur #these 3 libraries for thingspeak.cloud
net=cv2.dnn.readNet('yolov3.cfg','yolov3.weights')#reading weight and configuration file
classes=[]
with open('cocoo.names','r') as f:
  classes = f.read().splitlines() #reading our coco data set and sorting them in list classes.
cap=cv2.VideoCapture(0,cv2.CAP_DSHOW) #to turn on our webcam

while True:
  _, img=cap.read() #img=frame obtained from webcam, _ is for channel which is related to color
  height,width,_=img.shape #image shape = height,width,
  #since our image in BGR order,we need to swap in RGB order, for that we also neet to divide the pixels by 255 so that they could fit in our Yolo modal 
  blob=cv2.dnn.blobFromImage(img, 1/255, (416,416), (0,0,0), swapRB=True, crop=False)
  net.setInput(blob)  # setting new input value blob to our network
  output_layers_names=net.getUnconnectedOutLayersNames()
  layerOutputs=net.forward(output_layers_names) #run forward pass to compute output of layer with names
  #defining 3 list of bounding box,confidence level and class Id.
  boxes=[]
  confidences=[]
  classIds=[]

  for output in layerOutputs:#to extract all the information from layer output
    for detection in output: #to extract info from each of the outputs
      scores=detection[5:] #scores variable for 80 class prediction
      classId=np.argmax(scores)#using numpy to extract highest scores vector
      confidence=scores[classId]#extract highest scores and assign them to confidence
      if confidence > 0.5: #if confidence level is > 0.5, we will locate the boxes position 
        #x and y are coordinates of the object and w and h are width and height of box
        center_x=int(detection[0]*width)
        center_y=int(detection[1]*height)
        w=int(detection[2]*width)
        h=int(detection[3]*height)
        #in order to make this boxes compatible with our original image/frame from webcam,we need to multipy with width and height.

        x=int(center_x-w/2)
        y=int(center_y-h/2) 
        #subtracting value from upper left corner so that the box align properly

        boxes.append([x,y,w,h])
        confidences.append((float(confidence)))
        classIds.append(classId)
        #putting all these parameters in the respective lists
    
  indexes=cv2.dnn.NMSBoxes(boxes,confidences,0.5,0.4)
  #to filter boxes by score

  font=cv2.FONT_HERSHEY_PLAIN
  colors=np.random.uniform(0, 255, size=(len(boxes), 3))
  #giving color and font style to all the boxes
  #.flatten command is use to draw 2d modal for 3d object

  if len(indexes)>0:
    for i in indexes.flatten():
      x,y,w,h=boxes[i]
      label=str(classes[classIds[i]])
      confidence=str(round(confidences[i],2))
      color=colors[i]
      cv2.rectangle(img, (x,y), (x+w, y+h), color, 2)
      #rect(image,coordinates,size,color,thickness)
      cv2.putText(img, label + " " + confidence, (x,y+20), font, 2, (0,0,0), 2)
      #x,y+20 is location, 2 is font size , (0,0,0)=code for black font color another 2 is thickness
    cv2.imshow('image',img) #to show the window for our webcam
    if label=='eraser':   #1 is for eraser
      print("eraser is detected\nSending data to cloud........")
      data=ur.urlopen("https://api.thingspeak.com/update?api_key=5MPYLZGLWQPBV8GY&field1="+str(1))
      d=data.read()
      print("\ndata sent successfully")
    if label=='tape':      #2 is for tape
      print("tape is detected\nSending data to cloud........")
      data=ur.urlopen("https://api.thingspeak.com/update?api_key=5MPYLZGLWQPBV8GY&field1="+str(2))
      d=data.read()
      print("\ndata sent successfully")
    key=cv2.waitKey(1)
    if key==27: 
      break #if we press escape key,our loop will break and window showing our webcam will exit.
    elif key==13: #Enter key for sending null request.
      print("null request entered\nSending data to cloud........")
      data=ur.urlopen("https://api.thingspeak.com/update?api_key=5MPYLZGLWQPBV8GY&field1="+str(0))
      d=data.read()
      print("\ndata sent successfully")
  else:
    cv2.imshow('image',img) #to show the window for our webcam
cap.release()
cv2.destroyAllWindows()

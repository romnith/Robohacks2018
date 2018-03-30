import cv2
import sys
 
(major_ver, minor_ver, subminor_ver) = (cv2.__version__).split('.')

center = (320, 240)

# Define an initial bounding box
bbox = (287, 23, 86, 320)
boxcenter = (0, 0)

if __name__ == '__main__' :
 
    # Set up tracker.
    # Instead of MIL, you can also use
 
    tracker_types = ['BOOSTING', 'MIL','KCF', 'TLD', 'MEDIANFLOW', 'GOTURN']
    tracker_type = tracker_types[2]
 
    if int(minor_ver) < 3:
        tracker = cv2.Tracker_create(tracker_type)
    else:
        if tracker_type == 'BOOSTING':
            tracker = cv2.TrackerBoosting_create()
        if tracker_type == 'MIL':
            tracker = cv2.TrackerMIL_create()
        if tracker_type == 'KCF':
            tracker = cv2.TrackerKCF_create()
        if tracker_type == 'TLD':
            tracker = cv2.TrackerTLD_create()
        if tracker_type == 'MEDIANFLOW':
            tracker = cv2.TrackerMedianFlow_create()
        if tracker_type == 'GOTURN':
            tracker = cv2.TrackerGOTURN_create()
 
    # Read video
    video = cv2.VideoCapture(0)
 
    # Exit if video not opened.
    if not video.isOpened():
        print('Could not open video')
        sys.exit()
 
    # Read first frame.
    ok, frame = video.read()
    if not ok:
        print('Cannot read video file')
        sys.exit()
 
    # Uncomment the line below to select a different bounding box
    #bbox = cv2.selectROI(frame, False)
 
    # Initialize tracker with first frame and bounding box
    ok = tracker.init(frame, bbox)
 
    while True:
        # Read a new frame
        ok, frame = video.read()
        if not ok:
            break
         
        # Start timer
        timer = cv2.getTickCount()
 
        # Update tracker
        ok, bbox = tracker.update(frame)
 
        # Calculate Frames per second (FPS)
        #fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer);
 
        # Draw bounding box
        if ok:
            # Tracking success
            p1 = (int(bbox[0]), int(bbox[1]))
            p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
            cv2.rectangle(frame, p1, p2, (255,0,0), 2, 1)
            boxcenter = (int((p1[0] + p2[0])/2), int((p1[1] + p2[1])/2))
        else :
            # Tracking failure
            cv2.putText(frame, "Tracking failure detected", (100, 500), cv2.FONT_HERSHEY_SIMPLEX, 0.75,(255,255,255),2)
		
		#display center crosshair
        cv2.putText(frame, ".", center, cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255,255,255),2)
        
        x =	int(boxcenter[0]-center[0])
        y = - int(boxcenter[1]-center[1])
		
		#display x and y values
        cv2.putText(frame, "X/Y:" + str(x) + "/" + str(y), (0, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255,255,255),2)
		
		
        #display box center
        cv2.putText(frame, ".", boxcenter, cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255,255,255),2)		
     
        # Display FPS on frame
        #cv2.putText(frame, "FPS : " + str(int(fps)), (100,50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50), 2);
		
        # Display result
        cv2.imshow("Tracking", frame)
 
        # Exit if ESC pressed
        k = cv2.waitKey(1) & 0xff
        if k == 27 : break

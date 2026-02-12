
import cv2


img = cv2.imread("data/Lenna.png")
while True:
    cv2.imshow("Lenna", img)

    key = cv2.waitKey(1)
    if key == ord('q'):
        break


import cv2
import numpy as np

image_path = "Task-11/test_2.jpg"
image = cv2.imread(image_path)

cv2.imshow("Original Image", image)
cv2.waitKey(0)
blurred = cv2.GaussianBlur(image, (11, 11), 0)

hsv_image = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

hsv_min = np.array([36, 25, 25], dtype=np.uint8)
hsv_max = np.array([85, 255, 255], dtype=np.uint8)

green_mask = cv2.inRange(hsv_image, hsv_min, hsv_max)
cv2.imshow("Green Mask", green_mask)
cv2.waitKey(0)

contours, hierarchy = cv2.findContours(green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

print(f"Найдено зелёных контуров: {len(contours)}")

for i, contour in enumerate(contours):
    x, y, w, h = cv2.boundingRect(contour)
    center_x = int(x + w / 2)
    center_y = int(y + h / 2)

    print(x, y, w, h)

    cv2.drawContours(image, [contour], -1, (255, 0, 0), 10, cv2.LINE_AA, hierarchy, 1)
    cv2.circle(image, (center_x, center_y), 10, (0, 0, 255), 3)

cv2.imshow("Result with centers", image)
cv2.waitKey(0)
cv2.destroyAllWimdows()
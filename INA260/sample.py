import time
import Adafruit_SSD1306

from ina260.controller import Controller
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

RST = None     # on the PiOLED this pin isnt used

disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
disp.begin()
disp.clear()
disp.display()

width = disp.width
height = disp.height
image = Image.new('1',(width,height))
draw = ImageDraw.Draw(image)
draw.rectangle((0,0,width,height),outline=0,fill=0)

padding = -2
top = padding
bottom = height-padding
x = 5
font = ImageFont.truetype('/home/nhlee/dev/SSD1306/_font/DS-DIGI.TTF',15)

c = Controller(address=0x45)

while True:
    now = time.localtime()
#dt = "%04d-%02d-%02d" % (now.tm_year, now.tm_mon, now.tm_mday)
    tt = "%04d-%02d-%02d  %02d:%02d:%02d" % (now.tm_year, now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec)
    volt = "Voltage : %02.2f V" % (c.voltage())
    
    draw.rectangle((0,0,width,height), outline=0, fill=0)
#   draw.text((x,top), dt , font=font,fill=255)
#   draw.text((x,top+15), tt , font=font,fill=255)
    draw.text((x,top), tt , font=font,fill=255)
    draw.text((x,top+15), volt , font=font,fill=255)
    
    disp.image(image)
    disp.display()
    time.sleep(.1)

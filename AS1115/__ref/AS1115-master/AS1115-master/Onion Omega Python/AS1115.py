# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# AS1115
# This code is designed to work with the AS1115_I2CL_3CE I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/LED-Display?sku=AS1115_I2CL_3CE#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# AS1115 address, 0x00(00)
# Select Shutdown register, 0x0C(12)
#		0x01(01)	Normal Operation, Reset Feature Register to Default Settings
i2c.writeByte(0x00, 0x0C, 0x01)
# AS1115 address, 0x00(00)
# Select Intensity Control Register, 0x0A(10)
#		0x80(128)	Duty cycle = 1/16
i2c.writeByte(0x00, 0x0A, 0x80)
# AS1115 address, 0x00(00)
# Select Feature Register, 0x0E(14)
#		0x04(04)	Enable HEX decoding
i2c.writeByte(0x00, 0x0E, 0x04)
# AS1115 address, 0x00(00)
# Select Scan-limit Register, 0x0B(11)
#		0x02(02)	Display digits 0-2
i2c.writeByte(0x00, 0x0B, 0x02)
# AS1115 address, 0x00(00)
# Select Decode-enable Register, 0x09(09)
#		0x07(07)	Set all digits to font decode
i2c.writeByte(0x00, 0x09, 0x07)

time.sleep(0.3)

for data in range(0, 16):
	for digit in range(3):
		# Write data on the digits
		i2c.writeByte(0x00, digit+1, data)
	# Output to screen
	print "Display on 7-Segment : ",hex(data)
	time.sleep(0.8)
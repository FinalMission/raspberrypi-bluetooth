import subprocess
import time
import sys

CS_MAC = 'F4:0F:24:29:73:C0'
DJ_S8_PLUS = "94:8B:C1:5C:5D:17"
INTERVAL = 1

try:
    sys.argv[1]
    INTERVAL = int(sys.argv[1])
except: pass
print("Running {0} with interval {1} sec".format(sys.argv[0], INTERVAL))

while(1):
    subprocess.call('hcitool rssi {0}'.format(DJ_S8_PLUS), shell=True)
    time.sleep(INTERVAL)

import subprocess
import time

while(1):
    subprocess.call('ls -al', shell=True)
    time.sleep(1)

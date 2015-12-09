# intro-to-unix-final-project
1. In order to get all packages you should have pip.
To get pip enter command: 
python get-pip.py
2. Get packages using pip install:
sudo pip install pyowm
sudo pip install datetime
sudo pip install argparse
sudo pip install geopy
sudo pip install requests
sudo pip install re

3. (Optional) This step is optional but it will make sure you can run the python script. The script may take some time to run.
In the directory with the the script weather.py run command:
python weather.py -s Blacksburg -d Roanoke

**Blacksburg is the start and Roanoke is the destination.
**Check file weather.dat and make sure it has been updated with checkpoint locations and weather information

4. To run the Qt application, go to the direcotry containing the advisor.pro, main.cpp, mainwindow.cpp, mainwindow.h ,etc.
Run commands:
qmake advisor.pro
Then run command:
make
Finally run command:
./advisor 

5. To use this GUI, type your start location ie. Blacksburg, and Destination location ie. Roanoke. Then click the Weather button.  It may take some time to make the necessary RESTful GET requests from the weather and Google Maps API so the GUI may be unresponsive for period of time depending on internet connectivity and number of checkpoints in the trip



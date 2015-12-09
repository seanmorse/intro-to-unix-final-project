import pyowm
import datetime
import argparse
from geopy.geocoders import Nominatim
import zipcode
import googlemaps
import requests
import json
import urllib
import pprint
import re

parser = argparse.ArgumentParser()
parser.add_argument('-s', type=str)
parser.add_argument('-d', type=str)

geolocator=Nominatim()
#zip=zipcode.isequal(str(parser.parse_args().s))
#print zip.lat
coord=geolocator.geocode(str(parser.parse_args().s))
coord2=geolocator.geocode(str(parser.parse_args().d))
#print((coord.latitude, coord.longitude))
#Weather

#API KEY
owm = pyowm.OWM('f9f7892352c1e361678f022dd02894e3')

#Lat and Lon
obs = owm.weather_at_coords(coord.latitude, coord.longitude)

coordstring="("+str(coord.latitude)+","+str(coord.longitude)+")"
coordstring2="("+str(coord2.latitude)+","+str(coord2.longitude)+")"
#google maps
gmaps = googlemaps.Client(key='AIzaSyD_8SunCrqkR79uNj2fxGVZXKr8cHfsvXg')

directions_result = gmaps.directions(coordstring,
                                     "Blacksburg",
                                     mode="driving")
gm= requests.get('https://maps.googleapis.com/maps/api/directions/json?origin='+coordstring+'&destination='+coordstring2+'&mode=driving&key=AIzaSyD_8SunCrqkR79uNj2fxGVZXKr8cHfsvXg')
temp= gm.text
sl=[]
sl=temp.split('\n')
count=0
start_count=0
end_count=0
start_list=[]
end_list=[]
for item in sl:
	if "start_location" in sl[count]:
		
		if start_count > 0:
			start_list.append(sl[count])
			start_list.append(sl[count+1])
			start_list.append(sl[count+2])
		start_count=start_count+1
		
	if "end_location" in sl[count]:
		
		if end_count == 0:
			end_list.append(sl[count])
			end_list.append(sl[count+1])
			end_list.append(sl[count+2])
		end_count=end_count+1
	count=count+1
lat_list=[]
lon_list=[]
counter=0
for list_item in start_list:
	if "lat" in start_list[counter]:
		lat_list.append(str(re.split(': |,',start_list[counter])[1]))
	if "lng" in start_list[counter]:
		lon_list.append(str(re.split(': |,',start_list[counter])[1]))
	counter=counter+1	
	
print lat_list
print lon_list	
address_list=[]
	
#Obtain weather information
f = open('weather.dat', 'w')
f.truncate()
for z in range(0, len(lat_list)):
	obs = owm.weather_at_coords(float(lat_list[z]), float(lon_list[z]))

	location = obs.get_location()

	area =  location.get_name() + ', us'

	forecast = owm.daily_forecast(area, limit=1)

	display_forecast = forecast.get_forecast()

	lst = display_forecast.get_weathers()

	geolocator2=Nominatim()
	location2=geolocator.reverse(lat_list[z]+","+lon_list[z])
	f.write("Location: "+location2.address)
	
	weather_info = []
	date_info = []

	for weather in display_forecast:
		weather_String= (weather.get_reference_time('iso'),str(weather.get_status()))
		temp=''.join(weather_String)
		weather_info.append((weather.get_detailed_status()))		
		date_info.append(datetime.datetime.strptime(weather.get_reference_time('iso'), "%Y-%m-%d %H:%M:%S+00"))
	

	for x in range(0, len(weather_info)):
		
		#f.write(date_info[x].strftime("%m/%d/%Y")) #%H:%M:%S
		f.write('\nWeather: ')
		f.write(weather_info[x])
		#f.write(len(weather_info))
		#f.write(len(date_info))
		f.write('\n')
		f.write('\n')
f.close()

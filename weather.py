import pyowm
import datetime
import argparse
from geopy.geocoders import Nominatim

parser = argparse.ArgumentParser()
parser.add_argument('-s', type=str)
#parser.add_argument('-d', type=str)

geolocator=Nominatim()
location=geolocator.geocode(str(parser.parse_args().s))
print((location.latitude, location.longitude))
#Weather

#API KEY
owm = pyowm.OWM('f9f7892352c1e361678f022dd02894e3')

#Lat and Lon
obs = owm.weather_at_coords(location.latitude, location.longitude)

#Obtain weather information

location = obs.get_location()

area =  location.get_name() + ', us'

forecast = owm.daily_forecast(area, limit=15)

display_forecast = forecast.get_forecast()

lst = display_forecast.get_weathers()

f = open('weather.dat', 'weather')
f.truncate()

weather_info = []
date_info = []

for weather in display_forecast:
	weather_String= (weather.get_reference_time('iso'),str(weather.get_status()))
	temp=''.join(weather_String)
	weather_info.append((weather.get_detailed_status()))		
	date_info.append(datetime.datetime.strptime(weather.get_reference_time('iso'), "%Y-%m-%d %H:%M:%S+00"))
	
#print len(weather_info)
#print len(date_info)
for x in range(0, len(weather_info)):
	f.write(date_info[x].strftime("%m/%d/%Y")) #%H:%M:%S
	f.write(' ')
	f.write(weather_info[x])
	#f.write(len(weather_info))
	#f.write(len(date_info))
	f.write('\n')
f.close()

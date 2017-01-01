# dht21_mqtt_eth
An arduino sketch that sends dht21 temperature and humidity readings to OpenHAB via ethernet
You will need to configure the ethernet address for your network.
and change the mqtt topics to suit your setup.

you can configur the delay in the main loop to change the reading times
you can send a mqtt topic to the device to get an instant reading

You will need to install the dht, ethernet and mqtt libraries 

the mqtt library comes from
http://pubsubclient.knolleary.net/
the ethernet and dht librarys are standard, use your library maanger to install.



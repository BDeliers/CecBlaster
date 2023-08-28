## Power-on sequence of Samsung UE43TU7125 TV

```
0 INFO ../App/AppMain.c:230: Startup
8 DEBUG ../App/AppCec.c:129: Received command POLLING from TV to AUDIO_SYSTEM
8 DEBUG ../App/AppCec.c:129: Received command GET_CEC_VERSION from TV to AUDIO_SYSTEM
8 DEBUG ../App/AppCec.c:129: Sent command CEC_VERSION from AUDIO_SYSTEM to TV with payload: 	05 
8 DEBUG ../App/AppCec.c:129: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
8 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
9 DEBUG ../App/AppCec.c:129: Received command GIVE_DEVICE_VENDOR_ID from TV to AUDIO_SYSTEM
9 DEBUG ../App/AppCec.c:129: Sent command DEVICE_VENDOR_ID from AUDIO_SYSTEM to TV with payload: 	18 03 99 
9 DEBUG ../App/AppCec.c:129: Received command GIVE_DEVICE_POWER_STATUS from TV to AUDIO_SYSTEM
9 DEBUG ../App/AppCec.c:129: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to TV with payload: 	01 
10 DEBUG ../App/AppCec.c:129: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
10 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
11 DEBUG ../App/AppCec.c:129: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
11 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
13 DEBUG ../App/AppCec.c:129: Received command GIVE_PHYSICAL_ADDRESS from TV to AUDIO_SYSTEM
13 DEBUG ../App/AppCec.c:129: Sent command REPORT_PHYSICAL_ADDRESS from AUDIO_SYSTEM to TV with payload: 	05 
19 DEBUG ../App/AppCec.c:129: Received command GIVE_OSD_NAME from TV to AUDIO_SYSTEM
19 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
24 DEBUG ../App/AppCec.c:129: Received command VENDOR_COMMAND_WITH_ID from TV to AUDIO_SYSTEM with payload: 	00 00 f0 23 
24 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
24 DEBUG ../App/AppCec.c:129: Received command STANDBY from TV to UNREGISTERED_BROADCAST
```
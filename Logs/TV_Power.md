## Power-on sequence of Samsung UE43TU7125 TV

```
0 INFO ../Core/Src/main.c:119: -- Startup --
8DEBUG ../App/AppCec.c:140: Received command POLLING from TV to AUDIO_SYSTEM
9DEBUG ../App/AppCec.c:140: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
9DEBUG ../App/AppCec.c:140: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
10DEBUG ../App/AppCec.c:140: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
10DEBUG ../App/AppCec.c:140: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
11DEBUG ../App/AppCec.c:140: Received command FEATURE_ABORT from TV to AUDIO_SYSTEM with payload: 	e9 00 
12DEBUG ../App/AppCec.c:140: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
12DEBUG ../App/AppCec.c:140: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
13DEBUG ../App/AppCec.c:140: Received command FEATURE_ABORT from TV to AUDIO_SYSTEM with payload: 	e9 00 
14DEBUG ../App/AppCec.c:140: Received command GIVE_DEVICE_POWER_STATUS from TV to AUDIO_SYSTEM
14DEBUG ../App/AppCec.c:140: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to TV with payload: 	01 
15DEBUG ../App/AppCec.c:140: Received command FEATURE_ABORT from TV to AUDIO_SYSTEM with payload: 	e9 00 
19DEBUG ../App/AppCec.c:140: Received command GIVE_PHYSICAL_ADDRESS from TV to AUDIO_SYSTEM
19DEBUG ../App/AppCec.c:140: Sent command REPORT_PHYSICAL_ADDRESS from AUDIO_SYSTEM to TV with payload: 	05 
20DEBUG ../App/AppCec.c:140: Received command FEATURE_ABORT from TV to AUDIO_SYSTEM with payload: 	e9 00 
22DEBUG ../App/AppCec.c:140: Received command STANDBY from TV to UNREGISTERED_BROADCAST
```
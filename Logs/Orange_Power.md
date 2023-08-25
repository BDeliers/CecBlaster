## Power-on sequence from Orange UHD decoder connected to Samsung UE43TU7125 TV

```
0 INFO ../Core/Src/main.c:119: -- Startup --
3 DEBUG ../App/AppCec.c:140: Received command POLLING from PLAYBACK_1 to AUDIO_SYSTEM
4 DEBUG ../App/AppCec.c:140: Received command GIVE_DEVICE_POWER_STATUS from PLAYBACK_1 to AUDIO_SYSTEM
4 DEBUG ../App/AppCec.c:140: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	01 
5 DEBUG ../App/AppCec.c:140: Received command GIVE_DEVICE_POWER_STATUS from PLAYBACK_1 to AUDIO_SYSTEM
5 DEBUG ../App/AppCec.c:140: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	01 
6 DEBUG ../App/AppCec.c:140: Received command SYSTEM_AUDIO_MODE_REQUEST from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	10 00 
6 DEBUG ../App/AppCec.c:140: Sent command SET_SYSTEM_AUDIO_MODE from AUDIO_SYSTEM to UNREGISTERED_BROADCAST with payload: 	01 
7 DEBUG ../App/AppCec.c:140: Received command SYSTEM_AUDIO_MODE_REQUEST from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	10 00 
7 DEBUG ../App/AppCec.c:140: Sent command SET_SYSTEM_AUDIO_MODE from AUDIO_SYSTEM to UNREGISTERED_BROADCAST with payload: 	01 
9 DEBUG ../App/AppCec.c:140: Received command REPORT_PHYSICAL_ADDRESS from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 04 
10 DEBUG ../App/AppCec.c:140: Received command REPORT_PHYSICAL_ADDRESS from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 04 
12 DEBUG ../App/AppCec.c:140: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
12 DEBUG ../App/AppCec.c:140: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
14 DEBUG ../App/AppCec.c:140: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
14 DEBUG ../App/AppCec.c:140: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
15 DEBUG ../App/AppCec.c:140: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
15 DEBUG ../App/AppCec.c:140: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
17 DEBUG ../App/AppCec.c:140: Received command GIVE_DEVICE_POWER_STATUS from TV to AUDIO_SYSTEM
17 DEBUG ../App/AppCec.c:140: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to TV with payload: 	00 
22 DEBUG ../App/AppCec.c:140: Received command GIVE_PHYSICAL_ADDRESS from TV to AUDIO_SYSTEM
22 DEBUG ../App/AppCec.c:140: Sent command REPORT_PHYSICAL_ADDRESS from AUDIO_SYSTEM to TV with payload: 	05 
23 DEBUG ../App/AppCec.c:140: Received command FEATURE_ABORT from TV to AUDIO_SYSTEM with payload: 	16 00 
```
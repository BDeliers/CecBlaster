## Power-on sequence from Orange UHD decoder connected to Samsung UE43TU7125 TV

```
0 INFO ../App/AppMain.c:230: Startup
2 DEBUG ../App/AppCec.c:129: Received command POLLING from PLAYBACK_1 to AUDIO_SYSTEM
2 DEBUG ../App/AppCec.c:129: Received command GIVE_DEVICE_POWER_STATUS from PLAYBACK_1 to AUDIO_SYSTEM
2 DEBUG ../App/AppCec.c:129: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	01 
3 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	40 
3 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
3 DEBUG ../App/AppMain.c:191: Sent IR command 15
3 DEBUG ../App/AppIr.c:52: Sent frame with command 15 to address 30 (8b)
3 DEBUG ../App/AppCec.c:129: Received command SYSTEM_AUDIO_MODE_REQUEST from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	10 00 
3 DEBUG ../App/AppCec.c:129: Sent command SET_SYSTEM_AUDIO_MODE from AUDIO_SYSTEM to UNREGISTERED_BROADCAST with payload: 	01 
4 DEBUG ../App/AppCec.c:129: Received command ACTIVE_SOURCE from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 
4 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
9 DEBUG ../App/AppCec.c:129: Received command POLLING from TV to AUDIO_SYSTEM
10 DEBUG ../App/AppCec.c:129: Received command GET_CEC_VERSION from TV to AUDIO_SYSTEM
10 DEBUG ../App/AppCec.c:129: Sent command CEC_VERSION from AUDIO_SYSTEM to TV with payload: 	05 
10 DEBUG ../App/AppCec.c:129: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
10 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
10 DEBUG ../App/AppCec.c:129: Received command DEVICE_VENDOR_ID from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	00 15 82 
10 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
11 DEBUG ../App/AppCec.c:129: Received command GIVE_DEVICE_VENDOR_ID from TV to AUDIO_SYSTEM
11 DEBUG ../App/AppCec.c:129: Sent command DEVICE_VENDOR_ID from AUDIO_SYSTEM to TV with payload: 	18 03 99 
11 DEBUG ../App/AppCec.c:129: Received command GIVE_DEVICE_POWER_STATUS from TV to AUDIO_SYSTEM
11 DEBUG ../App/AppCec.c:129: Sent command REPORT_POWER_STATUS from AUDIO_SYSTEM to TV with payload: 	00 
11 DEBUG ../App/AppCec.c:129: Received command DEVICE_VENDOR_ID from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	00 15 82 
11 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
12 DEBUG ../App/AppCec.c:129: Received command REPORT_PHYSICAL_ADDRESS from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 04 
12 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
12 DEBUG ../App/AppCec.c:129: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
12 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
12 DEBUG ../App/AppCec.c:129: Received command REPORT_PHYSICAL_ADDRESS from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 04 
12 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
13 DEBUG ../App/AppCec.c:129: Received command REQUEST_SHORT_AUDIO_DESCRIPTOR from TV to AUDIO_SYSTEM with payload: 	0a 
13 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
15 DEBUG ../App/AppCec.c:129: Received command GIVE_PHYSICAL_ADDRESS from TV to AUDIO_SYSTEM
15 DEBUG ../App/AppCec.c:129: Sent command REPORT_PHYSICAL_ADDRESS from AUDIO_SYSTEM to TV with payload: 	05 
20 DEBUG ../App/AppCec.c:129: Received command GIVE_OSD_NAME from TV to AUDIO_SYSTEM
20 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
22 DEBUG ../App/AppCec.c:129: Received command ACTIVE_SOURCE from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 
22 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
25 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	41 
25 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
25 DEBUG ../App/AppMain.c:191: Sent IR command 12
25 DEBUG ../App/AppIr.c:52: Sent frame with command 12 to address 30 (8b)
25 DEBUG ../App/AppCec.c:129: Received command VENDOR_COMMAND_WITH_ID from TV to AUDIO_SYSTEM with payload: 	00 00 f0 23 
25 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
26 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	41 
26 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
26 DEBUG ../App/AppMain.c:191: Sent IR command 12
26 DEBUG ../App/AppIr.c:52: Sent frame with command 12 to address 30 (8b)
26 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	41 
27 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
27 DEBUG ../App/AppMain.c:191: Sent IR command 12
27 DEBUG ../App/AppIr.c:52: Sent frame with command 12 to address 30 (8b)
27 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	41 
27 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
27 DEBUG ../App/AppMain.c:191: Sent IR command 12
27 DEBUG ../App/AppIr.c:52: Sent frame with command 12 to address 30 (8b)
28 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	41 
28 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
28 DEBUG ../App/AppMain.c:191: Sent IR command 12
28 DEBUG ../App/AppIr.c:52: Sent frame with command 12 to address 30 (8b)
28 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	41 
28 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
28 DEBUG ../App/AppMain.c:191: Sent IR command 12
28 DEBUG ../App/AppIr.c:52: Sent frame with command 12 to address 30 (8b)
30 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	42 
30 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
30 DEBUG ../App/AppMain.c:191: Sent IR command 13
30 DEBUG ../App/AppIr.c:52: Sent frame with command 13 to address 30 (8b)
30 DEBUG ../App/AppCec.c:129: Received command GIVE_SYSTEM_AUDIO_MODE_STATUS from TV to AUDIO_SYSTEM
30 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to TV with payload: 	00 
30 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	42 
31 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
31 DEBUG ../App/AppMain.c:191: Sent IR command 13
31 DEBUG ../App/AppIr.c:52: Sent frame with command 13 to address 30 (8b)
31 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	42 
31 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
31 DEBUG ../App/AppMain.c:191: Sent IR command 13
31 DEBUG ../App/AppIr.c:52: Sent frame with command 13 to address 30 (8b)
31 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	42 
32 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
32 DEBUG ../App/AppMain.c:191: Sent IR command 13
32 DEBUG ../App/AppIr.c:52: Sent frame with command 13 to address 30 (8b)
32 DEBUG ../App/AppCec.c:129: Received command ACTIVE_SOURCE from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 	10 00 
32 DEBUG ../App/AppCec.c:129: Sent command FEATURE_ABORT from AUDIO_SYSTEM to PLAYBACK_1 with payload: 	00 
32 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_PRESSED from PLAYBACK_1 to AUDIO_SYSTEM with payload: 	42 
32 DEBUG ../App/AppCec.c:129: Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
32 DEBUG ../App/AppMain.c:191: Sent IR command 13
32 DEBUG ../App/AppIr.c:52: Sent frame with command 13 to address 30 (8b)
35 DEBUG ../App/AppCec.c:129: Received command POLLING from PLAYBACK_1 to AUDIO_SYSTEM
35 DEBUG ../App/AppCec.c:129: Received command STANDBY from PLAYBACK_1 to AUDIO_SYSTEM
35 DEBUG ../App/AppMain.c:191: Sent IR command 15
35 DEBUG ../App/AppIr.c:52: Sent frame with command 15 to address 30 (8b)
36 DEBUG ../App/AppCec.c:129: Received command STANDBY from TV to UNREGISTERED_BROADCAST
36 DEBUG ../App/AppCec.c:129: Received command STANDBY from TV to UNREGISTERED_BROADCAST
```
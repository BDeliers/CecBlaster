## Power-on sequence of Samsung UE43TU7125 TV

```
	[AppCec] Received command ROUTING_CHANGE from TV to UNREGISTERED_BROADCAST with payload: 
		20 00 10 00 
	[AppCec] Received command SET_STREAM_PATH from TV to UNREGISTERED_BROADCAST with payload: 
		10 00 
	[AppCec] Received command GIVE_SYSTEM_AUDIO_MODE_STATUS from TV to AUDIO_SYSTEM
	[AppCec] Received command SET_STREAM_PATH from TV to UNREGISTERED_BROADCAST with payload: 
		10 00 
	[AppCec] Received command ROUTING_CHANGE from TV to UNREGISTERED_BROADCAST with payload: 
		00 00 10 00 
	[AppCec] Received command SET_STREAM_PATH from TV to UNREGISTERED_BROADCAST with payload: 
		10 00 
	[AppCec] Received command SET_MENU_LANGUAGE from TV to UNREGISTERED_BROADCAST with payload: 
		66 72 61 
	// 8 * [AppCec] Error
	[AppCec] Received command FEATURE_ABORT from TV to AUDIO_SYSTEM
	// 18 * [AppCec] Error
	[AppCec] Received command GET_CEC_VERSION from TV to AUDIO_SYSTEM
	[AppCec] Received command POLLING from TV to AUDIO_SYSTEM with payload: 
		0a 
	[AppCec] Received command POLLING from TV to AUDIO_SYSTEM with payload: 
		0a 
	[AppCec] Received command POLLING from TV to AUDIO_SYSTEM with payload: 
		0a 
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from TV to AUDIO_SYSTEM
	[AppCec] Received command GIVE_DEVICE_POWER_STATUS from TV to AUDIO_SYSTEM
	[AppCec] Received command GIVE_PHYSICAL_ADDRESS from TV to AUDIO_SYSTEM
	[AppCec] Received command SET_OSD_NAME from TV to AUDIO_SYSTEM
	[AppCec] Received command VENDOR_COMMAND_WITH_ID from TV to AUDIO_SYSTEM with payload: 
		00 00 f0 23 
```

## Power-off sequence

```
	[AppCec] Received command GIVE_SYSTEM_AUDIO_MODE_STATUS from TV to AUDIO_SYSTEM
	[AppCec] Received command STANDBY from TV to UNREGISTERED_BROADCAST
```
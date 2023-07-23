## Power-on sequence from Orange UHD decoder connected to Samsung UE43TU7125 TV

```
	[AppCec] Received command FEATURE_ABORT from PLAYBACK_1 to TV
	[AppCec] Received command FEATURE_ABORT from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command IMAGE_VIEW_ON from PLAYBACK_1 to TV
	[AppCec] Received command GET_CEC_VERSION from TV to PLAYBACK_1
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		05 
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command GIVE_DEVICE_POWER_STATUS from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command GIVE_DEVICE_POWER_STATUS from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command POLLING from PLAYBACK_1 to AUDIO_SYSTEM with payload: 
		40 
	[AppCec] Received command USER_CONTROL_RELEASED from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command SYSTEM_AUDIO_MODE_REQUEST from PLAYBACK_1 to AUDIO_SYSTEM with payload: 
		10 00 
	[AppCec] Received command GET_CEC_VERSION from TV to PLAYBACK_1
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		05 
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from TV to PLAYBACK_1
	[AppCec] Received command DEVICE_VENDOR_ID from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 
		00 15 82 
	[AppCec] Received command GIVE_DEVICE_POWER_STATUS from TV to PLAYBACK_1
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		00 
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from TV to PLAYBACK_1
	[AppCec] Received command DEVICE_VENDOR_ID from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 
		00 15 82 
	[AppCec] Received command GIVE_DEVICE_POWER_STATUS from TV to PLAYBACK_1
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		00 
	[AppCec] Received command GIVE_PHYSICAL_ADDRESS from TV to PLAYBACK_1
	[AppCec] Received command REPORT_PHYSICAL_ADDRESS from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 
		10 00 04 
	[AppCec] Received command GIVE_PHYSICAL_ADDRESS from TV to PLAYBACK_1
	[AppCec] Received command SYSTEM_AUDIO_MODE_REQUEST from PLAYBACK_1 to AUDIO_SYSTEM with payload: 
		10 00 
	[AppCec] Error
	[AppCec] Received command REPORT_PHYSICAL_ADDRESS from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 
		10 00 04 
	[AppCec] Error
	[AppCec] Received command SET_OSD_NAME from TV to PLAYBACK_1
	[AppCec] Received command UNKNOWN 47 from PLAYBACK_1 to TV with payload: 
		44 65 63 6f 64 65 75 72 20 55 48 44 
	[AppCec] Error
	[AppCec] Error
	[AppCec] Received command VENDOR_COMMAND_WITH_ID from TV to PLAYBACK_1 with payload: 
		00 00 f0 23 
	[AppCec] Received command VENDOR_COMMAND_WITH_ID from PLAYBACK_1 to TV with payload: 
		00 00 f0 24 00 80 
	[AppCec] Error
	[AppCec] Error
	[AppCec] Received command SET_STREAM_PATH from TV to UNREGISTERED_BROADCAST with payload: 
		10 00 
	[AppCec] Received command IMAGE_VIEW_ON from PLAYBACK_1 to TV
	[AppCec] Received command FEATURE_ABORT from TV to PLAYBACK_1
	[AppCec] Received command ACTIVE_SOURCE from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 
		10 00 
	[AppCec] Received command FEATURE_ABORT from TV to AUDIO_SYSTEM
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		00 
	[AppCec] Received command SET_OSD_NAME from TV to PLAYBACK_1
	[AppCec] Received command UNKNOWN 47 from PLAYBACK_1 to TV with payload: 
		44 65 63 6f 64 65 75 72 20 55 48 44 
	[AppCec] Error
	[AppCec] Received command IMAGE_VIEW_ON from PLAYBACK_1 to TV
	[AppCec] Error
	[AppCec] Received command ACTIVE_SOURCE from PLAYBACK_1 to UNREGISTERED_BROADCAST with payload: 
		10 00 
	[AppCec] Received command POLLING from TV to PLAYBACK_1 with payload: 
		01 
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		00 
	[AppCec] Error
	[AppCec] Received command POLLING from PLAYBACK_1 to TV with payload: 
		1a 
	[AppCec] Error
	[AppCec] Received command SET_OSD_NAME from TV to PLAYBACK_1
	[AppCec] Received command UNKNOWN 47 from PLAYBACK_1 to TV with payload: 
		44 65 63 6f 64 65 75 72 20 55 48 44 
	// 14 * [AppCec] Error
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
	[AppCec] Received command FEATURE_ABORT from PLAYBACK_1 to TV
	[AppCec] Received command FEATURE_ABORT from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command STANDBY from PLAYBACK_1 to TV
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command GIVE_DEVICE_VENDOR_ID from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command STANDBY from TV to UNREGISTERED_BROADCAST
	[AppCec] Received command STANDBY from TV to UNREGISTERED_BROADCAST
	[AppCec] Received command STANDBY from PLAYBACK_1 to AUDIO_SYSTEM
	[AppCec] Received command INACTIVE_SOURCE from PLAYBACK_1 to TV with payload: 
		10 00 
```
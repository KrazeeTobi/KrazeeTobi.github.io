; datafile for the Fitzy by IKI
; Borrowed from Nokturn
; Borrowed from Mic...
; borrowed heavily from Eloist's wire-cube demo..
;
; zarmasm seems to be really picky about indentation. I got a bunch
; of errormessages when removing the tabs.
;
	AREA demo_data, DATA, READONLY
	EXPORT pic
	EXPORT pl
pic
	INCBIN bg.raw
pl
	INCBIN bg.pal
	END
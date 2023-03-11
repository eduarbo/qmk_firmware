SRC += process_records.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	WPM_ENABLE = yes        # required by bongocat

	SRC += oled_setup.c
	SRC += bongocat.c
	SRC += ocean_dream.c
	SRC += oled_eduarbo.c
endif

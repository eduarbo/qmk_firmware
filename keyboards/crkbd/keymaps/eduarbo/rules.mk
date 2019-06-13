
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
# BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration(+1000)
# MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
# EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
# CONSOLE_ENABLE = yes         # Console for debug(+400)
# COMMAND_ENABLE = yes         # Commands for debug and configuration
# NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality
# MIDI_ENABLE = yes            # MIDI controls
# AUDIO_ENABLE = yes           # Audio output on port C6
# UNICODE_ENABLE = yes         # Unicode
# BLUETOOTH_ENABLE = yes       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.
# SWAP_HANDS_ENABLE = yes      # Enable one-hand typing
VELOCIKEY_ENABLE = yes         # Control the speed of lighting effects
# TAP_DANCE_ENABLE = yes

# if firmware size over limit, try this option
LINK_TIME_OPTIMIZATION_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend


# This will include a library with similar OLED helpers than the one used by
# crkbd. Don't forget to disable the Crkbd implementation in config.h
OLED_DRIVER_ENABLE = no

ifeq ($(strip $(OLED_DRIVER_ENABLE)), no)
    # SRC +=  ./keymaps/eduarbo/glcdfont-no-face.c
    SRC +=  glcdfont-no-face.c
endif


# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/mode_icon_reader.c \
        # ./lib/layer_state_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
        # ./lib/keylogger.c \

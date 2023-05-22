// Copyright 2023 Eduardo Ruiz Macias (@eduarbo) <eduarbo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

// When USB_VBUS_PIN is not defined, SPLIT_USB_DETECT is used
#define USB_VBUS_PIN GP24 // for Raspberry Pi Pico

// use either hands as master as long as the flag that determines which half of
// the keyboard it is has been set in the persistent storage (EEPROM)
#define EE_HANDS

#define SPLIT_DETECTED_OS_ENABLE

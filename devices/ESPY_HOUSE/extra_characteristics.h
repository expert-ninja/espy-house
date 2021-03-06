/*
 * Espy House
 *
 * Copyright 2020 Expert Ninja
 *
 */

/*
 * Based on Home Accessory Architect (HAA) by José Antonio Jiménez Campos (@RavenSystem), licensed under Apache License 2.0.
 * https://github.com/RavenSystem/esp-homekit-devices
 *
 */

#ifndef __ESPY_EXTRA_CHARACTERISTICS__
#define __ESPY_EXTRA_CHARACTERISTICS__

#define HOMEKIT_MIAU_UUID(value) (value "-079E-48FF-8F27-9C2605A29F52")

#define HOMEKIT_CHARACTERISTIC_MIAU_VOLT HOMEKIT_MIAU_UUID("E863F10A")
#define HOMEKIT_DECLARE_CHARACTERISTIC_MIAU_VOLT(_value, ...) \
    .type = HOMEKIT_CHARACTERISTIC_MIAU_VOLT, \
    .description = "Voltage", \
    .format = homekit_format_float, \
    .permissions = homekit_permissions_paired_read \
                | homekit_permissions_notify, \
    .min_value = (float[]) {0}, \
    .max_value = (float[]) {10000}, \
    .value = HOMEKIT_FLOAT_(_value), \
    ##__VA_ARGS__

#define HOMEKIT_CHARACTERISTIC_MIAU_AMPERE HOMEKIT_MIAU_UUID("E863F126")
#define HOMEKIT_DECLARE_CHARACTERISTIC_MIAU_AMPERE(_value, ...) \
    .type = HOMEKIT_CHARACTERISTIC_MIAU_AMPERE, \
    .description = "Current", \
    .format = homekit_format_float, \
    .permissions = homekit_permissions_paired_read \
                | homekit_permissions_notify, \
    .min_value = (float[]) {0}, \
    .max_value = (float[]) {10000}, \
    .value = HOMEKIT_FLOAT_(_value), \
    ##__VA_ARGS__

#define HOMEKIT_CHARACTERISTIC_MIAU_WATT HOMEKIT_MIAU_UUID("E863F10D")
#define HOMEKIT_DECLARE_CHARACTERISTIC_MIAU_WATT(_value, ...) \
    .type = HOMEKIT_CHARACTERISTIC_MIAU_WATT, \
    .description = "Power", \
    .format = homekit_format_float, \
    .permissions = homekit_permissions_paired_read \
                | homekit_permissions_notify, \
    .min_value = (float[]) {0}, \
    .max_value = (float[]) {10000}, \
    .value = HOMEKIT_FLOAT_(_value), \
    ##__VA_ARGS__

#endif  // __ESPY_EXTRA_CHARACTERISTICS__

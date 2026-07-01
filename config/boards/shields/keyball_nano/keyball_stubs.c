#include <zephyr/kernel.h>
#include <zmk/keymap.h>

#if !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

int zmk_keymap_layer_activate(zmk_keymap_layer_id_t layer) {
    return 0;
}

int zmk_keymap_layer_deactivate(zmk_keymap_layer_id_t layer) {
    return 0;
}

uint8_t zmk_keymap_highest_layer_active(void) {
    return 0;
}

#endif

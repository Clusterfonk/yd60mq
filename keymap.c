#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _QWERTY,
    _EXTEND,
    _SYM,
};

enum macros {
    COPY = SAFE_RANGE,
    CUT,
    PASTE,
    UPDIR,
};

const key_override_t comm_ovr = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_EXLM);
const key_override_t dot_ovr = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUES);
const key_override_t coln_ovr = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_SCLN);
const key_override_t slsh_ovr = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS); // This one can change

const key_override_t **key_overrides = (const key_override_t *[]){
    &comm_ovr,
    &dot_ovr,
    &coln_ovr,
    &slsh_ovr,
    NULL // Null terminate the array of overrides!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_iso(
        KC_ESC,     KC_1,       KC_2,   KC_3,   KC_4,   KC_5,   KC_6,       KC_NO,      KC_7,   KC_8,   KC_9,       KC_0,       KC_EQL,         KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,   KC_F,   KC_P,   KC_B,   KC_LBRC,    KC_J,       KC_L,   KC_U,   KC_Y,       QK_REP,     KC_UNDS,
        MO(_EXTEND),KC_A,       KC_R,   KC_S,   KC_T,   KC_G,   KC_RBRC,    KC_M,       KC_N,   KC_E,   KC_I,       KC_O,       KC_COLN,        KC_ENT,
        KC_LSFT,    KC_Z,       KC_X,   KC_C,   KC_D,   KC_V,   QK_REP,     KC_SLSH,    KC_K,   KC_H,   KC_COMM,    KC_DOT,     KC_RSFT,
        KC_LCTL,    KC_LGUI,    KC_LALT,                            KC_SPC,                             MO(_SYM), MO(_EXTEND),  TO(_QWERTY),    KC_RCTL
    ),

	[_QWERTY] = LAYOUT_60_iso(
        KC_ESC,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,       KC_P,       KC_LBRC,    KC_RBRC,
        MO(_EXTEND),KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,       KC_SCLN,    KC_QUOTE,   KC_BSLS,    KC_ENT,
        KC_LSFT,    KC_GRV, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
        KC_LCTL,    KC_LGUI,    KC_LALT,                            KC_SPC,                     MO(_SYM),   MO(_EXTEND),TO(_BASE),  KC_RCTL
    ),

    [_EXTEND] = LAYOUT_60_iso(
        KC_DEL,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,  KC_F6,  KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11, KC_F12, KC_DEL,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,  KC_NO,  KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_NO,  KC_NO,
        KC_NO,      KC_NO,      KC_LCTL,    KC_LSFT,    KC_LGUI,    KC_NO,  KC_NO,  KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,  KC_NO,  KC_NO,
        KC_NO,      KC_NO,      CUT,        COPY,       KC_NO,      PASTE,  KC_NO,  KC_NO,      KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_NO,  KC_NO,
        KC_NO,      KC_NO,      KC_NO,                              KC_NO,                                              KC_NO,      KC_NO,  KC_NO,  KC_NO
    ),

    [_SYM] = LAYOUT_60_iso(
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,  KC_NO,      KC_NO,    KC_NO,        KC_NO,      KC_NO,      KC_NO,      ,
        KC_NO,      KC_QUOTE,   KC_LT,      KC_GT,      KC_DQT,     KC_DOT,     KC_NO,  KC_NO,      KC_AMPR,  KC_LBRC,      KC_RBRC,    KC_PERC,    KC_NO,
        KC_NO,      KC_CIRC,    KC_PMNS,    KC_PPLS,    KC_EQL,     KC_DLR,     KC_NO,  KC_NO,      KC_PIPE,  KC_LPRN,      KC_RPRN,    KC_AT,      KC_HASH,    KC_NO,
        KC_NO,      KC_GRV,     KC_NO,      KC_PSLS,    KC_PAST,    KC_BSLS,    UPDIR,  KC_NO,      KC_NO,    KC_TILD,      KC_LCBR,    KC_RCBR,    KC_NO,
        KC_NO,      KC_EXLM,    KC_NO,                              KC_SPC,                                                 KC_NO,      KC_NO,      KC_NO,      KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            }
            return false;
        case CUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x"));
            }
            return false;
        case PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("v"));
            }
            return false;
        case UPDIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
    }
    return true;
}

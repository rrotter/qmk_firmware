#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _COLEMAK,
  _NUM,
  _FN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      // opt-<letter> adds umlaut to a,o,u
      case KC_A:
      case KC_O:
      case KC_U:
      if (record->event.pressed) {
        uint8_t mods = get_mods();
        if (mods & MOD_MASK_ALT && !(mods & MOD_MASK_GUI)) {
          set_mods(mods & ~MOD_MASK_ALT & ~MOD_MASK_SHIFT);
          SEND_STRING(SS_ROPT("u"));
          set_mods(mods & ~MOD_MASK_ALT);
          tap_code(keycode);
          set_mods(mods);
          return false;
        }
      }
      break;
      // opt-<letter> adds accent to e
      case KC_E:
      if (record->event.pressed) {
        uint8_t mods = get_mods();
        if (mods & MOD_MASK_ALT && !(mods & MOD_MASK_GUI)) {
          set_mods(mods & ~MOD_MASK_ALT & ~MOD_MASK_SHIFT);
          SEND_STRING(SS_ROPT("e"));
          set_mods(mods & ~MOD_MASK_ALT);
          tap_code(keycode);
          set_mods(mods);
          return false;
        }
      }
      break;    
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak-DH-ish
 * ,-----------------------------------------------------------------------------------.
 * | esc  |   (  |   )  |   -  |   =  |   @  |   ^  |   $  |   /  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   !  |delete|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ctl  |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | shift|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |  up  |shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |          |   num   | opt  | cmd  |return|space |  opt |  cmd | left | down |right |
 * `-----------------------------------------------------------------------------------'
 */

[_COLEMAK] = LAYOUT_preonic_grid(
  KC_ESC,  KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,  KC_AT,   KC_CIRC, KC_DLR,  KC_SLSH, KC_LBRC, KC_RBRC, KC_BSLS,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_EXLM, KC_BSPC,
  KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
  XXXXXXX, XXXXXXX, MO(_NUM),KC_LOPT, KC_LCMD, KC_ENT,  KC_SPC,  KC_RCMD, KC_ROPT, KC_LEFT, KC_DOWN, KC_RGHT
),

/* num
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |      | del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  0   |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   0  |   .  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______,
  _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  _______, _______, _______
)

};

/* Overrides
 * ,-----------------------------------------------------------------------------------.
 * | ~   `| <  ‹ | >  › |      |      | #    | &  ¶ | %    | *  ° | {  ‚ | }  ‘ | |  ’ |
 * |esc  `| (  « | )  » |      |      | @  £ | ^  § | $  € | /  • | [  „ | ]  “ | \  ” |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | ?    |      |
 * |      |      |      |      |      |      |      |      |      |      | !    |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | ;    | :    |      |
 * |      |      |      |      |      |      |      |      |      | ,    | .    |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |          |         |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

// remap cmd-opt-[] to sft-opt-[]
const key_override_t b_1  = ko_make_with_layers_and_negmods(MOD_MASK_AG, KC_LBRC, G(S(KC_LBRC)),     ~0, MOD_MASK_SHIFT);
const key_override_t b_2  = ko_make_with_layers_and_negmods(MOD_MASK_AG, KC_RBRC, G(S(KC_RBRC)),     ~0, MOD_MASK_SHIFT);

// esc/~
const key_override_t e_1  = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_ESC, A(KC_GRV),       ~0, MOD_MASK_GUI);
const key_override_t e_2  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_ESC, KC_TILD,         ~0, MOD_MASK_GUI);
const key_override_t e_3  = ko_make_basic(MOD_MASK_GUI,   KC_ESC, G(KC_GRV));
const key_override_t e_4  = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_ESC, KC_GRV,          ~0, MOD_MASK_GUI);

// remap cmd/opt for symbol keys
const key_override_t o_1  = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_AT,    A(KC_3),       ~0, MOD_MASK_GUI);
const key_override_t o_2  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_AT,    KC_HASH,       ~0, MOD_MASK_GUI);
const key_override_t o_3  = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_AT,    A(KC_3),       ~0, MOD_MASK_GUI);
const key_override_t o_4  = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_BSLS,  S(A(KC_RBRC)), ~0, MOD_MASK_GUI);
const key_override_t o_5  = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_BSLS,  S(A(KC_LBRC)), ~0, MOD_MASK_GUI);
const key_override_t o_6  = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_CIRC,  A(KC_7),       ~0, MOD_MASK_GUI);
const key_override_t o_7  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_CIRC,  KC_AMPR,       ~0, MOD_MASK_GUI);
const key_override_t o_8  = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_CIRC,  A(KC_6),       ~0, MOD_MASK_GUI);
const key_override_t o_9  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_COMM,  KC_SCLN,       ~0, MOD_MASK_AG);
const key_override_t o_10 = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_COMM,  A(KC_SCLN),    ~0, MOD_MASK_GUI);
const key_override_t o_11 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_COMM,  A(KC_SCLN),    ~0, MOD_MASK_GUI);
const key_override_t o_12 = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_DLR,   KC_PERC,       ~0, MOD_MASK_ALT);
const key_override_t o_13 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_DLR,   S(A(KC_2)),    ~0, MOD_MASK_GUI);
const key_override_t o_14 = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_DOT,   KC_COLN,       ~0, MOD_MASK_AG);
const key_override_t o_15 = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_DOT,   A(KC_SCLN),    ~0, MOD_MASK_GUI);
const key_override_t o_16 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_DOT,   A(KC_SCLN),    ~0, MOD_MASK_GUI);
const key_override_t o_17 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_EXLM,  A(KC_1),       ~0, MOD_MASK_SG);
const key_override_t o_18 = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_EXLM,  KC_QUES,       ~0, MOD_MASK_GUI);
const key_override_t o_19 = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_LBRC,  S(A(KC_0)),    ~0, MOD_MASK_GUI);
const key_override_t o_20 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_LBRC,  S(A(KC_W)),    ~0, MOD_MASK_GUI);
const key_override_t o_21 = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_LPRN,  KC_LT,         ~0, MOD_MASK_AG);
const key_override_t o_22 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_LPRN,  A(KC_BSLS),    ~0, MOD_MASK_SG);
const key_override_t o_23 = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_LPRN,  S(A(KC_3)),    ~0, MOD_MASK_GUI);
const key_override_t o_24 = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_RBRC,  A(KC_RBRC),    ~0, MOD_MASK_GUI);
const key_override_t o_25 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_RBRC,  A(KC_LBRC),    ~0, MOD_MASK_GUI);
const key_override_t o_26 = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_RPRN,  KC_GT,         ~0, MOD_MASK_AG);
const key_override_t o_27 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_RPRN,  S(A(KC_BSLS)), ~0, MOD_MASK_SG);
const key_override_t o_28 = ko_make_with_layers_and_negmods(MOD_MASK_SA,    KC_RPRN,  S(A(KC_4)),    ~0, MOD_MASK_GUI);
const key_override_t o_29 = ko_make_with_layers_and_negmods(MOD_MASK_ALT,   KC_SLSH,  A(KC_8),       ~0, MOD_MASK_GUI);
const key_override_t o_30 = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_SLSH,  KC_ASTR,       ~0, MOD_MASK_GUI);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
  &b_1,  &b_2,
  &e_1,  &e_2,  &e_3,  &e_4,
  &o_1,  &o_2,  &o_3,  &o_4,  &o_5,  &o_6,  &o_7,  &o_8,  &o_9,  &o_10,
  &o_11, &o_12, &o_13, &o_14, &o_15, &o_16, &o_17, &o_18, &o_19, &o_20,
  &o_21, &o_22, &o_23, &o_24, &o_25, &o_26, &o_27, &o_28, &o_29, &o_30,
  NULL // Null terminate the array of overrides!
};


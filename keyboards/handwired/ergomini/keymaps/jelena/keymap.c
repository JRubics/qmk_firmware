#include "ergomini.h"

#define _QWE 0 // qwerty layout
#define _NUM 1 // numpad
#define _FN 2 // function
#define _RGB 3 // RGB

#define _____ KC_TRNS
#define XXXXX KC_NO

enum custom_keycodes {
    M_PASS = SAFE_RANGE, M_PWD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Keymap 0: QWERTY layer
	*
	* ,-----------------------------------------------------------------------------------.
	* |   `    |  1  |  2  |  3  |  4  |  5  |  =  |  6  |  7  |  8  |  9  |  0  |   -    |
	* |--------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
	* |  Tab   |  Q  |  W  |  E  |  R  |  T  |  (  |  Y  |  U  |  I  |  O  |  P  |   '    |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |Esc/Ctrl|  A  |  S  |  D  |  F  |  G  |-----|  H  |  J  |  K  |  L  |  ;  |  Enter |
	* |--------+-----+-----+-----+-----+-----|  )  |-----+-----+-----+-----+-----+--------|
	* | LShift |  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  \  | RShift |
	* |--------+-----+-----+-----+-----------+-----+-----------+-----+-----+-----+--------|
	* | QWERTY |     | LAlt| i3  |   Space   | Fn  | Backspace |  /  |PtScr|     |  Num   |
	* `-----------------------------------------------------------------------------------'
	*
	*/
	[_QWE] = KEYMAP(
			KC_ESC,		KC_1,			KC_2,			KC_3,			KC_4,			KC_5,			KC_EQL,		KC_6,			KC_7,			KC_8,			KC_9,			KC_0,			KC_MINS,
			KC_TAB,		KC_Q,			KC_W,			KC_E,			KC_R,			KC_T,			KC_LBRC,	KC_Y,			KC_U,			KC_I,			KC_O,			KC_P,			KC_QUOT,
			KC_LCTL,	KC_A,			KC_S,			KC_D,			KC_F,			KC_G,								KC_H,			KC_J,			KC_K,			KC_L,			KC_SCLN,	KC_ENT,
			KC_LSFT,	KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,			KC_RBRC,	KC_N,			KC_M,			KC_COMM,	KC_DOT,		KC_SLSH,	KC_RSFT,
			KC_LCTL,	KC_GRV,		KC_LALT,	KC_LGUI,			KC_BSPC,				MO(_FN),			KC_SPC,					KC_BSLS,	KC_PSCR,	MO(_FN),		TG(_RGB)
			),

	/* Keymap 1: Numpad Layer
	*
	* ,-----------------------------------------------------------------------------------.
	* |        |     |     |     |     |     |     |     |NMLCK|  /  |  *  |  -  |        |
	* |--------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
	* |        |     |     |     |     |     |     |     |  7  |  8  |  9  |  +  |        |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |        |     |     |     |     |     |-----|     |  4  |  5  |  6  |  +  |        |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |        |     |     |     |     |     |     |     |  1  |  2  |  3  | ENT |        |
	* |--------+-----+-----+-----+-----------+-----+-----------+-----+-----+-----+--------|
	* |        |     |     |     |           |     |           |  0  |  .  | ENT |        |
	* `-----------------------------------------------------------------------------------'
	*
	*/
	[_NUM] = KEYMAP(
			_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		KC_NLCK,	KC_PSLS,	KC_PAST,	KC_PMNS,	_____,
			_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		KC_P7,		KC_P8,		KC_P9,		KC_PPLS,	_____,
			_____,		_____,		_____,		_____,		_____,		_____,							_____,		KC_P4,		KC_P5,		KC_P6,		KC_PPLS,	_____,
			_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		KC_P1,		KC_P2,		KC_P3,		KC_ENT,		_____,
			_____,		_____,		_____,		_____,				_____,					_____,				_____,					KC_P0,		KC_PDOT,	KC_ENT,		_____
			),

	/* Keymap 2: Function Layer
	*
	* ,-----------------------------------------------------------------------------------.
	* |        | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 |  F12   |
	* |--------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
	* |        |Mute |Vol- |Vol+ |     |     |     |     |     |     |     |     |        |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |        |Play |Prev |Next |     |     |-----|  ←  |  ↓  |  ↑  |  →  |     |        |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |        |     |     |     |     |     |     |Home |PgUp |PgDn | End |     |        |
	* |--------+-----+-----+-----+-----------+-----+-----------+-----+-----+-----+--------|
	* |        |     |     |     |  Delete   |     |  Delete   |     |     |     |        |
	* `-----------------------------------------------------------------------------------'
	*
	*/
	[_FN] = KEYMAP(
			RESET,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,
			_____,		KC_MUTE,	KC_VOLD,	KC_VOLU,	XXXXX,		XXXXX,		_____,		XXXXX,		XXXXX,		KC_UP,		M_PWD,		M_PASS,		KC_HOME,
			_____,		KC_MPLY,	KC_MPRV,	KC_MNXT,	XXXXX,		XXXXX,							XXXXX,		KC_LEFT,	KC_DOWN,	KC_RGHT,	XXXXX,		KC_END,
			_____,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		_____,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		KC_PGUP,
			_____,		_____,		_____,		_____,				KC_DEL,					_____,				KC_DEL,					_____,		TG(_RGB),	_____,	KC_PGDN
			),

	/* Keymap 3: RGB Layer
	*
	* ,-----------------------------------------------------------------------------------.
	* |        | H+  | S+  | V+  |     |     |     |     |     |     |     |     |        |
	* |--------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
	* |        | H-  | S-  | V-  |     |     |     |     |     |     |     |     |        |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |        | Tog | Mod |     |     |     |-----|     |     |     |     |     |        |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |        |     |     |     |     |     |     |     |     |     |     |     |        |
	* |--------+-----+-----+-----+-----------+-----+-----------+-----+-----+-----+--------|
	* |        |     |     |     |           |     |           |     |     |     |        |
	* `-----------------------------------------------------------------------------------'
	*
	*/
	[_RGB] = KEYMAP(
			_____,		RGB_HUI,	RGB_SAI,	RGB_VAI,	_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,
			_____,		RGB_HUD,	RGB_SAD,	RGB_VAD,	_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,
			_____,		RGB_TOG,	RGB_SMOD,	_____,		_____,		_____,							_____,		_____,		_____,		_____,		_____,		_____,
			_____,		RGB_M_P,	RGB_M_B,	RGB_M_R,	_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,
			_____,		RGB_M_SW,	RGB_M_K,	RGB_M_G,			_____,					_____,				_____,					_____,		_____,		_____,		_____
			),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case M_PASS:
				SEND_STRING("password");
				return false;
			case M_PWD:
				SEND_STRING("password1");
				return false;
		}
	}

	return true;
};

void matrix_init_user(void) {
};

void matrix_scan_user(void) {
};

/*
* ,-----------------------------------------------------------------------------------.
* |        |     |     |     |     |     |     |     |     |     |     |     |        |
* |--------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
* |        |     |     |     |     |     |     |     |     |     |     |     |        |
* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
* |        |     |     |     |     |     |-----|     |     |     |     |     |        |
* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
* |        |     |     |     |     |     |     |     |     |     |     |     |        |
* |--------+-----+-----+-----+-----------+-----+-----------+-----+-----+-----+--------|
* |        |     |     |     |           |     |           |     |     |     |        |
* `-----------------------------------------------------------------------------------'
*/
// vim: ts=2 sw=2 sts=2 noet


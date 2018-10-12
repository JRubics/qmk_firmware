#include "ergomini.h"

#define _COL 0 // default layer
#define _QWE 1 // qwerty layout
#define _NUM 2 // numpad
#define _FN 3 // function
#define _RGB 4 // RGB
#define _PWD 5 // Password

#define _____ KC_TRNS
#define XXXXX KC_NO

#define PW_OFFSET_SPC 32
#define PW_OFFSET_NUM 48
#define PW_OFFSET_LET 65

#define PW_BUFFER_SIZE 32

#define SECRET_KEY "b6404b71a891f094"

enum custom_keycodes {
	ARW = SAFE_RANGE,
	PW_SPC = SAFE_RANGE + PW_OFFSET_SPC, PW_BSPC, PW_ENT, PW_RST, // Special characters
	PW_0 = SAFE_RANGE + PW_OFFSET_NUM, PW_1, PW_2, PW_3, PW_4, PW_5, PW_6, PW_7, PW_8, PW_9, // Numbers
	PW_A = SAFE_RANGE + PW_OFFSET_LET, PW_B, PW_C, PW_D, PW_E, PW_F, // Letters
	PW_G, PW_H, PW_I, PW_J, PW_K, PW_L, PW_M, PW_N, PW_O, PW_P,
	PW_Q, PW_R, PW_S, PW_T, PW_U, PW_V, PW_W, PW_X, PW_Y, PW_Z,
};

const char* password = "testpass";
char pw_buffer[PW_BUFFER_SIZE];
char* p;

void handle_pw(uint16_t keycode, bool shift);
bool check_pw(void);
void reset_pw_buffer(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Keymap 1: Base layer
	*
	* ,-----------------------------------------------------------------------------------.
	* |   `    |  1  |  2  |  3  |  4  |  5  |  =  |  6  |  7  |  8  |  9  |  0  |   -    |
	* |--------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
	* |  Tab   |  Q  |  W  |  F  |  P  |  G  |  (  |  J  |  L  |  U  |  Y  |  ;  |   '    |
	* |--------+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+--------|
	* |Esc/Ctrl|  A  |  R  |  S  |  T  |  D  |-----|  H  |  N  |  E  |  I  |  O  |  Enter |
	* |--------+-----+-----+-----+-----+-----|  )  |-----+-----+-----+-----+-----+--------|
	* | LShift |  Z  |  X  |  C  |  V  |  B  |     |  K  |  M  |  ,  |  .  |  \  | RShift |
	* |--------+-----+-----+-----+-----------+-----+-----------+-----+-----+-----+--------|
	* | QWERTY |     | LAlt| i3  |   Space   | Fn  | Backspace |  /  |PtScr|     |  Num   |
	* `-----------------------------------------------------------------------------------'
	*
	*/
	[_COL] = KEYMAP(
			KC_GRV,		KC_1,			KC_2,			KC_3,			KC_4,			KC_5,			KC_EQL,		KC_6,			KC_7,			KC_8,			KC_9,			KC_0,			KC_MINS,
			KC_TAB,		KC_Q,			KC_W,			KC_F,			KC_P,			KC_G,			KC_LPRN,	KC_J,			KC_L,			KC_U,			KC_Y,			KC_SCLN,	KC_QUOT,
			KC_LCTL,	KC_A,			KC_R,			KC_S,			KC_T,			KC_D,								KC_H,			KC_N,			KC_E,			KC_I,			KC_O,			KC_ENT,
			KC_LSFT,	KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,			KC_RPRN,	KC_K,			KC_M,			KC_COMM,	KC_DOT,		KC_BSLS,	KC_RSFT,
			TG(_QWE),	KC_ESC,		KC_LALT,	KC_LGUI,			KC_SPC,					MO(_FN),			KC_BSPC,				KC_SLSH,	KC_PSCR,	KC_APP,		TG(_NUM)
			),

	/* Keymap 1: QWERTY layer
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
			_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,		_____,
			_____,		KC_Q,			KC_W,			KC_E,			KC_R,			KC_T,			_____,		KC_Y,			KC_U,			KC_I,			KC_O,			KC_P,			_____,
			_____,		KC_A,			KC_S,			KC_D,			KC_F,			KC_G,								KC_H,			KC_J,			KC_K,			KC_L,			KC_SCLN,	_____,
			_____,		KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,			_____,		KC_N,			KC_M,			_____,		_____,		_____,		_____,
			_____,		_____,		_____,		_____,				_____,					_____,				_____,					_____,		_____,		_____,		_____
			),

	/* Keymap 2: Numpad Layer
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

	/* Keymap 3: Function Layer
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
	* |        |     |     |     |  Delete   |     |           |     |     |     |        |
	* `-----------------------------------------------------------------------------------'
	*
	*/
	[_FN] = KEYMAP(
			RESET,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,
			_____,		KC_MUTE,	KC_VOLD,	KC_VOLU,	XXXXX,		XXXXX,		KC_LBRC,	XXXXX,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		_____,
			_____,		KC_MPLY,	KC_MPRV,	KC_MNXT,	XXXXX,		XXXXX,							KC_LEFT,	KC_DOWN,	KC_UP,		KC_RGHT,	XXXXX,		_____,
			_____,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		XXXXX,		KC_RBRC,	KC_HOME,	KC_PGDN,	KC_PGUP,	KC_END,		XXXXX,		_____,
			TG(_PWD),	_____,		_____,		_____,				KC_DEL,					_____,				_____,					_____,		_____,		TG(_RGB),	_____
			),

	/* Keymap 4: RGB Layer
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

	/* Keymap 5: Password Layer */
	[_PWD] = KEYMAP(
			XXXXX,		PW_1,			PW_2,			PW_3,			PW_4,			PW_5,			XXXXX,		PW_6,			PW_7,			PW_8,			PW_9,			PW_0,			XXXXX,
			XXXXX,		PW_Q,			PW_W,			PW_F,			PW_P,			PW_G,			XXXXX,		PW_J,			PW_L,			PW_U,			PW_Y,			XXXXX,		XXXXX,
			XXXXX,		PW_A,			PW_R,			PW_S,			PW_T,			PW_D,								PW_H,			PW_N,			PW_E,			PW_I,			PW_O,			PW_ENT,
			_____,		PW_Z,			PW_X,			PW_C,			PW_V,			PW_B,			XXXXX,		PW_K,			PW_M,			XXXXX,		XXXXX,		XXXXX,		_____,
			_____,		XXXXX,		XXXXX,		XXXXX,				PW_SPC,					PW_RST,				PW_BSPC,				XXXXX,		XXXXX,		XXXXX,		XXXXX
			),
};

void handle_pw(uint16_t keycode, bool shift) {
	if (keycode == PW_BSPC - SAFE_RANGE) {
		if (p == pw_buffer) {
			return;
		}

		p--;
		*p = 0;
	} else if (keycode == PW_RST - SAFE_RANGE) {
		reset_pw_buffer();
	} else if (keycode == PW_ENT - SAFE_RANGE) {
		if (check_pw()) {
			SEND_STRING(SECRET_KEY);
		}
		reset_pw_buffer();
	} else {
		if (p >= pw_buffer + PW_BUFFER_SIZE) {
			return;
		}
		if (keycode == 32) {
			*p = ' ';
		} else if (keycode >= '0' && keycode <= '9') {
			*p = (char)keycode;
		} else {
			*p = (shift) ? (char)keycode : (char)(keycode + 32);
		}
		p++;
	}
}

bool check_pw(void) {
	uint8_t i = 0;

	do {
		if (pw_buffer[i] != password[i]) {
			return false;
		}
		i++;
	} while (pw_buffer[i] != 0);

	return true;
}

void reset_pw_buffer(void) {
	uint8_t i;
	p = pw_buffer;

	for (i = 0; i < PW_BUFFER_SIZE; i++) {
		pw_buffer[i] = 0;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (keycode >= SAFE_RANGE + PW_OFFSET_SPC) {
		static bool lshift = false;
		static bool rshift = false;

		lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
		rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);

		if (record->event.pressed) {
			handle_pw(keycode - SAFE_RANGE, lshift || rshift);
		}
		return false;
	}
	return true;
};

void matrix_init_user(void) {
	reset_pw_buffer();
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


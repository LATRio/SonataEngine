#pragma once

// Keycodes from GLFW 3.4

/* Printable keys */
#define SN_KEY_SPACE                32
#define SN_KEY_APOSTROPHE           39  /* ' */
#define SN_KEY_COMMA                44  /* , */
#define SN_KEY_MINUS                45  /* - */
#define SN_KEY_PERIOD               46  /* . */
#define SN_KEY_SLASH                47  /* / */
#define SN_KEY_0                    48
#define SN_KEY_1                    49
#define SN_KEY_2                    50
#define SN_KEY_3                    51
#define SN_KEY_4                    52
#define SN_KEY_5                    53
#define SN_KEY_6                    54
#define SN_KEY_7                    55
#define SN_KEY_8                    56
#define SN_KEY_9                    57
#define SN_KEY_SEMICOLON            59  /* ; */
#define SN_KEY_EQUAL                61  /* = */
#define SN_KEY_A                    65
#define SN_KEY_B                    66
#define SN_KEY_C                    67
#define SN_KEY_D                    68
#define SN_KEY_E                    69
#define SN_KEY_F                    70
#define SN_KEY_G                    71
#define SN_KEY_H                    72
#define SN_KEY_I                    73
#define SN_KEY_J                    74
#define SN_KEY_K                    75
#define SN_KEY_L                    76
#define SN_KEY_M                    77
#define SN_KEY_N                    78
#define SN_KEY_O                    79
#define SN_KEY_P                    80
#define SN_KEY_Q                    81
#define SN_KEY_R                    82
#define SN_KEY_S                    83
#define SN_KEY_T                    84
#define SN_KEY_U                    85
#define SN_KEY_V                    86
#define SN_KEY_W                    87
#define SN_KEY_X                    88
#define SN_KEY_Y                    89
#define SN_KEY_Z                    90
#define SN_KEY_LEFT_BRACKET         91  /* [ */
#define SN_KEY_BACKSLASH            92  /* \ */
#define SN_KEY_RIGHT_BRACKET        93  /* ] */
#define SN_KEY_GRAVE_ACCENT         96  /* ` */
#define SN_KEY_WORLD_1              161 /* non-US #1 */
#define SN_KEY_WORLD_2              162 /* non-US #2 */

/* Function keys */
#define SN_KEY_ESCAPE               256
#define SN_KEY_ENTER                257
#define SN_KEY_TAB                  258
#define SN_KEY_BACKSPACE            259
#define SN_KEY_INSERT               260
#define SN_KEY_DELETE               261
#define SN_KEY_RIGHT                262
#define SN_KEY_LEFT                 263
#define SN_KEY_DOWN                 264
#define SN_KEY_UP                   265
#define SN_KEY_PAGE_UP              266
#define SN_KEY_PAGE_DOWN            267
#define SN_KEY_HOME                 268
#define SN_KEY_END                  269
#define SN_KEY_CAPS_LOCK            280
#define SN_KEY_SCROLL_LOCK          281
#define SN_KEY_NUM_LOCK             282
#define SN_KEY_PRINT_SCREEN         283
#define SN_KEY_PAUSE                284
#define SN_KEY_F1                   290
#define SN_KEY_F2                   291
#define SN_KEY_F3                   292
#define SN_KEY_F4                   293
#define SN_KEY_F5                   294
#define SN_KEY_F6                   295
#define SN_KEY_F7                   296
#define SN_KEY_F8                   297
#define SN_KEY_F9                   298
#define SN_KEY_F10                  299
#define SN_KEY_F11                  300
#define SN_KEY_F12                  301
#define SN_KEY_F13                  302
#define SN_KEY_F14                  303
#define SN_KEY_F15                  304
#define SN_KEY_F16                  305
#define SN_KEY_F17                  306
#define SN_KEY_F18                  307
#define SN_KEY_F19                  308
#define SN_KEY_F20                  309
#define SN_KEY_F21                  310
#define SN_KEY_F22                  311
#define SN_KEY_F23                  312
#define SN_KEY_F24                  313
#define SN_KEY_F25                  314
#define SN_KEY_KP_0                 320
#define SN_KEY_KP_1                 321
#define SN_KEY_KP_2                 322
#define SN_KEY_KP_3                 323
#define SN_KEY_KP_4                 324
#define SN_KEY_KP_5                 325
#define SN_KEY_KP_6                 326
#define SN_KEY_KP_7                 327
#define SN_KEY_KP_8                 328
#define SN_KEY_KP_9                 329
#define SN_KEY_KP_DECIMAL           330
#define SN_KEY_KP_DIVIDE            331
#define SN_KEY_KP_MULTIPLY          332
#define SN_KEY_KP_SUBTRACT          333
#define SN_KEY_KP_ADD               334
#define SN_KEY_KP_ENTER             335
#define SN_KEY_KP_EQUAL             336
#define SN_KEY_LEFT_SHIFT           340
#define SN_KEY_LEFT_CONTROL         341
#define SN_KEY_LEFT_ALT             342
#define SN_KEY_LEFT_SUPER           343
#define SN_KEY_RIGHT_SHIFT          344
#define SN_KEY_RIGHT_CONTROL        345
#define SN_KEY_RIGHT_ALT            346
#define SN_KEY_RIGHT_SUPER          347
#define SN_KEY_MENU                 348

#define SN_KEY_LAST                 SN_KEY_MENU

/* Modifier keys */
#define SN_MOD_SHIFT                0x0001
#define SN_MOD_CONTROL              0x0002
#define SN_MOD_ALT                  0x0004
#define SN_MOD_SUPER                0x0008
#define SN_MOD_CAPS_LOCK            0x0010
#define SN_MOD_NUM_LOCK             0x0020

/* Mouse buttons */
#define SN_MOUSE_BUTTON_1           0
#define SN_MOUSE_BUTTON_2           1
#define SN_MOUSE_BUTTON_3           2
#define SN_MOUSE_BUTTON_4           3
#define SN_MOUSE_BUTTON_5           4
#define SN_MOUSE_BUTTON_6           5
#define SN_MOUSE_BUTTON_7           6
#define SN_MOUSE_BUTTON_8           7
#define SN_MOUSE_BUTTON_LAST        SN_MOUSE_BUTTON_8
#define SN_MOUSE_BUTTON_LEFT        SN_MOUSE_BUTTON_1
#define SN_MOUSE_BUTTON_RIGHT       SN_MOUSE_BUTTON_2
#define SN_MOUSE_BUTTON_MIDDLE      SN_MOUSE_BUTTON_3

/* Joystick buttons */
#define SN_JOYSTICK_1               0
#define SN_JOYSTICK_2               1
#define SN_JOYSTICK_3               2
#define SN_JOYSTICK_4               3
#define SN_JOYSTICK_5               4
#define SN_JOYSTICK_6               5
#define SN_JOYSTICK_7               6
#define SN_JOYSTICK_8               7
#define SN_JOYSTICK_9               8
#define SN_JOYSTICK_10              9
#define SN_JOYSTICK_11              10
#define SN_JOYSTICK_12              11
#define SN_JOYSTICK_13              12
#define SN_JOYSTICK_14              13
#define SN_JOYSTICK_15              14
#define SN_JOYSTICK_16              15
#define SN_JOYSTICK_LAST            SN_JOYSTICK_16

/* Gamepad buttons */
#define SN_GAMEPAD_BUTTON_A                 0
#define SN_GAMEPAD_BUTTON_B                 1
#define SN_GAMEPAD_BUTTON_X                 2
#define SN_GAMEPAD_BUTTON_Y                 3
#define SN_GAMEPAD_BUTTON_LEFT_BUMPER       4
#define SN_GAMEPAD_BUTTON_RIGHT_BUMPER      5
#define SN_GAMEPAD_BUTTON_BACK              6
#define SN_GAMEPAD_BUTTON_START             7
#define SN_GAMEPAD_BUTTON_GUIDE             8
#define SN_GAMEPAD_BUTTON_LEFT_THUMB        9
#define SN_GAMEPAD_BUTTON_RIGHT_THUMB       10
#define SN_GAMEPAD_BUTTON_DPAD_UP           11
#define SN_GAMEPAD_BUTTON_DPAD_RIGHT        12
#define SN_GAMEPAD_BUTTON_DPAD_DOWN         13
#define SN_GAMEPAD_BUTTON_DPAD_LEFT         14
#define SN_GAMEPAD_BUTTON_LAST              SN_GAMEPAD_BUTTON_DPAD_LEFT

#define SN_GAMEPAD_BUTTON_CROSS             SN_GAMEPAD_BUTTON_A
#define SN_GAMEPAD_BUTTON_CIRCLE            SN_GAMEPAD_BUTTON_B
#define SN_GAMEPAD_BUTTON_SQUARE            SN_GAMEPAD_BUTTON_X
#define SN_GAMEPAD_BUTTON_TRIANGLE          SN_GAMEPAD_BUTTON_Y

/* Gamepad axes */
#define SN_GAMEPAD_AXIS_LEFT_X              0
#define SN_GAMEPAD_AXIS_LEFT_Y              1
#define SN_GAMEPAD_AXIS_RIGHT_X             2
#define SN_GAMEPAD_AXIS_RIGHT_Y             3
#define SN_GAMEPAD_AXIS_LEFT_TRIGGER        4
#define SN_GAMEPAD_AXIS_RIGHT_TRIGGER       5
#define SN_GAMEPAD_AXIS_LAST                SN_GAMEPAD_AXIS_RIGHT_TRIGGER
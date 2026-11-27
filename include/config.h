#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#include <stdio.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>

#include <types/rule.h>
#include <types/input.h>
#include <enums/colorscheme.h>
#include <enums/cliks.h>

#include <api/layout.h>
#include <api/commands.h>
#include <api/movestack.h>
#include <api/scrollcompat.h>
#include <local/mouse_actions.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#fe8019";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
/* last tag is the hidden scratchpad, not a workspace */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "S" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* equal-width master/stack columns */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 144;  /* refresh rate (per second) for client move/resize */

#include <types/monitor.h>
#ifdef DWM_CONFIG_LAYOUTS
const Layout layouts[] = { //see include/types/monitor.h
	/*symbol      layout      attach       push_focus  detach  detach_stack     pop   restack*/
	{ ">>>",      scrolltile, attachaside, NULL,       NULL,   NULL,            NULL, NULL },
	{ "[]=",      tile,       NULL,        NULL,       NULL,   NULL,            NULL, NULL },
	{ "[\\]",     dwindle,    NULL,        NULL,       NULL,   NULL,            NULL, NULL },
	//{ "><>",    NULL,       NULL,        NULL,       NULL,   NULL,            NULL, NULL },
	//{ "[M]",    monocle,    NULL,        NULL,       NULL,   NULL,            NULL, NULL },
	//{ "[@]",    spiral,     NULL,        NULL,       NULL,   NULL,            NULL, NULL },
};

size_t
layoutcount(void) {
	return sizeof layouts / sizeof layouts[0];
}
#else
extern const Layout layouts[];
size_t layoutcount(void);
#endif

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "sh", "-c", "rofi -show drun -theme ~/.config/rofi/launcher.rasi", NULL };
static const char *termcmd[]    = { "kitty", NULL }; /* Поменяй на свой терминал */
static const char *filemgrcmd[] = { "nautilus", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* applications (as in scroll) */
	{ MODKEY,                       XK_Return,     spawn,           {.v = termcmd } },
	{ MODKEY,                       XK_d,          spawn,           {.v = dmenucmd } },
	{ MODKEY,                       XK_e,          spawn,           {.v = filemgrcmd } },
	{ MODKEY,                       XK_v,          spawn,           SHCMD("$HOME/.local/bin/xclip-history-menu") },

	/* screenshots */
	{ ControlMask,                  XK_Print,      spawn,           SHCMD("maim -s | magick - -monochrome png:- | xclip -selection clipboard -t image/png") },
	{ MODKEY,                       XK_Print,      spawn,           SHCMD("flameshot gui") },
	{ 0,                            XK_Print,      spawn,           SHCMD("maim | xclip -selection clipboard -t image/png") },

	/* session */
	{ Mod1Mask,                     XK_F4,         killclient,      {0} },
	{ MODKEY|ShiftMask,             XK_c,          spawn,           SHCMD("pkill -x dwm") },
	{ MODKEY|ShiftMask,             XK_e,          spawn,           SHCMD("touch $HOME/.dwm-exit; pkill -x dwm") },

	/* workspaces: Mod+1..0 view, Mod+Ctrl+1..0 toggle, Mod+Shift+1..0 move */
	{ MODKEY,                       XK_Up,         shiftview,       {.i = -1 } },
	{ MODKEY,                       XK_Down,       shiftview,       {.i = +1 } },
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
	TAGKEYS(XK_0, 9)

	/* focus / move containers — endless ribbon inside current workspace */
	{ MODKEY,                       XK_Left,       cyclefocus,      {.i = -1 } },
	{ MODKEY,                       XK_Right,      cyclefocus,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,       movestack,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,      movestack,       {.i = +1 } },

	/* layouts / window state */
	{ MODKEY,                       XK_1,          scrollmax,       {0} },
	{ MODKEY,                       XK_s,          setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,          setlayout,       {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,          togglefloating,  {0} },
	{ MODKEY,                       XK_space,      togglefocusmode, {0} },
	{ MODKEY,                       XK_F11,        togglefullscr,   {0} },
	{ MODKEY,                       XK_r,          toggleresizemode,{0} },

	/* scratchpad (hidden last tag) */
	{ MODKEY|ShiftMask,             XK_minus,      scratchpush,     {0} },
	{ MODKEY,                       XK_minus,      scratchshow,     {0} },

	/* audio / media / brightness (same keys as scroll) */
	{ 0, XF86XK_AudioMute,        spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	{ 0, XF86XK_AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
	{ 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
	{ 0, XF86XK_AudioMicMute,     spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_AudioPlay,        spawn, SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioPause,       spawn, SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioPrev,        spawn, SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,        spawn, SHCMD("playerctl next") },
	{ 0, XF86XK_AudioStop,        spawn, SHCMD("playerctl stop") },
	{ 0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 5%-") },
	{ 0, XF86XK_MonBrightnessUp,   spawn, SHCMD("brightnessctl set 5%+") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        cyclefocus,     {.i = -1 } },
	{ ClkClientWin,         MODKEY,         Button5,        cyclefocus,     {.i = +1 } },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

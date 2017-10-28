Wlinfo queries Wayland for information about physical displays connected to the
system. It can print information about the physical dimensions of such displays,
and screen resolution, and display scaling characteristics.

My personal motivation for this code is to allow Emacs instances to pick an
appropriate font size. This is necessary because I have a high-DPI laptop
screen, and a low-DPI monitor that I sometimes attach to my laptop. Wayland
itself supports per-monitor display scaling, so it can scale the high-DPI
monitor at 2x (for instance), and the low-DPI monitor at 1x. However, Emacs is a
legacy X11 application that can't do display scaling. Therefore I need my Emacs
instance to choose an appropriate font size based on which physical displays are
actually connected to the system at the time that Emacs starts up.

This code is released under a version of the MIT license used by X11. This is
the same license used by Wayland and Weston. Some of this code is derived from
code found in Weston (in particular, the code for `weston-info`).

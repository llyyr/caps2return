# caps2return

caps2return is an [Interception Tools](https://gitlab.com/interception/linux/tools) plugin that changes KEY_CAPSLOCK events to KEY_ENTER events and maps LCTRL+CAPSLOCK to CAPSLOCK. Works on Wayland/X11/TTY.

## Install

Compile and place the binary within `$PATH`.

``` shell
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

## Usage

`caps2return` is an [Interception Tools](https://gitlab.com/interception/linux/tools) plugin. Refer to _Interception Tools_'s README for more information. Suggested `udevmon` configuration:

``` yaml
- JOB: intercept -g $DEVNODE | caps2return | uinput -d $DEVNODE
  DEVICE:
    EVENTS:
      EV_KEY: [KEY_CAPSLOCK, KEY_LEFTCTRL]
```


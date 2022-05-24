#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

int read_event(struct input_event *event)
{
    return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

void write_event(const struct input_event *event)
{
    if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

int main()
{
    struct input_event input;
    const struct input_event
        syn = {.type = EV_SYN, .code = SYN_REPORT, .value = 0},
        capslock_up = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 0},
        capslock_down = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 1};
    enum {
        START, 
        CTRL_HELD 
    } state = START;
    setbuf(stdin, NULL), setbuf(stdout, NULL);

    while (read_event(&input)) {
        if (input.type == EV_MSC && input.code == MSC_SCAN)
            continue;
        switch (state) {
            case START:
                if (input.type == EV_KEY && input.code == KEY_LEFTCTRL && input.value == 1)
                    state = CTRL_HELD;
                if (input.type == EV_KEY && input.code == KEY_CAPSLOCK)
                    input.code = KEY_ENTER;
                break;
            case CTRL_HELD:
                if (input.type == EV_KEY && input.code == KEY_CAPSLOCK && input.value == 1) {
                    write_event(&capslock_down);
                    write_event(&syn);
                    write_event(&capslock_up);
                    continue;
                }
                if (input.type == EV_KEY && input.code == KEY_CAPSLOCK && input.value == 0)
                    continue;
                if (input.type == EV_KEY && input.code == KEY_LEFTCTRL && input.value == 0)
                    state = START;
                break;
        }
        write_event(&input);
    }
}


## Build
From the repo root:

```bash
make
```

This builds all demos into `build/`. To build only the signal demos:

```bash
make -C IPC/signals
```

## Run (signals)
```bash
./build/IPC/signals/ctrl_c
./build/IPC/signals/raise
./build/IPC/signals/kill_recv
./build/IPC/signals/kill_sender
```

Notes:
- `kill_sender` currently sends `SIGUSR1` to hardcoded PID `5939`. Update `IPC/signals/kill_sender.c` or use `kill -USR1 <pid>` from another terminal.
- You can run `kill_recv` in background to capture its PID, e.g. `./build/IPC/signals/kill_recv & echo $!`.

## Learner Notes: Linux Signals (short)
Signals are lightweight, asynchronous notifications used by the kernel or other processes to tell a process that something happened. A signal has a default action (terminate, ignore, stop, etc.), but many signals can be handled with a custom handler.

What the demos show:
- `ctrl_c`: registers handlers for `SIGINT` (Ctrl+C) and `SIGABRT` (from `abort()`), then exits cleanly after printing a message.
- `raise`: registers a handler and calls `raise(SIGINT)` to send a signal to itself.
- `kill_recv` + `kill_sender`: one process installs a `SIGUSR1` handler, another sends `SIGUSR1` using `kill()`.

As a learner, the key takeaway is that signals interrupt normal flow and jump to the handler, so handlers should be short and safe. Also, `SIGKILL` and `SIGSTOP` cannot be handled.

## Sample Logs
`ctrl_c` (Ctrl+C):
```
$ ./build/IPC/signals/ctrl_c
Abort process (y/n) ?
n
^C
Ctrl-C pressed
Bye Bye
```

`ctrl_c` (abort):
```
$ ./build/IPC/signals/ctrl_c
Abort process (y/n) ?
y
process is aborted
Bye Bye
```

`raise`:
```
$ ./build/IPC/signals/raise
Going to raise a signal
!! signal caught !!
Exiting...
```

`kill_recv` + `kill`:
```
$ ./build/IPC/signals/kill_recv &
[1] 12345
$ kill -USR1 12345
Signal 10 recieved
```

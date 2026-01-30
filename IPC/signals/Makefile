CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra
BUILD_DIR ?= ../../build/IPC/signals

PROGS := \
  $(BUILD_DIR)/ctrl_c \
  $(BUILD_DIR)/kill_sender \
  $(BUILD_DIR)/kill_recv \
  $(BUILD_DIR)/raise \
  $(BUILD_DIR)/timed_input

.PHONY: all clean
all: $(PROGS)

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/ctrl_c: ctrl_c.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/kill_sender: kill_sender.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/kill_recv: kill_recv.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/raise: raise.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/timed_input: timed_input.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra
PTHREAD_FLAGS ?= -pthread
RT_FLAGS ?= -lrt
BUILD_DIR ?= build

PROGS := \
  $(BUILD_DIR)/ITC/rtm \
  $(BUILD_DIR)/NewSHM/mmap_as_malloc_Demo1 \
  $(BUILD_DIR)/NewSHM/mmap_file_write_Demo2 \
  $(BUILD_DIR)/NewSHM/mmap_file_read_Demo3 \
  $(BUILD_DIR)/NewSHM/test \
  $(BUILD_DIR)/IPC/mmap_demo \
  $(BUILD_DIR)/IPC/Fork/ForkDemo \
  $(BUILD_DIR)/IPC/Fork/NChildren \
  $(BUILD_DIR)/IPC/Fork/SharedMemFork \
  $(BUILD_DIR)/IPC/HeapClone/p1 \
  $(BUILD_DIR)/IPC/HeapClone/p2 \
  $(BUILD_DIR)/IPC/HeapClone/mem_allocator \
  $(BUILD_DIR)/IPC/msgQ/sender \
  $(BUILD_DIR)/IPC/msgQ/recvr \
  $(BUILD_DIR)/IPC/pipes/pipe_demo \
  $(BUILD_DIR)/IPC/pipes/pipe_gpt \
  $(BUILD_DIR)/IPC/pthreads/barrier \
  $(BUILD_DIR)/IPC/pthreads/producer_consumer \
  $(BUILD_DIR)/IPC/pthreads/readers_writer \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/template \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/Alternation \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/sequence_using_api \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/test_api \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/conditionalVariables \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/sequence \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/SharedResource \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/Master_slave_threads \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/api_template \
  $(BUILD_DIR)/IPC/pthreads/Mutexes/mythread_api \
  $(BUILD_DIR)/IPC/signals/ctrl_c \
  $(BUILD_DIR)/IPC/signals/kill_sender \
  $(BUILD_DIR)/IPC/signals/kill_recv \
  $(BUILD_DIR)/IPC/signals/raise \
  $(BUILD_DIR)/IPC/signals/timed_input \
  $(BUILD_DIR)/IPC/SHM/shm_client \
  $(BUILD_DIR)/IPC/SHM/shm_server \
  $(BUILD_DIR)/IPC/SHM/samples/sample2a \
  $(BUILD_DIR)/IPC/SHM/samples/sample2b \
  $(BUILD_DIR)/IPC/SHM/samples/CallbackClient \
  $(BUILD_DIR)/IPC/SHM/samples/CallbackServer \
  $(BUILD_DIR)/IPC/SHM/Demo/reader \
  $(BUILD_DIR)/IPC/SHM/Demo/writer \
  $(BUILD_DIR)/IPC/SHM/igmp_pim_synchronisation/igmp \
  $(BUILD_DIR)/IPC/SHM/igmp_pim_synchronisation/pim \
  $(BUILD_DIR)/IPC/GENERIC_SHM_LOCAL/main

.PHONY: all clean
all: $(PROGS)

clean:
	rm -rf $(BUILD_DIR)

# ITC
$(BUILD_DIR)/ITC/rtm: ITC/rtm.c ITC/rt.c ITC/utils.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

# NewSHM
$(BUILD_DIR)/NewSHM/mmap_as_malloc_Demo1: NewSHM/mmap_as_malloc_Demo1.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/NewSHM/mmap_file_write_Demo2: NewSHM/mmap_file_write_Demo2.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/NewSHM/mmap_file_read_Demo3: NewSHM/mmap_file_read_Demo3.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/NewSHM/test: NewSHM/test.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# IPC
$(BUILD_DIR)/IPC/mmap_demo: IPC/mmap_demo.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# IPC/Fork
$(BUILD_DIR)/IPC/Fork/ForkDemo: IPC/Fork/ForkDemo.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/Fork/NChildren: IPC/Fork/NChildren.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/Fork/SharedMemFork: IPC/Fork/SharedMemFork.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# IPC/HeapClone
$(BUILD_DIR)/IPC/HeapClone/p1: IPC/HeapClone/p1.c IPC/HeapClone/mem_allocator.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/IPC/HeapClone/p2: IPC/HeapClone/p2.c IPC/HeapClone/mem_allocator.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/IPC/HeapClone/mem_allocator: IPC/HeapClone/mem_allocator.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DMEM_ALLOCATOR_STANDALONE $< -o $@

# IPC/msgQ
$(BUILD_DIR)/IPC/msgQ/sender: IPC/msgQ/sender.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(RT_FLAGS) -o $@

$(BUILD_DIR)/IPC/msgQ/recvr: IPC/msgQ/recvr.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(RT_FLAGS) -o $@

# IPC/pipes
$(BUILD_DIR)/IPC/pipes/pipe_demo: IPC/pipes/pipe_demo.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/pipes/pipe_gpt: IPC/pipes/pipe_gpt.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# IPC/pthreads
$(BUILD_DIR)/IPC/pthreads/barrier: IPC/pthreads/barrier.c IPC/pthreads/threadApi.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $^ -o $@

$(BUILD_DIR)/IPC/pthreads/producer_consumer: IPC/pthreads/producer_consumer.c IPC/pthreads/threadApi.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $^ -o $@

$(BUILD_DIR)/IPC/pthreads/readers_writer: IPC/pthreads/readers_writer.c IPC/pthreads/threadApi.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $^ -o $@

# IPC/pthreads/Mutexes
$(BUILD_DIR)/IPC/pthreads/Mutexes/template: IPC/pthreads/Mutexes/template.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/Alternation: IPC/pthreads/Mutexes/Alternation.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/sequence_using_api: IPC/pthreads/Mutexes/sequence_using_api.c IPC/pthreads/Mutexes/mythread_api.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $^ -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/test_api: IPC/pthreads/Mutexes/test_api.c IPC/pthreads/Mutexes/mythread_api.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $^ -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/conditionalVariables: IPC/pthreads/Mutexes/conditionalVariables.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/sequence: IPC/pthreads/Mutexes/sequence.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/SharedResource: IPC/pthreads/Mutexes/SharedResource.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/Master_slave_threads: IPC/pthreads/Mutexes/Master_slave_threads.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/api_template: IPC/pthreads/Mutexes/api_template.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BUILD_DIR)/IPC/pthreads/Mutexes/mythread_api: IPC/pthreads/Mutexes/mythread_api.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) -DMYTHREAD_API_STANDALONE $< -o $@

# IPC/signals
$(BUILD_DIR)/IPC/signals/ctrl_c: IPC/signals/ctrl_c.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/signals/kill_sender: IPC/signals/kill_sender.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/signals/kill_recv: IPC/signals/kill_recv.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/signals/raise: IPC/signals/raise.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/signals/timed_input: IPC/signals/timed_input.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# IPC/SHM
$(BUILD_DIR)/IPC/SHM/shm_client: IPC/SHM/shm_client.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/SHM/shm_server: IPC/SHM/shm_server.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/SHM/samples/sample2a: IPC/SHM/samples/sample2a.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/SHM/samples/sample2b: IPC/SHM/samples/sample2b.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/SHM/samples/CallbackClient: IPC/SHM/samples/CallbackClient.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/SHM/samples/CallbackServer: IPC/SHM/samples/CallbackServer.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/IPC/SHM/Demo/reader: IPC/SHM/Demo/reader.c IPC/SHM/Demo/shm_demo.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(RT_FLAGS) -o $@

$(BUILD_DIR)/IPC/SHM/Demo/writer: IPC/SHM/Demo/writer.c IPC/SHM/Demo/shm_demo.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(RT_FLAGS) -o $@

$(BUILD_DIR)/IPC/SHM/igmp_pim_synchronisation/igmp: IPC/SHM/igmp_pim_synchronisation/igmp.c IPC/SHM/igmp_pim_synchronisation/shm_struct.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(PTHREAD_FLAGS) $(RT_FLAGS) -o $@

$(BUILD_DIR)/IPC/SHM/igmp_pim_synchronisation/pim: IPC/SHM/igmp_pim_synchronisation/pim.c IPC/SHM/igmp_pim_synchronisation/shm_struct.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(PTHREAD_FLAGS) $(RT_FLAGS) -o $@

# IPC/GENERIC_SHM_LOCAL
$(BUILD_DIR)/IPC/GENERIC_SHM_LOCAL/main: \
  IPC/GENERIC_SHM_LOCAL/main.c \
  IPC/GENERIC_SHM_LOCAL/LinkedList/LinkedListApi.c \
  IPC/GENERIC_SHM_LOCAL/Trees/tree.c \
  IPC/GENERIC_SHM_LOCAL/map.c \
  IPC/GENERIC_SHM_LOCAL/shm_ds.c \
  IPC/GENERIC_SHM_LOCAL/struct.c \
  IPC/GENERIC_SHM_LOCAL/Utils.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(RT_FLAGS) -o $@

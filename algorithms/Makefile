CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

TARGETS = ss_backtracking ss_backtracking_positive ss_dp ss_greedy ss_monte_carlo

all: $(TARGETS)

ss_backtracking: ss_backtracking.c ss_backtracking.h
	$(CC) $(CFLAGS) -o $@ ss_backtracking.c $(LDFLAGS)

ss_backtracking_positive: ss_backtracking_positive.c ss_backtracking.h
	$(CC) $(CFLAGS) -o $@ ss_backtracking_positive.c $(LDFLAGS)

ss_dp: ss_dp.c
	$(CC) $(CFLAGS) -o $@ ss_dp.c $(LDFLAGS)

ss_greedy: ss_greedy.c
	$(CC) $(CFLAGS) -o $@ ss_greedy.c $(LDFLAGS)

ss_monte_carlo: ss_monte_carlo.c
	$(CC) $(CFLAGS) -o $@ ss_monte_carlo.c $(LDFLAGS)

clean:
	rm -f $(TARGETS)

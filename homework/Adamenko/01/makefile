CC      	= g++
CFLAGS  	= -Wall -std=c++11 -O2
VLGR 		= valgrind
VLGRMISSES 	= --tool=cachegrind
VLGRLEAKS	= --leak-check=full -v
DF 			= diff
DFFLAGS		= --side-by-side

compile: clean
	$(CC) $(CFLAGS) sum_by_rows.cpp -o sum_by_rows
	$(CC) $(CFLAGS) sum_by_columns.cpp -o sum_by_columns

run: compile
	@./sum_by_rows > res_by_rows.ans
	@./sum_by_columns > res_by_columns.ans
	@$(DF) $(DFFLAGS) res_by_rows.ans res_by_columns.ans || exit 0

valgrind-memory-leaks: compile # поиск утечек памяти
	@$(VLGR) $(VLGRLEAKS) --log-file=sum_by_rows.memory-leaks.out ./sum_by_rows
	@$(VLGR) $(VLGRLEAKS) --log-file=sum_by_columns.memory-leaks.out ./sum_by_columns
	@$(DF) $(DFFLAGS) sum_by_rows.memory-leaks.out sum_by_columns.memory-leaks.out || exit 0

valgrind-cach-misses: compile # поиск промахов в кеш
	@$(VLGR) $(VLGRMISSES) --log-file=sum_by_rows.cache-misses.out ./sum_by_rows
	@$(VLGR) $(VLGRMISSES) --log-file=sum_by_cols.cache-misses.out ./sum_by_columns
	@$(DF) $(DFFLAGS) sum_by_rows.cache-misses.out sum_by_columns.cache-misses.out || exit 0

clean:
	rm -rf *.o sum_by_rows sum_by_columns *.out* *.ans *.dSYM
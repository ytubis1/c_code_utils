rm -rf output
mkdir output
gcc -g -c -I util/queue -I pl/logger/include -I pl/memory/include test/queue_test.c -o output/test.o
gcc -g -c -I util/queue -I pl/lock/include util/queue/queue.c -o output/queue.o
gcc -g -c -I pl/lock/include pl/lock/linux/lock_pl.c -o output/lock_pl.o
gcc -g -c -I pl/logger/include pl/logger/linux/logger_pl.c -o output/logger_pl.o
gcc -g -c -I pl/memory/include pl/memory/linux/memory_pl.c -o output/memory_pl.o
gcc output/test.o output/queue.o output/lock_pl.o output/logger_pl.o output/memory_pl.o -lpthread -o  output/run.exe 
rm tags
ctags -R util pl test *
rm output/*.o

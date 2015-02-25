p1:
	/usr/bin/gcc -std=c99 -O2 -Wall -Wextra -Werror problem_1.c -o problem_1 -lm -pthread

p2:
	/usr/bin/gcc -std=c99 -O2 -Wall -Wextra -Werror problem_2.c -o problem_2 -lm -pthread

p3:
	/usr/bin/gcc -std=c99 -O2 -Wall -Wextra -Werror problem_3.c -o problem_3 -lm -pthread

run1: problem_1
	taskset -c 1 ./problem_1 10 5

run1_10min: problem_1
	taskset -c 1 ./problem_1 99 600

run2: problem_2
	taskset -c 1 ./problem_2 10 5

run3: problem_3
	./problem_3 10 5

clean:
	rm problem_1 problem_2 problem_3

# Chocolate Factory

Code execution with Semaphore + Mutex [code](chocolate_factory.c)

run:chocolate_factory.c
	gcc chocolate_factory.c -o chocolate_factory -pthread -o all


Chocolate Factory : In this process the chocolate factory produces the chocolates at specific slots, one box is allowed to process at a time. By using semaphore and mutex we can control 
the process. So, that one box be allowed at a time.

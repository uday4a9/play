.SILENT:clean
sll:	clean
	gcc -o sll sll.c -g
btree:
	gcc -o btree btree.c -g
clean:
	-@rm btree sll

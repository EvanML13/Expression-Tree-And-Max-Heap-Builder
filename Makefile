CFLAGS = -std=c99 -Wall -pedantic
CC = clang

all: bin/preorder bin/postorder bin/inorder bin/calculate bin/heap

bin/calculate: obj/calculate.o obj/binaryTree.o
	$(CC) $(CFLAGS) -o bin/calculate obj/calculate.o obj/binaryTree.o

bin/heap: obj/heap.o
	$(CC) $(CFLAGS) -o bin/heap obj/heap.o

bin/inorder: obj/inorder.o obj/binaryTree.o
	$(CC) $(CFLAGS) -o bin/inorder obj/inorder.o obj/binaryTree.o

bin/postorder: obj/postorder.o  obj/binaryTree.o
	$(CC) $(CFLAGS) -o bin/postorder obj/postorder.o obj/binaryTree.o

bin/preorder: obj/preorder.o obj/binaryTree.o
	$(CC) $(CFLAGS) -o bin/preorder obj/preorder.o obj/binaryTree.o

obj/binaryTree.o: src/binaryTree.c src/binaryTree.h
	$(CC) $(CFLAGS) -c src/binaryTree.c -o obj/binaryTree.o 

obj/calculate.o: src/calculate.c src/binaryTree.h
	$(CC) $(CFLAGS) -c src/calculate.c -o obj/calculate.o

obj/heap.o: src/heap.c src/heap.h
	$(CC) $(CFLAGS) -c src/heap.c -o obj/heap.o

obj/inorder.o: src/inorder.c src/binaryTree.h
	$(CC) $(CFLAGS) -c src/inorder.c -o obj/inorder.o

obj/postorder.o: src/postorder.c src/binaryTree.h
	$(CC) $(CFLAGS) -c src/postorder.c -o obj/postorder.o	

obj/preorder.o: src/preorder.c src/binaryTree.h
	$(CC) $(CFLAGS) -c src/preorder.c -o obj/preorder.o

clean:
	rm obj/*.o

cleaner:
	rm -f obj/*.o bin/preorder bin/postorder bin/inorder bin/calculate bin/heap

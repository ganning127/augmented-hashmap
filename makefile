all: 
	gcc avl_tree.c -o avl_tree -fsanitize=address; ./avl_tree
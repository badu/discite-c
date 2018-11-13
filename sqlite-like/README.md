Notes :
=======

1. I am pretty sure that writing cursor->table->pager is bad. Table is a pointer, which might be NULL
2. I've noticed that returning on else is put on else (e.g code below):
```
uint32_t *someFunc(){
    if (child_num == num_keys) {
		return internal_node_right_child(node);
	} else {
		return internal_node_cell(node, child_num);
	}
}
```
just like we couldn't make it more readable by avoiding else->return.

3. Operators : 
a. "&" address of (just like in Go)
b. "*" value of (just like in Go)
c. "->" structure dereference
d. "." structure reference
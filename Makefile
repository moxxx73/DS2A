SRCPATH := $(shell pwd)/src
BUILDPATH := $(shell pwd)/build
.PHONY: libds2a build_dir

libds2a: build_dir
	gcc -fPIC -shared $(SRCPATH)/llist.c $(SRCPATH)/merge-sort.c $(SRCPATH)/siphash.c -o $(BUILDPATH)/libds2a.so

build_dir:
	mkdir -p $(BUILDPATH)
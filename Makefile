CC=g++
CFLAGS=-g -pedantic # -Wall -Werror -Wextra
SOURCEDIR = src
BUILDDIR = build
OBJECTS = utils lobject ldump linstr lproto lvm ltable

LUAS = 
LUAC = luac5.3
LUASDIR = luas

.PHONY: all
all: luavm

luas: $(addsuffix .luac, $(LUAS))

%.luac: $(LUASDIR)/%.lua
	$(LUAC) -o $(LUASDIR)/$@ $^

luavm: luavm.o $(addsuffix .o, $(OBJECTS))
	$(CC) -o $@ $(addprefix $(BUILDDIR)/,$^) $(CFLAGS)

luavm.o: luavm.cpp
	$(CC) -c -o $(BUILDDIR)/$@ $< $(CFLAGS)

%.o: $(SOURCEDIR)/%.cpp $(SOURCEDIR)/%.hpp
	$(CC) -c -o $(BUILDDIR)/$@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o
# 	rm -f $(LUASDIR)/*.luac
	rm -f luavm
	rm -f luavm.tar.xz

package:
	tar cJf luavm.tar.xz Makefile build/DONOTREMOVEBUILDDIR src luavm.cpp
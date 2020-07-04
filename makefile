CC := clang
WARN := -Wno-unused-command-line-argument
CFLAGS := `pkg-config --cflags gtk+-3.0` 
CLIBS :=  `pkg-config --libs gtk+-3.0`
EXE := main
SRC := src/*

default: $(EXE)
	@./$(EXE)

$(EXE): $(SRC)
	@$(CC) $(WARN) -rdynamic -Iinclude $(CFLAGS) $(SRC) -lbitlib -o $(EXE) -lm $(CLIBS)

clean:
	@rm -f $(EXE)

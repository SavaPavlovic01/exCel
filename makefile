c_files=src/buffer.cpp \
src/csv_lexer.cpp \
src/Token.cpp \
src/csv_parser.cpp \
src/table_structs.cpp \
src/Cell.cpp \
src/table_struct_visitor.cpp

h_files=$(addprefix inc/,$(notdir $(c_files:.cpp=.hpp)))

library_path=-LC:\mingw_dev_lib\lib

include_path=-IC:\mingw_dev_lib\include\SDL2

linker_flags=-lSDL2 -lSDL2main -lmingw32 -lSDL2_ttf

compiler_flags=-g -Wall -Wextra

all: $(c_files) $(h_files)
	g++ $(c_files) $(include_path) $(library_path) $(compiler_flags) $(linker_flags) -o main.exe 

clean:
	rm -rf main.exe

eval:
	gcc src/eval.c -mwindows -g -o eval.exe

gui:
	g++ $(c_files) src/gui.cpp src/Window.cpp $(compiler_flags) $(linker_flags) $(include_path) $(library_path) -o gui.exe 
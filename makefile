c_files=src/buffer.cpp \
src/main.cpp \
src/csv_lexer.cpp \
src/Token.cpp \
src/csv_parser.cpp \
src/table_structs.cpp \
src/Cell.cpp \
src/table_struct_visitor.cpp

h_files=$(addprefix inc/,$(notdir $(c_files:.cpp=.hpp)))

all: $(c_files) $(h_files)
	g++ $(c_files) -g -Wall -Wextra -Iinc -o main.exe

clean:
	rm -rf main.exe
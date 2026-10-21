# Дополнительные библиотеки не для Mac, по умолчанию оставляем пустым, чтобы не портить сборку на Mac
LIBS_ADDITIONAL = 
# Команда для открытия файла отчета о покрытии по умполчанию
CMD_OPEN = open

# Определяем ОС
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif
# Настраиваем переменные в зависимости от ОС
ifeq ($(detected_OS), Linux)
	# Значение по умолчанию для любых версий Linux
	LIBS_ADDITIONAL = -lm -pthread -lrt
	CMD_OPEN = xdg-open
endif

# Набор цветов для оформления
GREEN   =   \033[0;32m
RED		=   \033[0;31m
RESET	=   \033[0m

# Компилятор / Линковщик
CC=gcc

# Команды
AR:= ar rc #для архива
RAN:= ranlib
MK:= mkdir -p # создание директории

# Пути до используемых папок
OBJ_DIR = obj
GCOV_OBJ_DIR = obj/gcov
TESTS_OBJ_DIR = obj/tests
TEST_DIR = tests
MODULES_DIR = s21_decimal
REPORT_DIR = report

#Цель и название исполняемого файла для тестов
TEST_EXE = test
#Цель и название исполняемого файла для отчета о покрытии
GCOV_EXE = gcov_report

# Имя статичной библиотеки со всеми модулями проекта
MODULES_STATIC_LIBRARY = s21_decimal.a
# Она же, но с флагами для отчета покрытия
MODULES_STATIC_LIBRARY_GCOV = s21_decimal_gcov.a

# Дефолтное значение 1 если не задано с консоли
# Задаем так: make test MODE=4
MODE?=1
ifeq ($(MODE), 2)
	# Собираем с fsanitizer
	LFLAGS=-g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover \
	-fstack-protector -fanalyzer
	CFLAGS_TESTS=-Wall -Werror -Wextra -c -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable \
	-fno-sanitize-recover -fstack-protector
	CFLAGS += $(CFLAGS_TESTS) -fanalyzer
else 
	ifeq ($(MODE), 3)
		# Собираем с отладочной информацией для valgrind
		LFLAGS=-g
		CFLAGS=-Wall -Werror -Wextra -c -g
		CFLAGS_TESTS = $(CFLAGS)
	else 
		# Стандартный режим
		LFLAGS= 
		CFLAGS=-Wall -Werror -Wextra -c -std=c11 -pedantic
		CFLAGS_TESTS = $(CFLAGS)
	endif
endif

# Флаги для gcov
GCOV_FLAGS =--coverage 

# Дополнительные библиотеки для линковки
LIBS = -lcheck $(LIBS_ADDITIONAL)

# Дополнительные библиотеки для линковки c отчетом о покрытии
LIBS_GCOV = $(LIBS) -lgcov

# Заполняем переменные со списком директорий, исходных и исполняемых файлов
ALL_MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
ALL_MODULES_C = $(notdir $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.c"))
ALL_MODULES_H = $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.h")
MAIN_H = $(shell find . -maxdepth 1 -name "*.h")
ALL_H = $(ALL_MODULES_H) $(MAIN_H)
ALL_MODULES_O = $(ALL_MODULES_C:%.c=%.o)

ALL_TESTS_DIRS = $(shell find $(TEST_DIR) -type d)
ALL_TESTS_C = $(notdir $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.c"))
ALL_TESTS_H = $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.h")
ALL_TESTS_O = $(addprefix $(TESTS_OBJ_DIR)/, $(notdir $(ALL_TESTS_C:%.c=%.o)))

ALL_MODULES_GCOV_O = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(ALL_MODULES_C:.c=.o)))

# Набор всех файлов для cppcheck
ALL_C_H_FILES = $(shell find . -type f | grep "\.(c|h)$$" -E)

# Указываем список каталогов, в которых make выполняет поиск
vpath %.c $(ALL_MODULES_DIRS) : $(ALL_TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# Далее идут все цели
all: $(TEST_EXE) $(GCOV_EXE)

$(TEST_EXE): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(MODULES_STATIC_LIBRARY) $(ALL_TESTS_O)
	@$(CC) $(LFLAGS) $(ALL_TESTS_O) $(MODULES_STATIC_LIBRARY) $(LIBS) -o $(TEST_EXE)
	@echo "\n-------------------------------------------------------------------------------------------------\n"
	@./$(TEST_EXE)

$(GCOV_EXE): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(MODULES_STATIC_LIBRARY_GCOV) $(ALL_TESTS_O) $(ALL_H) $(ALL_TESTS_H)
	@$(CC) $(LFLAGS) $(ALL_TESTS_O) $(MODULES_STATIC_LIBRARY_GCOV) $(LIBS_GCOV) -o ./$(GCOV_EXE)
	@echo "\n-------------------------------------------------------------------------------------------------\n"
	@./$(GCOV_EXE)
	gcovr -o gcov_report.html --html --html-self-contained -d $(GCOV_OBJ_DIR)
	#$(CMD_OPEN) gcov_report.html

lcov_report: $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(REPORT_DIR) $(MODULES_STATIC_LIBRARY_GCOV) $(ALL_TESTS_O) $(ALL_H) $(ALL_TESTS_H)
	@$(CC) $(LFLAGS) $(ALL_TESTS_O) $(MODULES_STATIC_LIBRARY_GCOV) $(LIBS_GCOV) -o ./$(GCOV_EXE)
	@echo "\n-------------------------------------------------------------------------------------------------\n"
	@./$(GCOV_EXE)
	@gcov -o $(GCOV_OBJ_DIR) $(ALL_MODULES_C)
	@lcov -b ./ -d $(GCOV_OBJ_DIR) --gcov-tool /usr/bin/gcov -c -o output.info
	@genhtml -o $(REPORT_DIR) output.info
	@rm *.c.gcov output.info
	$(CMD_OPEN) $(REPORT_DIR)/index.html

$(MODULES_STATIC_LIBRARY): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_O) $(ALL_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(AR) $(MODULES_STATIC_LIBRARY) $(addprefix $(OBJ_DIR)/, $(ALL_MODULES_O))
	@$(RAN) $(MODULES_STATIC_LIBRARY)

$(MODULES_STATIC_LIBRARY_GCOV): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_GCOV_O) $(ALL_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(AR) $(MODULES_STATIC_LIBRARY_GCOV) $(ALL_MODULES_GCOV_O)
	@$(RAN) $(MODULES_STATIC_LIBRARY_GCOV)

%.o: %.c $(ALL_H) $(ALL_TESTS_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) $<

$(GCOV_OBJ_DIR)/%.o : %.c $(ALL_H) $(ALL_TESTS_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $@ $<

$(TESTS_OBJ_DIR)/%.o : %.c $(ALL_H) $(ALL_TESTS_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS_TESTS) -o $@ $<

$(REPORT_DIR):
	@$(MK) $(REPORT_DIR)
	@echo "folder: $(GREEN)$(REPORT_DIR) was created$(RESET)"
$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)
	@echo "folder: $(GREEN)$(OBJ_DIR) was created$(RESET)"
$(GCOV_OBJ_DIR):
	@$(MK) $(GCOV_OBJ_DIR)
	@echo "folder: $(GREEN)$(GCOV_OBJ_DIR) was created$(RESET)"
$(TESTS_OBJ_DIR):
	@$(MK) $(TESTS_OBJ_DIR)
	@echo "folder: $(GREEN)$(TESTS_OBJ_DIR) was created$(RESET)"

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f gcov_report.html
	rm -f *.a *.o
	rm -f *.c.gcov *.gcno *.gcov *.gcda output.info
	rm -f ./$(GCOV_EXE) ./$(TEST_EXE)

rebuild: clean all

clang:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n --style=file $(shell find . -type f \( -name "*.c" -o -name "*.h" \) )
	rm -f .clang-format

clang-fix:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i --style=file $(shell find . -type f \( -name "*.c" -o -name "*.h" \) )
	rm -f .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_C_H_FILES)

leaks:
	leaks --atExit -- ./$(TEST_EXE)

valgrind:
	valgrind --tool=memcheck --leak-check=yes -s ./$(TEST_EXE)

.PHONY: all lcov_report clean rebuild clang clang-fix cppcheck leaks valgrind	



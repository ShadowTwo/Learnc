CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/path.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))
#SO_OBJECT=$(patsubst build/%.a,src/%.o,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests
	@echo IN All

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	@echo IN Target
	ar rcs $@ $(OBJECTS)
	ranlib $@
	

$(SO_TARGET): $(TARGET) $(OBJECT)
	@echo IN SO_TARGET
	$(CC) -shared -o $@ $(OBJECT)
	#$(CC) $(CFLAGS) $(TARGET)
build:
	@echo IN BUILD
	@mkdir -p build
	@mkdir -p bin

#the Unit Tests
.PHONY: tests
#tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	@echo IN TESTS
	sh ./tests/runtests.sh
	
$(TESTS): $(TEST_SRC)
	@echo IN TESTS CC
	$(CC) -Wall -g -DNDEBUG $(OBJECTS) $(TEST_SRC) -o $(TESTS)
#The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf 'find . -name "*.dSYM" -print'

#The Install
install: all
	install -d $(DSTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

#The Checker
check:
	@echo Files with potentially Dangerous Functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
	
#debug items
print-%  : ; @echo $* = $($*)


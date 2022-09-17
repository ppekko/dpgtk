OUT = "pick"
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -nostartfiles -Wall -fomit-frame-pointer -fmerge-all-constants  -fno-math-errno -Wall -ffast-math  -fno-unroll-loops -Os -nodefaultlibs -lm -lc
SOURCES = $(shell find src/ -name "*.cpp")
HEADERS = $(shell find src/ -name "*.h")
LIBS = `pkg-config --cflags --libs gtk+-3.0`

all: $(SOURCES) $(HEADERS)
	@echo "Sources: $(SOURCES)"
	@echo "Headers: $(HEADERS)"
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) $(LDFLAGS) -o $(OUT)
	strip -s -R .comment -R .gnu.version $(OUT)
	sstrip $(OUT)
	./autovndh.py $(OUT) --xz --vndh "" > $(OUT)~
	rm $(OUT) && mv $(OUT)~ $(OUT)
	@echo "Size of the program:"
	@du -h $(OUT)
	@du -b $(OUT)

run:
	./$(OUT)

clean:
	rm $(OUT)

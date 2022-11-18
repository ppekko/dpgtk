OUT = "pick"
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -Os -nostartfiles -nodefaultlibs -lc -fno-plt -fno-stack-protector -fno-stack-check -fno-unwind-tables -fno-asynchronous-unwind-tables -fomit-frame-pointer -ffast-math -no-pie -fno-pic -fno-PIE -ffunction-sections -fdata-sections -fno-plt -fmerge-all-constants -mno-fancy-math-387 -mno-ieee-fp

SOURCES = $(shell find src/ -name "*.cpp")
HEADERS = $(shell find src/ -name "*.h")
LIBS = `pkg-config --cflags --libs gtk+-3.0`

all: $(SOURCES) $(HEADERS)
	@echo "Sources: $(SOURCES)"
	@echo "Headers: $(HEADERS)"
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) $(LDFLAGS) -o $(OUT)
	strip -s -R .comment -R .gnu.version $(OUT)
	sstrip $(OUT)
	./autovndh.py $(OUT) --zopfli --lzma --vndh_unibin --vndh_no_argv  --vndh "" > $(OUT)~
	rm $(OUT) && mv $(OUT)~ $(OUT)
	@echo "Size of the program:"
	@du -b $(OUT)

run:
	./$(OUT)

clean:
	rm $(OUT)

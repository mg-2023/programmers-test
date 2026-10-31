CC      := gcc
CFLAGS  := -Wall -Wextra -g -MMD -MP
LDLIBS  :=
BUILD   := build

# 한 단계 깊이의 하위 폴더에 있는 .c 파일 수집 (build 폴더는 제외)
SRCS := $(filter-out $(BUILD)/%,$(wildcard */*.c))

# a/a.c -> build/a
BINS := $(addprefix $(BUILD)/,$(notdir $(basename $(SRCS))))

# 소스 폴더들을 검색 경로에 등록
vpath %.c $(patsubst %/,%,$(sort $(dir $(SRCS))))

.PHONY: all clean

all: $(BINS)

$(BUILD)/%: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf $(BUILD)

# 헤더 변경 시 자동 재빌드
-include $(BINS:=.d)

# 目标文件
# TARGET = haruhikage
TARGET = exp5

#头文件
INCS = include

#指定输出hex文件的路径与文件名
OUT_DIR = build
OUT_NAME = bin

$(OUT_DIR)/$(OUT_NAME).hex : $(OUT_DIR)/$(OUT_NAME).ihx 
	packihx  $(OUT_DIR)/$(OUT_NAME).ihx > $(OUT_DIR)/$(OUT_NAME).hex

$(OUT_DIR)/$(OUT_NAME).ihx : src/$(TARGET).c
	sdcc -I$(INCS) src/$(TARGET).c -o $(OUT_DIR)/$(OUT_NAME).ihx

# 烧录操作
download:
	stcgal -P stc89a  $(OUT_DIR)/$(OUT_NAME).hex 

# 清理操作
.PHONY : clean
clean :
	rm -f $(OUT_DIR)/*

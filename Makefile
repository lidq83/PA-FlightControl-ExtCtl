PROJECT				= pa3extctl
BUILD				= build

LIB					= lib
DRIVER				= driver
MODULES				= modules

MAIN				= main
GEO					= geo
COMMANDER			= commander
EXTCTL				= extctl


LIB_GEO				= $(LIB)_$(GEO)
MODULES_COMMANDER	= $(MODULES)_$(COMMANDER)
MODULES_EXTCTL		= $(MODULES)_$(EXTCTL)

OUTPUT				= apps

CC					= gcc
CFLAGS				+= -lm
CFLAGS				+= -lpthread
CFLAGS				+= -std=c11

all: mk$(BUILD) $(LIB_GEO) $(MODULES_COMMANDER) $(MODULES_EXTCTL) $(MAIN)

mk$(BUILD):
	mkdir -p $(BUILD)/
	mkdir -p $(BUILD)/apps/

$(LIB_GEO):
	mkdir -p $(BUILD)/$(LIB_GEO)/
	cd $(BUILD)/$(LIB_GEO)/ && cmake ../../src/$(LIB)/$(GEO)/ && make
	cp -v $(BUILD)/$(LIB_GEO)/*.a $(BUILD)/$(OUTPUT)/

$(MODULES_COMMANDER):
	mkdir -p $(BUILD)/$(MODULES_COMMANDER)/
	cd $(BUILD)/$(MODULES_COMMANDER)/ && cmake ../../src/$(MODULES)/$(COMMANDER)/ && make
	cp -v $(BUILD)/$(MODULES_COMMANDER)/*.a $(BUILD)/$(OUTPUT)/

$(MODULES_EXTCTL):
	mkdir -p $(BUILD)/$(MODULES_EXTCTL)/
	cd $(BUILD)/$(MODULES_EXTCTL)/ && cmake ../../src/$(MODULES)/$(EXTCTL)/ && make
	cp -v $(BUILD)/$(MODULES_EXTCTL)/*.a $(BUILD)/$(OUTPUT)/
	
$(MAIN):
	mkdir -p $(BUILD)/$(MAIN)/
	cd $(BUILD)/$(MAIN)/ && cmake ../../src/$(MAIN)/ && make
	cp -v $(BUILD)/$(MAIN)/*.a $(BUILD)/$(OUTPUT)/
	$(CC) $(CFLAGS) -o $(BUILD)/$(PROJECT) -L$(BUILD)/$(OUTPUT)/	\
		-l$(MAIN)	\
		-l$(MODULES_EXTCTL)	\
		-l$(MODULES_COMMANDER)	\
		-l$(LIB_GEO)
		

clean:
	rm -rvf $(BUILD)
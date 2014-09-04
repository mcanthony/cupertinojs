#TODO: this should be more integrated with XCode projects
ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR := $(BUILT_PRODUCTS_DIR)
SOURCE_DIR := $(ROOT_DIR)/Todoie

CUJS=/usr/local/bin/cujs
SOURCES = todoie.js

all: post-build

BUILD_SCRIPT = $(BUILD_DIR)/cujs-build.sh

# cujs compiles javascript to .s
js-build:
		mkdir -p $(ROOT_DIR)/build;
		mkdir -p $(BUILD_DIR); 

		if [ -a $(BUILD_SCRIPT) ] ;\
			then \
			rm -rf $(BUILD_SCRIPT); \
		fi

        # CUJS_ENV_PROJECT_ROOT_DIR is the base path for imports
		@echo export CUJS_ENV_PROJECT_ROOT_DIR=$(SOURCE_DIR) >> $(BUILD_SCRIPT)

        # CUJS_ENV_DEBUG_COMPILER=true will dump bitcode to stdio
#		@echo export CUJS_ENV_DEBUG_COMPILER=true >> $(BUILD_SCRIPT)

		# Pass xcode variables
		@echo export SDKROOT=$(SDKROOT) >> $(BUILD_SCRIPT)
		@echo export ARCHS=$(ARCHS) >> $(BUILD_SCRIPT)
		@echo export PLATFORM_NAME=$(PLATFORM_NAME) >> $(BUILD_SCRIPT)
		
        # CUJS_ENV_BUILD_DIR is where the build products are installed
		# for XCode projects, build to the source dir for now
		@echo export CUJS_ENV_BUILD_DIR=$(SRCROOT)/Todoie >> $(BUILD_SCRIPT)

		@echo $(CUJS) $(SOURCE_DIR)/$(SOURCES) >> $(BUILD_SCRIPT)
		chmod +x $(BUILD_SCRIPT)

		@echo $(BUILD_SCRIPT)
		$(BUILD_SCRIPT)

main-build: js-build 

post-build:	main-build
	@echo BUILD_SUCCEEDED!
    
clean:
	rm -rf $(BUILD_DIR)
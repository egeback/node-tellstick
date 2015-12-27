# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := hello
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=hello' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++0x

INCS_Debug := \
	-I/home/marky/.node-gyp/4.2.1/include/node \
	-I/home/marky/.node-gyp/4.2.1/src \
	-I/home/marky/.node-gyp/4.2.1/deps/uv/include \
	-I/home/marky/.node-gyp/4.2.1/deps/v8/include \
	-I$(srcdir)/node_modules/nan

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=hello' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-O3 \
	-ffunction-sections \
	-fdata-sections \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++0x

INCS_Release := \
	-I/home/marky/.node-gyp/4.2.1/include/node \
	-I/home/marky/.node-gyp/4.2.1/src \
	-I/home/marky/.node-gyp/4.2.1/deps/uv/include \
	-I/home/marky/.node-gyp/4.2.1/deps/v8/include \
	-I$(srcdir)/node_modules/nan

OBJS := \
	$(obj).target/$(TARGET)/tellstick-node.o \
	$(obj).target/$(TARGET)/device-node.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic

LDFLAGS_Release := \
	-pthread \
	-rdynamic

LIBS := \
	-ltelldus-core \
	-ltellstick

$(obj).target/hello.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/hello.node: LIBS := $(LIBS)
$(obj).target/hello.node: TOOLSET := $(TOOLSET)
$(obj).target/hello.node: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/hello.node
# Add target alias
.PHONY: hello
hello: $(builddir)/hello.node

# Copy this to the executable output path.
$(builddir)/hello.node: TOOLSET := $(TOOLSET)
$(builddir)/hello.node: $(obj).target/hello.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/hello.node
# Short alias for building this executable.
.PHONY: hello.node
hello.node: $(obj).target/hello.node $(builddir)/hello.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/hello.node

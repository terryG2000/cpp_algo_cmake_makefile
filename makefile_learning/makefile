lib_srcs := $(filter-out main.cpp, $(shell find ./ -name "*.cpp"))
lib_obj := $(patsubst %.cpp, objs/%.o, $(lib_srcs))

include_path := /home/terry/cpp_cmake_learning/makefile_learning/animal
library_path := ./lib
library_name := animal

l_flages := $(library_name:%=-l%)
L_flages := $(library_path:%=-L%)
i_flages := $(include_path:%=-I%)
r_options := $(library_path:%=-Wl,-rpath=%)
# 将所有路径前加上-I

compile_options := -g -O3 -w $(i_flages) -fpic
link_options := $(l_flages) $(L_flages) $(r_options)
###############编译目标文件###############
objs/%.o : %.cpp
# 目标文件objs/./animal/cat.o  依赖文件./animal/cat.cpp
	@mkdir -p $(dir $@)
# 如果没有目标的路径 将创建路径
	@echo FROME $< GENERATE $@
# FROME animal/cat.cpp GENERATE objs/./animal/cat.o
	@g++ -c $< -o $@ $(compile_options)
# 构建目标文件

#############编译动态库###############
lib/libanimal.so : $(lib_obj)
	@mkdir -p $(dir $@)
	@g++ -shared $^ -o $@
dynamic_lib : lib/libanimal.so

############连接静态库#############
objs/main.o : animal/main.cpp
	@mkdir -p $(dir $@)
	@echo FROME $< GENERATE $@
	@g++ -c $< -o $@ $(compile_options)

################连接#######
exec : objs/main.o
	g++ $< -o $@ $(link_options)

clean:
	rm -rf objs exec lib
.PHONY : debug clean exec

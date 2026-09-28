CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -g -O0
LDFLAGS  :=

TARGET   := campusguard


SRCS     := $(wildcard *.cpp)
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(OBJS:.o=.d)

.PHONY: all run clean rebuild debug valgrind


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)


run: $(TARGET)
	./$(TARGET)


debug: $(TARGET)
	gdb ./$(TARGET)


valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --error-exitcode=1 \
	         ./$(TARGET)


clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)


rebuild: clean all
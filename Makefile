CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g
TARGET   := campusguard_test

SRCS := \
    main.cpp \
    Incident.cpp \
    ReportedState.cpp \
    DispatchedState.cpp \
    InProgressState.cpp \
    ResolvedState.cpp \
    CancelledState.cpp \
    CommandDispatcher.cpp \
    DispatchUnitCommand.cpp \
    LockdownAreaCommand.cpp \
    IssueEvacuationCommand.cpp \
    ActivateAlertCommand.cpp \
    CancelLastCommand.cpp \
    CampusGuardMediator.cpp \
    TestZone.cpp

OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
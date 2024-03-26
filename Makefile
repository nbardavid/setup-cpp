CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
SRCDIR=src
OBJDIR=obj
SRCS=$(SRCDIR)/main.cpp
OBJS=$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET=setup

GREEN = \033[38;2;4;231;98m
BLUE = \033[38;2;119;166;182m
RED = \033[0;31m
RESET = \033[0m

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(GREEN)Linking...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)
	@echo "$(GREEN)Compilation successful!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiled $< successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning up object files...$(RESET)"
	@rm -frd obj
	@echo "$(RED)Cleaned.$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable $(TARGET)...$(RESET)"
	@rm -f $(TARGET)
	@echo "$(RED)Removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

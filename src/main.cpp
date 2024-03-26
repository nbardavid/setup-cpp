/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:10:07 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/26 19:08:40 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}

void makefile_create(){
    std::string makefileContent = R"(
CXX=g++
CXXFLAGS=-std=c++98 -Wall -Wextra -Werror
SRCDIR=src
OBJDIR=obj
SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET=default

GREEN = \033[38;2;4;231;98m
BLUE = \033[38;2;119;166;182m
RED = \033[0;31m
RESET = \033[0m

all: $(TARGET)

$(TARGET): $(OBJS)
        @printf "$(GREEN)Linking...$(RESET)\n"
        @$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)
        @printf "$(GREEN)Compilation successful!$(RESET)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
        @mkdir -p $(OBJDIR)
        @printf "$(BLUE)Compiling $<...$(RESET)\n"
        @$(CXX) $(CXXFLAGS) -c $< -o $@
        @printf "$(GREEN)Compiled $< successfully!$(RESET)\n"

clean:
        @printf "$(RED)Cleaning up object files...$(RESET)\n"
        @rm -frd obj
        @printf "$(RED)Cleaned.$(RESET)\n"

fclean: clean
        @printf "$(RED)Removing executable $(TARGET)...$(RESET)\n"
        @rm -f $(TARGET)
        @printf "$(RED)Removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

)";

    std::ofstream makefile("Makefile");
    if (makefile.is_open()) {
        makefile << makefileContent;
        makefile.close();
        std::cout << "Makefile created successfully.\n";
    } else {
        std::cerr << "Failed to create Makefile.\n";
    }
}

int main( void ){

    std::filesystem::create_directory("srcs");
    std::filesystem::create_directory("include");
	makefile_create();
    std::string input;
    std::cout << "write STOP to stop" << std::endl;
    while(true){
        std::cout << "Class name : ";
        std::getline(std::cin, input);
        if (input == "STOP" || input == "stop"){
            break;
        }
        else {
            std::ofstream file_cpp("./srcs/" + input + ".Class.cpp");
            if (file_cpp.is_open()){
                file_cpp << "#include \"../include/" << input << ".Class.hpp\"\n\n";
                file_cpp << input << "::" << input << "(){\n    // Constructeur\n}\n";
                file_cpp << input << "::" << input << "(const " << input << "& other){\n    // Constructeur de copie\n}\n";
                file_cpp << input << "::~" << input << "(){\n    // Destructeur\n}\n";
                file_cpp << input << "& " << input << "::operator=(const " << input << "& other){\n    // Operateur d'assignation de copie\n    return *this;\n}\n"; 
                file_cpp.close();
            }
            else {
                std::cerr << "Can't create the file" << std::endl;
            }
            std::ofstream file_hpp("./include/" + input + ".Class.hpp");
            if (file_hpp.is_open()){
                file_hpp << "#ifndef " << to_upper(input) << "_CLASS_HPP\n";
                file_hpp << "#define " << to_upper(input) << "_CLASS_HPP\n\n";
                file_hpp << "class " << input << " {\n";
                file_hpp << "public:\n";
                file_hpp << "    " << input << "();\n";
                file_hpp << "    " << input << "(const " << input << "& other);\n";
                file_hpp << "    ~" << input << "();\n";
                file_hpp << "    " << input << "& operator=(const " << input << "& other);\n";
                file_hpp << "};\n\n";
                file_hpp << "#endif";
                file_hpp.close();
            }
            else {
                std::cerr << "Can't create the file" << std::endl;
            }
        }
    }
}

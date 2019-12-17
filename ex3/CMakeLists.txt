cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h SimulatorManager.cpp SimulatorManager.h
        Commands/Command.h Commands/SingleCommands.h Commands/ConnectCommand.cpp Commands/ConnectCommand.h
        Commands/OpenServerCommand.cpp Commands/OpenServerCommand.h Expressions/Expression.h
        Expressions/ExpressionKinds.cpp Expressions/ExpressionKinds.h SymbolTableValue.h
        Commands/DefineVarCommand.cpp Commands/DefineVarCommand.h Commands/VarAssignCommand.cpp Commands/VarAssignCommand.h Commands/DefineLocalVarCommand.cpp Commands/DefineLocalVarCommand.h)
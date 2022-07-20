# Project's name and programming language
project (LotteryScheduling C)

# The following folder will be included
# include_directories ("${PROJECT_SOURCE_DIR}/")

add_executable (
LotteryScheduling
src/main.c
src/lottery.c
src/process.c
src/sched.c
src/lottery.h
src/process.h
src/sched.h
)

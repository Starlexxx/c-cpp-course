# CMake generated Testfile for 
# Source directory: /home/starlex/Documents/Study/prep-2021.01/project/tests
# Build directory: /home/starlex/Documents/Study/prep-2021.01/project/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BaseTest "/home/starlex/Documents/Study/prep-2021.01/project/tests/tests" "/home/starlex/Documents/Study/prep-2021.01/project/tests/data" "--gtest_filter=-*Extra*")
add_test(ExtraTest "/home/starlex/Documents/Study/prep-2021.01/project/tests/tests" "/home/starlex/Documents/Study/prep-2021.01/project/tests/data" "--gtest_filter=*Extra*")

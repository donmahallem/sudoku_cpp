aclocal
automake --add-missing
autoconf
find ./build -name '*.o' -delete
find ./buildTest -name '*.o' -delete
find ./build -name '*.gcda' -delete
find ./buildTest -name '*.gcda' -delete
find ./build -name '*.gcno' -delete
find ./buildTest -name '*.gcno' -delete
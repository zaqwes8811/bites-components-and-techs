@echo off
python %~d0%~p0cpplint.py ^
  --filter=-readability/utf8,-whitespace/line_length,-whitespace/braces,-whitespace/end_of_line ^
  --output=vs7 %1 %2 %3 %4 %5 %6 %7 %8 %9
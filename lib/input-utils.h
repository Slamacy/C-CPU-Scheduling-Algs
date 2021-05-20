#pragma once

// Yoinked from class demo on validating string input

// clear stdin buffer
void clear_to_newline();
// improved fgets that applies buffer handling
void fgets_str_stdin(char *, size_t);
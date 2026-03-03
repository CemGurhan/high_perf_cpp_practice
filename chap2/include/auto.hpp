#pragma once // Prevents double-inclusion

int& val_ref();
int& decltype_val_ref();
decltype(auto) decltype_val_ref_wrapper();
auto val_ref_wrapper();

void auto_ref_strip();
void decltype_auto();

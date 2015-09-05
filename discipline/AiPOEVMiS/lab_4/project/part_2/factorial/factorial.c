unsigned long
factorial(unsigned long x) {
  if (x == 0)
    return 1;
  else
    return x * factorial(x-1);
}

void
flush_stdin() {
  while (getchar() != '\n');
}

#include <string.h>
#include <stdio.h>

#include <chrono>

[[clang::optnone]]
void bench_memory(void *destination, void *memory, size_t size)
{
  auto start = std::chrono::high_resolution_clock::now();
  memcpy(destination, memory, size);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  fprintf(stderr, "Copied time %f - size %zu, at %f\n", duration.count(), size, (size/duration.count())/(1024*1024*1024));
}

[[clang::optnone]]
int main(int argc, char **argv)
{
  size_t array_elements = size_t(1024) * 512;
  int *source = new int[array_elements];
  int *destination = new int[array_elements];
  for (size_t i = 0; i < array_elements; i++)
  {
    source[i] = i;
    destination[i] = i;
  }

  bench_memory(destination, source, sizeof(*source) * array_elements);
  return 0;

}

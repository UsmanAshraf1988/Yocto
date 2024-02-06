#include <dump_info.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  while (1) {
    dump_info();
    sleep(1);
  }

  return 0;
}


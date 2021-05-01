#ifndef strlen_h
#define strlen_h

int strlen(char* buf){
  int size = 0;
  while(buf[size] != 0){
    size++;
  }
  return size;
}
#endif

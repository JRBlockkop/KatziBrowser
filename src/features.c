#include <stdio.h>
#include <string.h>

#include "../brand/var.h"

char *features(int argc, char *argv[]){
    char *url = KATZI_DEFAULT_URL;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], "--", 2) == 0) {
                //flag
            }else{
                url = argv[i];
            }
        }
    }

    return url;
}

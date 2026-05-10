#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void process_feedback() {
    char buffer[64];
    printf("\nEnter your feedback (Max 64 chars): ");
    fflush(stdout);
    
    // VULNERABILITY 2: Buffer Overflow
    // read() is used, but the size (256) exceeds the buffer (64).
    read(0, buffer, 256); 
}

void welcome_user(char *user_input) {
    char greeting[128];
    // VULNERABILITY 1: Format String Leak
    // Directly passing user_input to printf allows us to read the stack.
    printf("Current Session for: ");
    printf(user_input); 
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    welcome_user(argv[1]);
    process_feedback();

    return 0;
}

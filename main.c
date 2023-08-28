#include <stdio.h>
#include <stddef.h>

struct message_t {
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename) {
    if(cp == NULL || size <= 0 || filename == NULL) return -1;

    FILE *file;
    file = fopen(filename, "rb");
    if(file == NULL) return -2;

    unsigned int bytes_to_read, structures_to_read;
    if(fread(&bytes_to_read, sizeof(unsigned int), 1, file) != 1) {
        fclose(file);
        return -3;
    }

    if(bytes_to_read % sizeof(struct message_t) != 0) {
        fclose(file);
        return -3;
    }

    structures_to_read = bytes_to_read / sizeof(struct message_t);
    if(fread(cp, sizeof(struct message_t), structures_to_read, file) != structures_to_read) {
        fclose(file);
        return -3;
    }

    fclose(file);
    return structures_to_read;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {
    if(cp == NULL || size <= 0 || msg == NULL || text_size <= 0) return 1;
    char *ptr;
    unsigned int used_bytes, used_bytes_of_struct = 0;
    used_bytes = 0;
    ptr = (char *)&(*(cp));
    int msg_index = 0; // keep track of the number of characters written to msg
    while(used_bytes < 24 * (unsigned int)size - 1) {
        if(used_bytes_of_struct == 24) used_bytes_of_struct = 0;
        if(used_bytes_of_struct == 0) {
            used_bytes_of_struct += 1;
            used_bytes += 1;
            ptr += 1;
            for(int i = 0; i < 7; i++) {
                if(msg_index == text_size - 1) {
                    *msg = '\0';
                    return 0; // check if we have exceeded the size of msg
                }
                *msg = *ptr;
                msg++;
                msg_index++; // increment the number of characters written to msg
                used_bytes_of_struct += 1;
                used_bytes += 1;
                ptr += 1;
            }
        }
        else if(used_bytes_of_struct == 8) {
            used_bytes +=12 ;
            used_bytes_of_struct +=12 ;
            ptr +=12 ;
        }
        else if(used_bytes_of_struct == 20 ) {
            for(int i = 0 ; i < 4 ; i++) {
                if(msg_index == text_size - 1) {
                    *msg = '\0';
                    return 0; // check if we have exceeded the size of msg
                }
                *msg =*ptr ;
                msg++;
                msg_index++; // increment the number of characters written to msg
                used_bytes_of_struct +=1 ;
                used_bytes+=1 ;
                ptr+=1 ;
            }
        }
    }
    return 0;
}

int main(void) {
    char file_path[31], message[2001];
    struct message_t messages[100];
    int res, c;
    printf("Please input file path:");
    scanf("%30[^\n]", file_path);
    while((c = getchar()) && c != '\n' && c != EOF) {}
    res = load_data(messages, 100, file_path);
    if(res == -2) {
        printf("Couldn't open file");
        return 4;
    }
    else if(res == -3) {
        printf("File corrupted");
        return 6;
    }
    decode_message(messages, 100, message, 2000);
    printf("%s", message);
    return 0;
}

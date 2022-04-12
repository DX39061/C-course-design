#include<stdio.h>
#include<string.h>

int get_c_source_file_content(char *content);
int is_matching_brackets(char *content);

int main(){
    char content[1000000];
    int is_valid_file_path = get_c_source_file_content(content);

    if(!is_valid_file_path){
        printf("The file may not exist\n");
        printf("Check the path and try again\n");
        return 0;
    }

    int result = is_matching_brackets(content);

    if(result == 1){
        printf("OK ! The brackets are matching\n");
    }else{
        printf("Warnning ! The brackets are not matching\n");
    }

    return 0;
}

int get_c_source_file_content(char *content){
    FILE *fp;
    char path[100];
    char row_buffer[1000];

    printf("Give me a C source file within 1000 lines and I'll check if the brackets match\n");
    printf("Enter the path of a C source file : ");
    scanf("%s", path);

    fp = fopen(path, "r");
    if(fp == NULL){
        return 0;
    }
    while (fgets(row_buffer, 1000, fp) != NULL){
        strcat(content, row_buffer);
    }
    fclose(fp);
    return 1;
}

int is_matching_brackets(char * content){
    int i = 0;
    char stack[10000];
    int stack_cnt = -1;
    while(content[i] != '\0'){

        //check if the bracket is surrounded by ' '
        if(i>0){
            if(content[i-1] == '\'' && content[i+1] == '\''){
                i++;
                continue;
            }
        }

        switch (content[i]){
            case '(':
                stack[++stack_cnt] = '(';
                break;
            case ')':
                if(stack[stack_cnt] == '('){
                    stack_cnt--;
                }
                else{
                    return 0;
                }
                break;
            case '{':
                stack[++stack_cnt] = '{';
                break;
            case '}':
                if(stack[stack_cnt] == '{'){
                    stack_cnt--;
                }
                else{
                    return 0;
                }
                break;
            default:
                break;
        }
        i++;
    }
    return stack_cnt == -1;
}

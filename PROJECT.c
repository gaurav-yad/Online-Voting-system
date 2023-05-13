#include <stdio.h>
#include <string.h>

struct candidate {
    int id;
    char name[50];
    char vote; 
};

void add_Voter();
void cast_vote();
void view_results();
void print_voter_list();
void del_voter();

int main() {
    int choice;
    char adminpw[]="CSE101";
    char pw[10];
    
    while (1) {
        printf("\nWelcome to the ONLINE VOTING SYSTEM\n");
        printf("1. Add a Voter\n");
        printf("2. Cast Vote\n");
        printf("3. View Vote count of each party\n");
        printf("4. View eligible voters list.\n");
        printf("5. Delete a voter from voter list.\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        
        switch (choice) {
            case 1:
                add_Voter();
                break;
            case 2:
                cast_vote();
                break;
            case 3:
                printf("Enter the administrator password to see the results: ");
                gets(pw);
                if(strcmp(pw, adminpw)){
                    printf("Wrong admin pw, access denied.\n");;
                }else{
                    printf("Correct password, access granted.\n");
                    view_results();
                }
                break;
            case 4:
                printf("Enter the administrator password to see the voter list: ");
                gets(pw);
                if(strcmp(pw, adminpw)){
                    printf("Wrong admin pw, access denied.\n");
                }else{
                    printf("Correct password, access granted.\n");
                    print_voter_list();
                }
                break;
            case 5:
                printf("Enter the administrator passowrd to delete a voter: ");
                gets(pw);
                if(strcmp(pw, adminpw)){
                    printf("Wrong admin pw, access denied.\n");
                }else{
                    del_voter();
                }
                break;
            case 6:
                printf("Thank you for using the ONLINE VOTING SYSTEM.\n");
                goto end;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    end:
    return 0;
}

void add_Voter() {
    int age;
    printf("Enter voter age: ");
    scanf("%d",&age);
    if(age>=18){
        FILE *fp;
        char line[1000];
        struct candidate c;
     
        fp = fopen("candidates.txt","a+");
    
        printf("Enter a unique four digit voter ID: ");
        scanf("%d", &c.id);

        while(fgets(line, 1000, fp)){
            int ID;
            sscanf(line, "%4d", &ID);
            if(c.id==ID){
                printf("Voter ID already exist\n");
                goto end2;
            }
        }
            
        printf("Enter voter name: ");
        fflush(stdin);
        gets(c.name);
    
        c.vote = 'N';
    
        fprintf(fp, "%d\t%s\t%c\n",c.id, c.name, c.vote);
    
        printf("Voter added successfully.\n");
        goto end2;
        end2:
        fclose(fp);
    }else{
        printf("You are not eligible to vote!!\n");
    }
    
}

void cast_vote() {
    FILE *fp;
    int Cid;
    struct candidate c;
    int found = 0;
    char line[1000];
    
    fp = fopen("candidates.txt", "r+");
    
    printf("Candidates List:\n");
    printf("Candidate\tParty\n");
    printf("ABC\t\t A\n");
    printf("XYZ\t\t B\n");
    printf("PQR\t\t C\n");
    
    printf("Enter voter ID to cast vote: ");
    scanf("%d", &Cid);

    if(fp==NULL){
        printf("No data found.\n");
    } else {
        while (fgets(line, 1000, fp)) {
            int id;
            sscanf(line, "%4d", &id);
            if(id==Cid){
                found=1;
                break;
            }
        }
    
        if (found) {
            int len = strlen(line);
            if(line[len-2]!='N'){
                printf("You have already casted your vote.\n");
            } else {
                int choice;
                printf("You are an eligible voter.\n");
                printf("Enter 1 to cast vote to Party A.\n");
                printf("Enter 2 to cast vote to Party B.\n");
                printf("Enter 3 to cast vote to Party C.\n");
                scanf("%d",&choice);
                switch (choice)
                {
                case 1:
                    c.vote='A';
                    line[len-2]=c.vote;
                    fseek(fp, -(len+1), SEEK_CUR);
                    fputs(&line[0], fp);
                    printf("Vote casted successfully.\n");
                    break;
                case 2:
                    c.vote='B';
                    line[len-2]=c.vote;
                    fseek(fp, -(len+1), SEEK_CUR);
                    fputs(&line[0], fp);
                    printf("Vote casted successfully.\n");
                    break;
                case 3:
                    c.vote='C';
                    line[len-2]=c.vote;
                    fseek(fp, -(len+1), SEEK_CUR);
                    fputs(&line[0], fp);
                    printf("Vote casted successfully.\n");                            
                    break; 
                default:
                    printf("You did not enter the correct choice.\n");
                    break;
                } 
            }
        } else {
            printf("Invalid candidate ID. Please try again.\n");
        }
        fclose(fp);
    }
}

void view_results() {
    FILE *fp;
    struct candidate c;
    int count_A = 0;
    int count_B = 0;
    int count_C = 0;
    char line[1000];
    
    fp = fopen("candidates.txt", "r");
    
    if(fp==NULL){
        printf("No data in file.\n");
    }else{
        while (fgets(line, 1000, fp)) {
            if(line[strlen(line)-2]=='A'){
                count_A++;
            }
            else if(line[strlen(line)-2]=='B'){
                count_B++;
            }
            else if(line[strlen(line)-2]=='C'){
                count_C++;
            }
        
        }
    }   
    printf("Votes of Party A: %d\nVotes of Party B: %d\nVotes of Party C: %d\n",count_A, count_B, count_C);   
    fclose(fp);
}

void print_voter_list() {
    FILE *fp;
    struct candidate c;
    
    fp = fopen("candidates.txt", "r");
    
    char line[1000];
    printf("C_ID\tCandidate_name\tVote_Casted\n\n");
    while(fgets(line, 1000, fp)){
        printf("%s\n", line);
    }
}

void del_voter() {
    FILE *fp, *temp;
    int delid, found = 0, id;
    char line[1000];
    
    printf("Enter the voter ID to delete: ");
    scanf("%d", &delid);
    
    fp = fopen("candidates.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    while (fgets(line, 1000, fp)) {
        sscanf(line, "%4d", &id);
        if (id == delid) {
            found = 1;
            continue;
        }
        fprintf(temp, "%s", line);
    }
    
    fclose(fp);
    fclose(temp);
    
    if (found == 0) {
        printf("Entered Voter ID does not exist.\n");
    } else {
        if (remove("candidates.txt") == 0) {
            if (rename("temp.txt", "candidates.txt") == 0) {
                printf("Voter deleted successfully.\n");
            } else {
                printf("Error renaming temporary file.\n");
            }
        } else {
            printf("Error deleting original file.\n");
        }
    }
}


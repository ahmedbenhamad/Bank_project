#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Date {
    int day, month, year;
} date;

typedef struct Transactions {
    int amount;
    char type[20];
    date trans_date;
    struct Transactions *next;
} transaction;
transaction *trans;

typedef struct Accounts {
    int ref;
    char acc_type[20];
    int balance;
    date create_date;
    transaction *transaction_history;
    int trans_count;
} acc;

typedef struct Node {
    acc accounts;
    struct Node *next;
} node;
node *head;

typedef struct Customers {
    int id;
    char name[20];
    char address[30];
    int phone;
    char email[30];
    int mdp;
    //acc Account;
} customer;

customer cust[100];

typedef struct Bank_Accounts {
    acc accounts;
    customer customers;
    int tot_trans;
} bank_acc;
// global variables
int custNum = 0;

void AdminDef() {
    cust[0].id = 0;
    strcpy(cust[0].email, "abenhamad@gmail.com");
    strcpy(cust[0].address, "nouiel4222");
    cust[0].phone = 94134518;
    strcpy(cust[0].name, "admin");
    custNum++;
}

void adduser() {
    system("cls");
    printf("\nEnter your name : \n");
    scanf("%s", cust[custNum].name);
    printf("Enter your password :");
    scanf("%d",&cust[custNum].mdp);
    printf("\nEnter your phone : \n");
    scanf("%d",&cust[custNum].phone);
    printf("\nEnter your address : \n");
    scanf("%s", cust[custNum].address);
    printf("\nEnter your email : \n");
    scanf("%s", cust[custNum].email);
    cust[custNum].id = custNum;
    custNum++;
}

node *Add_account(node *l, acc acc1) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL) {
        return NULL;
    }

    newnode->accounts = acc1;
    newnode->next = l;
    return newnode;
}

node *delete_account(node *heads, int ref) {
    node *current = heads;
    node *prev = NULL;

    while (current != NULL && current->accounts.ref != ref) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Node with reference %d not found.\n", ref);
        return heads;
    }

    if (prev == NULL) {
        heads = current->next;
    } else {

        prev->next = current->next;
    }


    free(current);

    printf("Node with reference %d deleted successfully.\n", ref);

    return heads;
}
date trans_date(){
    date dt;
    printf("\nEnter the transaction date format(day/month/year) :");
    printf("\nDay:");
    scanf("%d",&dt.day);
    printf("\nMonth:");
    scanf("%d",&dt.month);
    printf("\nYear:");
    scanf("%d",&dt.year);
    return dt;
}
void create_Account() {
    int idx;
    acc acct;
    system("cls");
    printf("Enter the user id : \n");
    scanf("%d", &idx);
    for (int i = 0; i < custNum; i++) {
        if (idx == cust[i].id) {
            acct.ref = (idx + 100);
            printf("\nEnter the account type : ");
            scanf("%s", acct.acc_type);
            printf("\nEnter the account balance : ");
            scanf("%d", &acct.balance);
            printf("\nEnter the account creation date : ");
            printf("\n\t\tDay:");
            scanf("%d", &acct.create_date.day);
            printf("\n\t\tMonth : ");
            scanf("%d", &acct.create_date.month);
            printf("\n\t\tYear : ");
            scanf("%d", &acct.create_date.year);

            acct.transaction_history = NULL;
            acct.trans_count = 0;
        }
    }

    head = Add_account(head, acct);

    printf("Account created Successfully\n");
}
void transaction_hist(node *heads, int amounts, const char *t,date dt) {
    node *aux = heads;
    if (aux != NULL) {

        transaction *new_hist = (transaction *)malloc(sizeof(transaction));
        if (new_hist == NULL) {
            printf("Memory allocation error.\n");
            return;
        }

        new_hist->amount = amounts;
        strcpy(new_hist->type, t);
        new_hist->trans_date =dt;

        new_hist->next = aux->accounts.transaction_history;
        aux->accounts.transaction_history = new_hist;

        aux->accounts.trans_count++;

        printf("Transaction added successfully.\n");
    } else {
        printf("Invalid account.\n");
    }
}


/*void transaction_hist(node *heads,transaction *Trans,int amounts,char *t){
    node *aux=heads;
    if(Trans!=NULL) {
        transaction *new_hist = (transaction *) malloc(sizeof(transaction));
        aux->accounts.trans_count += 1;
        aux->accounts.transaction_history->amount = amounts;
        strcpy(aux->accounts.transaction_history->type, t);
        aux->accounts.transaction_history->trans_date = aux->accounts.create_date;
        new_hist->next = aux->accounts.transaction_history;
        aux->accounts.transaction_history = NULL;
        Trans = new_hist;
    }
}*/

bool deposit(node *heads, int refer, int amount) {
    node *tmp = heads;
    date d;
    while (tmp != NULL) {
        if (tmp->accounts.ref == refer) {
            tmp->accounts.balance += amount;

            d=trans_date();
            transaction_hist(tmp, amount, "deposit",d);
            return true;
        }
        tmp = tmp->next;
    }
    printf("Account with reference %d not found.\n", refer);
    return false;
}


void updateUserInfo(int id) {
    int i;
    for (i = 0; i < custNum; i++) {
        if (cust[i].id == id) {
            printf("Current Information for Customer ID %d:\n", id);
            printf("Name: %s\n", cust[i].name);
            printf("Phone: %d\n", cust[i].phone);
            printf("Address: %s\n", cust[i].address);
            printf("Email: %s\n", cust[i].email);

            printf("Enter updated information:\n");
            printf("New Name: ");
            scanf("%s", cust[i].name);
            printf("New Phone: ");
            scanf("%d", &cust[i].phone);
            printf("New Address: ");
            scanf("%s", cust[i].address);
            printf("New Email: ");
            scanf("%s", cust[i].email);

            printf("User information updated successfully.\n");
            break;
        }
    }

    if (i == custNum) {
        printf("Customer not found. Please check the id.\n");
    }
}

void show_account_info(node *heads, int ref) {
    node *current = heads;

    while (current != NULL && current->accounts.ref != ref) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Account with reference %d not found.\n", ref);
        return;
    }

    printf("Account Information:\n");
    printf("Reference: %d\n", current->accounts.ref);
    printf("Account Type: %s\n", current->accounts.acc_type);
    printf("Balance: %d Dt\n", current->accounts.balance);
    printf("Creation Date: %d/%d/%d\n", current->accounts.create_date.day,
           current->accounts.create_date.month, current->accounts.create_date.year);

    printf("Transaction History:\n");
    transaction *current_trans = current->accounts.transaction_history;
    while (current_trans != NULL) {
        printf("Transaction Type: %s\n", current_trans->type);
        printf("Transaction Amount: %d Dt\n", current_trans->amount);
        printf("Transaction Date: %d/%d/%d\n", current_trans->trans_date.day,
               current_trans->trans_date.month, current_trans->trans_date.year);
        printf("\n");

        current_trans = current_trans->next;
    }

    printf("\n");
}

void show_trans(node *heads, int ref) {
    node *current = heads;
    int i=0;
    while (current != NULL && current->accounts.ref != ref) {
        current = current->next;
    }
    if (current != NULL) {
        printf("Transaction History for Account Reference %d:\n", ref);
        transaction *current_trans = current->accounts.transaction_history;
        while (current_trans != NULL && i <= custNum) {
            printf("Amount: %d Dt\n", current_trans->amount);
            printf("Type: %s\n", current_trans->type);
            printf("Date: %d/%d/%d\n", current_trans->trans_date.day,
                   current_trans->trans_date.month,
                   current_trans->trans_date.year);
            printf("\n");
            current_trans = current_trans->next;
            i++;
        }
    } else {
        printf("Account with reference %d not found.\n", ref);
    }
}


void show_all_transactions(node *heads) {
    node *current = heads;

    while (current != NULL) {
        printf("Account Reference: %d\n", current->accounts.ref);
        printf("Account Type: %s\n", current->accounts.acc_type);
        printf("Transaction History:\n");

        transaction *current_trans = current->accounts.transaction_history;
        while (current_trans != NULL) {
            printf("Transaction Type: %s\n", current_trans->type);
            printf("Transaction Amount: %d Dt\n", current_trans->amount);
            printf("Transaction Date: %d/%d/%d\n", current_trans->trans_date.day,
                   current_trans->trans_date.month, current_trans->trans_date.year);
            printf("\n");

            current_trans = current_trans->next;
        }

        current = current->next;
    }
}


bool withdraw(node *heads, int refer, int amount) {
    node *tmp = heads;
    date d;
    while (tmp != NULL) {
        if (tmp->accounts.ref == refer) {
            if (tmp->accounts.balance >= amount) {
                tmp->accounts.balance -= amount;

                d=trans_date();
                transaction_hist(tmp, amount, "withdraw",d);
                return true;
            } else {
                printf("Insufficient balance.\n");
                return false;
            }
        }
        tmp = tmp->next;
    }
    printf("Account with reference %d not found.\n", refer);
    return false;
}


void delete_user(int id) {
    for (int i = 0; i < custNum; i++) {
        if (cust[i].id == id) {
            for (int j = i; j < custNum - 1; j++) {
                cust[j] = cust[j + 1];
            }
            custNum--;
            break;
        }
    }
}

int acc_ref_by_id(node *heads, int id) {
    node *tmp = heads;
    int refer;
    int i = 0;
    if (tmp == NULL)
        return 0;
    else {
        while (tmp != NULL) {
            if (tmp->accounts.ref == (id + 100))
                refer = tmp->accounts.ref;
            tmp = tmp->next;
        }
    }
    return refer;
}

void show_bank_customers() {
    if (custNum == 0) {
        printf("No customers in the bank.\n");
        return;
    }

    printf("\nBank Customers:\n");
    for (int i = 1; i < custNum ; i++) {
        printf("Customer ID: %d\n", cust[i].id);
        printf("Name: %s\n", cust[i].name);
        printf("Phone: %d\n", cust[i].phone);
        printf("Address: %s\n", cust[i].address);
        printf("Email: %s\n", cust[i].email);
        printf("----------------------------\n");
    }
}

void find_customer_by_id(int id) {
    int i;
    for (i = 0; i < custNum; i++) {
        if (cust[i].id == id) {
            printf("\n%s\n", cust[i].name);
            break;
        }
    }
    if (i == custNum) {
        printf("\nCustomer not found. Please check the id.\n");
    }
}
int show_total_money(node *heads) {
    node *current = heads;
    int total_money = 0;

    while (current != NULL) {

        total_money += current->accounts.balance;
        current = current->next;
    }

    printf("Total Money in the Bank: %d Dt\n", total_money);

    return total_money;
}
int Login() {
    int idx, pass, attempts = 0;
    char uname[20];
    // AdminDef();
    system("cls");

    do {

        printf("\nPlease enter your Id : ");
        scanf("%d", &idx);
        printf("\nPlease enter your username : ");
        scanf("%s", uname);
        printf("\nPlease enter your password : ");
        scanf("%d", &pass);

        for (int i = 0; i < custNum; i++) {
            if (idx == cust[i].id && strcmp(uname, cust[i].name) == 0 && pass == cust[i].mdp) {
                printf("\nLogin Successful!\n");
                return idx;
            } else {
                printf("\nInvalid credentials! Please try again.\n");
                attempts++;
            }
        }

        if (attempts >= 3) {
            printf("\nToo many failed attempts. Exiting...\n");
            exit(0);
        }
    } while (1);

    return -1;
}
void showAccountBalance(node *heads, int ref) {
    node *current = heads;

    while (current != NULL && current->accounts.ref != ref) {
        current = current->next;
    }

    if (current != NULL) {
        printf("Balance for Account Reference %d: %d Dt\n", ref, current->accounts.balance);
    } else {
        printf("Account with reference %d not found.\n", ref);
    }
}
void Menu();
void AdminPanel(int idy) {
    int chx, d;
    int refr, idx;
    do {
        printf("--------------------------------------------------\n");
        printf("\n\t\tWelcome to Admin Panel\n");
        printf("---------------------------------------------------\n");
        printf("1.Add user\n");
        printf("2.Create account\n");
        printf("3.Delete user\n");
        printf("4.Delete account\n");
        printf("5.Update userinfo\n");
        printf("6.Show transaction history \n");
        printf("7.Find customer by id \n");
        printf("8.Show bank customers \n");
        printf("9.Show bank liquidity\n");
        printf("10.Return to login menu \n");
        printf("11.Exit\n");
        printf("Enter your choice :");
        scanf("%d", &chx);
        switch (chx) {
            case 1:
                printf("----------------------------\n");
                adduser();
                break;
            case 2:
                printf("----------------------------\n");
                create_Account();
                break;
            case 3:
                printf("----------------------------\n");
                printf("Enter the user id :");
                scanf("%d", &idx);
                delete_user(idx);
                break;
            case 4:
                printf("----------------------------\n");
                printf("Enter the user id :");
                scanf("%d", &idx);
                refr = acc_ref_by_id(head, idx);
                head = delete_account(head, refr);
                break;
            case 5:
                printf("----------------------------\n");
                printf("Enter the user id to update their info \n:");
                scanf("%d", &idx);
                updateUserInfo(idx);
                break;
            case 6:
                printf("----------------------------\n");
                show_all_transactions(head);
                break;
            case 7:
                printf("----------------------------\n");
                printf("Enter the customer id you searched for :");
                scanf("%d", &d);
                find_customer_by_id(d);
                break;

            case 8:
                printf("----------------------------\n");
                show_bank_customers();
                break;
            case 9:
                show_total_money(head);
                break;
            case 10:
                system("cls");
                printf("----------------------------\n");
                Menu();
                break;
            case 11:
                exit(0);
                break;

            default:
                printf("----------------------------\n");
                printf("Please enter a valid choice!\n");
                break;
        }
    } while (chx != 11);
}
void CustomerPanel(int idy) {

    int chx,d;
    bool check;
    int refr, idx, amnt, wamnt;
    //int idy = Login();
    refr = acc_ref_by_id(head, idy);

        do {
            printf("----------------------------------------------------\n");
            printf("\n\t\tWelcome to Customer Panel\n");
            printf("-----------------------------------------------------\n");
            printf("1.show account info\n");
            printf("2.Deposit\n");
            printf("3.withdraw\n");
            printf("4.show transaction history \n");
            printf("5.Show Balance\n");
            printf("6.Return to login menu\n");
            printf("7.Exit\n");
            printf("Enter your choice :");
            scanf("%d",&chx);
            switch (chx) {
                case 1:
                    printf("----------------------------\n");
                    show_account_info(head, refr);
                    break;
                case 2:
                    printf("----------------------------\n");
                    printf("Enter the amount :");
                    scanf("%d",&amnt);
                    check=deposit(head, idy+100, amnt);
                    if (check)
                        printf("Your balance updated successfully *_*\n");
                    else
                        printf("There is a problem in this operation !\n");

                    break;
                case 3:
                    printf("----------------------------\n");
                    printf("Enter the withdrawing amount : ");
                    scanf("%d",&wamnt);
                    check=withdraw(head, idy+100, wamnt);
                    if (check)
                        printf("Operation successfully\n");
                    else
                        printf("Operation Fail!\n");
                    break;
                case 4:
                    printf("----------------------------\n");
                    show_trans(head,refr);
                    break;

                case 5:
                    showAccountBalance(head,refr);
                    break;
                case 6:
                    system("cls");
                    printf("----------------------------\n");
                    Menu();
                    break;
                case 7:
                    exit(0);
                    break;
                default:
                    printf("----------------------------\n");
                    printf("Please enter a valid choice!\n");
                    break;
            }
        } while (chx != 7);
    }

void Menu(){
    int id;

    printf("------------------------------------------------\n");
    printf("\n\tWelcome to the login page :\n");
    printf("-------------------------------------------------\n");
    AdminDef();
    id=Login();
    //printf("%d",id);
    if(id==0)
    {
        AdminPanel(id);
    }
    else{
        CustomerPanel(id);
    }

}
int main() {

    Menu();
    return 0;
}




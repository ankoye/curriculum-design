#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define H "---------------------------------------------------------"
#define N 10
typedef struct _book{
    char book_name[20];  // ����
    char author[20];     // ����
    char isbn[20];       // ISBN��
    char publisher[50];  // ���浥λ
    int pub_data;        // �������
    float price;         // �۸�
	int stock;		     //���
    struct _book *next;
    struct _book *prev;
}Book;
int psd_validate(char *, char *);

int psd_landing();

Book* book_form();

void book_insert(Book *);

int book_delete(Book *, Book *);

void book_display(Book *, Book *);

void book_inspect(Book *, Book *);

void book_alter(Book *, Book *);

void book_seek(Book *);

void book_construct(Book *);

void book_read(Book *);

void book_write(Book *);

void sort_of_bookname(Book *);

void book_unloose(Book *);

void default_book();

int show_num(Book *);

void show_std();

void show_admin(Book *);

void show_admin_meneu();

void show_std_meneu();

void show_books(Book *);

void show_insert();

void show_seek();

void show_book(Book *);

void show_landing();

void show_manage();

void pack_admin_title(Book *, Book *);

void pack_std_title(Book*, Book*);

void pack_up(Book **, Book *);

void pack_begin(Book **, Book *);

void pack_down(Book **, Book *);

void pack_insert(Book *);

void pack_delete(Book *, Book *);

void pack_seek(Book *);

void pack_admin_landing();

void pack_std_landing();

void show_login();

int obtain_account(char account[N][20]);

void login();

Book* dingwei(Book *, Book *);

void add_stock(Book *temp, Book *book);

void reduce_stock(Book *temp, Book *book);

void borrow_book(Book *temp, Book *book);

void admin();

void denglu();

void student();

int main()
{
	denglu();
	//admin();
	//student();
	return 0;
}

//----------------------- ϵͳ���˵� -----------------------
void denglu(){
    int chioce;
	system("cls");
    show_landing();
    scanf("%d", &chioce);
    fflush(stdin);
    switch(chioce){
        case 1:		 // ���ĵ�¼
            pack_std_landing();
            break;
        case 2:		// ����Ա��¼
            pack_admin_landing();
		case 3:		// ѧ��ע��
			login();
			break;
        case 4:		// �޸�����
            printf("\t�ù���δʵ��,");
            system("pause");
            denglu();
            break;
        case 5:		// �˳�
            exit(0);
        default:	// ����
            printf("\t�������������");
            system("pause");
            denglu();
            break;
    }
}

//----------------------- ѧ������ϵͳ -----------------------
void student(){
    Book *book = book_form();
    Book *temp = book;
    char chioce;
    book_read(book);
    pack_std_title(temp, book);

    while(1){
        printf("\t��ѡ���ܣ�");
        chioce = getch();
        fflush(stdin);
        switch(chioce){
            case 'a': // ����ͼ��
                pack_seek(book);
                break;
            case 'b': // ����
                borrow_book(temp, book);
                book_write(book);
                break;
            case 'c': // �鿴ͼ����Ϣ
                book_inspect(temp, book);
                break;
            case 'd': // �ѽ�ͼ��
                //��ʵ��
                break;
            case 'e': // ����
                //��ʵ��
                break;
            case 'f': // �˳�
                book_unloose(book);
                exit(0);
            case 72:  //������ҳ
                pack_begin(&temp, book);
                break;
            case 75: // ��һҳ
                pack_up(&temp, book);
                break;
            case 77: // ��һҳ
                pack_down(&temp, book);
                break;
            default:
                break;
        }
        pack_std_title(temp, book);
    }
    book_unloose(book);
}

//----------------------- ����Ա����ϵͳ -----------------------
void admin(){
    Book *book = book_form();
	Book *temp = book;
	char chioce;
    book_read(book);
    pack_admin_title(temp, book);

    while(1){
        printf("\t��ѡ���ܣ�");
        chioce = getch();
        fflush(stdin);
        switch(chioce){
            case 'a': // ͼ��¼��
                pack_insert(book);
                book_write(book);
                break;
            case 'b': // �鿴ͼ����Ϣ
                book_inspect(temp, book);
                break;
            case 'c': // ����ͼ��
                pack_seek(book);
                break;
            case 'd': // ɾ��ͼ��
                pack_delete(temp, book);
                book_write(book);
                break;
            case 'e': // �޸�ͼ����Ϣ
                book_alter(temp, book);
                book_write(book);
                break;
            case 'f': // ���
                add_stock(temp, book);
                book_write(book);
                break;
            case 'g': // ����
                reduce_stock(temp, book);
                book_write(book);
                break;
            case 'h': //����
                sort_of_bookname(book);
                break;
            case 'i': // �˳�
                book_unloose(book);
                exit(0);
            case 72:  //������ҳ
                pack_begin(&temp, book);
                break;
            case 75: // ��һҳ
                pack_up(&temp, book);
                break;
            case 77: // ��һҳ
                pack_down(&temp, book);
                break;
            default:
                break;
        }
        pack_admin_title(temp, book);
    }
    book_unloose(book);
}
//--------------------------��¼����------------------------
/** ����Ա��¼ģ�� */
void pack_admin_landing(){
    static int k = 1;
    show_manage();
    if(psd_landing() != 1){ //��ֹ�ǹ���Ա�˺ŵ�¼
        if(++k > 3){
            printf("\a\n\t�������3�Σ�ϵͳǿ���˳���");
            exit(-1);
        }
        printf("\n\t�˺Ż����벻���ڣ������µ�¼\n\t");
        system("pause");
        pack_admin_landing();
    }
    printf("\n\n\t��¼�ɹ���");
    system("pause");
    admin();
}

 /** ���ĵ�¼ģ�� */
void pack_std_landing() {
    static int k = 1;
    show_manage();
    if(psd_landing() == 0){
        if(++k > 3){
            printf("\a\n\t�������3�Σ�ϵͳǿ���˳���");
            exit(-1);
        }
        printf("\n\t�˺Ż����벻���ڣ������µ�¼\n\t");
        system("pause");
        pack_std_landing();
    }
    fflush(stdin);
    printf("\n\n\t��¼�ɹ���");
    system("pause");
    student();
}

 /** �����¼���ҳ�� */
void show_manage(){
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t    �� �� �� ¼\t\t\t\t|\n");
    printf("\t"H"\n");
}

 /** ����������֤ */
int psd_landing(){
	char account[20];       //����֤���˺�
    char password[20];      //����֤������
	int i, n;
	char ch;
    printf("\n\t�������˺ţ�");
    gets(account);
    printf("\n\t���������룺");
    for(i = 0; (ch = getch()) != 13; i++ ){
        printf("*");
        password[i] = ch;
    }password[i] = '\0';
    n = psd_validate(account, password);
    return n;
 }

 /** ���ļ��л�ȡ�˺����벢��֤ */
int psd_validate(char *account, char *password){
	struct _user{
        char account[20];
        char password[20];
        int privilege;  //Ȩ�� 1-����Ա 2-ѧ�� 
	}user[N];
	FILE *fp = NULL;
    int i = 0, j;
    if((fp = fopen("user.txt", "r")) == NULL){
        printf("\t�ļ���ʧ�ܣ�\n");
        exit(-1);
    }
    while(!feof(fp)){
        fscanf(fp, "%s %s %d", user[i].account, user[i].password, &user[i].privilege);
        i++;
    }
    fclose(fp);
    for(j = 0 ; j < i; j++){
        if( (strcmp(user[j].account,  account) == 0) &&
        		(strcmp(user[j].password, password) == 0) ) {
        	return user[j].privilege;    //����Ȩ��
		}
    }
	return 0;
}
//------------------------end----------------------------

//--------------------------ע��--------------------------

void show_login(){
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t    �� �� ע ��\t\t\t\t|\n");
    printf("\t"H"\n");
}

int obtain_account(char account[N][20]){
    char password[20];
    int data;
    int i = 0;
    FILE *fp;
    if((fp = fopen("user.txt", "r")) == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        exit(-1);
    }
    while(!feof(fp)){
        fscanf(fp, "%s %s %d", account[i], password, &data);
        i++;
    }
    fclose(fp);
    if(i < N)
        return 1;
    return 0;
}

void login(){
    char account[20];
    char password[20];
    char faccount[N][20]; //���ļ���ȡ���е��˺�
    char ch;
    FILE *fp;
    int i = 0;
    show_login();
    if(obtain_account(faccount) == 0){
        printf("\t�˺�����ע��ʧ�ܣ�");
        system("pause");
        exit(-1);
    }
    printf("\n\t�������˺ţ�");
    gets(account);
    while(account[i])
        i++;
    if(i < 6){
        printf("\n\t������˺�Ҫ����6λ��");
        system("pause");
        login();
    }
    for(i = 0; i < N; i++){
        if( strcmp(faccount[i], account) == 0 ){
            printf("\n\t�˺��Ѵ��ڣ�");
            system("pause");
            login();
        }
    }
    printf("\n\t���������룺");
    for(i = 0; (ch = getch()) != 13; i++ ){
        printf("*");
        password[i] = ch;
    }password[i] = '\0';
    i = 0;
    while(password[i])
        i++;
    if(i < 6){
        printf("\n\n\t����Ҫ������λ��,");
        system("pause");
		login();
    }
    if((fp = fopen("user.txt", "a+")) == NULL){
        printf("\t�ļ���ʧ�ܣ�\n");
        exit(-1);
    }
    fprintf(fp, "\n%s %s %d", account, password, 2);
    printf("\n\n\tע��ɹ���");
    system("pause");
    fclose(fp);
    denglu();
}
//------------------------����˵�����---------------------
/** ������� */
void pack_admin_title(Book *temp, Book *book){
    system("cls");
    show_admin(book);
    book_display(temp, book);
    show_admin_meneu();
}

/** �����ҳ�� */
void show_landing(){
    printf("\t"H"\n");
    printf("\t|\t\t��ӭʹ��ͼ�����ϵͳ\t\t\t|\n");
    printf("\t"H"\n");
    printf("\t|\t\t\t\t\t\t\t|\n");
    printf("\t|\t\t1��ѧ �� �� ¼\t\t\t\t|\n");
    printf("\t|\t\t2���� �� Ա �� ¼\t\t\t|\n");
	printf("\t|\t\t3���� �� ע ��\t\t\t\t|\n");
    printf("\t|\t\t4���� �� �� ��\t\t\t\t|\n");
    printf("\t|\t\t5����     ��\t\t\t\t|\n");
    printf("\t|\t\t\t\t\t\t\t|\n");
    printf("\t"H"\n");
    printf("\t��ѡ��,����1-5����");
}

/** ������� */
void show_admin(Book *book){
    int n = show_num(book);
    printf("\t"H"\n");
    printf("\t|\t\t     ͼ�����ϵͳ\t\t\t|\n");
    printf("\t"H"\n");
    printf("\t|   ��ǰ��棺\t\t\t\t\t%d\t|\n",n);
    printf("\t"H"\n");
    printf("\t|\t����\t\t����\t\t�۸�\t\t|\n");
}

/** ����˵� */
void show_admin_meneu(){
    printf("\t|\t\t\t\t\t\t\t|\n");
    printf("\t|    �� ��һҳ\t\t����ҳ \t\t��һҳ��\t|\n");
    printf("\t"H"\n");
    printf("\t| a��ͼ��¼�� \t    b���鿴ͼ����Ϣ \tc������ͼ��\t|\n");
    printf("\t| d��ɾ��ͼ�� \t    e���޸�ͼ����Ϣ \tf�����\t\t|\n");
    printf("\t| g����    �� \t    h������(������) \ti���˳�\t\t|\n");
    printf("\t"H"\n");

}

/** ���˵����ͼ�鲿����Ϣ */
void show_books(Book *book){
    printf("\t%-15s %-15s %-5.2f\t\t|\n",book->book_name,book->author,book->price);
}
//--------------------------------end----------------------------

//--------------------------����ͼ�鹦��-------------------------------
/** �������ͼ�� */
void pack_seek(Book *book){
    show_seek();
    book_seek(book);
}

/** ����ͼ��ʱ��� */
void show_seek(){
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t\t����ͼ��\t\t\t|\n");
    printf("\t"H"\n");
    printf("\t������Ҫ���ҵ�������");
}

/** ����ͼ�� */
void book_seek(Book *book){
    Book *temp = book->next;
    char book_name[20];
    gets(book_name);
    while(temp != book){
        if(strcmp(temp->book_name, book_name) == 0)
            break;
        temp = temp->next;
    }
    if(temp == book){
        printf("\n\tδ�ҵ�����鼮,");
        system("pause");
        return ;
    }
    printf("\t���ҵ�ͼ����Ϣ���£�\n");
    show_book(temp);
    system("pause");

}
//--------------------------------end-----------------------------------

//-------------------------�鿴ͼ����Ϣ����---------------------------
/** �鿴ͼ����Ϣ */
void book_inspect(Book *temp, Book *book){
    Book *tep = NULL;
    printf("[�鿴ͼ����Ϣ]\n\t������ͼ����ţ�");
    tep = dingwei(temp, book);
    if(tep == NULL)
        return ;
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t\t�鿴ͼ��\t\t\t|\n");
    printf("\t"H"\n");
    show_book(tep);
    system("pause");
}

/** ���ͼ����Ϣ */
void show_book(Book *book){
    printf("\t"H"\n");
    printf("\t|\t\t��  ����\t%-20s\t|\n",book->book_name);
    printf("\t|\t\t��  �ߣ�\t%-20s\t|\n",book->author);
    printf("\t|\t\tISBN�ţ�\t%-20s\t|\n",book->isbn);
    printf("\t|\t\t�����磺\t%-20s\t|\n",book->publisher);
    printf("\t|\t\t������ݣ�\t%-6d\t\t\t|\n",book->pub_data);
    printf("\t|\t\t��  ��\t%-6.2f\t\t\t|\n",book->price);
    printf("\t|\t\t��  �棺\t%-6d\t\t\t|\n",book->stock);
    printf("\t"H"\n\t");
}
//----------------------------end-------------------------------

//-------------------------ͼ��¼�빦��---------------------------
/** ������ͼ�� */
void pack_insert(Book *book){
    show_insert();
    book_insert(book);
    printf("\tͼ��¼��ɹ���");
    system("pause");
}

/** ͼ��¼��ʱ��� */
void show_insert(){
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t\t����ͼ��\t\t\t|\n");
    printf("\t"H"\n");
}

/** ����ͼ�� */
void book_insert(Book *book){
    Book *temp = book;
    Book *p;
    p = (Book *)malloc(sizeof(*p));
    book_construct(p);   //�������뺯��
    printf("\t������������");
    scanf("%d", &p->stock); //���
    //β������
    while(temp->next != book)
        temp = temp->next;
    p->next = temp->next;
    temp->next = p;
    p->prev = temp;
    p->next->prev = p;
}
//----------------------------end---------------------------------

//--------------------------ɾ��ͼ�鹦��--------------------------
/** ���ɾ��ͼ�� */
void pack_delete(Book *temp, Book *book){
	int n;
    printf("[ɾ��ͼ��]\n\t������ͼ����ţ�");
    n = book_delete(temp, book);
    if(n == 1){
        printf("\tɾ���ɹ�,");
        system("pause");
    }
    if(n == -1){
        printf("\tɾ��ʧ��,");
        system("pause");
    }
}

/** ɾ��ͼ�� */
int book_delete(Book *temp, Book *book){
    Book *p = NULL;
    Book *tep = NULL;
    char chioce;
    tep = dingwei(temp, book);
    fflush(stdin);
    if(tep == NULL)
        return 0;

    system("cls");
	printf("\t"H"\n");
    printf("\t|\t\t\tɾ��ͼ��\t\t\t|\n");
    printf("\t"H"\n");
    printf("\tҪɾ������Ϣ���£�\n");
    show_book(tep);
    printf("\t�Ƿ�ȷ��ɾ��(Y/N)��");
    chioce = getchar();
    if(chioce == 'Y' || chioce == 'y'){
        p = tep;
        tep->prev->next = p->next;
        p->next->prev = tep->prev;
        free(p);
        return 1;
    }
    return -1;
}
//----------------------------end----------------------------

//------------------------�޸�ͼ����Ϣ����--------------------
/** �޸�ͼ����Ϣ */
void book_alter(Book *temp ,Book *book){
    Book *tep = NULL;
    printf("[�޸�ͼ����Ϣ]\n\t������ͼ����ţ�");
    tep = dingwei(temp, book);
    if(tep == NULL)
        return ;
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t\t�޸�ͼ��\t\t\t|\n");
    printf("\t"H"\n");
    printf("\tҪ�޸ĵ�ͼ����Ϣ\n");
    show_book(tep);
    printf("������ͼ����Ϣ��\n");
	printf("\t"H"\n");
    book_construct(tep);
    printf("\t�޸ĳɹ�,");
    system("pause");
}
//----------------------------end------------------------

//---------------------------�ļ�����-------------------------
/** ���ļ���ȡ���� */
void book_read(Book *book){
    FILE *fp = NULL;
    Book *p = NULL, *temp = book;
    if((fp = fopen("books.txt", "r")) == NULL){
        default_book();
        fp = fopen("books.txt", "r");
    }
    while( !feof(fp) ){
        p = (Book *)malloc(sizeof(*p));
        fscanf(fp,"%s%s", p->book_name, p->author);
        fscanf(fp,"%s%s", p->isbn, p->publisher);
        fscanf(fp,"%d", &p->pub_data);
        fscanf(fp,"%f%d",&p->price, &p->stock);

        while(temp->next != book)
            temp = temp->next;
        p->next = temp->next;
        temp->next = p;
        p->prev = temp;
        p->next->prev = p;
    }
    fclose(fp);
}

/** �����ݵ����ļ� */
void book_write(Book *book){
    FILE *fp = NULL;
    Book *temp = book;
    int falg = 0;
    if((fp = fopen("books.txt", "w")) == NULL){
        printf("\t�ļ���ʧ�ܣ�\n");
        exit(-1);
    }
    while(temp->next != book){
        if( falg )
            fputc('\n', fp);
        fprintf(fp, "%s %s %s %s %d %f %d",temp->next->book_name, temp->next->author,temp->next->isbn,
                temp->next->publisher, temp->next->pub_data, temp->next->price, temp->next->stock);
        temp = temp->next;
        falg = 1;
    }
    fclose(fp);
}
//------------------------------end------------------------------

//-----------------------------ѧ�����Ĺ���-------------------------
void pack_std_title(Book *temp, Book *book) {
    system("cls");
    show_std(book);
    book_display(temp, book);
    show_std_meneu();
}

void show_std(Book *book){
    int n = show_num(book);
    printf("\t"H"\n");
    printf("\t|\t\t     ͼ�����ϵͳ\t\t\t|\n");
    printf("\t"H"\n");
    printf("\t|   ��ǰ��棺\t\t\t\t\t%d\t|\n",n);
    printf("\t"H"\n");
    printf("\t|\t����\t\t����\t\t�۸�\t\t|\n");
}

 void show_std_meneu() {
    printf("\t|\t\t\t\t\t\t\t|\n");
    printf("\t|    �� ��һҳ\t\t�� ��ҳ\t\t��һҳ��\t|\n");
    printf("\t"H"\n");
    printf("\t| a������ͼ��\t\tb������ \tc���鿴ͼ����Ϣ\t|\n");
    printf("\t| d���ѽ�ͼ��\t\te������ \tf���˳� \t|\n");
    printf("\t"H"\n");
 }
//-----------------------------end-------------------------------

//------------------------ ͼ��������---------------------------

void sort_of_bookname(Book *book){
    Book *i = NULL, *j = NULL;
    Book *follow = NULL;
    Book *temp = book;
    char book_name[20];
    temp->next->prev = temp->prev;  //��һ����㲻�μ�����
    for(i = temp->next; i->prev != i; i = i->prev){
        strcpy(book_name,i->prev->book_name);
        follow = i;
        for(j = i->prev; j != i; j = j->prev){
            if(strcmp(j->prev->book_name,book_name) < 0){
                strcpy(book_name ,j->prev->book_name);
                follow = j;
            }
        }
        temp->next = follow->prev;
        temp = follow->prev;
        follow->prev = temp->prev;
    }
    temp->next = i;  //ʣ�����һ������
    i->next = book;
    book->prev = i;  //���õ�һ������prevָ�����һ������
    //���½�prevָ��������
    temp = book;
    while(temp->next != book){
        temp->next->prev = temp;
        temp = temp->next;
    }
}

//------------------------���--------------------------
void add_stock(Book *temp, Book *book){
    Book *tep = NULL;
    int num = 0;
    printf("[���]\n\t������ͼ����ţ�");
    tep = dingwei(temp, book);
    if(tep == NULL)
        return ;
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t\t ��   ��  \t\t\t|\n");
    printf("\t"H"\n");
    printf("\tѡ���ͼ����Ϣ���£�\n");
    show_book(tep);
    printf("\t���������������");
    scanf("%d", &num);
    tep->stock += num;
    printf("\t���ɹ���");
    system("pause");
}

//------------------------����--------------------------
void reduce_stock(Book *temp, Book *book){
    Book *tep = NULL;
    int num = 0;
    printf("[����]\n\t������ͼ����ţ�");
    tep = dingwei(temp, book);
    if(tep == NULL)
        return ;
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t\t ��   ��  \t\t\t|\n");
    printf("\t"H"\n");
    printf("\tѡ���ͼ����Ϣ���£�\n");
    show_book(tep);
    printf("\t���������������");
    scanf("%d", &num);
    if(tep->stock < num){
        printf("\t����ʧ�ܣ���治�㣡");
        system("pause");
        return ;
    }
    tep->stock -= num;
    printf("\t����ɹ���");
    system("pause");
}
//------------------------����-------------------------
void borrow_book(Book *temp, Book *book){
    Book *tep = NULL;
    char chioce;
    int num = 1;
    printf("[����]\n\t������ͼ����ţ�");
    tep = dingwei(temp, book);
    if(tep == NULL)
        return ;
    system("cls");
    printf("\t"H"\n");
    printf("\t|\t\t    �� �� ͼ ��\t\t\t\t|\n");
    printf("\t"H"\n");
    printf("\tѡ���ͼ����Ϣ���£�\n");
    show_book(tep);
    printf("\t�Ƿ�ȷ�Ͻ���(Y/N)��");
    getchar();
    chioce = getchar();
    if((chioce == 'Y' || chioce == 'y') && tep->stock > 0){
        tep->stock -= num;
        printf("\t���ĳɹ���");
        system("pause");
    }
    else{
        if(!(tep->stock > 0))
            printf("\t��治�㣬����ʧ�ܣ�");
        else
            printf("\t����ʧ�ܣ�");
        system("pause");
        return ;
    }

}
//----------------------��λͼ��------------------------
Book* dingwei(Book *temp, Book *book){
    int i, chioce;
    scanf("%d", &chioce);
    for(i = 0; i < chioce; i++){
        temp = temp->next;
        if(chioce > 9 || temp == book){
            printf("\tδ�ҵ�����鼮��");
            system("pause");
            return NULL;
        }
    }
    return temp;
}
//------------------------ ��һҳ -----------------------
void pack_up(Book **temp, Book *book){
    Book *tep = *temp;
    int flag = 1, i;
    for(i = 0; i < 9; i++){
        tep = tep->prev;
        if(tep == book->prev){
            flag = 0;
            break;
        }
    }
    if(flag)
        *temp = tep;
}

//------------------------ ��ҳ -----------------------
void pack_begin(Book **temp, Book *book){
    *temp = book;
}

//------------------------ ��һҳ-----------------------
void pack_down(Book **temp, Book *book){
    Book *tep = *temp;
    int flag = 1, i;
    for(i = 0; i < 9; i++){
        tep = tep->next;
        if(tep == book){
            flag = 0;
            break;
        }
    }
    if(flag)
        *temp = tep;
}

/** ����ͼ�� */
void book_display(Book *temp, Book *book){
    int i = 1;
    while(temp->next != book && i < 10){
        printf("\t| %d��",i++);
        show_books(temp->next);
        temp = temp->next;
    }
}

 /** ���캯�� */
void book_construct(Book *book){
    fflush(stdin);
    printf("\t������������");
    gets(book->book_name);
    printf("\t���������ߣ�");
    gets(book->author);
    printf("\t������ISBN�ţ�");
    gets(book->isbn);
    printf("\t����������磺");
    gets(book->publisher);
    fflush(stdin);
    printf("\t������ʱ�䣺");
    scanf("%d", &book->pub_data);
    printf("\t������۸�");
    scanf("%f", &book->price);
}

/** ����Ĭ��ͼ�� */
void default_book(){
    FILE *fp = NULL;
    if((fp = fopen("books.txt", "w")) == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        exit(-1);
    }
    fprintf(fp, "%s %s %s %s %d %f %d", "c����","�Ͼž�", "c123",
            "�Ͼ�ѧ��", 2016, 30.0f, 1);
    fclose(fp);
}

/** �������� */
Book* book_form(){
    Book *book;
    book = (Book *)malloc(sizeof(* book));
    if( !book )
        exit(-1);
    book->next = book->prev = book;
    return book;
}

/** �ͷ����� */
void book_unloose(Book *book){
    Book *temp = book;
    Book *q;
    while(temp->next != book){
        q = temp->next;
        temp->next = q->next;
        free(q);
    }
    free(book);
}

/** ������ */
int show_num(Book *book){
    Book *temp = book;
    int num = 0;
    while(temp->next != book){
        num++;
        temp = temp->next;
    }
    return num;
}

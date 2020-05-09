#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100		// ��ྰ�����
#define M 10		// map
#define INF 999999	// ���ֵ
#define L "------------------------------------------------------------"

/** �洢������Ϣ�Ľṹ�� */
typedef struct _vertex {
    int number; // ÿ��������Ψһ�ı�ţ���ϵͳ����
    int x;      // ���������
    int y;      // ����������
    char designation[20];   // ����
    char synopsis[200];     // ���
}Vertex;
/** �洢������Ϣ�Ľṹ�� */
typedef struct {
    Vertex vexs[N];     // ������Ϣ��
    int edges[N][N];    // �ڽӾ���
    int n;				// ������
}Mgraph;

/** stack */
typedef struct {
    int data[N];
    int top;
}Stack;

void _main(Mgraph g, Stack st, int path[N][N], int dist[N][N]);
void show_plane_title();
void show_plane_content(Mgraph g);
void show_plane_menu();
int show_plane_model(Mgraph g);
void show_grid_content(Mgraph g);
void show_grid_menu();
int show_grid_model(Mgraph g);
void read_file(Mgraph *g);
void update_file(Mgraph g);
void shortest_path(Mgraph g, int path[N][N], int dist[N][N]);
void show_path(Mgraph g, int path[N][N], int dist[N][N], int n1, int n2);
void search(Mgraph g, int search_num);
int judeg(Stack *st, int num);
void all_path(Mgraph g, Stack *st,  int s1, int s2);
void add_side(Mgraph *g, int n);
void del_site(Mgraph *g, int number);
void add_site(Mgraph *g);
void update_edges(Mgraph *g, int n);
void change_msg(Mgraph *g, int n);
int str_lenght(char *s);

int OK = 0; 	// 1����ʾpath��dist����ʹ��

int main() {
    Mgraph g;
    Stack st;
    st.top = 0;
    int path[N][N];
    int dist[N][N];	
    read_file(&g);				// ��ȡ�ļ�
	_main(g, st, path, dist);	// ���г���
    return 0;
}

void _main(Mgraph g, Stack st, int path[N][N], int dist[N][N]) {
	system("cls");
	int k = 1;			// ��ʾ����Ĳ˵�
	int chioce;			// ѡ��Ĺ���
	int num, n1, n2;	// ѡ��ı��
	while(1) {
		if(k == 1)
			chioce = show_plane_model(g);
		else
			chioce = show_grid_model(g);
		
		switch(chioce) {
			case 1:		// �л��˵�
				if (k == 1) k = 2;
				else k = 1;
				break;
			case 2:		// ���Ҿ���
				printf("\t�����뾰���ţ�");
				scanf("%d", &num);
				search(g, num);
				break;
			case 3:		// ��Ӿ���
				add_site(&g);
				update_file(g);
				break;
			case 4:		// ɾ������
				printf("\t�����뾰���ţ�");
				scanf("%d", &num);
				del_site(&g, num);
				update_file(g);
				break;
			case 5:		// �޸ľ���
				printf("\t�����뾰���ţ�");
				scanf("%d", &num);
				change_msg(&g, num-1);
				update_file(g);
				break;
			case 6:		// ���·��
				printf("\t������������ı�ţ�");
				scanf("%d%d", &n1, &n2);
				if(n1<1 || n1>g.n || n2<1 || n2>g.n) {
					printf("\t����ı������,");
					system("pause");
					break;
				}
				if(!OK) shortest_path(g, path, dist);
				show_path(g, path, dist, n1-1, n2-1);
				break;
			case 7:		// ȫ��·��
				printf("\t������������ı�ţ�");
				scanf("%d%d", &n1, &n2);
				if(n1<1 || n1>g.n || n2<1 || n2>g.n) {
					printf("\t����ı������,");
					system("pause");
					break;
				}
				system("cls");
				printf("\t " L "\n");
				printf("\t|\t\t\tȫ��·����ѯ\t\t\t    |\n");
				printf("\t " L "\n");
				all_path(g, &st, n1-1, n2-1);
				printf("\n\t");
				system("pause");
				break;
			case 0:		// �˳�����
				printf("\t");
				exit(0);
			default:
				break;
		}
	}
}

// ----------------------------�б�ģʽ�˵�------------------------------
/**
 * ��ʼ�˵�ҳ���
 */
void show_plane_title() {
	printf("\t " L "\n");
	printf("\t|\t\t\tУ԰���γ���\t\t\t    |\n");
	printf("\t " L "\n");
}

/**
 * ���ݿ����
 */
void show_plane_content(Mgraph g) {
	char str[50];
	int n = 0;
	printf("\t|   ���      ����\t\t\t���\t\t    |\n");
	for(int i=0; i < g.n; i++) {
		strncpy(str, g.vexs[i].synopsis, 30);
		if((n = str_lenght(g.vexs[i].synopsis) > 30)) {
			str[30] = '\0';
			strcat(str, "..");
		}
		printf("\t|   %-9d%-15s%-32s|\n", g.vexs[i].number, g.vexs[i].designation, str);
	}
	printf("\t " L "\n");
}

/**
 * ���ܿ����
 */
void show_plane_menu() {
	printf("\t| 1��ƽ��ģʽ\t2����ѯ����\t3�����Ӿ���\t4��ɾ������ |\n");
	printf("\t| 5���޸ľ���\t6�����·��\t7��ȫ��·��\t0���� ��    |\n");
	printf("\t " L "\n");
}

/**
 * �б�ģʽ�˵�
 */
int show_plane_model(Mgraph g) {
	system("cls");
	show_plane_title();
	show_plane_content(g);
	show_plane_menu();
	int choice;
	printf("\t��ѡ���ܣ�");
	scanf("%d", &choice);
	return choice;
}
// ---------------------------------end----------------------------------

// ----------------------------ƽ��ģʽ�˵�------------------------------
/**
 * ���ݿ����
 */
void show_grid_content(Mgraph g) {
	char str[20];       	// ��ʱ�������
    char map[M][M][20]; 	// ƽ��ͼ����
	char tab[10] = "     ";	// �ո񳤶�
	int i;
    // ��ʼ��ƽ��ͼ
    for(i=0; i < M; i++) {
        for(int j=0; j < M; j++) {
            strcpy(map[i][j], tab);
        }
    }
    // ����bug�����xy�ظ�������ֵ��������
    for(i=0; i < g.n; i++) {
        // sprintf: ������ת�����ַ��������Ҹ���ǰ����ַ���
        sprintf(str, "%d", g.vexs[i].number);
        strcat(str, g.vexs[i].designation);
        strcat(str, "  ");
        strcpy(map[g.vexs[i].x][g.vexs[i].y], str);
    }
    // ���ƽ��ͼ
    for(i=0; i < M; i++) {
		printf("\t");
        for(int j=0; j < M; j++) {
            printf("%s",map[i][j]);
        }
        printf("\n");
    }
}

/**
 * ���ܿ����
 */
void show_grid_menu() {
	printf("\t " L "\n");
	printf("\t| 1���б�ģʽ\t2����ѯ����\t3�����Ӿ���\t4��ɾ������ |\n");
	printf("\t| 5���޸ľ���\t6�����·��\t7��ȫ��·��\t0���� ��    |\n");
	printf("\t " L "\n");
}

/**
 * ƽ��ģʽ�˵�
 */
int show_grid_model(Mgraph g) {
	system("cls");
	show_plane_title();
	show_grid_content(g);
	show_grid_menu();
	int choice;
	printf("\t��ѡ���ܣ�");
	scanf("%d", &choice);
	return choice;
}
// ---------------------------------end----------------------------------

// ------------------------------�ļ���ȡ����----------------------------
/**
 * ��ȡ�ļ���Ϣ
 */
void read_file(Mgraph *g) {
    FILE *fv, *fe;
    int n = 0;  // ��ȡ�Ķ������
	// ���ļ�
    if ((fv = fopen("vexs.txt", "r")) == NULL || (fe = fopen("edges.txt", "r")) == NULL) {
        printf("�ļ���ʧ��\n");
        exit(-1);
    }
    // ��ȡ������Ϣ
    while (!feof(fv)) {
        fscanf(fv, "%d%d%d%s%s", &g->vexs[n].number, &g->vexs[n].x, &g->vexs[n].y,
               g->vexs[n].designation, g->vexs[n].synopsis);
        n++;
    }
    g->n = n;
    // ��ʼ������
    int x, y, val;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                g->edges[i][j] = 0;
            else
                g->edges[i][j] = INF;
        }
    }
	// ��ȡ���Ӿ���
    while(!feof(fe)) {
        fscanf(fe, "%d%d%d", &x, &y, &val);
        g->edges[x][y] = val;
        g->edges[y][x] = val;
    }
    fclose(fv);
    fclose(fe);
}

/**
 * �����ļ�����Ϣ
 */
void update_file(Mgraph g) {
    FILE *fv, *fe;
	int i;
	// ���ļ�
	if ((fv = fopen("vexs.txt", "w")) == NULL || (fe = fopen("edges.txt", "w")) == NULL) {
        printf("�ļ���ʧ��\n");
        exit(-1);
    }
    // ���¶�����Ϣ
    fprintf(fv, "%d %d %d %s %s", g.vexs[0].number, g.vexs[0].x, g.vexs[0].y, g.vexs[0].designation, g.vexs[0].synopsis);
    for(i = 1; i < g.n; i++) {
        fprintf(fv, "\n%d %d %d %s %s", g.vexs[i].number, g.vexs[i].x, g.vexs[i].y,
              g.vexs[i].designation, g.vexs[i].synopsis);
    }
    // ���¾�����Ϣ
    int flag = 0;				// �ж��Ƿ����ļ��мӻ��У���һ�β���
    for(i = 0; i < g.n; i++) {
        for(int j=i+1; j < g.n; j++) {
            if(g.edges[i][j] != 0 && g.edges[i][j] != INF) {
                if(flag) fputc('\n',fe);
                fprintf(fe, "%d %d %d", i, j, g.edges[i][j]);
                flag = 1;
            }
        }
    }
    fclose(fv);
    fclose(fe);
}

// ---------------------------------end----------------------------------

// -------------------------------���ܺ���-------------------------------

/**
 * ���Ӿ�����Ϣ
 */
void add_site(Mgraph *g) {
	system("cls");
	printf("\t " L "\n");
	printf("\t|\t\t\t��Ӿ�����Ϣ\t\t\t    |\n");
	printf("\t " L "\n");
    int n = g->n;
    g->vexs[n].number = n+1;
    fflush(stdin);
    printf("\t�����뾰�����ƣ�");
    scanf("%s", g->vexs[n].designation);
    fflush(stdin);
    printf("\t�����뾰�������x y��");
    scanf("%d%d", &g->vexs[n].x, &g->vexs[n].y);
    fflush(stdin);
    printf("\t�����뾰���������");
    scanf("%s", g->vexs[n].synopsis);
	fflush(stdin);
    add_side(g, g->vexs[n].number);
    printf("\t��Ӿ���ɹ�,");
    g->n++;
	system("pause");
}

/**
 * �����ɾ������
 * @param number Ҫɾ���ı��
 */
void del_site(Mgraph *g, int number) {
	char c;
	system("cls");
	printf("\t " L "\n");
	printf("\t|\t\t\t��Ӿ�����Ϣ\t\t\t    |\n");
	printf("\t " L "\n");
	// ����ı�Ų�����
    if(number > g->n || number < 1) {
        printf("\t����ı������,");
		system("pause");
        return ;
    }
	printf("\n\t��ţ�%d\n", g->vexs[number-1].number);
	printf("\t���ƣ�%s\n", g->vexs[number-1].designation);
	printf("\t��飺%s\n\n", g->vexs[number-1].synopsis);
	printf("\t�Ƿ�ȷ��ɾ��(y/n)��");
	fflush(stdin);
	c = getchar();
	// ȡ��ɾ��
	if(c == 'n') {
		printf("\tȡ��ɾ������,");
		system("pause");
		return ;
	}
    // ɾ������
    for(int j=number; j < g->n; j++) {
        g->vexs[j] = g->vexs[j+1];
        g->vexs[j].number -= 1;
    }
    // ���±ߵĹ�ϵ
    update_edges(g, number);
    g->n--;
	printf("\n\tɾ���ɹ���");
	system("pause");
}

/**
 * ���ľ�����Ϣ
 * @param n Ҫ���ĵĶ������Ϣ
 */
void change_msg(Mgraph *g, int n) {
    int choice = 0;
	system("cls");
	printf("\t " L "\n");
	printf("\t|\t\t\t���ľ�����Ϣ\t\t\t    |\n");
	printf("\t " L "\n");
    printf("\t��ѡ���޸ĸö����ʲô��Ϣ: \n");
    while(choice != 5) {
        printf("\t1:���� 2������ 3������ 4���޸�/���ӱ߹�ϵ: 5: �˳���");
        scanf("%d", &choice);
		fflush(stdin);
        switch (choice) {
            case 1:		// �޸�����
                printf("\t���������ƣ�");
                scanf("%s", g->vexs[n].designation);
				fflush(stdin);
                break;
            case 2:		// �޸�����
                printf("\t����������(x,y)��");
                scanf("(%d,%d)", &g->vexs[n].x, &g->vexs[n].y);
				fflush(stdin);
                break;
            case 3:		// �޸�����
                printf("\t������������");
                scanf("%s", g->vexs[n].synopsis);
				fflush(stdin);
                break;
            case 4:		// �޸ı��ϵ
                add_side(g, n+1);
                break;
            case 5:		// �˳��޸�
				printf("\n\t�޸ĳɹ�,");
				system("pause");
                return ;
            default:
                break;
        }
    }
}

/**
 * ��ѯ���ص����Ϣ
 * ����Ų�ѯ
 */
void search(Mgraph g, int search_num) {
	system("cls");
	printf("\t " L "\n");
	printf("\t|\t\t\t������Ϣ��ѯ\t\t\t    |\n");
	printf("\t " L "\n");
	if(search_num < 1 || search_num > g.n) {
		printf("\tδ�ҵ���صص�,");
	} else {
		printf("\n\t��ţ�%d\n", g.vexs[search_num-1].number);
		printf("\t���ƣ�%s\n", g.vexs[search_num-1].designation);
		printf("\t���꣺%d %d\n", g.vexs[search_num-1].x, g.vexs[search_num-1].y);
		printf("\t��飺%s\n\n\t", g.vexs[search_num-1].synopsis);
	}
	system("pause");
}

/**
 * ����������·������
 * @param path ������������·������
 * @param dist �����������·����������
 */
void shortest_path(Mgraph g, int path[N][N], int dist[N][N]) {
    // ��ʼ��
    for(int i=0; i < g.n; i++) {
        for(int j=0; j < g.n; j++) {
            dist[i][j] = g.edges[i][j];
            if(i!=j && dist[i][j] < INF)
                path[i][j] = j;
            else
                path[i][j] = -1;
        }
    }
    // �������ÿһ�Զ��㽫����̾���
    for(int k=0; k < g.n; k++) {
        for(int i=0; i < g.n; i++){
            for(int j=0; j < g.n; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j]; //ȡС��
                    path[i][j] = path[i][k];    //��Vi�ĺ��
                }
            }
        }
    }
	OK = 1;		// ��OK��1����ʾdist��path�������
}

/**
 * ȫ��·�� => �����������
 * @param s1,s2 ����Ų��������ص��ȫ��·��
 */
void all_path(Mgraph g, Stack *st,  int s1, int s2) {
	// ����ʼ�������st��
    if(st->top == 0) st->data[st->top++] = s1;
	// �õ����˵�Ԫ��
    int s = st->data[st->top-1];
	// �������Ԫ��ʱ�����ľ��㣬���������·��
    if(s == s2) {
		printf("\t");
        for(int i=0; i < st->top-1; i++) {
            printf("%d -> ", st->data[i]+1);
        }
        printf("%d\n", s2+1);
        st->top--;
        return ;
    }
	// �ݹ����
    for(int i = 0; i < g.n; i++) {
        if(s == i) continue;
        if(g.edges[s][i] != INF && !judeg(st, i)) {
            st->data[st->top++] = i;
            all_path(g, st, s1, s2);
        }
    }
    st->top--;
}

// ---------------------------------end----------------------------------

// -------------------------------���ߺ���-------------------------------
/**
 * ��ȡ�ַ�������
 */
int str_lenght(char *s) {
	int i=0;
	while(*(s+i))
		i++;
	return i;
}

/**
 * �ж�num�Ƿ���st��
 * @return ���ڷ���1
 */
int judeg(Stack *st, int num) {
    for(int i=0; i < st->top; i++) {
        if(st->data[i] == num)
            return 1;
    }
    return 0;
}

/**
 * ����/���������ߵĹ�ϵ
 * @param n ָ����һ����
 */
void add_side(Mgraph *g, int n) {
    printf("\t������þ���%d����������x�ľ���s\n\t��ʽ��x s, 0 0�˳����룺", n);
    int x, s;
	scanf("%d%d", &x, &s);
    while(x > 0 && s > 0) {
        g->edges[n-1][x-1] = s;
        g->edges[x-1][n-1] = s;
        printf("\t��ʽ��x s, 0 0�˳����룺");
		scanf("%d%d", &x, &s);
		OK = 0;		// ��OK��0����ʾdist��path���鲻����
    }
}

/**
 * ���¾�����Ϣ
 * @param n ��n��ʼ����
 */
void update_edges(Mgraph *g, int n) {
    int x, y;
    for(int i=n; i < g->n; i++) {
        for(int j=i+1; j < g->n; j++) {
            if(i < n && j < n) continue;
			// ����ĳ���㱻ɾ���������ı��Ҫ��ǰ����
            x = i < n ? i : i-1;
            y = j < n ? j : j-1;
            g->edges[x][y] = g->edges[i][j];
            g->edges[y][x] = g->edges[j][i];
        }
    }
}

/**
 * ������·��
 */
void show_path(Mgraph g, int path[N][N], int dist[N][N], int n1, int n2) {
    int k;
	system("cls");
	printf("\t " L "\n");
	printf("\t|\t\t\t���·����ѯ\t\t\t    |\n");
	printf("\t " L "\n");
	printf("\n\tV%d��V%d����̳���:",n1+1,n2+1);
    printf("%d\t",dist[n1][n2]);		//���Vi��Vj�����·������
	k = path[n1][n2];					//ȡ·����Vi�ĺ���Vk
    if(k == -1){
		printf("\n\tThere is no path between V%d and V%d\n",n1+1,n2+1);   //·��������
	}else{
		printf("\n\t���·��Ϊ:");
		printf("(V%d",n1+1);			//���Vi�����i
		while(k != n2){					//k������·���յ�jʱ
			printf(" -> V%d",k+1);		//���k
			k=path[k][n2];				//��·������һ�������
		}
		printf(" -> V%d)\n",n2+1);		//���·���յ����
	}
	printf("\n\t");
	system("pause");
}

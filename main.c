#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
const int dim_users = 100;
const int dim_publish = 200;
const int dim_messenge = 150;
const int ESC = 27;

typedef struct
{
    int idIssuing;
    int idReceiver;
    int idContent;
    char message [150];
    char timeSend[50];
    int read;
} stMessenge;

typedef struct
{
    int idUserContact;
    int idContent;
    char userNamePost[30];
    char title [30];
    char description[300];
    char categoria[30];
    int likes;
    int active;
    char report[100];
    int cost;
    char time[30];
    char places[100];
    char feedback[60];
    char currentTIME[50];
    int idFeedback;
} stPublish;

typedef struct
{
    int idUser;
    char lastName[50];
    char firstName[50];
    int dni;
    char userName[30];
    char password[30];
    char city[50];
    int age;
    char email[50];
    char gender[30];
    int points;
    int level;
    char ranki[20];
    int status;
} stUser;

///**********************************************************************************************************///
///**********************************************************************************************************///
void registe(char mainArchivo[]);
void login(char mainArchivo[], char publishArch[], char messangerUsuarios[],char currentTIME[50]);
int searchUserName(char mainArchivo[], char name[]);
void userActive(char mainArchivo[], int currentID);
int validationDNI(char mainArchivo[], int dni);
int ageOver(int age);
int lastID(char mainArchivo[]);

///**********************************************************************************************************///
///**********************************************************************************************************///
void mainMenu(int currentID, char publishArch[], char mainArchivo[], char messangerUsuarios[],char currentTIME[50]);
void editUserMenu(int currentID, char mainArchivo[]);
void showUserOff(char mainArchivo[]);
void editUserCity(char mainArchivo[],int currentID, char newCity[50]);
int editUserStatus(char mainArchivo[], int currentID);
int editUserStatus(char mainArchivo[], int currentID);
void editUserGender(char arch[],int currentID, char newGender[30]);
void editUserEmail(char arch[],int currentID, char newEmail[30]);
void editUserAge(char arch[],int currentID);
void editUserPassword(char arch[],int currentID, char newPassword[30]);
void showOneUser(stUser user);
void showMyUser(stUser user);
void showUser(char archivo[]);
///**********************************************************************************************************///
///**********************************************************************************************************///
void postMenu(int currentID, int idContent, char publishArch[], char mainArchivo[],char currentTIME[50]);
int getIdPost(char publishArch[],char mainArchivo[],int currentID,int postArray[]);
void showPostID(char publishArch[],int idPost,char mainArchivo[]);
int idPostToArray(char publishArch[],int allPostArray[]);
void randomPost(int validosRandom, int allPostArray[],char publishArch[],char mainArchivo[]);
int randomValuePost(int random,int randomArray[]);
void otherMenu(int currentID, char mainArchivo[],char publishArch[],char currentTIME[]);
void feedbackMenu(char publishArch[],char mainArchivo[],int currentID,char currentTIME[]);
void showFeedback(char publishArch[],char mainArchivo[],char currentTIME, int currentID);
void reportPost(char publishArch[],int reportID);
void showReport(char publishArch[],char mainArchivo[]);
void feedback(char publishArch[],int currentID, char mainArchivo[], int value);
int publishPost(int currentID,char publish [],char mainArchivo[],char currenTime[]);
void statusPublisPost (int postStatus);
void showPublishOne(stPublish post, stUser user);
void showPublishPostIndividual(char publish[],char mainArchivo[],int currentID);
void showPublish(char publish[],char mainArchivo[],int currentID,char currentTIME[]);
void postLike(char publishArch[],int like,char mainArchivo[],int currentID);
void points(char mainArchivo[],int currentID);
void rankUser(char mainArchivo[],int currentID);
int lastIDPost(char publish[]);
void editPostMenu(int idContent, char publishArch[], int currentID, char mainArchivo[],char currentTIME,int validos,int postArray[]);
int rightPost(int validos,int postArray[], int value);
void editSelectPlace(char publish[],stPublish post, int value);
void editPostTopics(char publish[],int value,char newTopics[30]);
void editPostTime(char publish[],int value,int newTime);
void disablePost(char publish[], int value);
void editPostTitle(char publish[],int value,char newTitle[30]);
void editPostCost(char publish[],int value, int newCost);
void editPostDescription(char publish[],int value,char newDescription[300]);
void searchMyPost(char publish[],char mainArchivo[],int currentID);
stUser searchNamePOST(int currentID, char mainArchivo[]);
///**********************************************************************************************************///
///**********************************************************************************************************///
void messengeMenu(int currentID, char mainArchivo[], char messangerUsuarios[], char timeSend[]);
void sendMesengges (int currentID, char messangerUsuarios[], char mainArchivo[],char timeSend[]);
stUser searchUserMessenge(char name[],char mainArchivo[]);
int lastIDsms (char messangerUsuarios[]);
void viewMesenggesSend (stUser user,char messangerUsuarios[], char mainArchivo[]);
void statusRead(stMessenge sms);
void messagesDisplay(stMessenge sms);
int viwePendingInbox(stUser user,int currentID,char messangerUsuarios[], char mainArchivo[]);
int viewInboxMessagerOk (stUser user,char mainArchivo[], char messangerUsuarios[]);
void inboxMessenger(stUser userSearch,int currentID,char messangerUsuarios[],char mainArchivo[],char currenTime[]);
void viewMesenggesInbox(int currentID,char messangerUsuarios[],char mainArchivo[],stUser userSearch,stUser userSearch1);
void replyMessage (int currentID, char messangerUsuarios[], char mainArchivo[],char userNameSearchR[],char currenTime[]);
int loadInbox(int j);
int viewMessagenPending(int i,int arrayMessangerInd[],stUser arrayMessanger[]);
void statusMessangerRead(char messangerUsuarios[],char mainArchivo[],stUser userSearch,stMessenge arraySms[],int validos);
void statusNENE(char messangerUsuarios[],char mainArchivo[],stUser userSearch);
void displayUsersName(char mainArchivo[], int currentID);
///**********************************************************************************************************///
///**********************************************************************************************************///


int main()
{
    char mainArchivo[]= {"users.dat"};
    char publishArch[]= {"publish.dat"};
    char messangerUsuarios[]= {"messangerUsuarios.dat"};
    stPublish publish [dim_publish];
    stUser user [dim_users];
    stMessenge messagesUser[dim_messenge];
    ///-////////////////////////////////////////////////////// Current Time
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char currentTIME[50];
    strftime(currentTIME,50,"%d/%m/%y a las %H:%M:%S",tlocal);
    ///-//////////////////////////////////////////////////////

    int control,menu;
    do
    {
        printf("\n\t\t\t\t\t\t ==================== \n");
        printf("\n\t\t\t\t\t\t   [4] Punteros   \n");
        printf("\n\t\t\t\t\t\t ==================== \n\n\n");
        printf("\n\t\t\t\t\t[1] - Registrate!\n");
        printf("\n\t\t\t\t\t[2] - Inicia Sesion!\n");
        printf("\n\n\n\t\t\t\t\t");

        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            system("cls");
            fflush(stdin);
            registe(mainArchivo);
            break;
        case 2:
            system("cls");
            fflush(stdin);
            login(mainArchivo, publishArch,messangerUsuarios,currentTIME);
            break;
        }
        printf("\n Presione cualquier tecla volver al Inicio, ESC para salir... \n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=ESC);
    return 0;
}

///**********************************************************************************************************/// LOGIN

void login(char mainArchivo[], char publishArch[], char messangerUsuarios[],char currentTIME[50])
{
    int control;
    char username[30];
    char password[30];
    char userCopyName[30];
    FILE *log =fopen(mainArchivo,"r+b");
    stUser user;
    int status=0;
    int userStatus=0;
    int currentID;
    do
    {
        do
        {
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*** Ingrese el nombre de Usuario: ***");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t--> ");
            fflush(stdin);
            gets(username);
            printf("\n\n\n");

            if(strlen(username)==0)
            {
                printf("\n\t  Password incorrecto, intente nuevamente...");
            }
            else
            {
                userStatus=searchUserName(mainArchivo,username);
                if(userStatus==0)
                {
                    printf("\n\t  El Usuario ingresado no existe, intente nuevamente...\n");
                }
            }
        }
        while(userStatus==0);

        do
        {

            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*** Ingrese la contrasenia:       ***");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t--> ");
            fflush(stdin);
            gets(password);
            rewind(log);
            while(fread(&user,sizeof(user),1,log)>0)
            {
                if(strcmp(username,user.userName)== 0 && strcmp(password,user.password)== 0)
                {
                    system("cls");
                    printf("\n  Hola de nuevo %s! \n\n", username);
                    strcpy(userCopyName,username);
                    currentID=user.idUser;
                    userActive(log,currentID);
                    mainMenu(currentID,publishArch,mainArchivo,messangerUsuarios,currentTIME);
                    status=1;
                }
            }
            if(status==0)
            {
                printf("\n\t  El password ingresado es incorrecto...\n");
                printf("\n\t  Presione cualquier tecla para volver a intentar, ESC para salir.\n");
                fflush(stdin);
                control=getch();
            }
        }
        while(status==0 && control!=ESC);
    }
    while(status=0);
    fclose(log);
}

///**********************************************************************************************************/// LOGIN
///**********************************************************************************************************/// REGISTRO

void registe(char mainArchivo[])
{
    int flag=0;
    stUser user;
    FILE *User_Arch = fopen(mainArchivo,"ab");
    int i=lastID(mainArchivo);

    if (User_Arch!=NULL)
    {
        fflush(stdin);
        printf("\n  Ingrese su Apellido: \n");
        printf("\n --->  ");
        gets(user.lastName);

        fflush(stdin);
        printf("\n  Ingrese su Nombre:  \n");
        printf("\n --->  ");
        gets(user.firstName);

        do
        {
            printf("\n  Ingrese su edad: \n");
            printf("\n --->  ");
            scanf("%d",&user.age);
            flag=ageOver(user.age);
        }
        while(flag==0);
        do
        {
            printf("\n  Ingrese su DNI: \n");
            printf("\n --->  ");
            fflush(stdin);
            scanf("%d",&user.dni);
            flag=validationDNI(User_Arch,user.dni);
            if(flag==1)
            {
                printf("\n  DNI ya registrado, ingrese un nuevo DNI\n");
            }
        }
        while(flag==1);

        do
        {
            fflush(stdin);
            printf("\n Ingrese su nombre de Usuario: \n");
            printf("\n --->  ");
            scanf("%s",&user.userName);
            flag=searchUserName(User_Arch,user.userName);
            if(flag==1)
            {
                printf("\n  Nombre de Usuario ya resgistrado, intente nuevamente...\n");
            }

        }
        while(flag==1);


        fflush(stdin);
        printf("\n  Ingrese su password: \n");
        printf("\n --->  ");
        scanf("%s",&user.password);

        printf("\n  Ingrese su correo electronico \n");
        printf("\n --->  ");
        fflush(stdin);
        gets(user.email);

        fflush(stdin);
        printf("\n  Ingrese su ciudad actual: \n");
        printf("\n --->  ");
        scanf("%s",&user.city);

        fflush(stdin);
        printf("\n  Ingrese su percepcion de genero: \n");
        printf("\n --->  ");
        scanf("%s",&user.gender);
        i++;
        user.idUser=i;
        user.status=1;
        user.points=0;

        fwrite(&user, sizeof(stUser),1, User_Arch);

        fclose(User_Arch);
    }
}
///**********************************************************************************************************/// REGISTRO


int searchUserName(char mainArchivo[], char name[])
{
    int flag =0;
    stUser user;
    FILE * User_arch = fopen (mainArchivo,"rb");
    if(User_arch!=NULL)
    {
        while(flag == 0 && fread(&user, sizeof(stUser),1,User_arch)>0)
        {
            if(strcmp(name,user.userName)==0)
            {
                flag=1;
            }
        }
        fclose(User_arch);
    }
    return flag;
}

void userActive(char mainArchivo[], int currentID)
{
    FILE *pArch = fopen(mainArchivo,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            user.status=1;
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
        fclose(pArch);
    }
}


///**********************************************************************************************************/// VALIDACION DNI

int validationDNI(char mainArchivo[], int dni)
{
    int flag= 0;
    stUser u;
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(User_Arch)
    {
        while(flag==0 && fread(&u, sizeof(stUser),1, User_Arch)>0)
        {
            if(u.dni == dni)
            {
                flag = 1;
            }
        }
        fclose(User_Arch);
    }
    return flag;
}

int ageOver(int age)
{
    int flag;
    if(age>16 && age<105)
    {
        flag=1;
    }
    else
    {
        if(age<16)
        {
            printf("Usted debe tener mas de 16 anios para registrarse");
        }
        else
        {
            printf("\nIngrese una edad correcta\n");
        }
    }

    return flag;
}

///**********************************************************************************************************/// USER ID

int lastID(char mainArchivo[])
{
    FILE *User_Arch =fopen(mainArchivo,"r+b");
    stUser user;
    int lastId=0;
    if(User_Arch)
    {
        fseek(User_Arch, -1*sizeof(stUser), SEEK_END);
        if(fread(&user, sizeof(stUser),1,User_Arch)>0)
        {
            lastId=user.idUser;
        }
        fclose(User_Arch);
    }
    return lastId;
}

///**********************************************************************************************************/// MENU PRINCIPAL

void mainMenu(int currentID, char publishArch[], char mainArchivo[], char messangerUsuarios[],char currentTIME[50])
{
    int idContent;
    int menu,control;

    do
    {
        printf("\n\t Bienvenido, que desea consultar? \n\n");
        printf("\n\t\t [1] - Casilla de Mensajes \n");
        printf("\n\t\t [2] - Posts \n");
        printf("\n\t\t [3] - Editar perfil \n");
        printf("\n\t\t [4] - Cerrar sesion \n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            messengeMenu(currentID,mainArchivo,messangerUsuarios,currentTIME);
            break;
        case 2:
            postMenu(currentID, idContent, publishArch,mainArchivo,currentTIME);
            break;
        case 3:
            editUserMenu(currentID,mainArchivo);
            break;
        case 4:
            printf("\n  Saliendo... Presione ESC\n");
            control=ESC;
            break;
        }

        system("cls");
    }
    while(control!=ESC);
}

///**********************************************************************************************************/// EDICION PERFIL

void editUserMenu(int currentID, char mainArchivo[])
{
    stUser aux;
    system("cls");
    int menu,control,flag=0;
    char newGender[30];
    char newPassword[30];
    char newCity[50];
    char newPlaces[150];
    char newEmail[50];
    do
    {
        printf("\n\t Editar Perfil: \n\n\n");
        printf("\n\t\t[1] - Cambiar Password \n");
        printf("\n\t\t[2] - Cambiar Ciudad \n");
        printf("\n\t\t[3] - Cambiar Edad \n");
        printf("\n\t\t[4] - Cambiar E-mail\n");
        printf("\n\t\t[5] - Cambiar Percepcion de genero\n");
        printf("\n\t\t[6] - Mostrar Perfil\n");
        printf("\n\t\t[7] - Dar de baja la cuenta\n");
        printf("\n\t\t[8] - Usuarios dados de baja\n");
        printf("\n\t\t[0] - Volver al Menu Principal\n");
        printf("\n\n\t\t  ");

        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            printf("\n\t  Ingrese el nuevo Password: \n");
            printf("\n\n\t  ");
            scanf("%s",&newPassword);
            editUserPassword(mainArchivo,currentID,newPassword);
            break;
        case 2:
            printf("\n\t  Ingrese su nueva locacion: \n");
            printf("\n\n\t  ");
            scanf("%s",&newCity);
            editUserCity(mainArchivo,currentID,newCity);
            break;
        case 3:
            editUserAge(mainArchivo,currentID);
            printf("\n\t Edad editada\n");
            break;
        case 4:
            searchNamePOST(currentID,mainArchivo);
            printf("\n\t  Ingrese el nuevo correo electronico: \n");
            printf("\n\n\t  ");
            scanf("%s",&newEmail);
            editUserEmail(mainArchivo,currentID,newEmail);
            break;
        case 5:
            printf("\n\t  Ingrese su percepcion de genero: \n");
            printf("\n\n\t  ");
            scanf("%s",&newGender);
            editUserGender(mainArchivo,currentID,newGender);
            break;
        case 6:
            aux=searchNamePOST(currentID,mainArchivo);
            rankUser(mainArchivo,currentID);
            showMyUser(aux);
            break;
        case 7:
            while(control!=ESC && flag==0)
            {
                printf("\n\t  Esta segurx que quiere darse de baja? \n\n");
                printf("\n\t  Intro para confirmar, ESC para volver.\n");
                fflush(stdin);
                control=getch();
                flag=editUserStatus(mainArchivo,currentID);
                if(flag==1)
                {
                    exit(0);
                }
            }
            break;
        case 8:
            showUserOff(mainArchivo);
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para Menu Principal...\n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=ESC);
}


///***************************************************************************/// Usuarios OFF

void showUserOff(char mainArchivo[])
{
    FILE *User_Arch = fopen(mainArchivo, "rb");
    stUser a;
    if(User_Arch)
    {
        while(fread(&a, sizeof(stUser), 1, User_Arch)>0 && a.status==0)
        {
            showOneUser(a);
        }
        fclose(User_Arch);
    }
}

///**********************************************************************************************************/// EDITOR PERFIL
///*************************************************************************/// CIUDAD

void editUserCity(char mainArchivo[],int currentID, char newCity[50])
{
    FILE *pArch = fopen(mainArchivo,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            strcpy(user.city,newCity);
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }

    }
    fclose(pArch);
}

///*************************************************************************/// STATUS

int editUserStatus(char mainArchivo[], int currentID)
{
    int flag=0;
    FILE *pArch = fopen(mainArchivo,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            user.status=0;
            flag=1;
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
        fclose(pArch);
    }
    return flag;
}

///*************************************************************************/// GENERO ///REVISAR

void editUserGender(char arch[],int currentID, char newGender[30])
{
    FILE *pArch = fopen(arch,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            strcpy(user.gender,newGender);
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
    }
    fclose(pArch);
}

///*************************************************************************/// EMAIL

void editUserEmail(char arch[],int currentID, char newEmail[30])
{
    FILE *pArch = fopen(arch,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            strcpy(user.email,newEmail);
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
    }
    fclose(pArch);
}

///*************************************************************************/// EDAD

void editUserAge(char arch[],int currentID)
{
    FILE *pArch = fopen(arch,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            user.age=user.age+1;
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
    }
    fclose(pArch);
}

///*************************************************************************/// PASSWORD

void editUserPassword(char arch[],int currentID, char newPassword[30])
{
    FILE *pArch = fopen(arch,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            strcpy(user.password,newPassword);
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
        fclose(pArch);
    }
}

///**********************************************************************************************************/// MOSTRAR USER

void showOneUser(stUser user)
{
    printf("\n\t\t\t Informacion de Usuario: \n\n");
    printf("\n\t\t\t Id.......................: %15d", user.idUser);
    printf("\n\t\t\t Usuario..................: %15s", user.userName);
    printf("\n\t\t\t Password.................: %15s", user.password);
    printf("\n\t\t\t Informacion Personal.....: \n\n");
    printf("\n\t\t\t Nombre...................: %15s",user.firstName);
    printf("\n\t\t\t Apellido.................: %15s", user.lastName);
    printf("\n\t\t\t Edad.....................: %15d", user.age);
    printf("\n\t\t\t DNI......................: %15d", user.dni);
    printf("\n\t\t\t Genero...................: %15s \n", user.gender);
    printf("\n\t\t\t Ciudad...................: %15s\n",user.city);
    printf("\n\t\t\t Informacion de Contacto..: \n\n");
    printf("\n\t\t\t Correo electronico.......: %15s\n\n", user.email);
    printf("\n\t\t\t User Status..............: %15d\n",user.status);
}
///**********************************************************************************************************/// User
void showMyUser(stUser user)
{
    printf("\t\t\t------------------------------------------------------------------\n");
    printf("\n\t\t\t***  Usuario.............. : %25s         ***\n", user.userName);
    printf("\n\t\t\t***  Password............. : %25s         ***\n", user.password);
    printf("\n\t\t\t***  Nombre............... : %25s         ***\n", user.firstName);
    printf("\n\t\t\t***  Apellido............. : %25s         ***\n", user.lastName);
    printf("\n\t\t\t***  Edad................. : %25d         ***\n", user.age);
    printf("\n\t\t\t***  DNI.................. : %25d         ***\n", user.dni);
    printf("\n\t\t\t***  Genero............... : %25s         ***\n", user.gender);
    printf("\n\t\t\t***  Ciudad............... : %25s         ***\n", user.city);
    printf("\n\t\t\t***  Email................ : %25s         ***\n", user.email);
    printf("\n\t\t\t***  Ranking.............. : %25s         ***\n", user.ranki);
    printf("\n\t\t\t***  Nivel................ : %25d         ***\n", user.level);
    printf("\n\t\t\t***  Puntos............... : %25d         ***\n", user.points);
    printf("\n\t\t\t------------------------------------------------------------------");
}
///**********************************************************************************************************/// User
void showUser(char archivo[])
{
    FILE *User_Arch = fopen(archivo, "rb");
    stUser a;
    if(User_Arch)
    {
        while(fread(&a, sizeof(stUser), 1, User_Arch)>0 && a.status==1)
        {
            showOneUser(a);
        }
        fclose(User_Arch);
    }
}

///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
///**************************************            Posteos                          ********************************************///
///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
void postMenu(int currentID, int idContent, char publishArch[], char mainArchivo[],char currentTIME[50])
{
    system("cls");
    int menu,control,deletepost;
    int like;
    int validos;
    stPublish postArray[15];

    do
    {
        printf("\n\t Seleccione una accion \n\n");
        printf("\n\t\t [1] - Mis posts \n");
        printf("\n\t\t [2] - Ver post \n");
        printf("\n\t\t [3] - Crear post \n");
        printf("\n\t\t [4] - Editar post \n");
        printf("\n\t\t [5] - Otros  \n");
        printf("\n\t\t [0] - Volver al Menu Principal \n");
        printf("\n\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            showPublishPostIndividual(publishArch,mainArchivo,currentID);
            break;
        case 2:
            showPublish(publishArch,mainArchivo,currentID,currentTIME);
            break;
        case 3:
            publishPost(currentID,publishArch,mainArchivo,currentTIME);
            break;
        case 4:
            validos=getIdPost(publishArch,mainArchivo,currentID,postArray);
            editPostMenu(idContent,publishArch,currentID,mainArchivo,currentTIME,validos,postArray);
            break;
        case 5:
            otherMenu(currentID,mainArchivo,publishArch,currentTIME);
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para menu principal...\n");
        control=getch();
        system("cls");
    }
    while(control!=ESC);
}

///**********************************************************************************************************///

int getIdPost(char publishArch[],char mainArchivo[],int currentID,int postArray[])
{
    stPublish post;
    stUser user;
    int i=0;
    FILE *pOpen =fopen(publishArch,"rb");
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(pOpen && User_Arch)
    {
        user=searchNamePOST(currentID,mainArchivo);

        while(fread(&post,sizeof(stPublish),1,pOpen)>0)
        {
            if(post.idUserContact==user.idUser)
            {
                if(post.active == 1)
                {
                    postArray[i]=post.idContent;
                    i++;
                }
            }
        }
        fclose(pOpen);
        fclose(User_Arch);
    }
    return i;
}
///**********************************************************************************************************///

///**********************************************************************************************************///ShowPostID
void showPostID(char publishArch[],int idPost,char mainArchivo[])
{
    stPublish post;
    stUser user;
    FILE *pOpen =fopen(publishArch,"rb");
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(pOpen && User_Arch)
    {
        fseek(pOpen,(idPost-1)*sizeof(stPublish),SEEK_SET);
        fread(&post,sizeof(stPublish),1,pOpen);
        user=searchNamePOST(post.idUserContact,mainArchivo);
        if(post.idUserContact==user.idUser)
        {
            showPublishOne(post,user);
        }

        fclose(pOpen);
        fclose(User_Arch);
    }
}
///**********************************************************************************************************///ShowPostID

///**********************************************************************************************************///

///**********************************************************************************************************/// IdContentToArray
int idPostToArray(char publishArch[],int allPostArray[])
{
    stPublish post;
    int i=0;
    FILE *pOpen =fopen(publishArch,"rb");
    if(pOpen )
    {
        while(fread(&post,sizeof(stPublish),1,pOpen)>0)
        {
            if(post.active == 1)
            {
                allPostArray[i]=post.idContent;
                i++;
            }
        }
        fclose(pOpen);
    }
    return i;
}
///**********************************************************************************************************/// IdContentToArray

///**********************************************************************************************************/// Random Post
void randomPost(int validosRandom, int allPostArray[],char publishArch[],char mainArchivo[])
{
    srand (time(NULL));
    stPublish post;
    stUser user;
    int randomArray[5];
    int i=0;
    int random;
    int flag=0;
    FILE *pOpen =fopen(publishArch,"rb");
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(pOpen && User_Arch)
    {
        while(i<5)
        {
            do
            {
                random=allPostArray[rand()%validosRandom];
                flag=randomValuePost(random,randomArray);
            }
            while(flag==0);
            showPostID(publishArch,random,mainArchivo);
            i++;
        }
        fclose(pOpen);
        fclose(User_Arch);
    }

}
///**********************************************************************************************************///Random Post

///**********************************************************************************************************///
int randomValuePost(int random,int randomArray[])
{
    int flag;
    int i=0;

    while(i<5 && flag==0)
    {

        if(random!=randomArray[i])
        {
            flag=1;
            randomArray[i]=random;
        }
        i++;
    }

    return flag;
}
///**********************************************************************************************************///

///**********************************************************************************************************///
void otherMenu(int currentID, char mainArchivo[],char publishArch[],char currentTIME[])
{
    int menu,control;
    int like;
    int reportID =0;
    int value;
    int allPostArray[30];
    int validos;
    int validosRandom;
    int idPost;
    do
    {
        printf("\n\t Seleccione que accion quiere realizar \n\n");
        printf("\n\t\t [1] - Ver 5 post aleatorios \n");
        printf("\n\t\t [2] - Dar like a post \n");
        printf("\n\t\t [3] - Feedback de post \n");
        printf("\n\t\t [4] - Reportar post \n");
        printf("\n\t\t [5] - Ver posts reportados \n");
        printf("\n\t\t [6] - Salir\n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:

            validosRandom=idPostToArray(publishArch,allPostArray);
            randomPost(validosRandom,allPostArray,publishArch,mainArchivo);
            break;
        case 2:
            showPublish(publishArch,mainArchivo,currentID,currentTIME);
            printf("Ingrese el post a dar me gusta\n");
            scanf("%d",&like);
            postLike(publishArch,like,mainArchivo,currentID);
            break;
        case 3:
            feedbackMenu(publishArch,mainArchivo,currentID,currentTIME);
            break;
        case 4:
            showPublish(publishArch,mainArchivo,currentID,currentTIME);
            printf("\n Ingrese el ID del post a reportar\n");
            scanf("%d",&reportID);
            reportPost(publishArch,reportID);
            break;
        case 5:
            showReport(publishArch,mainArchivo);
            break;
        case 6:
            printf("\n  Saliendo... Presione ESC\n");
            control=ESC;
            break;
        }
        printf("\nEnter para continuar, ESC para salir.\n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=ESC);

}
///**********************************************************************************************************///

///**********************************************************************************************************///
void feedbackMenu(char publishArch[],char mainArchivo[],int currentID,char currentTIME[])
{
    int menu,control;
    int value;
    do
    {
        printf("\n\t Seleccione que accion quiere realizar \n\n");
        printf("\n\t\t [1] - Dar feedback \n");
        printf("\n\t\t [2] - Ver feedbacks \n");
        printf("\n\t\t [3] - Salir\n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            system("cls");
            showPublish(publishArch,mainArchivo,currentID,currentTIME);
            printf("\n Ingrese el post a cual quiere dar un feedback\n");
            scanf("%d",&value);
            feedback(publishArch,currentID,mainArchivo,value);
            break;
        case 2:
            system("cls");
            showFeedback(publishArch,mainArchivo,currentTIME,currentID);
            break;
        case 3:
            printf("\nEnter para continuar, ESC para salir.\n");
            fflush(stdin);
            control=getch();
            system("cls");
            break;
        }
    }
    while(control!=ESC);
}
///**********************************************************************************************************///

///**********************************************************************************************************///SHOW FEED
void showFeedback(char publishArch[],char mainArchivo[],char currentTIME, int currentID)
{
    FILE *User_Arch = fopen(mainArchivo,"rb");
    FILE *pPost = fopen(publishArch,"rb");
    stUser user;
    stPublish post;
    if(User_Arch && pPost)
    {

        while(fread(&post,sizeof(stPublish),1,pPost)>0)
        {


            if(post.active==1 && strlen(post.feedback)>5)
            {
                user=searchNamePOST(post.idFeedback,mainArchivo);
                printf("\n\t\t Feedback realizado por: %s \n",user.userName);
                printf("\n\t\t ID del post: %d \n",post.idContent);
                printf("\n\t\t Titulo del post: %s \n",post.title);
                printf("\n\t\t Descripcion: %s \n",post.description);
                printf("\n\t\t Feedback: %s \n",post.feedback);
            }
        }
        fclose(User_Arch);
        fclose(pPost);
    }
}
///**********************************************************************************************************///SHOW FEED

///**********************************************************************************************************/// REPORT
void reportPost(char publishArch[],int reportID)
{
    stPublish post;
    FILE *pPost = fopen(publishArch,"r+b");
    if(pPost)
    {
        if(fread(&post,sizeof(stPublish),1,pPost)>0)
        {
            disablePost(publishArch,reportID);
            fseek(pPost,(reportID-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pPost);
            printf("\nIngrese la razon por el reporte\n");
            fflush(stdin);
            gets(post.report);
            fseek(pPost,(reportID-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pPost);
        }
        fclose(pPost);
    }
}
///**********************************************************************************************************/// REPORT

///**********************************************************************************************************/// SHOW REPORT
void showReport(char publishArch[],char mainArchivo[])
{
    stPublish post;
    stUser user;
    FILE *pPost =fopen(publishArch,"rb");
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(pPost && User_Arch)
    {
        while(fread(&post,sizeof(stPublish),1,pPost)>0)
        {
            if(post.active !=1 && strlen(post.report)>4)
            {
                showPublishOne(post,user);
                printf("\n\t\t Razon del reporte: %s\n",post.report);
            }
        }
        fclose(pPost);
        fclose(User_Arch);
    }
}
///**********************************************************************************************************///SHOW REPORT
///**********************************************************************************************************/// FEEDBACK
void feedback(char publishArch[],int currentID, char mainArchivo[], int value)
{
    FILE *pPost = fopen(publishArch,"r+b");
    stPublish post;
    if(fread(&post,sizeof(stPublish),1,pPost)>0)
    {
        fseek(pPost,(value-1)*sizeof(stPublish),SEEK_SET);
        fread(&post,sizeof(stPublish),1,pPost);
        printf("\nIngrese su feedback\n");
        fflush(stdin);
        gets(post.feedback);
        post.idFeedback=currentID;
        points(mainArchivo,currentID);
        fseek(pPost,(value-1)*sizeof(stPublish),SEEK_SET);
        fwrite(&post,sizeof(stPublish),1,pPost);
    }
    fclose(pPost);

}
///**********************************************************************************************************/// FEEDBACK
///**********************************************************************************************************/// PUBLICAR

int publishPost(int currentID,char publish [],char mainArchivo[],char currenTime[])
{
    int postStatus=0;
    int idContent=lastIDPost(publish);
    int iDpost=idContent;
    char userNamePost1[20];
    int menu;
    stPublish post;
    stUser user;
    FILE * pPost = fopen(publish,"ab");
    if(pPost)
    {
        strcpy(post.currentTIME,currenTime);
        printf("\n\t\t  Ingrese cabecera del post: \n");
        printf("\n\n\t\t  ");
        fflush(stdin);
        gets(post.title);

        printf("\n\t\t   Ingrese una breve descripcion de su persona: \n");
        printf("\n\n\t\t  ");
        fflush(stdin);
        gets(post.description);

        printf("\n\t\t   Ingrese el valor requerido: \n");
        printf("\n\n\t\t  ");
        scanf("%d",&post.cost);

        printf("\n\t\t   Ingrese el horario a reunirse: \n");
        printf("\n\n\t\t  ");
        fflush(stdin);
        gets(post.time);

        printf("\n\t\t   Ingrese tematica a charlar: \n");
        printf("\n\n\t\t  ");
        fflush(stdin);
        gets(post.categoria);

        printf("\n\t\t   Seleccione el lugar preferido para la reunion: \n");
        selectPlace(publish,&post);///-///////////////////////////////TIRO ERROR /////////////////////////////////////

        user=searchNamePOST(currentID,mainArchivo);
        iDpost++;
        strcpy(post.userNamePost,userNamePost1);
        post.idContent=iDpost;
        post.idUserContact=user.idUser;
        post.active=1;
        postStatus=1;
        points(mainArchivo,currentID);
        post.likes=0;
        fwrite(&post,sizeof(stPublish),1,pPost);

    }
    fclose(pPost);
    statusPublisPost(postStatus);
    return postStatus;
}

///*************************************************************************/// CONFIRMACION POST

void statusPublisPost (int postStatus)
{
    if (postStatus==1)
    {
        printf("\n\t\t El post se ha publicado exitosamente!\n\n");
    }
    else
    {
        printf("\n\t\t El post no pudo publicarse, intente nuevamente...\n\n");
    }
}

///*************************************************************************/// LOCALIZACION

void selectPlace(char publish[],stPublish post)
{
    FILE * pPublish = fopen(publish,"ab");
    int menu;
    printf("\n\n\n\t  Seleccione un sitio: \n\n");
    printf("\n [1]  - La Fonte D큀ro || Colon y Buenos Aires \n");
    printf("\n [2]  - La Fonte D큀ro || Constitucion y Tejedor \n");
    printf("\n [3]  - La Fonte D큀ro || Luro y 180 \n");
    printf("\n [4]  - La Fonte D큀ro || Urquiza y la Costa \n");
    printf("\n [5]  - Cafe Martinez  || Colon 3651 - 7 a 22 \n");
    printf("\n [6]  - Di Mero Espresso Cafeteria || Martin Miguel de Guemes 2483 - 7 a 20 \n");
    printf("\n [7]  - ADORADO Cafe & Bar || Paseo Aldrey - 8 a 20 \n");
    printf("\n [8]  - De Postres || Carlos Alvear 2889 \n");
    printf("\n [9]  - Croissant Cafe || Cordoba 2361 \n");
    printf("\n [10] - Adorado Cafe || Independencia 2546 \n");
    do
    {
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            strcpy(post.places,"La Fonte D큀ro - Colon y Buenos Aires");
            break;
        case 2:
            strcpy(post.places,"La Fonte D큀ro - Constitucion y Tejedor");
            break;
        case 3:
            strcpy(post.places,"La Fonte D큀ro - Luro y 180");
            break;
        case 4:
            strcpy(post.places,"La Fonte D큀ro - Urquiza y la Costa");
            break;
        case 5:
            strcpy(post.places,"Cafe Martinez - Colon 3651 - 7 a 22");
            break;
        case 6:
            strcpy(post.places,"Di Mero Espresso Cafeteria - Martin Miguel de Guemes 2483 - 7 a 20");
            break;
        case 7:
            strcpy(post.places,"ADORADO Cafe & Bar - Paseo Aldrey - 8 a 20");
            break;
        case 8:
            strcpy(post.places,"De Postres - Carlos Alvear 2889");
            break;
        case 9:
            strcpy(post.places,"Croissant Cafe - Cordoba 2361");
            break;
        case 10:
            strcpy(post.places,"Adorado Cafe - Independencia 2546");
            break;
        }
        if(menu>0 && menu>=11)
        {
            printf("\n  La opcion ingresada no se encuentra, intente nuevamente...\n");
        }
    }
    while(menu>0 && menu>=11);
    fwrite(&post,sizeof(stPublish),0,pPublish);
    fclose(pPublish);
}

///*************************************************************************/// PREVISUALIZACION POST
void showPublishOne(stPublish post, stUser user)
{
    printf("\n\t\t **************************************************************************************\n");
    printf("\n\t\t *****----------------------------------------------------------------------------*****\n");
    printf("\n\t\t El post se publico: %s\n",post.currentTIME);
    printf("\n\t\t\t\t\t\t\t\t\t\t\t  %s\n",user.userName);
    printf("\n\t\t ID post: %d\n", post.idContent);
    printf("\n\t\t\t\t\t\t\t %s \n",post.title);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t Descripcion: %s \n", post.description);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t Las tematicas a tratar seran: %s \n",post.categoria);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t Localizacion : %s \n",post.places);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t El horario de la reunion sera: %s",post.time);
    printf("\n \t\t Likes de la publicacion: %d",post.likes);
    printf("\n\t\t\t\t\t\t\t\t\t\t  El valor es: $%d\n",post.cost);
    printf("\n\t\t *****----------------------------------------------------------------------------*****\n");
    printf("\n\t\t **************************************************************************************\n");
}
///*************************************************************************/// PREVISUALIZACION POST
///*************************************************************************/// PREVISUALIZACION POST

void showPublishPostIndividual(char publish[],char mainArchivo[],int currentID)
{
    stPublish post;
    stUser user;
    FILE *pOpen =fopen(publish,"rb");
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(pOpen && User_Arch)
    {
        user=searchNamePOST(currentID,mainArchivo);

        while(fread(&post,sizeof(stPublish),1,pOpen)>0)
        {
            if(post.idUserContact==user.idUser)
            {
                if(post.active == 1)
                {
                    showPublishOne(post,user);
                }
            }
        }
        fclose(pOpen);
        fclose(User_Arch);
    }
}

///*************************************************************************///


void showPublish(char publish[],char mainArchivo[],int currentID,char currentTIME[])
{
    stPublish post;
    stUser user;
    FILE *pOpen =fopen(publish,"rb");
    FILE *User_Arch = fopen(mainArchivo,"rb");
    if(pOpen && User_Arch)
    {
        while(fread(&post,sizeof(stPublish),1,pOpen)>0)
        {
            user=searchNamePOST(post.idUserContact,mainArchivo);
            if(post.active == 1)
            {
                showPublishOne(post,user);
            }
        }
        fclose(pOpen);
        fclose(User_Arch);
    }
}

///*************************************************************************/// POST LIKE
void postLike(char publishArch[],int like,char mainArchivo[],int currentID)
{
    FILE *pPost = fopen(publishArch,"r+b");
    stPublish post;
    if(pPost)
    {
        if(fread(&post,sizeof(stPublish),1,pPost)>0)
        {
            fseek(pPost,(like-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pPost);
            post.likes=post.likes+1;
            points(mainArchivo,currentID);
            fseek(pPost,(like-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pPost);
        }
        fclose(pPost);
    }
}

///*************************************************************************/// POST LIKE

///*************************************************************************/// POINTS
void points(char mainArchivo[],int currentID)
{
    FILE *User_Arch = fopen(mainArchivo,"r+b");
    stUser user;
    if(User_Arch)
    {
        if(fread(&user,sizeof(stUser),1,User_Arch)>0)
        {
            fseek(User_Arch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,User_Arch);
            user.points=user.points+1;
            fseek(User_Arch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,User_Arch);
        }
        fclose(User_Arch);
    }
}
///*************************************************************************/// POINTS

///*************************************************************************/// RANK USER
void rankUser(char mainArchivo[],int currentID)
{
    FILE *User_Arch = fopen(mainArchivo,"r+b");
    stUser user;
    if(User_Arch)
    {
        fseek(User_Arch,(currentID-1)*sizeof(stUser),SEEK_SET);
        fread(&user,sizeof(stUser),1,User_Arch);
        if(user.points<10)
        {
            strcpy(user.ranki,"Bronce");
            user.level=0;
        }
        else if(user.points>10 && user.points<20)
        {
            strcpy(user.ranki,"Plata");
            user.level=1;
        }
        else if(user.points>20 && user.points<30)
        {
            strcpy(user.ranki,"Oro");
            user.level=2;
        }
        else
        {
            strcpy(user.ranki,"Diamante");
            user.level=3;
        }
        fseek(User_Arch,(currentID-1)*sizeof(stUser),SEEK_SET);
        fwrite(&user,sizeof(stUser),1,User_Arch);
    }
    fclose(User_Arch);
}
///*************************************************************************/// RANK USER

///*************************************************************************/// ID POST

int lastIDPost(char publish[])
{
    FILE *pArch =fopen(publish,"rb");
    stPublish post;
    int lastIdPost=0;

    if(pArch)
    {
        fseek(pArch, (-1)*sizeof(stPublish), SEEK_END);
        if(fread(&post, sizeof(stPublish),1,pArch)>0)
        {
            lastIdPost=post.idContent;
        }
        fclose(pArch);
    }
    return lastIdPost;
}

///**********************************************************************************************************/// MENU EDITAR PUBLICACION

void editPostMenu(int idContent, char publishArch[], int currentID, char mainArchivo[],char currentTIME,int validos,int postArray[])
{
    stPublish post;
    stUser user;
    int value;
    int menu,control;
    int publication;

    char newTitle[30];
    char newDescription[300];
    char categoria[30];
    int active;
    int newCost;
    int newTime[20];
    char newPlaces[100];
    char newTopics[30];
    int flag=0;

    do
    {
        showPublishPostIndividual(publishArch,mainArchivo,currentID);
        printf("\n\t Seleccione una accion: \n\n");
        printf("\n\t\t[1] - Editar Titulo \n");
        printf("\n\t\t[2] - Editar Descripcion \n");
        printf("\n\t\t[3] - Editar Categoria \n");
        printf("\n\t\t[4] - Editar Valor \n");
        printf("\n\t\t[5] - Editar Horario \n");
        printf("\n\t\t[6] - Editar Lugar \n");
        printf("\n\t\t[7] - Dar de baja una publicacion \n");
        printf("\n\t\t[0] - Volver al Menu Principal \n");
        printf("\n\t\t  ");

        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese el nuevo titulo: \n");
            fflush(stdin);
            gets(newTitle);
            editPostTitle(publishArch,value,newTitle);
            break;
        case 2:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese la nueva descripcion: \n");
            fflush(stdin);
            gets(newDescription);
            editPostDescription(publishArch,value,newDescription);
            break;
        case 3:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese los nuevos topicos a hablar: \n");
            fflush(stdin);
            gets(newTopics);
            editPostTopics(publishArch,value,newTopics);
            break;
        case 4:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese el nuevo valor: \n");
            scanf("%d",&newCost);
            editPostCost(publishArch,value,newCost);
            break;
        case 5:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese el nuevo horario: \n");
            fflush(stdin);
            gets(newTime);
            editPostTime(publishArch,value,newTime);
            break;
        case 6:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            editSelectPlace(publishArch,post,value);
            break;
        case 7:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                flag=rightPost(validos,postArray,value);
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            disablePost(publishArch,value);
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para Menu Principal...\n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=ESC);
}

///*************************************************************************/// EDITAR LOCALIZACION
///*************************************************************************/// Right POST
int rightPost(int validos,int postArray[], int value)
{
    stPublish post;
    int i=0;
    int flag=0;


    while(i<validos && flag==0)
    {
        if(value==postArray[i])
        {
            flag=1;
        }
        i++;
    }
    return flag;
}
///*************************************************************************/// Right POST

///*************************************************************************///

///*************************************************************************///
///*************************************************************************/// EDITAR LOCALIZACION


void editSelectPlace(char publish[],stPublish post, int value)
{
    FILE * pPublish = fopen(publish,"r+b");
    int menu;
    printf("\n\t  Seleccione un sitio: \n\n");
    printf("\n [1]  - La Fonte D큀ro || Colon y Buenos Aires \n");
    printf("\n [2]  - La Fonte D큀ro || Constitucion y Tejedor \n");
    printf("\n [3]  - La Fonte D큀ro || Luro y 180 \n");
    printf("\n [4]  - La Fonte D큀ro || Urquiza y la Costa \n");
    printf("\n [5]  - Cafe Martinez  || Colon 3651 - 7 a 22 \n");
    printf("\n [6]  - Di Mero Espresso Cafeteria || Martin Miguel de Guemes 2483 - 7 a 20 \n");
    printf("\n [7]  - ADORADO Cafe & Bar || Paseo Aldrey - 8 a 20 \n");
    printf("\n [8]  - De Postres || Carlos Alvear 2889 \n");
    printf("\n [9]  - Croissant Cafe || Cordoba 2361 \n");
    printf("\n [10] - Adorado Cafe || Independencia 2546 \n");
    fseek(pPublish,(value-1)*sizeof(stPublish),SEEK_SET);
    fread(&post,sizeof(stPublish),1,pPublish);
    do
    {
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            strcpy(post.places,"La Fonte D큀ro - Colon y Buenos Aires");
            break;
        case 2:
            strcpy(post.places,"La Fonte D큀ro - Constitucion y Tejedor");
            break;
        case 3:
            strcpy(post.places,"La Fonte D큀ro - Luro y 180");
            break;
        case 4:
            strcpy(post.places,"La Fonte D큀ro - Urquiza y la Costa");
            break;
        case 5:
            strcpy(post.places,"Cafe Martinez - Colon 3651 - 7 a 22");
            break;
        case 6:
            strcpy(post.places,"Di Mero Espresso Cafeteria - Martin Miguel de Guemes 2483 - 7 a 20");
            break;
        case 7:
            strcpy(post.places,"ADORADO Cafe & Bar - Paseo Aldrey - 8 a 20");
            break;
        case 8:
            strcpy(post.places,"De Postres - Carlos Alvear 2889");
            break;
        case 9:
            strcpy(post.places,"Croissant Cafe - Cordoba 2361");
            break;
        case 10:
            strcpy(post.places,"Adorado Cafe - Independencia 2546");
            break;
        }
        if(menu>0 && menu>=11)
        {
            printf("\n  La opcion ingresada no se encuentra, intente nuevamente...\n");
        }
    }
    while(menu>0 && menu>=11);
    fseek(pPublish,(value-1)*sizeof(stPublish),SEEK_SET);
    fwrite(&post,sizeof(stPublish),1,pPublish);
    fclose(pPublish);
}

///*************************************************************************/// EDITAR TOPICOS

void editPostTopics(char publish[],int value,char newTopics[30])
{
    FILE *pArch = fopen(publish,"r+b");
    stPublish post;
    if(pArch)
    {
        if(fread(&post,sizeof(stPublish),1,pArch)>0)
        {
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pArch);
            strcpy(post.categoria,newTopics);
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pArch);
        }
    }
    fclose(pArch);
}

///*************************************************************************/// EDITAR HORARIO

void editPostTime(char publish[],int value,int newTime)
{
    FILE *pArch = fopen(publish,"r+b");
    stPublish post;
    if(pArch)
    {
        if(fread(&post,sizeof(stPublish),1,pArch)>0)
        {
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pArch);
            strcpy(post.time,newTime);
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pArch);
        }
    }
    fclose(pArch);
}

///*************************************************************************/// BAJA PUBLICACION

void disablePost(char publish[], int value)
{
    FILE *pPost = fopen(publish,"r+b");
    stPublish post;
    if(pPost)
    {
        if(fread(&post,sizeof(stPublish),1,pPost)>0)
        {
            fseek(pPost,(value-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pPost);
            post.active=0;
            strcpy(post.report,"Baja");
            fseek(pPost,(value-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pPost);
        }
        fclose(pPost);
    }
}

///*************************************************************************/// EDITAR TITULO

void editPostTitle(char publish[],int value,char newTitle[30])
{
    FILE *pArch = fopen(publish,"r+b");
    stPublish post;
    if(pArch)
    {
        if(fread(&post,sizeof(stPublish),1,pArch)>0)
        {
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pArch);
            strcpy(post.title,newTitle);
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pArch);
        }
        fclose(pArch);
    }
}

///*************************************************************************/// EDITAR VALOR

void editPostCost(char publish[],int value, int newCost)
{
    {
        FILE *pArch = fopen(publish,"r+b");
        stPublish post;
        if(pArch)
        {
            if(fread(&post,sizeof(stPublish),1,pArch)>0)
            {
                fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
                fread(&post,sizeof(stPublish),1,pArch);
                post.cost=newCost;
                fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
                fwrite(&post,sizeof(stPublish),1,pArch);
            }
        }
        fclose(pArch);
    }
}

///*************************************************************************/// EDITAR DESCRIPCION

void editPostDescription(char publish[],int value,char newDescription[300])
{
    FILE *pArch = fopen(publish,"r+b");
    stPublish post;
    if(pArch)
    {
        if(fread(&post,sizeof(stPublish),1,pArch)>0)
        {
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fread(&post,sizeof(stPublish),1,pArch);
            strcpy(post.description,newDescription);
            fseek(pArch,(value-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stPublish),1,pArch);
        }
    }
    fclose(pArch);
}

///***************************************************************************///
///***************************************************************************///
///***************************************************************************/// PUBLICAR

void searchMyPost(char publish[],char mainArchivo[],int currentID)
{
    stUser user;
    stPublish post;
    FILE *User_Arch=fopen(mainArchivo,"rb");
    FILE *pOpen = fopen(publish,"rb");

    if(pOpen && User_Arch)
    {
        user=searchNamePOST(currentID,mainArchivo);

        while(fread(&post,sizeof(stPublish),1,pOpen)>0)
        {
            if(post.idUserContact==user.idUser)
            {
                printf("\n \t \t **************************************************************************************\n");
                printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                printf("\n \t \t \t \t \t \t \t \t \t \t \t  %s\n", user.userName);
                printf("\n \t \t ID post: %d\n", post.idContent);
                printf("\n \t \t \t %s \n",post.title);
                printf("\n \t \t  %s \n", post.description);
                printf("\n \t \t Localizacion: %s \n",post.places);
                printf("\n \t \t \t \t \t \t \t \t \t \t  El valor es: $%d\n",post.cost);
                printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                printf("\n \t \t **************************************************************************************\n");
            }
        }
        fclose(User_Arch);
        fclose(pOpen);
    }
}

///***************************************************************************///
///***************************************************************************/// PUBLICAR

///***************************************************************************///
///***************************************************************************///  BUSCADOR DE USARIO

///***************************************************************************///
///***************************************************************************///  BUSCADOR DE USARIO

stUser searchNamePOST(int currentID, char mainArchivo[])
{
    FILE *User_Arch=fopen(mainArchivo,"rb");
    stUser user;
    int flag=0;
    if(User_Arch!=NULL)
    {
        while(flag==0 && fread(&user, sizeof(stUser),1,User_Arch)>0)
        {
            if(currentID==user.idUser)
            {
                flag=1;
            }
        }
        fclose(User_Arch);
    }
    return user;
}

///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
///**************************************          Mensajeria                         ********************************************///
///*******************************************************************************************************************************///
///*******************************************************************************************************************************///
void messengeMenu(int currentID, char mainArchivo[], char messangerUsuarios[], char timeSend[])
{
    stUser user;
    stPublish post;
    int flag=0;
    int op=0;
    user=searchNamePOST(currentID,mainArchivo);
    int menu;
    do
    {
        system("cls");
        printf("\n\t\t\t Mensajes de %s \n", user.userName);
        printf("\n[1] - Ver bandeja de mensajes\n");
        printf("\n[2] - Mandar mensajes\n");
        printf("\n[3] - Ver mensajes enviados\n");
        printf("\n[4] - Salir\n");
        fflush(stdin);
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:

            flag=viewInboxMessagerOk(user,mainArchivo,messangerUsuarios);
            system("cls");
            if(flag==1)
            {
                printf("\nTienes mensajes pendientes\n 1 - VER \n 2 -Salir \n");
                fflush(stdin);
                scanf("%d",&op);
                if (op==1)
                    inboxMessenger(user,currentID,messangerUsuarios,mainArchivo,timeSend);
            }
            else
            {
                printf("\nNo tienes mensajes nuevos");
            }
            break;
        case 2:
            sendMesengges (currentID,messangerUsuarios,mainArchivo,timeSend);
            break;
        case 3:
            viewMesenggesSend(user,messangerUsuarios,mainArchivo);
            break;
        case 4:
            printf("\nVuelve cuando quieras");
            printf("\nEsc para salir");
            break;
        }
        fflush(stdin);
        menu=getch();
        printf("\nEsc para salir");
    }
    while(menu!=ESC);
    system("cls");
}



void sendMesengges (int currentID, char messangerUsuarios[], char mainArchivo[],char timeSend[])
{
    stMessenge sms;
    stUser user,userSearch;
    int idMessenge = lastIDsms(messangerUsuarios);
    char name[20];

    FILE * mSn = fopen(messangerUsuarios,"ab");
    if(mSn)
    {
        user=searchNamePOST(currentID,mainArchivo);
        displayUsersName(mainArchivo,currentID);
        printf("\n Ingrese a que usuario desea enviar mensaje\n");
        fflush(stdin);
        gets(name);

        userSearch=searchUserMessenge(name,mainArchivo);

        printf("\nEscriba el mensaje al usuario %s, nombre %s \n", userSearch.userName,userSearch.firstName);
        fflush(stdin);
        gets(sms.message);
        idMessenge++;
        strcpy(sms.timeSend,timeSend);
        sms.idContent=idMessenge;
        sms.idReceiver=userSearch.idUser;
        sms.idIssuing=user.idUser;
        sms.read=0;

        fwrite(&sms,sizeof(stMessenge),1,mSn);
        points(mainArchivo,currentID);
        fclose(mSn);
    }
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

stUser searchUserMessenge(char name[],char mainArchivo[])
{
    int flag =0;
    stUser user;
    FILE * User_arch = fopen (mainArchivo,"rb");
    if(User_arch!=NULL)
    {
        while(flag == 0 && fread(&user, sizeof(stUser),1,User_arch)>0)
        {
            if(strcmp(name,user.userName)==0)
            {
                flag=1;
            }
        }
        fclose(User_arch);
    }
    return user;
}

///***************************************************************************///
///***************************************************************************///  LAST ID MENSAJERIA

int lastIDsms (char messangerUsuarios[])
{
    FILE *mSn =fopen(messangerUsuarios,"r+b");
    stMessenge sms;
    int lastIdPost=0;

    if(mSn)
    {
        fseek(mSn, (-1)*sizeof(stMessenge), SEEK_END);
        if(fread(&sms, sizeof(stMessenge),1,mSn)>0)
        {
            lastIdPost=sms.idContent;
        }
        fclose(mSn);
    }
    return lastIdPost;
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void viewMesenggesSend (stUser user,char messangerUsuarios[], char mainArchivo[])
{
    stMessenge sms;
    stUser userSearchSend;

    FILE * User_Archi = fopen(mainArchivo,"rb");
    FILE * mSn = fopen(messangerUsuarios,"rb");
    if (User_Archi && mSn)
    {
        while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {

            if(user.idUser==sms.idIssuing)
            {
                userSearchSend=searchNamePOST(sms.idReceiver,mainArchivo);
                printf("\n**************** Enviado de : %s \n", user.userName);
                printf("\n**************** Para : %s \n", userSearchSend.userName);
                messagesDisplay(sms);

                statusRead(sms);
                printf("\nEnviado el %s\n",sms.timeSend);
            }
        }
        fclose(User_Archi);
        fclose(mSn);
    }
}

///***************************************************************************///
///***************************************************************************///
void statusRead(stMessenge sms)
{
    if(sms.read==1)
    {
        printf("\n Mensaje leido\n");
    }
    else
    {
        printf("\n Mensaje no leido\n");
    }
}
///***************************************************************************///
///***************************************************************************///
void messagesDisplay(stMessenge sms)
{
    printf("\n Mensaje: %s\n",sms.message);
}
///***************************************************************************///
///***************************************************************************///  MENSAJERIA

int viwePendingInbox(stUser user,int currentID,char messangerUsuarios[], char mainArchivo[])
{
    int i=0;
    stUser userSearchSend;
    stMessenge sms;
    FILE * User_Archi = fopen(mainArchivo,"rb");
    FILE * mSn = fopen(messangerUsuarios,"rb");
    if (User_Archi && mSn)
    {
        while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {


            if(user.idUser==sms.idReceiver)
            {

                i++;
            }

        }
        fclose(User_Archi);
        fclose(mSn);
    }

    return i;
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

int viewInboxMessagerOk (stUser user,char mainArchivo[], char messangerUsuarios[])
{
    int flag=0;
    stMessenge sms;

    FILE * User_Arch = fopen(mainArchivo,"rb");
    FILE * mSn = fopen(messangerUsuarios,"rb");
    if(User_Arch && mSn)
    {

        while(flag==0 && fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {
            if(user.idUser==sms.idReceiver && sms.read!=1)
            {
                flag=1;
            }
        }
        fclose(User_Arch);
        fclose(mSn);
    }
    return flag;
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void inboxMessenger(stUser userSearch,int currentID,char messangerUsuarios[],char mainArchivo[],char currenTime[])
{
    stUser user,userSearch1;
    stMessenge sms;
    int i=1;
    int flag1=0;
    int j=0;
    int v=0;
    int op=0;
    char userNameSearchR[20];
    stUser arrayMessanger[10];
    int arrayMessangerInd[10];
    FILE * User_Arch = fopen(mainArchivo,"rb");
    FILE * mSn = fopen(messangerUsuarios,"rb");
    if(User_Arch && mSn)
    {
        while(fread(&user,sizeof(stUser),1,User_Arch))
        {
            if(user.idUser!=userSearch.idUser)
            {
                rewind(mSn);
                while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
                {
                    if(user.idUser==sms.idIssuing && userSearch.idUser==sms.idReceiver)
                    {
                        if(sms.read!=1)
                            j++;
                    }
                }
                flag1=loadInbox(j);
                if(flag1==1)
                {
                    arrayMessangerInd[i]=j;
                    arrayMessanger[i]=user;
                    i++;
                }
                j=0;
            }
        }
        v=viewMessagenPending(i,arrayMessangerInd,arrayMessanger);

        printf("\nDesea ver mensajes \n 1 - SI \n 2 - NO \n\n");
        fflush(stdin);
        scanf("%d",&op);
        if(op==1)
        {
            printf("\nIngrese el nombre de Usuario para ver los mensajes.\n");
            fflush(stdin);
            gets(userNameSearchR);
            userSearch1=searchUserMessenge(userNameSearchR,mainArchivo);

            viewMesenggesInbox(currentID,messangerUsuarios,mainArchivo,userSearch,userSearch1);
            printf("\n\n\t\t\t 풯uiere contestar el mensaje?\n\n\t\t\t 1 - Si \n\t\t\t 2 - No\n");
            fflush(stdin);
            scanf("%d",&op);
            if(op==1)
            {
                replyMessage(currentID,messangerUsuarios,mainArchivo,userNameSearchR,currenTime);
            }

        }

        fclose(User_Arch);
        fclose(mSn);
    }
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void viewMesenggesInbox(int currentID,char messangerUsuarios[],char mainArchivo[],stUser userSearch,stUser userSearch1)
{
    stMessenge sms;
    stMessenge arraySms[20];
    int i=1;
    FILE * User_Archi = fopen(mainArchivo,"r+b");
    FILE * mSn = fopen(messangerUsuarios,"r+b");
    if (User_Archi && mSn)
    {
        while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {
            if(userSearch1.idUser==sms.idIssuing && userSearch.idUser==sms.idReceiver)
            {
                printf("\n*************************************************************");
                printf("\n Enviado el dia %s\n",sms.timeSend);
                printf("\n %s ", userSearch1.userName);
                printf("\n---> %s", sms.message);
                arraySms[i]=sms;
                i++;
            }
            else if(userSearch1.idUser==sms.idReceiver && userSearch.idUser==sms.idIssuing)
            {
                printf("\n*************************************************************");
                printf("\n  \t\t\t\t\t%s ", userSearch.userName);
                printf("\n\n \t\t\t\t%s <---", sms.message);
            }
        }
        statusMessangerRead(messangerUsuarios,mainArchivo,userSearch,arraySms,i);
        fclose(User_Archi);
        fclose(mSn);
    }
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void replyMessage (int currentID, char messangerUsuarios[], char mainArchivo[],char userNameSearchR[],char currenTime[])
{
    stMessenge sms;
    stUser user,userSearch;
    int idMessenge = lastIDsms(messangerUsuarios);
    char name[20];

    FILE * User_Archi = fopen(mainArchivo,"r+b");
    FILE * mSn = fopen(messangerUsuarios,"ab");
    if(User_Archi && mSn)
    {
        user=searchNamePOST(currentID,mainArchivo);

        userSearch=searchUserMessenge(userNameSearchR,mainArchivo);
        printf("\n\t usuarios emite %s\n",user.userName);
        printf("\n\t usuarios recibe %s\n",userSearch.userName);
        printf("\n\t Escriba el mensaje a %s \n", userSearch.userName);
        fflush(stdin);
        gets(sms.message);
        strcpy(sms.timeSend,currenTime);
        idMessenge++;
        sms.idContent=idMessenge;
        sms.idReceiver=userSearch.idUser; /// RECIBE
        sms.idIssuing=user.idUser;        /// ENVIA
        sms.read=0;

        points(mainArchivo,currentID);
        fwrite(&sms,sizeof(stMessenge),1,mSn);
        fclose(mSn);
        fclose(User_Archi);
    }
}


///***************************************************************************///
///***************************************************************************///  MENSAJERIA

int loadInbox(int j)
{
    int flag=0;
    if(j!=0)
    {
        flag=1;
    }
    return flag;
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

int viewMessagenPending(int i,int arrayMessangerInd[],stUser arrayMessanger[])
{
    int v=0;
    for(v=1; v<i; v++)
    {
        printf("\nTienes total de mensajes %d",arrayMessangerInd[v]);
        printf("\nUsuario %s\n\n",arrayMessanger[v].userName);
    }
    return v;
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void statusMessangerRead(char messangerUsuarios[],char mainArchivo[],stUser userSearch,stMessenge arraySms[],int validos)
{
    stMessenge sms;
    int i;
    FILE * User_Arch =fopen (mainArchivo,"r+b");
    FILE * mSn =fopen (messangerUsuarios,"r+b");
    if(mSn)
    {
        for(i=0; i<validos; i++)
        {
            sms=arraySms[i];
            if(sms.read!=1)
            {
                fseek(mSn,(sms.idContent-1)*sizeof(stMessenge),SEEK_SET);
                fread(&sms,sizeof(stMessenge),1,mSn);
                sms.read=1;
                fseek(mSn,(sms.idContent-1)*sizeof(stMessenge),SEEK_SET);
                fwrite(&sms,sizeof(stMessenge),1,mSn);
            }
        }
        fclose(User_Arch);
        fclose(mSn);
    }
}

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void statusNENE(char messangerUsuarios[],char mainArchivo[],stUser userSearch)
{
    stMessenge sms;
    FILE * User_Arch =fopen (mainArchivo,"r+b");
    FILE * mSn =fopen (messangerUsuarios,"r+b");
    if(User_Arch && mSn)
    {
        while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {
            if(userSearch.idUser==sms.idReceiver)
            {
                printf("\n user %s",userSearch.userName);
                printf("\n read %d",sms.read);
            }
        }
        fclose(User_Arch);
        fclose(mSn);
    }
    system("pause");
}
///***************************************************************************///
void displayUsersName(char mainArchivo[], int currentID)
{
    stUser user;
    FILE *User_Arch =fopen(mainArchivo,"rb");
    if(User_Arch)
    {

        while(fread(&user,sizeof(stUser),1,User_Arch)>0 && user.status!=0)
        {
            if(user.idUser!=currentID)
            {
                printf("\n Usuario disponibles: %s \n",user.userName);
            }
        }
    }
}
///***************************************************************************/// Muestra los usuarios disponibles para enviar un mensaje

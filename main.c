#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
const int dim_users = 100;
const int dim_publish = 500;
const int ESC = 27;
const char mainArchivo[]= {"users.dat"};


void muestraArchivo(char mainArchivo[]);
void login();
int lastID(char mainArchivo[]);
typedef struct
{
    int idUser;
    char lastName[50];
    char firstName[50];
    int dni;
    char userName[20];
    char password[30];
    char city[50];
    char places[150];
    int age;
    char email[50];
    char gender[40];
    float points;
    int level;
    char topics[50];
    int role;
    int status;
} stUser;

typedef struct
{
    int idContent;
    char title [30];
    char descption[300];
    char categoria[30];
    int likes;
    int active;
    char report[100];
    int cost;
    int time;
    char places[500];
    int share;
    char feedback[60];
} stPublish;

int main()
{
    stPublish publish [dim_publish];
    stUser user [dim_users];


    registe();
    login();
    showUser(mainArchivo);
    return 0;
}
void login()
{
    int control;
    char username[20];
    char password[30];
    FILE *log =fopen(mainArchivo,"r+b");
    stUser user;
    int status=0;
    int userStatus=0;
    int currentID;
    do
    {
        do
        {
            printf("\nIngrese el nombre de Usuario: \n");
            gets(username);
            userStatus=searchUserName(user,username);
            if(userStatus==0)
            {
                printf("\nThe username doesn`t exist\n");
            }
        }
        while(userStatus==0);

        do{
        rewind(log);
        printf("\n Ingrese el password\n");
        gets(password);

            while(fread(&user,sizeof(user),1,log)>0)
            {
                if(strcmp(username,user.userName)== 0 && strcmp(password, user.password)== 0)
                {
                    system("cls");
                    printf("\nWelcome %s\n", username);
                    currentID=user.idUser;
                    userActive(mainArchivo,currentID);
                    mainMenu(currentID);
                    status=1;
                }
            }
            if(status==0)
            {
            printf("\nPassword is wrong\n");
            printf("\nDesea volver a intentar, ESC para finalizar\n");
            fflush(stdin);
            control=getch();
            }
        }while(status==0 && control!=ESC);
    }
    while(status=0);
    fclose(log);
}
void registe()
{
    int flag=0;
    stUser user;
    FILE *User_Arch = fopen(mainArchivo, "ab");
    int i=lastID(mainArchivo);

    if (User_Arch!=NULL)
    {
        fflush(stdin);
        printf("\nIngrese su apellido: \n");
        gets(user.lastName);

        fflush(stdin);
        printf("\n Ingrese su nombre:  \n");
        gets(user.firstName);

        do{
        printf("\n Ingrese su edad: \n");
        scanf("%d",&user.age);
        flag=ageOver(user.age);
        if(flag==0)
        {
            printf("\nLa edad tiene que ser superior a 16 anios\n");
        }
        }while(flag==0);
        do
        {
            printf("\n Ingrese su DNI: \n");
            fflush(stdin);
            scanf("%d",&user.dni);
            flag=validationDNI(mainArchivo,user.dni);
            if(flag==1)
            {
                printf("\n DNI ya registrado, ingrese un nuevo DNI\n");
            }
        }
        while(flag==1);

        do
        {
            fflush(stdin);
            printf("\n Ingrese el nombre de Usuario: \n");
            scanf("%s",&user.userName);
            flag=searchUserName(user,user.userName);
            if(flag==1)
            {
                printf("\nNombre de usuario existente, ingrese otro nombre de usuario\n");
            }

        }
        while(flag==1);


        fflush(stdin);
        printf("\n Ingrese la contrasenia: \n");
        scanf("%s",&user.password);

        fflush(stdin);
        printf("\n Ingrese la Ciudad: \n");
        scanf("%s",&user.city);

        fflush(stdin);
        printf("\n Ingrese el genero: \n");
        scanf("%s",&user.gender);
        i++;
        user.idUser=i;
        user.status=1;
        fwrite(&user, sizeof(stUser),1, User_Arch);
    }
    fclose(User_Arch);
}

int validationDNI(char arch[], int dni)
{
    int flag= 0;
    stUser u;
    FILE *User_Arch = fopen(arch,"rb");

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

void showOneUser(stUser a)
{
    printf("\nId.....................: %d", a.idUser);
    printf("\nUserName.................: %s", a.userName);
    printf("\nPassword.................: %s", a.password);
    printf("\nApellido.................: %s", a.lastName);
    printf("\nNombre...............: %s", a.firstName);
    printf("\nAge..................: %d", a.age);
    printf("\nDNI....................: %d", a.dni);
    printf("\nGenero..................: %s \n", a.gender);
    printf("\nCiudad..................: %s\n",a.city);
    printf("\nUser Status............: %d\n",a.status);
}
int searchUserName(stUser userN, char name[])
{
    int flag =0;
    stUser user;
    FILE *User_arch=fopen(mainArchivo,"rb");

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

int lastID(char archivo[])
{
    FILE *pArch =fopen(archivo,"r+b");
    stUser a;
    int lastId=0;

    if(pArch)
    {
        fseek(pArch, -1*sizeof(stUser), SEEK_END);

        if(fread(&a, sizeof(stUser),1,pArch)>0)
        {
            lastId=a.idUser;
        }

        fclose(pArch);
    }
    return lastId;
}
int ageOver(int age)
{
    int flag;
    if(age>16)
    {
        flag=1;
    }
    return flag;
}
void editUserCity(char arch[],int currentID, char newCity[50])
{
    FILE *pArch = fopen(arch,"r+b");
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

    }
    fclose(pArch);
}
void editUserAge(char arch[],int currentID, int newAge)
{
    FILE *pArch = fopen(arch,"r+b");
    stUser user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            user.age=newAge;
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }

    }
    fclose(pArch);
}

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

int editUserStatus(char arch[], int currentID)
{
    int flag=0;
    FILE *pArch = fopen(arch,"r+b");
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

void mainMenu(int currentID)
{
    stUser user;
    int menu;
    printf("Bienvenido, que desea realizar");
    printf("\n [1] - Mensajes \n");
    printf("\n [2] - Editar perfil \n");
    printf("\n [3] - Crear post \n");
    printf("\n [4] - Buscar post \n");
    scanf("%d",&menu);

    switch(menu)
    {
    case 1:
        break;
    case 2:
         editUserMenu(currentID);
        break;
    case 3:
        break;
    case 4:
        break;
    }
}
void editUserMenu(int currentID)
{
    stUser aux;
    system("cls");
    int menu,control,flag=0;
    char newGender[40];
    char newPassword[30];
    char newCity[50];
    char newPlaces[150];
    int newAge;
    char newEmail[50];
   /// char newTopics[50];
   /// int status;
   do{
    printf("\n \t \t \t \t \t \t Editar Usuario");
    printf("\n [1] - Cambiar password \n");
    printf("\n [2] - Cambiar ciudad \n");
    printf("\n [3] - Cambiar Edad \n");
    printf("\n [4] - Cambiar E-mail\n");
    printf("\n [5] - Cambiar Genero\n");
    printf("\n [6] - Dar de baja la cuenta\n");

    scanf("%d",&menu);

    switch(menu)
    {
    case 1:
        printf("\nIngrese la nueva contraseña: \n");
        scanf("%s",&newPassword);
        editUserPassword(mainArchivo,currentID,newPassword);
        break;
    case 2:
        printf("\nIngrese la nueva contraseña: \n");
        scanf("%s",&newCity);
        editUserCity(mainArchivo,currentID,newCity);
        break;
    case 3:
        printf("\n Ingrese la nueva Edad: \n");
        scanf("%d",&newAge);
        editUserAge(mainArchivo,currentID,newAge);
        break;
    case 4:
        printf("\n Ingrese el nuevo correo electronico: \n");
        scanf("%s",&newEmail);
        editUserEmail(mainArchivo,currentID,newEmail);
        break;
    case 5:
        printf("\n Ingrese el nuevo genero: \n");
        scanf("%s",&newGender);
        editUserGender(mainArchivo,currentID,newGender);
        break;
    case 6:
        while(control!=ESC && flag==0)
        {
        printf("\n Esta seguro que quiere realizar la baja de la cuenta? \n");
        printf("\n Enter para continuar ESC para cancelar\n");
        fflush(stdin);
        control=getch();
        flag=editUserStatus(mainArchivo,currentID);
        if(flag=1)
        {
        return 1;
        }
        }
        break;
    }
    printf("\nPresione ESC para finalizar.\n");
    fflush(stdin);
    control=getch();
    system("cls");
    }while(control!=ESC);
}
void showUserOff(char archivo[]) // Perfil admin only
{
    FILE *User_Arch = fopen(archivo, "rb");
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
void userActive(char arch[], int currentID)
{

    FILE *pArch = fopen(arch,"r+b");
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

void selectPlace()
{

}

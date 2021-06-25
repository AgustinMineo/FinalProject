#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
const int dim_users = 100;
const int dim_publish = 300;
const int dim_messenge = 150;
const int ESC = 27;
const char mainArchivo[]= {"users.dat"};
const char publish[]= {"publish.dat"};
const char messangerUsuarios[]= {"messangerUsuarios.dat"};

typedef struct
{
    int idIssuing;
    int idReceiver;
    int idContent;
    char message [150];
    int read;
} stMessenge;

typedef struct
{
    int idUserContact;
    int idContent;
    char userNamePost[20];
    char title [30];
    char description[300];
    char categoria[30];
    int likes;
    int active;
    char report[100];
    int cost;
    int time;
    char places[100];
    int share;
    char feedback[60];
} stPublish;

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
    stPublish post;
} stUser;

///***************************************************************************///
///***************************************************************************///
void showPublish(char publish[],char mainArchivo[],int currentID); ///Todas las publish
stUser searchNamePOST(int currentID, char mainArchivo[]);
stUser searchUserMessenge(char name[],char mainArchivo[]);
void showMyUser(stUser a);
int main()
{
    stPublish publish [dim_publish];
    stUser user [dim_users];
    stMessenge messagesUser[dim_messenge];

    int control,menu;
    do
    {
        printf("\n \t \t \t \t \t BIENVENIDOS AL HIMALAYA\n");
        printf("\n [1] - Registrar un usuario\n");
        printf("\n [2] - Logear un usuario\n");
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
            showUser(mainArchivo);
            fflush(stdin);
            login(mainArchivo);
            break;
        }
        printf("\n Desea ingresar nuevamente, ESC para finalizar \n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=ESC);
    return 0;
}

///***************************************************************************///
///***************************************************************************/// LOGIN

void login(char mainArchivo[])
{
    int control;
    char username[20];
    char password[30];
    char userCopyName[20];
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

            if(strlen(username)==0)
            {
                printf("Wrong Username");
            }
            else
            {
                userStatus=searchUserName(mainArchivo,username);
                if(userStatus==0)
                {
                    printf("\nThe username doesn`t exist\n");
                }
            }
        }
        while(userStatus==0);

        do
        {
            rewind(log);
            printf("\n Ingrese el password\n");
            gets(password);

            while(fread(&user,sizeof(user),1,log)>0)
            {
                if(strcmp(username,user.userName)== 0 && strcmp(password, user.password)== 0)
                {
                    system("cls");
                    printf("\nWelcome %s\n", username);
                    strcpy(userCopyName,username);
                    currentID=user.idUser;
                    userActive(mainArchivo,currentID);
                    mainMenu(currentID, userCopyName);
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
        }
        while(status==0 && control!=ESC);
    }
    while(status=0);
    fclose(log);
}

///***************************************************************************///
///***************************************************************************/// REGISTRO/LOGIN

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

///***************************************************************************///
///***************************************************************************/// REGISTRO/LOGIN

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

///***************************************************************************///
///***************************************************************************/// REGISTRO

void registe(char mainArchivo[])
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

        do
        {
            printf("\n Ingrese su edad: \n");
            scanf("%d",&user.age);
            flag=ageOver(user.age);
            if(flag==0)
            {
                printf("\nLa edad tiene que ser superior a 16 anios\n");
            }
        }
        while(flag==0);
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
            flag=searchUserName(mainArchivo,user.userName);
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

        fclose(User_Arch);
    }
}

///***************************************************************************///
///***************************************************************************/// REGISTRO

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

///***************************************************************************///
///***************************************************************************/// REGISTRO

int ageOver(int age)
{
    int flag;
    if(age>16)
    {
        flag=1;
    }
    return flag;
}

///***************************************************************************///
///***************************************************************************/// ID USUARIO

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

///***************************************************************************///
///***************************************************************************/// MENU USUARIO

void mainMenu(int currentID)
{
    stPublish aux;
    stUser user;
    int idContent;
    int menu,control;

    do
    {
        printf("Bienvenido, que desea realizar");
        printf("\n [1] - Mensajes \n");
        printf("\n [2] - Post \n");
        printf("\n [3] - Editar perfil \n");
        printf("\n [4] - Cerrar sesion \n");
        // printf("\n [5] - Editar post\n");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            messengeMenu(currentID);
            break;
        case 2:
            postMenu(currentID, idContent);
            break;
        case 3:
            editUserMenu(currentID);
            break;
        case 4:
            printf("\nVuelva pronto\n");
            control=ESC;
            break;
            //   case 5:
            //       editPostMenu(idContent,publish,currentID);
            //      break;
        }
        // printf("\nEnter para continuar, ESC para salir.\n");
        //  fflush(stdin);
        //  control=getch();
        system("cls");
    }
    while(control!=ESC);
}

///***************************************************************************///
///***************************************************************************/// EDITOR
void postMenu(int currentID, int idContent)
{
    FILE *pPost = fopen(publish,"r+b");
    stPublish post;
    stUser user;
    int menu,control,deletepost;

    do
    {
        printf("\n\t Seleccione una opcion \n");
        printf("\n\t [1] - Mis post \n");
        printf("\n\t [2] - Ver post \n");
        printf("\n\t [3] - Crear post \n");
        printf("\n\t [4] - Editar post \n");
        /// printf("\n\t [5] - Eliminar post \n");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            showPublishPostIndividual(publish,mainArchivo,currentID);
            break;
        case 2:
            showPublish(publish,mainArchivo,currentID);
            break;
        case 3:
            publishPost(currentID,publish);
            break;
        case 4:
            showPublishPostIndividual(publish,mainArchivo,currentID);
            editPostMenu(idContent,publish,currentID);
            break;
        }
        printf("\nEnter para continuar, ESC para salir.\n");
        control=getch();
        system("cls");
    }
    while(control!=ESC);
}


///***************************************************************************///
///***************************************************************************///
///***************************************************************************///
///***************************************************************************///

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
    do
    {
        printf("\n \t \t \t \t \t \t Editar Usuario");
        printf("\n [1] - Cambiar password \n");
        printf("\n [2] - Cambiar ciudad \n");
        printf("\n [3] - Cambiar Edad \n");
        printf("\n [4] - Cambiar E-mail\n");
        printf("\n [5] - Cambiar Genero\n");
        printf("\n [6] - Mostrar Usuario\n");
        printf("\n [7] - Dar de baja la cuenta\n");

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
            searchNamePOST(currentID,mainArchivo);
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
            aux=searchNamePOST(currentID,mainArchivo);
            showMyUser(aux);
            break;
        case 7:
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
    }
    while(control!=ESC);
}

///***************************************************************************///
///***************************************************************************/// EDITOR

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

///***************************************************************************///
///***************************************************************************/// EDITOR

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

///***************************************************************************///
///***************************************************************************/// EDITOR

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

///***************************************************************************///
///***************************************************************************/// EDITOR

void editUserGender(char arch[],int currentID, char newGender[30])
{
    FILE *pArch = fopen(arch,"r+b");
    stUser *user;
    if(pArch)
    {
        if(fread(&user,sizeof(stUser),1,pArch)>0)
        {
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fread(&user,sizeof(stUser),1,pArch);
            strcpy(user->gender,newGender);
            fseek(pArch,(currentID-1)*sizeof(stUser),SEEK_SET);
            fwrite(&user,sizeof(stUser),1,pArch);
        }
    }
    fclose(pArch);
}

///***************************************************************************///
///***************************************************************************/// EDITOR

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

///***************************************************************************///
///***************************************************************************/// EDITOR

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

///***************************************************************************///
///***************************************************************************/// EDITOR

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

///***************************************************************************///
///***************************************************************************/// MOSTRAR USUARIO

void showOneUser(stUser a)
{
    printf("\nId.......................: %d", a.idUser);
    printf("\nUserName.................: %s", a.userName);
    printf("\nPassword.................: %s", a.password);
    printf("\nApellido.................: %s", a.lastName);
    printf("\nNombre...................: %s", a.firstName);
    printf("\nAge......................: %d", a.age);
    printf("\nDNI......................: %d", a.dni);
    printf("\nGenero...................: %s \n", a.gender);
    printf("\nCiudad...................: %s\n",a.city);
    printf("\nUser Status..............: %d\n",a.status);
}

///***************************************************************************///
///***************************************************************************///
void showMyUser(stUser a)
{
    printf("\t\t\t******************************************************");
    printf("\n\t\t\t***UserName.................: %10s           ***", a.userName);
    printf("\n\t\t\t***Password.................: %10s           ***", a.password);
    printf("\n\t\t\t***Apellido.................: %10s           ***", a.lastName);
    printf("\n\t\t\t***Nombre...................: %10s           ***", a.firstName);
    printf("\n\t\t\t***Age......................: %10d           ***", a.age);
    printf("\n\t\t\t***DNI......................: %10d           ***", a.dni);
    printf("\n\t\t\t***Genero...................: %10s           ***", a.gender);
    // printf("\t\t\t\nCorreo electronico.......: %s\n", a.corre);
    printf("\n\t\t\t***Ciudad...................: %10s          ***\n",a.city);
    printf("\t\t\t******************************************************");
}

///***************************************************************************///
///***************************************************************************/// MOSTRAR USUARIO

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

///***************************************************************************///
///***************************************************************************/// PUBLICAR

int publishPost(int currentID,char publish [])
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
        printf("\n Ingrese el titulo de la publicacion \n");
        fflush(stdin);
        gets(post.title);

        printf("\n Ingrese una breve descripcion suya.\n");
        fflush(stdin);
        gets(post.description);

        printf("\n Ingrese el precio\n");
        scanf("%d",&post.cost);

        printf("\nSeleccione un lugar de reunion\n");
        selectPlace(publish,&post);

        user=searchNamePOST(currentID,mainArchivo);
        iDpost++;
        strcpy(post.userNamePost,userNamePost1);
        post.idContent=iDpost;
        post.idUserContact=user.idUser;
        post.active=1;
        postStatus=1;
        fwrite(&post,sizeof(stPublish),1,pPost);
        fclose(pPost);
    }
    statusPublisPost(postStatus);
    return postStatus;
}

///***************************************************************************///
///***************************************************************************/// PUBLICAR

void statusPublisPost (int postStatus)
{
    if (postStatus==1)
    {
        printf("\n La publicacion se cargo con exito");
    }
    else
    {
        printf("\n La publicacion tuvo problemas para poder se cargada.");
    }
}

///***************************************************************************///
///***************************************************************************/// PUBLICAR

void selectPlace(char publish[],stPublish post)
{
    FILE * pPublish = fopen(publish,"ab");
    int menu;
    printf("\nSeleccione el lugar: \n");
    printf("\n [1] - La Fonte D´Oro || Colon y Buenos Aires Buenos Aires 2098 \n");
    printf("\n [2] - La Fonte D´Oro || Constitucion y Av. Tejedor \n");
    printf("\n [3] - La Fonte D´Oro || Luro y 180 \n");
    printf("\n [4] - La Fonte D´Oro || Urquiza y la Costa \n");
    printf("\n [5] - Café Martínez  || Av. Colón 3651 · 7 a 22 \n");
    printf("\n [6] - Di Mero Espresso Cafeteria || Martin Miguel de Guemes 2483 - 7 a 20 \n");
    printf("\n [7] - ADORADO Cafe & Bar || Paseo Aldrey Shopping 8- 20:30 \n");
    printf("\n [8] - De Postres || Carlos Alvear 2889 \n");
    printf("\n [9] - Croissant Cafe || Cordoba 2361 \n");
    printf("\n [10]-Adorado Cafe || Av. Independencia 2546 \n");
    do
    {
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            strcpy(post.places,"La Fonte D´Oro- Colón y Buenos Aires Buenos Aires 2098");
            break;
        case 2:
            strcpy(post.places,"La Fonte D´Oro - Constitucion y Av. Tejedor");
            break;
        case 3:
            strcpy(post.places,"La Fonte D´Oro - Luro y 180");
            break;
        case 4:
            strcpy(post.places,"La Fonte D´Oro - Urquiza y la Costa");
            break;
        case 5:
            strcpy(post.places,"Cafe Martinez  - Av. Colón 3651 · 7 a 22");
            break;
        case 6:
            strcpy(post.places,"Di Mero Espresso Cafeteria - Martin Miguel de Guemes 2483 - 7 a 20");
            break;
        case 7:
            strcpy(post.places,"ADORADO Cafe & Bar - Paseo Aldrey Shopping 8- 20:30");
            break;
        case 8:
            strcpy(post.places,"De Postres - Carlos Alvear 2889");
            break;
        case 9:
            strcpy(post.places,"Croissant Cafe - Cordoba 2361");
            break;
        case 10:
            strcpy(post.places,"Adorado Cafe - Av. Independencia 2546");
            break;
        }
        if(menu>0 && menu>=11)
        {
            printf("\nLa opcion ingresada es inconrrecta, vuelva a ingresar.\n");
        }
    }
    while(menu>0 && menu>=11);
    fwrite(&post,sizeof(stPublish),1,pPublish);
    fclose(pPublish);
}

///***************************************************************************///
///***************************************************************************/// PUBLICAR

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
                    printf("\n \t \t **************************************************************************************\n");
                    printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                    printf("\n \t \t \t \t \t \t \t \t \t \t \t  %s\n",user.userName);
                    printf("\n \t \t ID post: %d\n", post.idContent);
                    printf("\n \t \t \t %s \n",post.title);
                    printf("\n \t \t  %s \n", post.description);
                    printf("\n \t \t Localizacion : %s \n",post.places);
                    printf("\n \t \t \t \t \t \t \t \t \t \t  El precio es :%d\n",post.cost);
                    printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                    printf("\n \t \t **************************************************************************************\n");
                }
            }
        }
        fclose(pOpen);
        fclose(User_Arch);
    }
}

///***************************************************************************///
///***************************************************************************///
void showPublish(char publish[],char mainArchivo[],int currentID)
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
                    printf("\n \t \t **************************************************************************************\n");
                    printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                    printf("\n \t \t \t \t \t \t \t \t \t \t \t  %s\n",user.userName);
                    printf("\n \t \t ID post: %d\n", post.idContent);
                    printf("\n \t \t \t %s \n",post.title);
                    printf("\n \t \t  %s \n", post.description);
                    printf("\n \t \t Localizacion : %s \n",post.places);
                    printf("\n \t \t \t \t \t \t \t \t \t \t  El precio es :%d\n",post.cost);
                    printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                    printf("\n \t \t **************************************************************************************\n");
                }
            }
        fclose(pOpen);
        fclose(User_Arch);
    }
}

///***************************************************************************///
///***************************************************************************/// ID DE LA PUBLCIACIÓN

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

///***************************************************************************///
///***************************************************************************/// PUBLICAR

void editPostMenu(int idContent, char publish[], int currentID)
{
    FILE *pPost = fopen(publish,"r+b");
    stPublish post;
    stUser user;
    int value=0;
    int menu,control;
    int publication;

    char newTitle[30];
    char newDescription[300];
    char categoria[30];
    int active;
    int newCost;
    int newTime;
    char newPlaces[100];

    do
    {
        printf("\n\t Seleccione una opcion \n");
        printf("\n\t [1] - Editar Titulo \n");
        printf("\n\t [2] - Editar Descripcion \n");
        printf("\n\t [3] - Editar Categoria \n"); ///FALTA
        printf("\n\t [4] - Editar Precio \n");
        printf("\n\t [5] - Editar tiempo \n");///FALTA
        printf("\n\t [6] - Editar lugar \n");///FALTA
        printf("\n\t [7] - Dar de baja una publicacion \n");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            printf("\n Ingrese el ID del post que quiere editar \n");
            scanf("%d",&value);
            printf("\n Ingrese el nuevo titulo\n");
            fflush(stdin);
            gets(newTitle);
            editPostTitle(publish,value,newTitle);
            break;
        case 2:
            printf("\n Ingrese el ID del post que quiere editar \n");
            scanf("%d",&value);
            printf("\n Ingrese la nueva descripcion\n");
            fflush(stdin);
            gets(newDescription);
            editPostDescription(publish,value,newDescription);
            break;
        case 3:
            break;
        case 4:
            printf("\n Ingrese el ID del post que quiere editar \n");
            scanf("%d",&value);
            printf("\n Ingrese el nuevo precio \n");
            scanf("%d",&newCost);
            editPostCost(publish,value,newCost);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            printf("\n Ingrese el ID del post que quiere editar \n");
            scanf("%d",&value);
            disablePost(publish,value);
            break;
        }
        printf("\nEnter para continuar, ESC para salir.\n");
        control=getch();
        system("cls");
    }
    while(control!=ESC);
}

///***************************************************************************///
///***************************************************************************/// PUBLICAR

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
            fseek(pPost,(value-1)*sizeof(stPublish),SEEK_SET);
            fwrite(&post,sizeof(stUser),1,pPost);
        }
        fclose(pPost);
    }
}

///***************************************************************************///
///***************************************************************************/// PUBLICAR
///***************************************************************************///Edit Title post
///***************************************************************************///
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
    }
    fclose(pArch);
}
///***************************************************************************///
///***************************************************************************///Edit title post
///***************************************************************************///
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
///***************************************************************************///
///***************************************************************************///Edit
///***************************************************************************///
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
    printf("\n%d",currentID);

    if(pOpen && User_Arch)
    {
        ///(fread(&user,sizeof(stUser),1,User_Arch);
        user=searchNamePOST(currentID,mainArchivo);

        while(fread(&post,sizeof(stPublish),1,pOpen)>0)
        {
            if(post.idUserContact==user.idUser)///user.idUser==post.idContent &&///
            {
                printf("\n \t \t **************************************************************************************\n");
                printf("\n \t \t *****----------------------------------------------------------------------------*****\n");
                printf("\n \t \t \t \t \t \t \t \t \t \t \t  %s\n", user.userName);
                printf("\n \t \t ID post: %d\n", post.idContent);
                printf("\n \t \t \t %s \n",post.title);
                printf("\n \t \t  %s \n", post.description);
                printf("\n \t \t Localizacion : %s \n",post.places);
                printf("\n \t \t \t \t \t \t \t \t \t \t  El precio es :%d\n",post.cost);
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

//int searchNamePOST(int currentID, char mainArchivo[], char *userNamePost[20])
//{
//    FILE *User_Arch=fopen(mainArchivo,"rb");
//    stUser user;
//    int i=0;
//    if(User_Arch!=NULL)
//    {
//       /// printf("%s",userNamePost);
//        fseek(User_Arch,(currentID-1)*sizeof(stUser),SEEK_CUR);
//        fread(&user,sizeof(stUser),1,User_Arch);
//        if (user.idUser==currentID)
//            {i=strcpy(&userNamePost,user.userName);}
//            else{printf("\n nose encontro");}
//        printf("%d",&userNamePost);
//        fclose(User_Arch);
//    }
//    return i;
//}

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

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void messengeMenu(int currentID)
{
    stUser user;
    stPublish post;
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
            viewMesengges (currentID,messangerUsuarios,mainArchivo);

            break;
        case 2:
            sendMesengges (currentID,messangerUsuarios,mainArchivo);
            break;
        case 3:
            viewMesenggesSend(currentID,messangerUsuarios,mainArchivo);
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

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void viewMesengges (int currentID,char messangerUsuarios[], char mainArchivo[])
{
    stMessenge sms;
    stUser user, userSearchSend;

    FILE * User_Archi = fopen(mainArchivo,"rb");
    FILE * mSn = fopen(messangerUsuarios,"r+b");
    if (User_Archi && mSn)
    {
        user=searchNamePOST(currentID,mainArchivo);
        while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {
            userSearchSend=searchNamePOST(sms.idIssuing,mainArchivo);

            if(user.idUser==sms.idReceiver)
            {
                printf("\n**************** Enviado de %s \n", userSearchSend.userName);
                printf("\n---> %s \n", sms.message);
                //printf("\n---> %d \n", sms.read);
               // sms.read=1;
                // printf("\n---> %d \n", sms.read);
                //printf("\n---> %d \n", sms.read);
                //fwrite(&sms,sizeof(stMessenge),1,mSn);
            }
        }
        fclose(User_Archi);
        fclose(mSn);
    }
}

///

///***************************************************************************///
///***************************************************************************///  MENSAJERIA

void sendMesengges (int currentID, char messangerUsuarios[], char mainArchivo[])
{
    stMessenge sms;
    stUser user,userSearch;
    int idMessenge = lastIDsms(messangerUsuarios);
    char name[20];

    FILE * User_Archi = fopen(mainArchivo,"rb");
    if(User_Archi)
    {
        user=searchNamePOST(currentID,mainArchivo);

        printf("\n Ingrese a que usuario desea enviar mensaje\n");
        fflush(stdin);
        gets(name);

        userSearch=searchUserMessenge(name,mainArchivo);

        FILE * mSn = fopen(messangerUsuarios,"ab");
        if(mSn)
        {
            printf("\nEscriba el mensaje a %s \n", userSearch.userName);
            fflush(stdin);
            gets(sms.message);
            idMessenge++;
            sms.idContent=idMessenge;
            sms.idReceiver=userSearch.idUser; /// RECIBE
            sms.idIssuing=user.idUser;        /// ENVIA
            sms.read=0;
            printf("\n------------%d",sms.read);
            fwrite(&sms,sizeof(stMessenge),1,mSn);
            fclose(mSn);
        }
        fclose(User_Archi);
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
    FILE *mSn =fopen(messangerUsuarios,"rb");
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

void viewMesenggesSend (int currentID,char messangerUsuarios[], char mainArchivo[])
{
    stMessenge sms;
    stUser user, userSearchSend;

    FILE * User_Archi = fopen(mainArchivo,"rb");
    FILE * mSn = fopen(messangerUsuarios,"rb");
    if (User_Archi && mSn)
    {
        user=searchNamePOST(currentID,mainArchivo);
        while(fread(&sms,sizeof(stMessenge),1,mSn)>0)
        {
            userSearchSend=searchNamePOST(sms.idReceiver,mainArchivo);
            if(user.idUser==sms.idIssuing)
            {
                printf("\n**************** Enviado de : %s \n", user.userName);
                printf("\n**************** Para : %s \n", userSearchSend.userName);
                printf("\n---> %s \n", sms.message);
                printf("\n---> %d \n", sms.read);
            }
        }
    }
}

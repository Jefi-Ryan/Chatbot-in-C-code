#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#define IDI_ICON 1
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <string.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
HWND textbox,button,process,user;
HWND bot;
HWND question;
HMENU menubar,childmenu;
char text[1000];
char initial[]="Hello ";
SCROLLINFO si;
//20,10,300,100

int textleft=280,texttop=30,textwidth=200,textheight=50;
int botleft=20,bottop=140,botwidth=300,botheight=100;

int buttonleft=430,buttontop=75,buttonwidth=50,buttonheight=20;
int run=0,count=0;
int donotrun=0;

char data[250][2][200]={
    {"bit","zeros and ones are called bits"},
    {"byte","The byte is a unit of digital information that most commonly consists of eight bits."},
    {"batch processing","In batch processing, a number of jobs are entered into the computer, stored internally, and then processed sequentially."},
    {"timesharing","Timesharing allows many different users to use a single computer simultaneously."},
    {"interactive computing","In an interactive computing environment, the user and the computer interact with each other during the computational session."},
    {"main","main is a name of function which is predefined function in C library"},
    {"integrity","Integrity refers to the accuracy of the calculations."},
    {"clarity","Clarity refers to the overall readability of the program"},
    {"simplicity","The clarity and accuracy of a program are usually enhanced by keeping things as simple as possible, consistent with the overall program objectives."},
    {"efficiency","Efficiency is concerned with execution speed and efficient memory utilization."},
    {"modularity","Many programs can be broken down into a series of identifiable subtasks."},
    {"generality","Generality refers to a program to be as general as possible within reasonable limits."},
    {"identifier","Identifiers are names that are given to various program elements, such as variables, functions and arrays."},
    {"keyword","keywords have standard, predefined meanings in C."},
    {"data type","C supports several different types of data, each of which may be represented differently within the computer's memory."},
    {"int","int is integer quantity."},
    {"char","char is single character. size of char is 1 byte(-128 to 127)"},
    {"signed char","size of signed char is 1 byte (-128 to 127)"},
    {"unsigned char","size of unsigned char is 1 byte (0 to 255)"},
    {"short","size of short is 2 byte (-32,768 to 32,767)"},
    {"signed short","size of short is 2 byte (-32,768 to 32,767)"},
    {"unsigned int","size of unsigned int is 2 byte (0 to 65,535)"},
    {"short int","size of short int is 2 byte (-32,768 to 32,767)"},
    {"signed short int","size of signed short int is 2 byte (-32,768 to 32,767)"},
    {"unsigned short int","size of unsigned short int is 2 byte (0 to 65,535)"},
    {"long int","size of long int is 4 byte (-2,147,483,648 to 2,147,483,647)"},
    {"signed long int","size of signed long int is 4 byte (-2,147,483,648 to 2,147,483,647)"},
    {"unsigned long int","size of unsigned long int is 4 byte (0 to 4,294,967,295)"},
    {"float","float is floating-point number. size of float is 4 byte"},
    {"double","double is double-precision floating-point number. size of double is 8 byte"},
    {"long double","size of long double is 16 byte"},
    {"basic data type","int, char, float, double"},
    {"derived data type","array, pointer, structure, union"},
    {"enumeration data type","enum"},
    {"void data type","void type means that the function will not return any value."},
    {"integer constant","integer constant is an integer-valued number"},
    {"decimal integer constant","decimal integer constant can consist of any combination of digits taken from the set 0 through 9"},
    {"octal integer constant","octal integer constant can consist of any combination of digits taken from the set 0 through 7."},
    {"hexadecimal integer constant","hexadecimal integer constant must begin with either Ox or OX."},
    {"Unsigned integer constant","Unsigned integer constants may exceed the magnitude of ordinary integer constants by approximately a factor of 2, though they may not be negative."},
    {"long integer constant","Long integer constants may exceed the magnitude of ordinary integer constants."},
    {"unsigned long integer constant","unsigned long integer may be specified by appending the letters UL to the end of the constant."},
    {"floating point constant","A floating-point constant is a base- 10 number that contains either a decimal point or an exponent"},
    {"character constant","character constant is a single character, enclosed in apostrophes"},
    {"escape sequence","Certain non printing characters, as well as the backslash (\\) and the apostrophe (I), can be expressed in terms of escape sequences."},
    {"string constant","A string constant consists of any number of consecutive characters (including none), enclosed in (double) quotation marks."},
    {"variable","A variable is an identifier that is used to represent some specified type of information within a designated portion of the program."},
    {"array","An array is an identifier that refers to a collection of data items that all have the same name."},
    {"declaration","A declaration associates a group of variables with a specific data type. A declaration consists of a data type, followed by one or more variable names, ending with a semicolon."},
    {"expression","An expression represents a single data item, such as a number or a character."},
    {"statement","A statement causes the computer to carry out some action."},
    {"control statement","Control statements are used to create special program features, such as logical tests, loops and branches."},
    {"compound statement","A compound statement consists of several individual statements enclosed within a pair of braces { }."},
    {"symbolic constant","A symbolic constant is a name that substitutes for a sequence of characters."},
    {"subscript","In programming, a symbol or number used to identify an element in an array called subscript."},
    {"index","In programming, a symbol or number used to identify an element in an array called index."},
    {"integer division","Division of one integer quantity by another is referred to as integer division."},
    {"modulus operator","The % operator is sometimes referred to as the modulus operator."},
    {"cast","converting the value of an expression to a different data type called cast"},
    {"unary operator","C includes a class of operators that act upon a single operand to produce a new value. Such operators are known as unary operators.(-, ++, -- ,! ,sizeof ,(type))"},
    {"sizeof","This operator returns the size of its operand, in bytes. The sizeof operator always precedes its operand."},
    {"logical operator","A logical operator is a symbol or word used to connect two or more expressions eg: AND, OR, NOT."},
    {"assignment operator","assignment operators are used to assign the value of an expression to an identifier.(= ,+= ,-= ,*= ,/= ,%=)"},
    {"relational operator","Relational operators are symbols used to specify a certain relationship between two numbers or numeric values.(< ,<= ,> ,>=)"},
    {"equality operator","The equality operator (==) is used to compare two values or expressions."},
    {"conditional operator","Simple conditional operations can be carried out with the conditional operator (? :)."},
    {"library function","The C language is accompanied by a number of library functions that carry out various commonly used operations or calculations."},
    {"abs","Return the absolute value of i."},
    {"ceil","Round up to the next integer value"},
    {"cos","Return the cosine."},
    {"cosh","Return the hyperbolic cosine"},
    {"fabs","Return the absolute value"},
    {"floor","Round down to the next integer value"},
    {"fmod","Return the remainder"},
    {"getchar","Enter a character from the standard input device"},
    {"log","Return the natural logarithm"},
    {"putchar","Send a character to the standard output device."},
    {"rand","Return a random positive integer."},
    {"sin","Return the sine"},
    {"sqrt","Return the square root"},
    {"srand","Initialize the random number generator."},
    {"tan","Return the tangent"},
    {"toascii","Convert value of argument to ASCII."},
    {"tolower","Convert letter to lowercase."},
    {"toupper","Convert letter to uppercase."},
    {"operator","operator is a symbol that usually represents an action or process."},
    {"operand","The quantity on which an operation is to be done."},
    {"printf","This function can be used to output any combination of numerical values, single characters and strings"},
    {"scanf","function enters data from the standard input device and stores it in the computer's memory"},
    {"precision","the maximum number of decimal places for a floating-point value, or the maximum number of characters for a string"},
    {"syntax error","Errors that occur when you violate the rules of writing C"},
    {"logical error","These types of errors which provide incorrect output but appears to be error free are called logical error"},
    {"Error isolation","the property in which corrupted messages do not propagate errors between processes of the system"},
    {"watch value", "A watch value is the value of a variable or an expression which is displayed continuously as the program executes"},
    {"breakpoint","A breakpoint is a temporary stopping point within a program"},
    {"Stepping","Stepping refers to the execution of one instruction at a time, typically by pressing a fbnction key to execute each instruction"},
    {"Branching","Branching is deciding what actions to take"},
    {"looping","deciding how many times to take a certain action"},
    {"break","The word break is a keyword that terminates the execution of the loop or the control statement and the control is transferred to the statement immediately following it"},
    {"negation operator","The negation operator is used to reverse the meaning of a logical expression"},
    {"conditional operator","The conditional operator (? :) is a ternary operator (it takes three operands)"},
    {"Infinite Loop","A loop becomes an infinite loop if a condition never becomes false"},
    {"if else","The if-else statement in C is used to perform the operations based on some specific condition, condition is true then it displays the if statement otherwise displays the else statement"},
    {"while statement","The while statement is used to carry out looping operations, in which a group of statements is executed repeatedly, until some condition is satisified"},
    {"while","The while statement is used to carry out looping operations, in which a group of statements is executed repeatedly, until some condition is satisified"},
    {"ASCII","abbreviation of American Standard Code For Information Interchange"},
    {"count","an iteration counter (count will increase by 1 at each successive iteration"},
    {"flag","A flag variable is simply a boolean variable whose contents is true or false"},
    {"switch statement", "The switch statement causes a particular group of statements to be chosen from several available groups"},
    {"switch", "The switch statement causes a particular group of statements to be chosen from several available groups"},
    {"continue statement","The continue statement is used to bypass the remainder of the current pass through a loop"},
    {"continue","The continue statement is used to bypass the remainder of the current pass through a loop"},
    {"goto statement","The goto statement is used to alter the normal sequence of program execution by transferring control to someother part of the program"},
    {"goto","The goto statement is used to alter the normal sequence of program execution by transferring control to someother part of the program"},
    {"getchar function","Single characters can be entered into the computer using the C library function getchar"},
    {"getchar","Single characters can be entered into the computer using the C library function getchar"},
    {"putchar function","Single characters can be displayed (i.e, written out of the computer) using the C library function putchar"},
    {"putchar","Single characters can be displayed (i.e, written out of the computer) using the C library function putchar"},
    {"control string","control string refers to a string that contains formatting information"},
    {"argument","the arguments can be written as constants, single variable or array names, or more complex expressions"},
    {"arguments","the arguments can be written as constants, single variable or array names, or more complex expressions"},
    {"jefi","He is the creator of SPIDEY!"},
    {"ryan","He is the creator of SPIDEY!"},
    {"jefi ryan","He is the creator of SPIDEY!"},
    {"Ashwala","He is the co-creator of SPIDEY!"},
    {"Ashwala ravi","He is the co-creator of SPIDEY!"},
    {"Ashwala ravi teja","He is the co-creator of SPIDEY!"},
    {"Harsha","She is the co-creator of SPIDEY!"},
    {"Emmanuel","He is the co-creator of SPIDEY!"},
    {"Emmanuel arthur","He is the co-creator of SPIDEY!"},
    {"Emmanuel arthur george","He is the co-creator of SPIDEY!"},
    {"Pointer","Pointer represents the location of data item such as a variable or an array"},
    {"Ampersand","It is a address operator and it is used to find the address of a variable"},
    {"Asterisk","It is a indirection operator and it is used to access the data stored in a variable"},
    {"Pointer declaration","A pointer is declared as a variable but with * in front of it"},
    {"Double parentheses","This type of decleration is used to establish precedence"},
    {"Typedef","This allows the user to define new data types that are equivalent to exisitng data types"},
    {"Union","Union is user defined datatype.It is a collection of variables of different datatypes"},
    {"Use of unions","Unions can be useful in many situations where we want to use the same memory for two or more members"},
    {"Data files","Data files allow us to store information permanently, and to access and alter that information whenever necessary"},
    {"fopen","The library function 'fopen' is used to open a file"},
    {"fclose","A data file must be closed at the end of the program and fclose is used for that.The syntax is 'fclose(ptvar);' "},
    {"strset()","strset ( ) function sets all the characters in a string to given character"},
    {"strset","strset ( ) function sets all the characters in a string to given character"},
    {"f_eof","The f_eof function returns a non-zero value if the read/write pointer has reached end of the file; otherwise it returns a zero"},
    {"function","A function is a self contained block or a sub-program of one or more statements that performs a specific task when called."},
	{"user defined function" , "user can modify according to need."},
	{"benefits of function", "divide and conquer, code reusability and avoid code repetitions."},
	{"types of function call", "call by value and call by reference."},
	{"Call by value", "The call by value method of passing arguments to a function copies the actual value of an argument into the formal parameter of the function."},
	{"call by reference", "The call by reference method of passing arguments to a function copies the address of an argument into the formal parameter"},
	{"function overloading" , "In a c program, more than one function with same name but different number of arguments and different types of arguments is called as function overloading."},
	{"variable","A variable is a way to represent memory location through symbol so that it can be easily identified."},
	{"whitespace", "whitespace is any character or series of characters that represents horizontal or vertical space in typography."},
	{"local variable","A variable that is declared inside the function or blocks is called a local variable."},
	{"global variable", "A variable that is declared outside the function or block is called as global variable."},
	{"static variable", "A variable that is declared with the static keyword is called as static variable."},
	{"automation variable", "All variable in c that are declared inside the block, are automation variables by default"},
	{"external variable", "Can share a variable in multiple c source files using an external variable."},
	{"One dimensional array"," A one-dimensional array is a structured collection of components that can be accessed individually by specifying the position of a component with a single index value."},
	{"Two dimensional array","the simplest form of multidimensional array is the two-dimensional array."},
	{"Three dimensional array", "A 3D array is a multi-dimensional array (array of arrays). More dimensions in an array means more data can be stored in that array."},
	{"index()","The index() function locates the first occurrence of c in the string pointed to by string."},
    {"initialization", "Giving initial value to the variable"},
	{"compile time initialization", "declaring the array during the declaration time is called compile time initialization."},
	{"run time initialization", "scanning the values during the execution of the program by using for loop is called as run time error."},
	{"int sample", "can define a variable as an integer and assign a value to it in a single declaration."},
	{"input array", "input array is a special case of the INPUT statement which allows user to input data from a screen array into a program array"},
    {"range of array", "Array range notation is a shorthand notation to facilitate passing of array variables to built-in, internal and external Functions and Procedures."},
	{"searching algorithm", "searching algorithm is an algorithm made up of a series of instructions that retrieves information stored within some data structure, or calculated in the search space of a problem domain."},
	{"Linear search", "linear search is a method for finding a target value within a list."},
	{"disadvantage of linear search", "Slow searching of large lists."},
	{"sorting algorithm", "A sorting algorithm is used to rearrange a given array or list elements according to a comparison operator on the elements."},
	{"Bubble sort", "bubble sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in wrong order."},
	{"Advantage of bubble sort", "easy to implement, memory efficient, it gives stable sort."},
	{"advantage of linear search", "the list does not need to sorted, not  affected by insertions and deletions."},
	{"String", "A sequence of one or more characters enclosed in double quotes."},
	{"null character" , "In the C programming language, character strings are terminated by using NULL Character."},
	{"char[]", "It is short for character, which is a data type that holds one character (letter, number, etc.) of data."},
	{"char", "It is short for character, which is a data type that holds one character (letter, number, etc.) of data."},
	{"Traversing strings","Traversing a string means accessing all the elements of the string one after the other by using the subscript. A string can be traversed using for loop or while loop."},
	{"strlen", "to find the length of a string."},
	{"strlen()", "to find the length of a string."},
	{"Strupr", "converts a string to uppercase"},
	{"Strupr()", "converts a string to uppercase"},
	{"strrev", "reverses a string."},
	{"strrev()", "reverses a string."},
	{"strlwr", "converts a string to lowercase."},
	{"strlwr()", "converts a string to lowercase."},
	{"strcpy", "to copy or assign a string to another variable"},
	{"strcpy()", "to copy or assign a string to another variable"},
	{"strcmp", "to compare a string with another."},
	{"strcmp()", "to compare a string with another."},
	{"strcat", "to concatenate or join two strings."},
	{"strcat()", "to concatenate or join two strings."},
	{"test array", "To initialize and test an array, specify the same value for all the array elements."}
};
char string[100];
char string2[100];
char* check;
void keyword(){
    int count=0;
    for(int k=0;k<strlen(text);k++){
        if(text[k]=='\"'){
            for(int j=k+1;j<50;j++){
                if(text[k]=='\"'){
                    string2[count]='\0';

                }
                string2[count]=text[j];
                count++;
            }
        }
    }
    for(int l=0;l<strlen(string2);l++){
        if(string2[l]=='\"'){
            string2[l]='\0';
        }



    }
    if(strlen(string2)==0)
    {
        string2[0]=='\0';
    }
    check=strstr(text,string2);
    if(check==NULL){
        string2[0]=NULL;
    }
}
void chat(HWND hwnd,int flag,int place){
    printf("\ntexttop: %d",texttop);
    printf("\nbottop: %d",bottop);
    char elsepart[]="Sorry, I'm not trained to answer this.\nI think you missed to type your keywords within double quotes(\" \") or there's a typo in your question!";
    if(run==1){

            printf("\nrun is 1 so if block");
            process=CreateWindow("STATIC","",
                    WS_VISIBLE |WS_CHILD,
                    0,0,600,550,
                    hwnd,NULL,NULL,NULL);

            printf("\nanswered!");
            printf("\nquestioned!");
            if(place==-1){
            printf("\nanswered!");
            CreateWindow("STATIC","SPIDEY",
                         WS_VISIBLE | WS_CHILD,
                         20,bottop-20,300,20,process,NULL,NULL,NULL);
            bot=CreateWindow("STATIC",elsepart,
                    WS_VISIBLE | WS_CHILD |WS_BORDER | SS_LEFT | SS_EDITCONTROL,
                    20,bottop,300,100,
                    process,NULL,NULL,NULL);

            }
            else{
                printf("\nanswered!");
                CreateWindow("STATIC","SPIDEY",
                         WS_VISIBLE | WS_CHILD,
                         20,bottop-20,300,20,process,NULL,NULL,NULL);
                bot=CreateWindow("STATIC",data[place][1],
                    WS_VISIBLE | WS_CHILD |WS_BORDER | SS_LEFT | SS_EDITCONTROL,
                    20,bottop,300,100,
                    process,NULL,NULL,NULL);
            }
            printf("\n In chat user input is : %s",text);
            CreateWindow("STATIC","USER",
                         WS_VISIBLE | WS_CHILD,
                         520,texttop-20,250,20,process,NULL,NULL,NULL);
            question=CreateWindow("STATIC",text,
                    WS_VISIBLE | WS_BORDER | WS_CHILD |SS_LEFT | SS_EDITCONTROL,
                    310,texttop,250,90,
                    process,NULL,NULL,NULL);
            run=0;
            donotrun=0;
            printf("\n run resetted!");

            }
    else{
        if(place==-1){
            printf("\nanswered!");
            CreateWindow("STATIC","SPIDEY",
                         WS_VISIBLE | WS_CHILD,
                         20,bottop-20,300,20,process,NULL,NULL,NULL);
            bot=CreateWindow("STATIC",elsepart,
                    WS_VISIBLE | WS_CHILD |WS_BORDER | SS_LEFT | SS_EDITCONTROL,
                    20,bottop,300,100,
                    process,NULL,NULL,NULL);
        }
        else{
            printf("\nanswered!");
            CreateWindow("STATIC","SPIDEY",
                         WS_VISIBLE | WS_CHILD,
                         20,bottop-20,300,20,process,NULL,NULL,NULL);
            bot=CreateWindow("STATIC",data[place][1],
                    WS_VISIBLE | WS_CHILD |WS_BORDER | SS_LEFT | SS_EDITCONTROL,
                    20,bottop,300,100,
                    process,NULL,NULL,NULL);
        }


            }
    if(flag==1){
        printf("\nquestioned!");
        printf("\n In chat user input is : %s",text);
        CreateWindow("STATIC","USER",
                         WS_VISIBLE | WS_CHILD,
                         520,texttop-20,250,20,process,NULL,NULL,NULL);
        question=CreateWindow("STATIC",text,
                    WS_VISIBLE | WS_BORDER | WS_CHILD | SS_LEFT | SS_EDITCONTROL,
                    310,texttop,250,90,
                    process,NULL,NULL,NULL);


    }
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = (HICON) LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,16,16,0);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Spidey chat bot"),       /* Title Text */
           WS_SYSMENU | WS_MINIMIZEBOX , /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           670,                 /* The programs width */
           750,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {

        case WM_CREATE:

            //menu(hwnd);

            menubar=CreateMenu();
            childmenu=CreateMenu();

            AppendMenu(menubar,MF_POPUP,(UINT_PTR)childmenu,"Help");
            AppendMenu(childmenu,MF_STRING,2,"Tips");
            AppendMenu(childmenu,MF_STRING,3,"About");
            SetMenu(hwnd,menubar);

            process=CreateWindow("STATIC","",
                WS_VISIBLE |WS_CHILD  |WS_BORDER,
                30,10,600,550,
                hwnd,NULL,NULL,NULL);
            user=CreateWindow("EDIT","",
                WS_VISIBLE | WS_CHILD |WS_BORDER| ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                30,580,400,70,
                hwnd,NULL,NULL,NULL);
            button=CreateWindow("BUTTON","Send",
                WS_VISIBLE | WS_BORDER | WS_CHILD ,
                440,600,80,30,
                hwnd,(HMENU) 1,NULL,NULL);


            break;
//92, 77, 238

        case WM_COMMAND:

            switch(LOWORD(wParam))
            {


                 case 1:

                       count+=1;
                       int retrieved1;
                       retrieved1=GetWindowText(user,text,1000);
                       if(strlen(text)==0){
                            MessageBeep("IconError");
                            MessageBox(hwnd,"Please enter a value!","Warning",MB_OK);
                            count-=1;
                            goto bottom;

                       }
                       printf("\n------------count: %d----------------",count);

                       if(count==3){
                            run=1;
                            count=1;
                       }
                       else{
                            printf("\ncount is not 3!");
                            run=0;
                       }
                       printf("\nCase 1 is executed!");


                       int search;

                       int state;
                       keyword();
                       printf("\nKeyword is : %s",string2);
                        for(int i=0;i<sizeof(data)/sizeof(data[0]);i++)
                        {

                            if(strcmp(strlwr(string2),strlwr(data[i][0]))==0){

                                state=i;
                                search=1;
                                printf("\n--------------found in data!----------");
                                printf("\nIn data what I've found : %s",strlwr(data[i][0]));
                                break;

                            }

                            else{
                                search=0;
                            }
                        }
                            if(search==0){
                                printf("\n--------------Not found in data!----------");
                                state=-1;


                            }
                        if((strlen(string2))==0){
                            state=-1;
                        }
                       if (count==2){
                        printf("\ncount is 2!");
                        goto condition;
                       }
                       printf("\nInput: %s",text);
                       if (run==1){

                            bottop=140;
                            texttop=30;
                            printf("\ndestroyed!");

                            if(strlen(text)>0){
                                printf("\nchat(run) is called!");
                                chat(process,0,state);
                                donotrun=1;
                            }

                           }

                       if(strlen(text)>0 && donotrun==0 && count==2){
                           condition:
                           printf("\nChanged the tops");
                           bottop+=210;
                           texttop+=220;
                           printf("\nchat is called!");
                           chat(process,1,state);



                       }
                       else if(strlen(text)>0 && donotrun==0 && count==1){
                            printf("\nchat is called!");
                           chat(process,1,state);
                       }
                       else{
                        printf("\nNot matched! so chat is not called!");
                       }
                       bottom:


                       break;
                 case 2:
                        MessageBox(hwnd,"Spidey is trained to answer \"what\" questions in basic C programming\n\nYou just have to type your keywords within double quotes(\" \") \n\n\"The important thing is never to stop questioning\"\n\t\t\t\t-Albert Einstein\nHappy learning!","Tips",MB_OK);
                        break;
                 case 3:
                        MessageBox(hwnd,"         SPIDEY CHAT BOT\n\nSpidey is developed by:\n\nJefi Ryan\nAshwala Ravi Teja\nHarsha\nEmmanuel Arthur George\n\n\nVersion: 1.0.0\n\n---Spidey is free to use---","About",MB_OK);
                        break;



            }
            break;






        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

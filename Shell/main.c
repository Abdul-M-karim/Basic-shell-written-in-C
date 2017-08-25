//
//  main.c
//  Shell
//
//  Created by abdul karim on 8/23/17.
//  Copyright © 2017 Abdul Karim. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/*
    This function will take the input and parse through the commands or arguments... 
    conversion takes place with strok
    and we loop through until the given arguements are done.
 */

char** parser( char* S)
{
    char** arguments = malloc( 256);
    int i = 0;
    arguments[i] = strtok(S, " ");
    while( arguments[i])
    {
        i++;
        arguments[i] = strtok(NULL, " ");
    }
    return arguments;
}
/*
    the execution of the fork and exevp and wait take place here in this function 
    fork() clearly creates a new process, and we basically check to see if its succesful 
    based on a serious of switch casesif the pid is -1 ( if fork returns -1 ) clearly the fork failed
    if it isnt -1, you run execvp with the argument and the arguemnts list. 
    otherwise you wait for the exit status.
 */

void exe( char* argument_list)
{
    int pid;
    int exitStatus;
    char** arguments;
    arguments = parser(argument_list);
    pid = fork();                                   // creating a new ( child) process with a unique (pid)
    
    switch( pid )
    {
        case -1:                                    // if pid is -1 ( fork return -1 ) then the fork failed
            perror( "fork failed!!" );
            exit(1);
        case 0:                                     // if it returns 0 then the Execvp failed.
            execvp( arguments[0], arguments );
            
            perror( "execvp failed!!" );
            exit(1);
        default:                                    // run child process and wait fo exitstatus... 
            while( wait( &exitStatus ) != pid );
    }
}
/*
    checks to see if the user is trying to exit the program if a argumwnt as an input is "exit"
    this would cause the program to terminate. 
 
 */

void exitSituation(char* in)
{
    printf(" Tish >>");
    fgets( in, 255, stdin );                 // get command
    
    in[strlen(in)-1] = '\0';              // overwrite
    
    if ( strcmp( in, "exit" ) == 0 )         // shell command
        exit(0);
    
}
/*
    this runs the entire Shell in a infite while loop.
    checks to see if we need to exit, 
    and it checks to see if we have a command for our shell.
 */

int main(int argc, const char * argv[])
{
    char argument_buffer[255];
    signal(SIGINT, SIG_IGN);
    while(&free)
    {
        exitSituation(argument_buffer);
        exe(argument_buffer);
    }
    return 0;
}



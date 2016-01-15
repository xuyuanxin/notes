
A function can be defined as follows:
function fname()
{
  statements;
}
Or alternately,
fname()
{
  statements;
}
A function can be invoked just by using its name:
$ fname ; # executes function
Arguments can be passed to functions and can be accessed by our script:
fname arg1 arg2 ; # passing args


$1 is the first argument
$2 is the second argument
$n is the nth argument
"$@" expands as "$1" "$2" "$3" and so on
"$*" expands as "$1c$2c$3", where c is the first character of IFS


--> Exporting functions
 A function can be exported like environment variables using export such that the sc-
 ope of the function can be extended to subprocesses, as follows:
 export -f fname
 
--> Reading command return value (status)
 We can get the return value of a command or function as follows:
 cmd;
 echo $?;
 $? will give the return value of the command cmd.
 The return value is called exit status. It can be used to analyze whether a  command
 completed its execution successfully or unsuccessfully. If the command exits succes-
 sfully, the exit status will be zero, else it will be non-zero. We can check whether 
 a command terminated successfully or not as follows:
 #!/bin/bash
 #Filename: success_test.sh
 CMD="command" #Substitute with command for which you need to test exit
 status
 $CMD
 if [ $? ¨Ceq 0 ];
 then
 echo "$CMD executed successfully"
 else
 echo "$CMD terminated unsuccessfully"
 fi

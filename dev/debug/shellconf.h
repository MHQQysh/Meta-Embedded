#ifndef SHELLCONF_H
#define SHELLCONF_H

/*===========================================================================*/
/* ChibiOS Shell related settings.                                           */
/*===========================================================================*/

// Disable shell test commands, so we don't rely on ChibiOS's test codes
#define SHELL_CMD_TEST_ENABLED              FALSE

// Disable exiting the shell
#define SHELL_CMD_EXIT_ENABLED              FALSE

// Disable history in the shell
#define SHELL_USE_HISTORY                   TRUE

// Enable completion
#define SHELL_USE_COMPLETION                FALSE

// Clear shell prompt string
#define SHELL_PROMPT_STR                    ""

// Enable float in chprintf
#define CHPRINTF_USE_FLOAT                  TRUE

// Enlarge the maximum number of arguments
#define SHELL_MAX_ARGUMENTS                 10


#if !defined(SHELL_NO_ECHO_MODE)
#define SHELL_NO_ECHO_MODE                  FALSE
#endif

#endif